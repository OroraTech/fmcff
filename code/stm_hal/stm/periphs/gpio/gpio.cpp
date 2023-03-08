/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/periphs/gpio/gpio.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::gpio {

void Gpio::set(bool state) {
    uint32_t state_as_uint = state ? 1 : 0;
    // note: lower 16 bits set pins, upper 16 bits reset pins
    // this always resets the pin because setting the pin has priority anyway
    uint32_t mask = ((0x1 << 16) | state_as_uint) << pin_in_port_;
    gpio_.BSRR.write(mask);
}

[[nodiscard]] bool Gpio::read() {
    return bool((gpio_.IDR.read() >> pin_in_port_) & 1);
}

Gpio::Gpio(Pin pin) :
    gpio_ { __PERIPHERAL_GPIOS__[pin.get_port_number()] }, pin_in_port_ { pin.get_port_pin_number() } {
}
} // namespace stm::periphs::gpio
