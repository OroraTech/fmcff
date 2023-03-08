/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/regs/gpio_registers.hpp"

namespace stm::periphs::gpio {
/**
 * @brief Initialize and use a GPIO pin.
 * Use init() to construct an Gpio object and initialize the peripheral.
 */
class Gpio {
public:
    template <PinConfig CONFIG>
    static Gpio init();

    void set(bool state);
    [[nodiscard]] bool read();

private:
    explicit Gpio(Pin pin);
    regs::gpio::GPIOStruct& gpio_;
    uint8_t pin_in_port_;
};

template <PinConfig CONFIG>
Gpio Gpio::init() {
    gpio::apply_pin_config(CONFIG);
    return Gpio(CONFIG.pin);
}
} // namespace stm::periphs::gpio
