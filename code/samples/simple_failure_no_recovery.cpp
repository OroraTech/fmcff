/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdio>

#include "mpy_helpers.hpp"
#include "stm/support/cycle_count.hpp"
#include "stm/support/interrupt_timer.hpp"

#include "modules/gpio/gpio.hpp"

constexpr stm::periphs::gpio::PinConfig OUTPUT_CONFIG {
    target_specific::GPIO_OUTPUT_PIN,
    stm::periphs::gpio::Mode::OUTPUT
};
constexpr stm::periphs::gpio::PinConfig INPUT_CONFIG {
    target_specific::GPIO_INPUT_PIN,
    stm::periphs::gpio::Mode::INPUT
};
constexpr stm::periphs::gpio::PinConfig LED_CONFIG {
    target_specific::LED_PIN,
    stm::periphs::gpio::Mode::OUTPUT
};

int main() {
    using namespace std::chrono_literals;

    CycleCount cycles {};

    std::function failure_handler = [&] {
        static size_t cnt = 0;
        if (cnt++ == 0) {
            // Do not have a failure on first call
            return;
        }
        printf("Failure detected\r\n");
        cycles.register_tick();
        setup_micropython();
        setup_wrapper();
        // blink on error
        execute_script(R"(
import gpio
led_output = gpio.GPIO(2)
for i in range(4):
    led_output.set_high()
    for k in range(100000):
        pass
    led_output.set_low()
    for k in range(100000):
        pass
)");
        cycles.register_tick();
        cycles.print_ticks();
    };

    std::array gpios { stm::periphs::gpio::Gpio::init<OUTPUT_CONFIG>(), stm::periphs::gpio::Gpio::init<INPUT_CONFIG>(), stm::periphs::gpio::Gpio::init<LED_CONFIG>() };
    gpiomodule::setup_gpiomodule(gpios);

    // Setup a "failure" in 5 seconds
    stm::support::InterruptTimer failure_timer { failure_handler, 5s };

    // Execute a long script:
    setup_micropython();
    setup_wrapper();
    execute_script(R"(
import gc
import gpio
gpio_output = gpio.GPIO(0)
gpio_input = gpio.GPIO(1)
for i in range(10000):
    if gpio_input.get():
        print("is high, setting low")
        gpio_output.set_low()
    else:
        print("is low, setting high")
        gpio_output.set_high()
    gc.mem_alloc()
    for k in range(100000):
        pass
)");
    __builtin_trap();
}
