/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdint>
#include <cstddef>
#include <atomic>
#include <functional>

namespace fmcff {

/**
 * @brief struct representing a stack frame that automatically gets pushed by the MCU on exception entry. Default values are there to initialize a stack cleanly.
 *
 * See Figure B1-3 in the ARMv7m architecture reference manual
 */
struct alignas(8) BasicStackFrame {
    uint32_t r0 = 0;
    uint32_t r1 = 0;
    uint32_t r2 = 0;
    uint32_t r3 = 0;
    uint32_t r12 = 0;
    uint32_t lr = 0xffff'ffff;
    void* return_address = nullptr;
    uint32_t xpsr = 0;
};

static constexpr size_t PROCESS_STACK_SIZE = 8192;

class ProcessContext {
public:
    ProcessContext();
    void switch_to_context(const std::function<void()>& function);

    static void return_to_main();
private:
    struct alignas(std::max_align_t) Stack {
        std::array<uint8_t, PROCESS_STACK_SIZE-sizeof(BasicStackFrame)> rest_of_the_stack {};
        BasicStackFrame initial_stack {};
    } stack_;

    static void process_wrapper(const std::function<void()> function);
};

} // namespace fmcff
