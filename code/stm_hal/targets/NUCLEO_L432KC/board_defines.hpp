/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "rcc_config.hpp"
#include "stm/periphs/can/can_config.hpp"
#include "stm/periphs/can/periphs.hpp"
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/periphs/uart/periphs.hpp"
#include "stm/periphs/uart/uart_config.hpp"
#include "stm/regs/peripherals.hpp"
#include <cstdint>

namespace target_specific {
using namespace stm::periphs;

constexpr uart::UartConfig STDOUT = {
    .uart = uart::USART2DEF,
    .baudrate = 115200,
    .tx = gpio::PA2,
    .rx = gpio::PA15,
};

constexpr gpio::Pin CAN1_TX_PIN = gpio::PA12;
constexpr gpio::Pin CAN1_RX_PIN = gpio::PA11;

constexpr stm::periphs::can::CanConfig CAN1 = {
    .can = stm::periphs::can::CAN1DEF,
    .baudrate = 1000000,
    .tx = target_specific::CAN1_TX_PIN,
    .rx = target_specific::CAN1_RX_PIN,
    .loopback = false
};

// Alias so that the samples can use <CAN> and not care about what the hardware needs.
// Change here to switch between CAN buses.
constexpr stm::periphs::can::CanConfig CAN = CAN1;

// Green LED on NUCLEO_L432KC
constexpr gpio::Pin LED_PIN = gpio::PB3;

} // namespace target_specific
