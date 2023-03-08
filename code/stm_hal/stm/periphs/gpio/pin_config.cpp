/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "pin_config.hpp"
#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::gpio {

void apply_pin_config(const PinConfig& pin_config) {
    if (pin_config.pin == NULL_PIN) {
        return;
    }
    using namespace stm::regs::pwr::CR2;

    rcc::enable_rcc_periph(rcc::get_gpio_rcc_periph(pin_config.pin.get_port_number()));
    if (pin_config.pin.get_port() == Port::G) {
        rcc::enable_rcc_periph(rcc::PWR_PERIPH);
        __PERIPHERAL_PWR__.CR2.set(IOSV(1));
    }

    regs::gpio::GPIOStruct& gpio = __PERIPHERAL_GPIOS__[pin_config.pin.get_port_number()];
    uint16_t pin_mask = pin_config.pin.get_pin_mask();

    gpio.ODR.set_masked(pin_mask, (int)pin_config.initial_output_state);
    gpio.OTYPER.set_masked(pin_mask, (int)pin_config.output_type);
    gpio.OSPEEDR.set_masked(pin_mask, (int)pin_config.speed);
    gpio.PUPDR.set_masked(pin_mask, (int)pin_config.pupd);
    gpio.AFRL.set_masked(pin_mask, (int)pin_config.alternate_function);
    gpio.AFRH.set_masked(pin_mask >> 8, (int)pin_config.alternate_function);
    gpio.MODER.set_masked(pin_mask, (int)pin_config.mode);
}

} // namespace stm::periphs::gpio
