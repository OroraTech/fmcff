/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/cortex_m/cm4_fpu.hpp"
#include "stm/periphs/dbgmcu/dbgmcu.hpp"
#include "stm/periphs/flash/flash_manager.hpp"
#include "stm/periphs/uart/uart.hpp"
#include "stm/startup/global_timer.hpp"
#include "stm/startup/irq_table.hpp"
#include "stm/support/timer.hpp"
#include <cstddef>
#include <cstdint>
#include <span>

namespace stm {
extern void init_stdout();
}

using InitFn = void* (*)();
extern "C" const InitFn __init_array_start__[]; // NOLINT(bugprone-reserved-identifier, readability-identifier-naming)
extern "C" const InitFn __init_array_end__[];   // NOLINT(bugprone-reserved-identifier, readability-identifier-naming)

extern "C" const volatile uint32_t __data_flash_start__[]; // NOLINT(bugprone-reserved-identifier, readability-identifier-naming)
extern "C" volatile uint32_t __data_start__[];             // NOLINT(bugprone-reserved-identifier, cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
extern "C" volatile uint32_t __data_end__[];               // NOLINT(bugprone-reserved-identifier, cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
extern "C" volatile uint32_t __bss_start__[];              // NOLINT(bugprone-reserved-identifier, cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)
extern "C" volatile uint32_t __bss_end__[];                // NOLINT(bugprone-reserved-identifier, cppcoreguidelines-avoid-non-const-global-variables, readability-identifier-naming)

namespace stm::support {
volatile uint64_t g_timer_overflow_counter; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
}

extern int main();
extern "C" [[noreturn, gnu::used, gnu::naked]] void _start() {
    asm volatile("ldr sp, =__stack_end__ \n"
                 "b start_cpp");
}

extern "C" [[noreturn, gnu::used]] void start_cpp() {
    using namespace std;
    __PERIPHERAL_SCB__.VTOR.write(reinterpret_cast<uint32_t>(&stm::IRQ_TABLE)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    const size_t data_size { (uint32_t(__data_end__) - uint32_t(__data_start__)) / sizeof(uint32_t) };
    span data_flash { __data_flash_start__, data_size };
    copy(data_flash.begin(), data_flash.end(), __data_start__);
    for (auto& word : span { __bss_start__, __bss_end__ }) {
        word = 0x0;
    }
    stm::dbgmcu::enable_debugging();
    stm::fpu::setup_fpu();
    stm::periphs::rcc::ClockManager::init_clocks();
    stm::periphs::flash::FlashManager::init_cache();
    stm::periphs::rcc::VCORERangeManager::init();
    stm::init_stdout();

    stm::support::g_timer_overflow_counter = 0;
    stm::support::Timer timer {};

    for (const InitFn& fn : span { __init_array_start__, __init_array_end__ }) {
        fn();
    }
    main();
    while (true) {}
}
