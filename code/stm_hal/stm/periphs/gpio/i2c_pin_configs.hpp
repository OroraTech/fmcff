/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/i2c/periphs.hpp"

namespace stm::periphs::gpio {

enum class I2cPinFunction {
    SDA,
    SCL,
    SMBA
};

template <Pin PIN, AlternateFunction AF>
// NOLINTNEXTLINE(bugprone-dynamic-static-initializers) warning makes no sense here
constexpr PinConfig I2C_PIN_CONF {
    .pin = PIN,
    .mode = Mode::ALTERNATE_FUNCTION,
    .alternate_function = AF,
    .output_type = OutputType::OPENDRAIN,
    .speed = OutputSpeed::VERY_HIGH,
    .pupd = PullUpPullDown::NONE,
};

template <i2c::I2cDef, Pin PIN, I2cPinFunction>
constexpr PinConfig I2C_PIN_CONFIG = [] { // NOLINT(bugprone-dynamic-static-initializers) warning make no sense here
    static_assert(PIN == NULL_PIN, "I2c pin is neither NULL_PIN nor valid for it's function.");
    return I2C_PIN_CONF<NULL_PIN, AF::AF0>;
}();

template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PB6, I2cPinFunction::SCL> = I2C_PIN_CONF<PB6, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PB8, I2cPinFunction::SCL> = I2C_PIN_CONF<PB8, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PG14, I2cPinFunction::SCL> = I2C_PIN_CONF<PG14, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PB7, I2cPinFunction::SDA> = I2C_PIN_CONF<PB7, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PB9, I2cPinFunction::SDA> = I2C_PIN_CONF<PB9, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PG13, I2cPinFunction::SDA> = I2C_PIN_CONF<PG13, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PA1, I2cPinFunction::SMBA> = I2C_PIN_CONF<PA1, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PA14, I2cPinFunction::SMBA> = I2C_PIN_CONF<PA14, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PB5, I2cPinFunction::SMBA> = I2C_PIN_CONF<PB5, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C1DEF, PG15, I2cPinFunction::SMBA> = I2C_PIN_CONF<PG15, AF::AF4>;

template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PB10, I2cPinFunction::SCL> = I2C_PIN_CONF<PB10, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PB13, I2cPinFunction::SCL> = I2C_PIN_CONF<PB13, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PF1, I2cPinFunction::SCL> = I2C_PIN_CONF<PF1, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PH4, I2cPinFunction::SCL> = I2C_PIN_CONF<PH4, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PB11, I2cPinFunction::SDA> = I2C_PIN_CONF<PB11, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PB14, I2cPinFunction::SDA> = I2C_PIN_CONF<PB14, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PF0, I2cPinFunction::SDA> = I2C_PIN_CONF<PF0, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PH5, I2cPinFunction::SDA> = I2C_PIN_CONF<PH5, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PB12, I2cPinFunction::SMBA> = I2C_PIN_CONF<PB12, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PF2, I2cPinFunction::SMBA> = I2C_PIN_CONF<PF2, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C2DEF, PH6, I2cPinFunction::SMBA> = I2C_PIN_CONF<PH6, AF::AF4>;

template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PA7, I2cPinFunction::SCL> = I2C_PIN_CONF<PA7, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PC0, I2cPinFunction::SCL> = I2C_PIN_CONF<PC0, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PG7, I2cPinFunction::SCL> = I2C_PIN_CONF<PG7, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PH7, I2cPinFunction::SCL> = I2C_PIN_CONF<PH7, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PB4, I2cPinFunction::SDA> = I2C_PIN_CONF<PB4, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PC1, I2cPinFunction::SDA> = I2C_PIN_CONF<PC1, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PC9, I2cPinFunction::SDA> = I2C_PIN_CONF<PC9, AF::AF6>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PG8, I2cPinFunction::SDA> = I2C_PIN_CONF<PG8, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PH8, I2cPinFunction::SDA> = I2C_PIN_CONF<PH8, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PB2, I2cPinFunction::SMBA> = I2C_PIN_CONF<PB2, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PG6, I2cPinFunction::SMBA> = I2C_PIN_CONF<PG6, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C3DEF, PH9, I2cPinFunction::SMBA> = I2C_PIN_CONF<PH9, AF::AF4>;

template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PB10, I2cPinFunction::SCL> = I2C_PIN_CONF<PB10, AF::AF3>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PB6, I2cPinFunction::SCL> = I2C_PIN_CONF<PB6, AF::AF5>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PC0, I2cPinFunction::SCL> = I2C_PIN_CONF<PC0, AF::AF2>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PD12, I2cPinFunction::SCL> = I2C_PIN_CONF<PD12, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PF14, I2cPinFunction::SCL> = I2C_PIN_CONF<PF14, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PB11, I2cPinFunction::SDA> = I2C_PIN_CONF<PB11, AF::AF3>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PB7, I2cPinFunction::SDA> = I2C_PIN_CONF<PB7, AF::AF5>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PC1, I2cPinFunction::SDA> = I2C_PIN_CONF<PC1, AF::AF2>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PD13, I2cPinFunction::SDA> = I2C_PIN_CONF<PD13, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PF15, I2cPinFunction::SDA> = I2C_PIN_CONF<PF15, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PA14, I2cPinFunction::SMBA> = I2C_PIN_CONF<PA14, AF::AF5>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PD11, I2cPinFunction::SMBA> = I2C_PIN_CONF<PD11, AF::AF4>;
template <>
constexpr PinConfig I2C_PIN_CONFIG<i2c::I2C4DEF, PF13, I2cPinFunction::SMBA> = I2C_PIN_CONF<PF13, AF::AF4>;

} // namespace stm::periphs::gpio
