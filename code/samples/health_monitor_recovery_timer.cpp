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
#include "stm/periphs/rng/rng.hpp"
#include "stm/periphs/can/can_interrupt.hpp"
#include "context_switch.hpp"
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

fmcff::ProcessContext g_mpy_context {};

int main() {
    using namespace std::chrono_literals;
    printf("Health Monitor Recovery Sample Bootup\r\n");

    std::array gpios { stm::periphs::gpio::Gpio::init<LED0>(),
        stm::periphs::gpio::Gpio::init<LED1>() };
    gpiomodule::setup_gpiomodule(gpios);

    std::atomic<const char*> failure_handling_script = nullptr;

    fmcff::ChunkTable<fmcff::ValueRange> table {};
    fmcff::HealthMonitor monitor { table, [&] ([[maybe_unused]] int id, std::string_view script) {
        //setup_micropython();
        //execute_script(script.data());
        failure_handling_script = script.data();
        fmcff::ProcessContext::return_to_main();
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

    stm::periphs::rng::Rng rng {};

    std::function timer_handler = [&] () {
        float random_value = rng.get_random_float();
        float temp = random_value*80.0F-10.0F; // random number between -10 and 70
        printf("Got temp: %dmillicelsius, %f, from random value: %f\r\n", int(temp*1000.0F), temp, random_value); // for some reason float prints inside this handler are only correct on the first call and then wrong(wtf)
        monitor.check_value((int)MONITOR::TEMPERATURE_HIGH, temp);
        monitor.check_value((int)MONITOR::TEMPERATURE_LOW, temp);
    };
    stm::support::InterruptTimer failure_timer { timer_handler, 5s };

    printf("Setup Complete, starting main script\r\n");

    // Main script:
    while(true) {
        setup_micropython();
        constexpr const char default_script[] = R"(
print("Hello from µPython")
import gpio
pl = gpio.GPIO(0)
heater = gpio.GPIO(1)
for k in range(1000000):
    pass
print("Started default mode, pl on, heater off")
a = pl.set_high()
a = heater.set_low()
    )";

        g_mpy_context.switch_to_context([&]{
            const char* failure_handling = failure_handling_script.exchange(nullptr);
            const char* used_script = failure_handling ? failure_handling : default_script;
            execute_script(used_script);
            return 0;
        });
        
    }
    __builtin_trap();
}
