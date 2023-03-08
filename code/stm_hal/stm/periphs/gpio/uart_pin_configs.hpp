/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/uart/periphs.hpp"

namespace stm::periphs::gpio {

enum class UartPinFunction {
    RX,
    TX,
    CK,
    CTS,
    RTS_DE
};

template <Pin PIN, AlternateFunction AF>
// NOLINTNEXTLINE(bugprone-dynamic-static-initializers) warning makes no sense here
constexpr PinConfig UART_PIN_CONF {
    .pin = PIN,
    .mode = Mode::ALTERNATE_FUNCTION,
    .alternate_function = AF,
    .output_type = OutputType::PUSHPULL,
    .speed = OutputSpeed::VERY_HIGH,
    .pupd = PullUpPullDown::NONE,
};

template <uart::UartDef, Pin PIN, UartPinFunction>
constexpr PinConfig UART_PIN_CONFIG = [] { // NOLINT(bugprone-dynamic-static-initializers) warning make no sense here
    static_assert(PIN == NULL_PIN, "Uart pin is neither NULL_PIN nor valid for it's function.");
    return UART_PIN_CONF<NULL_PIN, AF::AF0>;
}();

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PA8, UartPinFunction::CK> = UART_PIN_CONF<PA8, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PB5, UartPinFunction::CK> = UART_PIN_CONF<PB5, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PG13, UartPinFunction::CK> = UART_PIN_CONF<PG13, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PA11, UartPinFunction::CTS> = UART_PIN_CONF<PA11, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PB4, UartPinFunction::CTS> = UART_PIN_CONF<PB4, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PG11, UartPinFunction::CTS> = UART_PIN_CONF<PG11, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PA12, UartPinFunction::RTS_DE> = UART_PIN_CONF<PA12, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PB3, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB3, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PG12, UartPinFunction::RTS_DE> = UART_PIN_CONF<PG12, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PA10, UartPinFunction::RX> = UART_PIN_CONF<PA10, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PB7, UartPinFunction::RX> = UART_PIN_CONF<PB7, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PG10, UartPinFunction::RX> = UART_PIN_CONF<PG10, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PA9, UartPinFunction::TX> = UART_PIN_CONF<PA9, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PB6, UartPinFunction::TX> = UART_PIN_CONF<PB6, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART1DEF, PG9, UartPinFunction::TX> = UART_PIN_CONF<PG9, AF::AF7>;

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA4, UartPinFunction::CK> = UART_PIN_CONF<PA4, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PD7, UartPinFunction::CK> = UART_PIN_CONF<PD7, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA0, UartPinFunction::CTS> = UART_PIN_CONF<PA0, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PD3, UartPinFunction::CTS> = UART_PIN_CONF<PD3, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA1, UartPinFunction::RTS_DE> = UART_PIN_CONF<PA1, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PD4, UartPinFunction::RTS_DE> = UART_PIN_CONF<PD4, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA15, UartPinFunction::RX> = UART_PIN_CONF<PA15, AF::AF3>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA3, UartPinFunction::RX> = UART_PIN_CONF<PA3, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PD6, UartPinFunction::RX> = UART_PIN_CONF<PD6, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PA2, UartPinFunction::TX> = UART_PIN_CONF<PA2, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART2DEF, PD5, UartPinFunction::TX> = UART_PIN_CONF<PD5, AF::AF7>;

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB0, UartPinFunction::CK> = UART_PIN_CONF<PB0, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB12, UartPinFunction::CK> = UART_PIN_CONF<PB12, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PC12, UartPinFunction::CK> = UART_PIN_CONF<PC12, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD10, UartPinFunction::CK> = UART_PIN_CONF<PD10, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PA6, UartPinFunction::CTS> = UART_PIN_CONF<PA6, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB13, UartPinFunction::CTS> = UART_PIN_CONF<PB13, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD11, UartPinFunction::CTS> = UART_PIN_CONF<PD11, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PA15, UartPinFunction::RTS_DE> = UART_PIN_CONF<PA15, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB1, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB1, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB14, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB14, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD12, UartPinFunction::RTS_DE> = UART_PIN_CONF<PD12, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD2, UartPinFunction::RTS_DE> = UART_PIN_CONF<PD2, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB11, UartPinFunction::RX> = UART_PIN_CONF<PB11, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PC11, UartPinFunction::RX> = UART_PIN_CONF<PC11, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PC5, UartPinFunction::RX> = UART_PIN_CONF<PC5, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD9, UartPinFunction::RX> = UART_PIN_CONF<PD9, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PB10, UartPinFunction::TX> = UART_PIN_CONF<PB10, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PC10, UartPinFunction::TX> = UART_PIN_CONF<PC10, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PC4, UartPinFunction::TX> = UART_PIN_CONF<PC4, AF::AF7>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::USART3DEF, PD8, UartPinFunction::TX> = UART_PIN_CONF<PD8, AF::AF7>;

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PB7, UartPinFunction::CTS> = UART_PIN_CONF<PB7, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PA15, UartPinFunction::RTS_DE> = UART_PIN_CONF<PA15, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PA1, UartPinFunction::RX> = UART_PIN_CONF<PA1, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PC11, UartPinFunction::RX> = UART_PIN_CONF<PC11, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PA0, UartPinFunction::TX> = UART_PIN_CONF<PA0, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART4DEF, PC10, UartPinFunction::TX> = UART_PIN_CONF<PC10, AF::AF8>;

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART5DEF, PB5, UartPinFunction::CTS> = UART_PIN_CONF<PB5, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART5DEF, PB4, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB4, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART5DEF, PD2, UartPinFunction::RX> = UART_PIN_CONF<PD2, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::UART5DEF, PC12, UartPinFunction::TX> = UART_PIN_CONF<PC12, AF::AF8>;

template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PA6, UartPinFunction::CTS> = UART_PIN_CONF<PA6, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PB13, UartPinFunction::CTS> = UART_PIN_CONF<PB13, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PG5, UartPinFunction::CTS> = UART_PIN_CONF<PG5, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PB1, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB1, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PB12, UartPinFunction::RTS_DE> = UART_PIN_CONF<PB12, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PG6, UartPinFunction::RTS_DE> = UART_PIN_CONF<PG6, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PA3, UartPinFunction::RX> = UART_PIN_CONF<PA3, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PB10, UartPinFunction::RX> = UART_PIN_CONF<PB10, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PC0, UartPinFunction::RX> = UART_PIN_CONF<PC0, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PG8, UartPinFunction::RX> = UART_PIN_CONF<PG8, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PA2, UartPinFunction::TX> = UART_PIN_CONF<PA2, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PB11, UartPinFunction::TX> = UART_PIN_CONF<PB11, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PC1, UartPinFunction::TX> = UART_PIN_CONF<PC1, AF::AF8>;
template <>
constexpr PinConfig UART_PIN_CONFIG<uart::LPUART1DEF, PG7, UartPinFunction::TX> = UART_PIN_CONF<PG7, AF::AF8>;

template <uart::UartDef UART, Pin PIN>
constexpr PinConfig UART_1WIRE_PIN_CONFIG = []() { // NOLINT(bugprone-dynamic-static-initializers) warning make no sense here
    PinConfig pin_config = UART_PIN_CONFIG<UART, PIN, UartPinFunction::TX>;
    pin_config.output_type = OutputType::OPENDRAIN;

    pin_config.speed = OutputSpeed::MEDIUM;
    pin_config.pupd = PullUpPullDown::NONE;
    return pin_config;
}();
} // namespace stm::periphs::gpio
