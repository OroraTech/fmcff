/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/support/timer.hpp"
#include "stm/cortex_m/irq.hpp"
#include "stm/cortex_m/nvic.hpp"
#include "stm/periphs/rcc/clock_manager.hpp"
#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/tim_registers.hpp"
#include "stm/startup/global_timer.hpp"
#include "stm/startup/irq_handlers.hpp"

#include <cstdio>

namespace stm::support {

constexpr uint32_t RELOAD_VALUE = 0x1'0000;
constexpr uint16_t PRESCALER = 0x8;
constexpr uint16_t ARR_REG = RELOAD_VALUE - 1;
constexpr uint16_t PSC_REG = PRESCALER - 1;

Timer::Timer() {
    using namespace std::chrono_literals;

    using namespace stm::regs::tim::CR1;
    // enable the timer peripheral of the stm32
    stm::periphs::rcc::enable_rcc_periph(stm::periphs::rcc::TIM6_PERIPH);
    // enable the timer interrupt in the interrupt controller
    stm::nvic::Nvic::enable_irq(INTERRUPT_NR);
    stm::nvic::Nvic::set_irq_priority(INTERRUPT_NR, stm::nvic::Nvic::HIGHEST_PRIORITY);
    // configure the timer to to produce an interrupt on tick
    __PERIPHERAL_TIM6__.DIER.set_bits(1);
    __PERIPHERAL_TIM6__.ARR.write(ARR_REG);
    __PERIPHERAL_TIM6__.PSC.write(PSC_REG);
    // reset counter to 0
    __PERIPHERAL_TIM6__.CNT.write(0x0);
    // enable the timer itself
    __PERIPHERAL_TIM6__.CR1.write(CEN(1));
}

[[nodiscard]] std::chrono::nanoseconds Timer::current_time() {
    constexpr uint64_t NSEC_PER_SEC = 1'000'000'000;
    // nanosecondsPerCycle = (PSC + 1) * nanoseconds per second / TIMclock
    constexpr uint64_t NSEC_PER_CYCLE = PRESCALER * NSEC_PER_SEC / stm::periphs::rcc::PCLK::FREQ1;

    // catching race conditions
    uint64_t timer_overflow_counter = g_timer_overflow_counter;
    auto timer_cnt = (uint16_t)__PERIPHERAL_TIM6__.CNT.read();

    while (timer_overflow_counter != g_timer_overflow_counter) {
        timer_overflow_counter = g_timer_overflow_counter;
        timer_cnt = (uint16_t)__PERIPHERAL_TIM6__.CNT.read();
    }

    // passed cycles = current register count + overflow value * times it has overflowed
    uint64_t passed_cycles = timer_cnt + RELOAD_VALUE * timer_overflow_counter;
    uint64_t passed_nsec = passed_cycles * NSEC_PER_CYCLE;
    return std::chrono::nanoseconds { passed_nsec };
}

[[nodiscard]] uint16_t Timer::current_timer_count() {
    // returns the passed time since last overflow in clock cycles
    return (uint16_t)__PERIPHERAL_TIM6__.CNT.read();
}

extern "C" void TIM6_DAC_IRQHandler() {
    // this has triggered because the TIM6 counter overflowed
    g_timer_overflow_counter = g_timer_overflow_counter + 1;
    // Status register, no update occured (anymore)
    __PERIPHERAL_TIM6__.SR.write(0);
}
} // namespace stm::support
