/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/i2c/i2c_master.hpp"
#include <cstdint>

namespace stm::drivers::ina3221 {

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

enum class ConvTime {
    US_140 = 0b000,
    US_204 = 0b001,
    US_332 = 0b010,
    US_588 = 0b011,
    US_1100 = 0b100,
    US_2116 = 0b101,
    US_4156 = 0b110,
    US_8244 = 0b111
};

enum class Averages {
    AVG_1 = 0b000,
    AVG_4 = 0b001,
    AVG_16 = 0b010,
    AVG_64 = 0b011,
    AVG_128 = 0b100,
    AVG_256 = 0b101,
    AVG_512 = 0b110,
    AVG_1024 = 0b111
};

struct Ina3221Config {
    Mode mode = Mode::SHUNT_BUS_CONT;
    ConvTime shunt_conv_time = ConvTime::US_1100;
    ConvTime bus_conv_time = ConvTime::US_1100;
    Averages averages = Averages::AVG_1;
    bool enable_channel[3] = { true, true, true };

    [[nodiscard]] constexpr uint16_t to_register_value() const {
        return static_cast<uint16_t>(
            uint16_t(mode)
            | uint16_t(shunt_conv_time) << 3
            | uint16_t(bus_conv_time) << 6
            | uint16_t(averages) << 9
            | (enable_channel[2] ? 1 : 0) << 12
            | (enable_channel[1] ? 1 : 0) << 13
            | (enable_channel[0] ? 1 : 0) << 14);
    }
};

class Ina3221 {
public:
    Ina3221(periphs::i2c::I2cMaster& i2c, uint8_t address, Ina3221Config config, float shunt_resistance_ohms);

    [[nodiscard]] float get_current_amps(int channel); ///<< Note: the sensor does not do an actual conversion to current, this is done in software
    [[nodiscard]] float get_bus_voltage_volts(int channel);
    [[nodiscard]] float get_shunt_voltage_volts(int channel);

    [[nodiscard]] bool check_id();

private:
    void apply_config(const Ina3221Config& config);

    uint16_t read_reg(uint8_t reg);
    void write_reg(uint8_t reg, uint16_t data);

    periphs::i2c::I2cMaster& i2c_;
    uint8_t address_;
    float shunt_resistance_ohms_;

    static constexpr uint8_t CONFIGURATION_REG = 0x00;
    static constexpr const auto SHUNT_VOLTAGE_REG = [](int channel) { return (channel < 1 || channel > 3) ? -1 : (channel * 2 - 1); };
    static constexpr const auto BUS_VOLTAGE_REG = [](int channel) { return (channel < 1 || channel > 3) ? -1 : (channel * 2); };
    static constexpr const auto CRITICAL_ALERT_LIMIT_REG = [](int channel) { return (channel < 1 || channel > 3) ? -1 : (channel * 2 + 5); };
    static constexpr const auto WARNING_ALERT_LIMIT_REG = [](int channel) { return (channel < 1 || channel > 3) ? -1 : (channel * 2 + 6); };
    static constexpr uint8_t SHUNT_VOLTAGE_SUM_REG = 0xD;
    static constexpr uint8_t SHUNT_VOLTAGE_SUM_LIMIT_REG = 0xE;
    static constexpr uint8_t MASK_ENABLE_REG = 0xF;
    static constexpr uint8_t POWER_VALID_UPPER_LIMIT_REG = 0x10;
    static constexpr uint8_t POWER_VALID_LOWER_LIMIT_REG = 0x11;
    static constexpr uint8_t MANUFACTURER_ID_REG = 0xFE;
    static constexpr uint8_t DIE_ID_REG = 0xFF;
};

} // namespace stm::drivers::ina3221
