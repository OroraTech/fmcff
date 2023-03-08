/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/can/can_def.hpp"
#include "stm/periphs/gpio/pin_config.hpp"

namespace stm::periphs::can {
struct CanConfig {
    CanDef can;
    uint32_t baudrate {};
    gpio::Pin tx;
    gpio::Pin rx;
    bool loopback = false;
};
} // namespace stm::periphs::can
