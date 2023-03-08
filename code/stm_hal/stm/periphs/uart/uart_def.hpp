/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/regs/uart_registers.hpp"

namespace stm::periphs::uart {
/**
 * @brief Definition of a single UART peripheral.
 * Should be created once for each UART peripheral on the chip
 * and placed globally as a constexpr object.
 */
struct UartDef {
    rcc::RccPeriph rcc_periph;
    /**
     * @brief Should be defined in namespace peripheral_symbols
     */
    regs::uart::UARTStruct& periph;

    /**
     * @brief See STM32 reference manual
     */
    uint8_t irq_n;

    /**
     * @brief Use PCLK::freq1 for all but USART1. Use PCLK::freq2 for USART2
     */
    uint32_t input_clock;
};
} // namespace stm::periphs::uart
