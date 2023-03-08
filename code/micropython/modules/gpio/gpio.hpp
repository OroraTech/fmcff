/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "board_defines.hpp"
#include "stm/periphs/gpio/gpio.hpp"
#include "stm/support/cycle_count.hpp"

#include <cstdio>
#include <span>

namespace gpiomodule {
extern CycleCount cycles;
void setup_gpiomodule(std::span<stm::periphs::gpio::Gpio> gpios);

class GPIO {
public:
    explicit GPIO(std::span<stm::periphs::gpio::Gpio> gpios, size_t index) :
        gpios_ { gpios }, index_ { index } {};

    ~GPIO() {};

    void set(bool val) {
        gpios_[index_].set(val);
    }

    void set_high() {
        gpios_[index_].set(true);
        printf("Setting pin high\r\n");
    }

    void set_low() {
        static bool registered = false;
        gpios_[index_].set(false);
        printf("Setting pin low\r\n");
        if (!registered) {
            cycles.register_tick();
            cycles.print_ticks();
            registered = true;
        }
    }

    bool get() {
        return (bool)gpios_[index_].read();
    }

private:
    std::span<stm::periphs::gpio::Gpio> gpios_;
    size_t index_;
};
}
