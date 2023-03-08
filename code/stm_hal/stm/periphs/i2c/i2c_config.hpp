/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/i2c/i2c_def.hpp"

namespace stm::periphs::i2c {

/**
 * @brief User configuration of a I2C peripheral.
 * The user can choose a globally defined I2cDef and baudrate.
 * The object can be used as input to I2c::init()
 * @note This config struct has to be constructed as constexpr
 */
struct I2cConfig { // NOLINT(cppcoreguidelines-pro-type-member-init), no sensible default possible and I2cConfig can't be constructed anyway without the i2c being explicitely given
    I2cDef i2c;
    uint32_t baudrate {};
    gpio::Pin sda {};
    gpio::Pin scl {};
};
} // namespace stm::periphs::i2c
