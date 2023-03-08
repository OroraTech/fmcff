/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "interrupt_timer.hpp"
#include "stm/cortex_m/irq.hpp"
#include "stm/cortex_m/nvic.hpp"
#include "stm/periphs/rcc/clock_manager.hpp"
#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/tim_registers.hpp"
#include "stm/startup/irq_handlers.hpp"

namespace stm::support {
InterruptTimer::InterruptTimer(std::function<void()> on_timer, std::chrono::milliseconds period) {
    using namespace stm::regs::tim::CR1;
    // enable the timer peripheral of the stm32
    stm::periphs::rcc::enable_rcc_periph(stm::periphs::rcc::TIM7_PERIPH);
    // enable the timer interrupt in the interrupt controller
    stm::nvic::Nvic::enable_irq(INTERRUPT_NR);
    stm::nvic::Nvic::set_irq_priority(INTERRUPT_NR, stm::nvic::Nvic::LOWEST_PRIORITY);
    // configure the timer to to produce an interrupt on tick
    __PERIPHERAL_TIM7__.DIER.set_bits(1);

    constexpr uint64_t CLOCK_FREQ_1S = 0xFFFF;
    // ARR defines at which counter value the interrupt is triggered:
    __PERIPHERAL_TIM7__.ARR.write(CLOCK_FREQ_1S);
    // the interrupt is generated once the clock counter reaches CLOCK_FREQ_1S, therefore:
    uint64_t period_ms = period.count();
    constexpr uint64_t MS_PER_S = 1000;
    uint64_t clock_freq = (CLOCK_FREQ_1S * MS_PER_S) / period_ms;
    // set the clock prescaler. The timer freq is input_freq/prescaler -> prescaler = input_freq / timer_freq
    __PERIPHERAL_TIM7__.PSC.write((uint32_t)((stm::periphs::rcc::PCLK::FREQ1 / clock_freq) - 1));

    InterruptTimer::on_timer = std::move(on_timer);

    // enable the timer itself
    __PERIPHERAL_TIM7__.CR1.write(CEN(1));
}

std::function<void()> InterruptTimer::on_timer = []() {}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

extern "C" void TIM7_IRQHandler() {
    InterruptTimer::on_timer();
    __PERIPHERAL_TIM7__.SR.write(0);
    __PERIPHERAL_NVIC__.ICPR[InterruptTimer::INTERRUPT_NR / 32].write(1UL << (InterruptTimer::INTERRUPT_NR % 32));
}
} // namespace stm::support
