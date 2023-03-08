/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdio>

#include "health_monitor.hpp"
#include "mpy_helpers.hpp"
#include "stm/support/cycle_count.hpp"
#include "stm/support/interrupt_timer.hpp"
#include "stm/periphs/can/can.hpp"
#include "stm/periphs/can/can_interrupt.hpp"

#include "modules/gpio/gpio.hpp"

constexpr stm::periphs::gpio::PinConfig LED0 {
    stm::periphs::gpio::PC7,
    stm::periphs::gpio::Mode::OUTPUT
};
constexpr stm::periphs::gpio::PinConfig LED1 {
    target_specific::LED_PIN,
    stm::periphs::gpio::Mode::OUTPUT
};

enum class MONITOR {
    TEMPERATURE_LOW = 0,
    TEMPERATURE_HIGH = 1,
};

int main() {
    using namespace std::chrono_literals;
    printf("Health Monitor Recovery Sample Bootup\r\n");

    std::array gpios { stm::periphs::gpio::Gpio::init<LED0>(),
        stm::periphs::gpio::Gpio::init<LED1>() };
    gpiomodule::setup_gpiomodule(gpios);

    fmcff::ChunkTable<fmcff::ValueRange> table {};
    fmcff::HealthMonitor monitor { table, [] ([[maybe_unused]] int id, std::string_view script) {
        setup_micropython();
        execute_script(script.data());
    } };

    // Define healthy range for temperature too high
    fmcff::ValueRange temp_high_range = { (int)MONITOR::TEMPERATURE_HIGH, -1000.0f, 60.0f };
    // Define healthy range for temperature too low
    fmcff::ValueRange temp_low_range = { (int)MONITOR::TEMPERATURE_LOW, -5.0f, 1000.0f };
    // Define fault mitigation for temp too high
    table.insert(temp_high_range, { R"(
import gpio

print("Detected too high temperature!")
power_switch_pl = gpio.GPIO(0)
power_switch_pl.set_low()
print("Turned off payload")
)" });
    // Define fault mitigation for temp too low
    table.insert(temp_low_range, { R"(
import gpio

print("Detected too low temperature!")
power_switch_heater = gpio.GPIO(1)
power_switch_heater.set_high()
print("Turned on heater")
)" });

    ot::Shared<stm::periphs::can::Can> can = stm::periphs::can::Can::init_shared<target_specific::CAN1>();

    std::function can_handler = [&] (stm::periphs::can::CanMsg& msg) {
        printf("Got msg\r\n");
        if (msg.can_id == 0xF) {
            float temp = std::bit_cast<float>(msg.data[0]);
            printf("Got temp: %f\r\n", temp);
            monitor.check_value((int)MONITOR::TEMPERATURE_HIGH, temp);
            monitor.check_value((int)MONITOR::TEMPERATURE_LOW, temp);
        }
    };

    stm::periphs::can::NewRx0MessageInterrupt interrupt { can, can_handler };

    printf("Setup Complete, starting main script\r\n");

    // Main script:
    while(true) {
        setup_micropython();
        execute_script(R"(
print("Hello from µPython")
import gpio
pl = gpio.GPIO(0)
heater = gpio.GPIO(1)
for k in range(1000000):
    pass
print("Started default mode, pl on, heater off")
a = pl.set_high()
a = heater.set_low()
    )");
    }
    __builtin_trap();
}
