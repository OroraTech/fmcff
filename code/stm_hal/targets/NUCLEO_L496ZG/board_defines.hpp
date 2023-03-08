/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/can/can_config.hpp"
#include "stm/periphs/can/periphs.hpp"
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/periphs/uart/periphs.hpp"
#include "stm/periphs/uart/uart_config.hpp"
#include "stm/regs/peripherals.hpp"

namespace target_specific {
using namespace stm::periphs;

constexpr uart::UartConfig STDOUT = {
    .uart = uart::LPUART1DEF,
    .baudrate = 115200,
    .tx = gpio::PG7,
    .rx = gpio::PG8,
};

constexpr gpio::Pin CAN1_TX_PIN = gpio::PD1;
constexpr gpio::Pin CAN1_RX_PIN = gpio::PD0;

constexpr stm::periphs::can::CanConfig CAN1 = {
    .can = stm::periphs::can::CAN1DEF,
    .baudrate = 1000000,
    .tx = target_specific::CAN1_TX_PIN,
    .rx = target_specific::CAN1_RX_PIN,
    .loopback = false
};

// Blue LED on NUCLEO_L496ZG
constexpr gpio::Pin LED_PIN = gpio::PB7;

constexpr gpio::Pin GPIO_OUTPUT_PIN = gpio::PB0;
constexpr gpio::Pin GPIO_INPUT_PIN = gpio::PE0;
} // namespace target_specific
