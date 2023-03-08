/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/uart/uart_def.hpp"

namespace stm::periphs::uart {
/**
 * @brief User configuration of a UART peripheral.
 * The user can choose a globally defined UartDef and baudrate.
 * The object can be used as input to Uart::init()
 * @note This config struct has to be constructed as constexpr
 */
struct UartConfig { // NOLINT(cppcoreguidelines-pro-type-member-init), no sensible default possible and UartConfig can't be constructed anyway without the uart being explicitely given
    UartDef uart;
    uint32_t baudrate {};
    gpio::Pin tx {};
    gpio::Pin rx {};
};
} // namespace stm::periphs::uart
