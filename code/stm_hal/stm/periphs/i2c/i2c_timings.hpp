/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstdint>

namespace stm::periphs::i2c {

template <uint32_t I2C_INPUT_CLOCK, uint32_t I2C_SPEED>
constexpr uint32_t I2C_TIMING_REG_VALUE = [] {                          // NOLINT(bugprone-dynamic-static-initializers) warning makes no sense here
    constexpr bool ALWAYS_FALSE = (I2C_SPEED == 0) && (I2C_SPEED != 0); // the condition in the static_assert needs to depend on the template args
    static_assert(ALWAYS_FALSE, "Desired I2c speed is not supported. Use the Stm32CubeIde to generate the I2C timing register value for your desired speed and add it to the i2c_timings.hpp");
};

template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<80'000'000, 400'000> = 0x0070'2991UL;
template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<80'000'000, 100'000> = 0x1030'89FFUL;
template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<80'000'000, 10'000> = 0xF000'F3FEUL;

template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<16'000'000, 400'000> = 0x0010'061AUL;
template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<16'000'000, 100'000> = 0x0010'0A8EUL;
template <>
constexpr uint32_t I2C_TIMING_REG_VALUE<16'000'000, 10'000> = 0x4000'3EFFUL;
} // namespace stm::periphs::i2c
