/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdio>

#include "context_switch.hpp"
#include "health_monitor.hpp"
#include "modules/gpio/gpio.hpp"
#include "mpy_helpers.hpp"
#include "stm/drivers/ina/ina226.hpp"
#include "stm/periphs/can/can.hpp"
#include "stm/periphs/can/can_interrupt.hpp"
#include "stm/periphs/i2c/i2c_master.hpp"
#include "stm/periphs/rng/rng.hpp"
#include "stm/support/cycle_count.hpp"
#include "stm/support/interrupt_timer.hpp"

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
    HEATER_OFF = 2,
    OVERVOLTAGE = 3,
};

fmcff::ProcessContext g_mpy_context {};

constexpr uint8_t INA_ADDRESS = 0x40;
constexpr float INA_SHUNT_OHMS = 0.1F;

constexpr stm::drivers::ina226::InaConfig INA_CONFIG {
    .mode = stm::drivers::ina226::Mode::SHUNT_BUS_CONT,
    .shunt_conv_time = stm::drivers::ina226::ConvTime::US_1100,
    .bus_conv_time = stm::drivers::ina226::ConvTime::US_1100,
    .averages = stm::drivers::ina226::Averages::AVG_1
};

// I2C_B on the nucleo
constexpr stm::periphs::i2c::I2cConfig I2C {
    .i2c = stm::periphs::i2c::I2C2DEF,
    .baudrate = 100'000,
    .sda = stm::periphs::gpio::PF0,
    .scl = stm::periphs::gpio::PF1
};

constexpr float INA_MAX_CURRENT_AMPS = 2;
constexpr stm::drivers::ina226::InaCalibration INA_CALIBRATION = stm::drivers::ina226::InaCalibration::generate<INA_SHUNT_OHMS, INA_MAX_CURRENT_AMPS>();

constexpr stm::drivers::ina226::InaAlertConfig LOW_CURRENT_ALERT {
    .threshold_current_amps = 0.02F
};

int main() {
    using namespace std::chrono_literals;
    printf("Health Monitor Recovery Sample Bootup\r\n");

    std::array gpios { stm::periphs::gpio::Gpio::init<LED0>(),
                       stm::periphs::gpio::Gpio::init<LED1>() };
    gpiomodule::setup_gpiomodule(gpios);

    stm::periphs::i2c::I2cMaster i2c = stm::periphs::i2c::I2cMaster::init<I2C>();
    stm::drivers::ina226::Ina226 ina { i2c, INA_ADDRESS, INA_CALIBRATION, INA_CONFIG, LOW_CURRENT_ALERT };

    printf("Read MCU INA data:\r\nVoltage: %fV\r\nShunt voltage: %fV\r\nCurrent: %fA\r\nPower: %fW\r\n",
           ina.get_bus_voltage_volts(),
           ina.get_shunt_voltage_volts(),
           ina.get_current_amps(),
           ina.get_power_watts());

    std::atomic<const char*> failure_handling_script = nullptr;

    fmcff::ChunkTable<fmcff::ValueRange> table {};
    fmcff::HealthMonitor monitor { table, [&]([[maybe_unused]] int id, std::string_view script) {
                                      failure_handling_script = script.data();
                                      fmcff::ProcessContext::return_to_main();
                                  } };

    // Define healthy range for temperature too high
    fmcff::ValueRange temp_high_range = { (int)MONITOR::TEMPERATURE_HIGH, -1000.0f, 60.0f };
    // Define healthy range for temperature too low
    fmcff::ValueRange temp_low_range = { (int)MONITOR::TEMPERATURE_LOW, -5.0f, 1000.0f };

    // Define range end for when to disable the heater again
    fmcff::ValueRange temp_too_high_for_heater_range = { (int)MONITOR::HEATER_OFF, -1000.0f, 5.0f };

    // Define nominal voltage range for payload
    fmcff::ValueRange nominal_voltage_range = { (int)MONITOR::OVERVOLTAGE, -0.5f, 5.2f };

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
    // Define fault mitigation for temp too high for heater
    table.insert(temp_too_high_for_heater_range, { R"(
import gpio

print("Temp warm enough, disable heater again")
power_switch_heater = gpio.GPIO(1)
power_switch_heater.set_low()
print("Turned off heater")
)" });

    // Define fault mitigation for overvoltage
    table.insert(nominal_voltage_range, { R"(
import gpio

power_switch_heater = gpio.GPIO(0)
power_switch_heater.set_low()
print("Overvoltage detected, payload off")
)" });

    stm::periphs::rng::Rng rng {};

    ot::Shared<stm::periphs::can::Can> can = stm::periphs::can::Can::init_shared<target_specific::CAN1>();

    std::function can_handler = [&](stm::periphs::can::CanMsg& msg) {
        printf("Got msg\r\n");
        if (msg.can_id == 0xF) {
            float temp = 0.0F;
            memcpy(&temp, &msg.data[0], 4);
            auto bytes = reinterpret_cast<char(&)[4]>(msg.data[0]);
            for (int i = 0; i < 4; i++) {
                printf("%02x", bytes[i]);
            }
            printf("\r\nGot temp: %d\r\n", (int)(temp * 100.0F));
            monitor.check_value((int)MONITOR::TEMPERATURE_HIGH, temp);
            monitor.check_value((int)MONITOR::TEMPERATURE_LOW, temp);
            monitor.check_value((int)MONITOR::HEATER_OFF, temp);
        }
    };

    stm::periphs::can::NewRx0MessageInterrupt interrupt { can, can_handler };

    std::function timer_handler = [&monitor, &ina]() {
        static bool registered = false;
        static auto start = stm::support::SteadyClock::now();
        float volts = ina.get_bus_voltage_volts();
        if (volts > 5.2f && !registered) {
            gpiomodule::cycles.register_tick();
            registered = true;
        }
        monitor.check_value((int)MONITOR::OVERVOLTAGE, volts);
        printf("%ld,%d\r\n", (long)std::chrono::duration_cast<std::chrono::milliseconds>(stm::support::SteadyClock::now() - start).count(), (int)(volts * 1000));
    };
    stm::support::InterruptTimer failure_timer { timer_handler, 100ms };

    printf("Setup Complete, starting main script\r\n");

    // Main script:
    while (true) {
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
#a = heater.set_low()
    )";

        g_mpy_context.switch_to_context([&] {
            const char* failure_handling = failure_handling_script.exchange(nullptr);
            const char* used_script = failure_handling ? failure_handling : default_script;
            execute_script(used_script);
            return 0;
        });
    }
    __builtin_trap();
}
