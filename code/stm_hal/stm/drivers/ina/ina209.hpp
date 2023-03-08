/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/i2c/i2c_master.hpp"
#include <cstdint>

namespace stm::drivers::ina209 {

enum class BusVoltageRange {
    V_16 = 0,
    V_32 = 1
};

enum class ShuntVoltageRange {
    MV_40 = 0,
    MV_80 = 1,
    MV_160 = 2,
    MV_320 = 3
};

enum class Mode {
    POWER_DOWN = 0b000,
    SHUNT_TRIG = 0b001,
    BUS_TRIG = 0b010,
    SHUNT_BUS_TRIG = 0b011,
    POWER_DOWN_CONT = 0b100,
    SHUNT_CONT = 0b101,
    BUS_CONT = 0b110,
    SHUNT_BUS_CONT = 0b111,
};

enum class AdcSetting {
    US_84 = 0b0000,
    US_148 = 0b0001,
    US_276 = 0b0010,
    US_532 = 0b0011,
    US_1060 = 0b1001,
    US_2130 = 0b1010,
    US_4260 = 0b1011,
    US_8510 = 0b1100,
    US_17020 = 0b1101,
    US_34050 = 0b1110,
    US_68100 = 0b1111
};

struct Ina209Config {
    Mode mode = Mode::SHUNT_BUS_CONT;
    AdcSetting shunt_adc_setting = AdcSetting::US_532;
    AdcSetting bus_adc_setting = AdcSetting::US_532;
    ShuntVoltageRange shunt_voltage_range = ShuntVoltageRange::MV_320;
    BusVoltageRange bus_voltage_range = BusVoltageRange::V_32;
    float shunt_resistance_ohms;
    float max_current_a;

    [[nodiscard]] constexpr uint16_t to_register_value() const {
        return static_cast<uint16_t>(
            uint16_t(mode) | uint16_t(shunt_adc_setting) << 3 | uint16_t(bus_adc_setting) << 7 | uint16_t(shunt_voltage_range) << 11 | uint16_t(bus_voltage_range) << 13);
    }

    [[nodiscard]] constexpr float get_max_bus_voltage() const {
        return (bus_voltage_range == BusVoltageRange::V_16) ? 16.0F : 32.0F; // NOLINT(readability-magic-numbers)
    }

    [[nodiscard]] constexpr float get_max_shunt_voltage() const {
        switch (shunt_voltage_range) {
        // NOLINTBEGIN(readability-magic-numbers)
        case ShuntVoltageRange::MV_40:
            return 40.0F;
        case ShuntVoltageRange::MV_80:
            return 80.0F;
        case ShuntVoltageRange::MV_160:
            return 160.0F;
        case ShuntVoltageRange::MV_320:
            return 320.0F;
        // NOLINTEND(readability-magic-numbers)
        default:
            return std::numeric_limits<float>::signaling_NaN();
        }
    }
};

class Ina209 {
public:
    template <Ina209Config CONFIG>
    static Ina209 init(periphs::i2c::I2cMaster& i2c, uint8_t address);

    [[nodiscard]] float get_current_amps();
    [[nodiscard]] float get_bus_voltage_volts();
    [[nodiscard]] float get_shunt_voltage_volts();
    [[nodiscard]] float get_power_watts();
    [[nodiscard]] float get_shunt_voltage_positive_peak();
    [[nodiscard]] float get_shunt_voltage_negative_peak();
    [[nodiscard]] float get_bus_voltage_positive_peak();
    [[nodiscard]] float get_bus_voltage_negative_peak();
    [[nodiscard]] float get_power_peak();

private:
    Ina209(periphs::i2c::I2cMaster& i2c, uint8_t address, const Ina209Config& config, uint16_t cal, float current_lsb);
    void reset();
    void apply_config(const Ina209Config& config);
    void apply_calibration(uint16_t calibration);

    [[nodiscard]] static float convert_to_bus_voltage(uint16_t register_value);
    [[nodiscard]] static float convert_to_shunt_voltage(int16_t register_value);
    [[nodiscard]] float convert_to_current(int16_t register_value) const;
    [[nodiscard]] float convert_to_power(uint16_t register_value) const;

    [[nodiscard]] uint16_t read_reg(uint8_t reg);
    void write_reg(uint8_t reg, uint16_t data);

    periphs::i2c::I2cMaster& i2c_;
    uint8_t address_;
    Ina209Config config_;
    float current_lsb_;
};

template <Ina209Config CONFIG>
Ina209 Ina209::init(periphs::i2c::I2cMaster& i2c, uint8_t address) {
    constexpr float MINIMUM_CURRENT_LSB = CONFIG.max_current_a / 32767.0F; // Datasheet equation 2
    constexpr float CURRENT_LSB = MINIMUM_CURRENT_LSB;
    constexpr float CAL_FLOAT = 0.04096F / (CURRENT_LSB * CONFIG.shunt_resistance_ohms); // Datasheet equation 4
    constexpr auto CAL = uint16_t(CAL_FLOAT);                                            // Note: bounds checking is not necessary here because an out-of-bounds value would cause a compile error in constexpr
    return Ina209 { i2c, address, CONFIG, CAL, CURRENT_LSB };
}

} // namespace stm::drivers::ina209
