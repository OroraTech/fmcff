/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/can/periphs.hpp"

namespace stm::periphs::gpio {

enum class CanPinFunction {
    RX,
    TX,
};

template <Pin PIN, AlternateFunction AF>
// NOLINTNEXTLINE(bugprone-dynamic-static-initializers) warning makes no sense here
constexpr PinConfig CAN_PIN_CONF {
    .pin = PIN,
    .mode = Mode::ALTERNATE_FUNCTION,
    .alternate_function = AF,
    .output_type = OutputType::PUSHPULL,
    .speed = OutputSpeed::MEDIUM,
    .pupd = PullUpPullDown::PULLUP,
};

template <can::CanDef, Pin PIN, CanPinFunction>
constexpr PinConfig CAN_PIN_CONFIG = [] { // NOLINT(bugprone-dynamic-static-initializers) warning make no sense here
    static_assert(PIN == NULL_PIN, "CAN pin is neither NULL_PIN nor valid for it's function.");
    return CAN_PIN_CONF<NULL_PIN, AF::AF0>;
}();

template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PA11, CanPinFunction::RX> = CAN_PIN_CONF<PA11, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PB8, CanPinFunction::RX> = CAN_PIN_CONF<PB8, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PD0, CanPinFunction::RX> = CAN_PIN_CONF<PD0, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PI9, CanPinFunction::RX> = CAN_PIN_CONF<PI9, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PA12, CanPinFunction::TX> = CAN_PIN_CONF<PA12, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PB9, CanPinFunction::TX> = CAN_PIN_CONF<PB9, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PD1, CanPinFunction::TX> = CAN_PIN_CONF<PD1, AF::AF9>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN1DEF, PH13, CanPinFunction::TX> = CAN_PIN_CONF<PH13, AF::AF9>;

template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN2DEF, PB12, CanPinFunction::RX> = CAN_PIN_CONF<PB12, AF::AF10>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN2DEF, PB5, CanPinFunction::RX> = CAN_PIN_CONF<PB5, AF::AF3>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN2DEF, PB13, CanPinFunction::TX> = CAN_PIN_CONF<PB13, AF::AF10>;
template <>
constexpr PinConfig CAN_PIN_CONFIG<can::CAN2DEF, PB6, CanPinFunction::TX> = CAN_PIN_CONF<PB6, AF::AF8>;
} // namespace stm::periphs::gpio
