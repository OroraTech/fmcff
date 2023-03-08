/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "context_switch.hpp"
#include "stm/regs/peripherals.hpp"
#include "stm/startup/irq_handlers.hpp"
#include <bit>

namespace fmcff {

void invoke_pendsv(){
    using namespace stm::regs::scb::ICSR;
    __PERIPHERAL_SCB__.ICSR.write(PENDSVSET(1));
}

ProcessContext::ProcessContext(){
    constexpr uint8_t PENDSV_INDEX = 14;
    constexpr uint8_t SVC_INDEX = 11;
    constexpr uint8_t SHPR_REGISTER_OFFSET = 4;
    constexpr uint8_t MINIMUM_PRIORITY = 0xF0;
    __PERIPHERAL_SCB__.SHPR[PENDSV_INDEX-SHPR_REGISTER_OFFSET].write(MINIMUM_PRIORITY);
    __PERIPHERAL_SCB__.SHPR[SVC_INDEX-SHPR_REGISTER_OFFSET].write(MINIMUM_PRIORITY);
}

void ProcessContext::process_wrapper(const std::function<void()> function){
    function();
    return_to_main();
}

void ProcessContext::return_to_main(){
    invoke_pendsv();
}

void ProcessContext::switch_to_context(const std::function<void()>& function){
    stack_.initial_stack = BasicStackFrame {
        .r0 = std::bit_cast<uint32_t>(&function),
        .return_address = (void*)&process_wrapper,
        .xpsr = 1<<24 // set only the T bit(thumb execution) of the xPSR. See ARMv7-M Architecture reference manual B1.4.2
    };

    register void* stack_ptr asm ("r0") = &(stack_.initial_stack);
    asm volatile("svc #0" : : "r"(stack_ptr) : "memory");
}

extern "C" {
/**
 * @brief responsible for switching from the main function to micropython. r0 should contain the micropython stack pointer when calling the svc instruction.
 */
[[gnu::naked, gnu::used]] void SVC_Handler(){
    asm volatile(
        "tst lr, #8             \n" // check if this returns to another exception. IRQ priorities are wrongly configured in this case and execution is aborted.
        "it eq                  \n" // check if bit was 0(it should be 1)
        "udfeq #0               \n" // abort execution
        "tst lr, #4             \n" // check if process stack was used(bit should be 0, if it is 1 that means micropython is trying to switch to itself)
        "it ne                  \n" // check if bit was 1(it should be 0)
        "udfne #1               \n" // abort execution
        "ldr r0, [sp,#0]        \n" // load value of r0 from main stack(this is the parameter that was passed to the syscall, which we are using as the mpy stack address)
        
        "tst lr, #0x10                  \n" // check if FPU context has been pushed to the stack
        "it eq                          \n"
        "vstmdbeq sp!, {s16-s31}        \n" // save FPU registers
        "stmdb sp!, {r4-r11, lr}        \n" // save core registers

        "mov lr, #0xfffffffd            \n" // value to return to thread mode with the process stack and a basic stack frame
        "msr psp, r0                    \n" // set the process stack pointer to the mpy stack
        "bx lr                          \n"
    );
}

/**
 * @brief responsible for switching back to the main context. PENDSV is called from either the micropython context or another interrupt
 */
[[gnu::naked, gnu::used]] void PendSV_Handler(){
    asm volatile(
        "tst lr, #8             \n" // check if this returns to another exception. IRQ priorities are wrongly configured in this case and execution is aborted.
        "it eq                  \n" // check if bit was 0(it should be 1)
        "udfeq #0               \n" // abort execution
        "tst lr, #4             \n" // check if process stack was used
        "beq 1f                 \n" // go directly to return if bit was 0(main stack was used, meaning that execution is still in the main function and no context was pushed)
        "ldmia sp!, {r4-r11,lr} \n" // pop registers from main stack
        "tst lr, #0x10          \n" // check if floating point registers have been pushed to the main stack
        "it eq                  \n"
        "vldmiaeq sp!, {s16-s31} \n"
        "1: bx lr               \n"
    );
}

} // extern "C"

} // namespace fmcff
