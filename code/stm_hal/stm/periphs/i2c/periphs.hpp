/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/i2c/i2c_def.hpp"
#include "stm/periphs/rcc/clock_manager.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::i2c {

constexpr i2c::I2cDef I2C1DEF {
    .rcc_periph = rcc::I2C1_PERIPH,
    .periph = __PERIPHERAL_I2C1__,
    .irq_n = 31,
    .input_clock = rcc::PCLK::FREQ1
};

constexpr i2c::I2cDef I2C2DEF {
    .rcc_periph = rcc::I2C2_PERIPH,
    .periph = __PERIPHERAL_I2C2__,
    .irq_n = 33,
    .input_clock = rcc::PCLK::FREQ1
};

constexpr i2c::I2cDef I2C3DEF {
    .rcc_periph = rcc::I2C3_PERIPH,
    .periph = __PERIPHERAL_I2C3__,
    .irq_n = 72,
    .input_clock = rcc::PCLK::FREQ1
};

constexpr i2c::I2cDef I2C4DEF {
    .rcc_periph = rcc::I2C4_PERIPH,
    .periph = __PERIPHERAL_I2C4__,
    .irq_n = 83,
    .input_clock = rcc::PCLK::FREQ1
};

} // namespace stm::periphs::i2c
