/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/rcc/clock_manager.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/periphs/uart/uart_def.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::uart {

constexpr uart::UartDef USART1DEF {
    .rcc_periph = rcc::USART1_PERIPH,
    .periph = __PERIPHERAL_USART1__,
    .irq_n = 37,
    .input_clock = rcc::PCLK::FREQ2,
};

constexpr uart::UartDef USART2DEF {
    .rcc_periph = rcc::USART2_PERIPH,
    .periph = __PERIPHERAL_USART2__,
    .irq_n = 38,
    .input_clock = rcc::PCLK::FREQ1,
};

constexpr uart::UartDef USART3DEF {
    .rcc_periph = rcc::USART3_PERIPH,
    .periph = __PERIPHERAL_USART3__,
    .irq_n = 39,
    .input_clock = rcc::PCLK::FREQ1,
};

constexpr uart::UartDef UART4DEF {
    .rcc_periph = rcc::UART4_PERIPH,
    .periph = __PERIPHERAL_UART4__,
    .irq_n = 52,
    .input_clock = rcc::PCLK::FREQ1,
};

constexpr uart::UartDef UART5DEF {
    .rcc_periph = rcc::UART5_PERIPH,
    .periph = __PERIPHERAL_UART5__,
    .irq_n = 53,
    .input_clock = rcc::PCLK::FREQ1,
};

constexpr uart::UartDef LPUART1DEF {
    .rcc_periph = rcc::LPUART1_PERIPH,
    .periph = __PERIPHERAL_LPUART1__,
    .irq_n = 70,
    .input_clock = rcc::PCLK::FREQ1,
};

} // namespace stm::periphs::uart
