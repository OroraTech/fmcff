/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/regs/i2c_registers.hpp"

namespace stm::periphs::i2c {
/**
 * @brief Definition of a single I2C peripheral.
 * Should be created once for each I2C peripheral on the chip
 * and placed globally as a constexpr object.
 */
struct I2cDef {
    rcc::RccPeriph rcc_periph;
    /**
     * @brief Should be defined in namespace peripheral_symbols
     */
    regs::i2c::I2CStruct& periph;

    /**
     * @brief See STM32 reference manual
     */
    uint8_t irq_n;

    /**
     * @brief Use PCLK::freq1 for all but USART1. Use PCLK::freq2 for USART2
     */
    uint32_t input_clock;
};
} // namespace stm::periphs::i2c
