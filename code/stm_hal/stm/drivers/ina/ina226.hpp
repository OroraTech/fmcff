/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/i2c/i2c_master.hpp"
#include <cstdint>

namespace stm::drivers::ina226 {

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

/**
 * @brief struct to configure the alert pin functionality on the INA226
 *
 * @note currently only meant for overcurrent protection because that's what we will most likely use
 */
struct InaAlertConfig {
    float threshold_current_amps = 0; ///<< will trigger above this current. Set to 0 to disable
};

struct InaConfig {
    Mode mode = Mode::SHUNT_BUS_CONT;
    ConvTime shunt_conv_time = ConvTime::US_1100;
    ConvTime bus_conv_time = ConvTime::US_1100;
    Averages averages = Averages::AVG_1;

    [[nodiscard]] constexpr uint16_t to_register_value() const {
        return static_cast<uint16_t>(
            uint16_t(mode) | uint16_t(shunt_conv_time) << 3 | uint16_t(bus_conv_time) << 6 | uint16_t(averages) << 9);
    }
};

class InaCalibration {
public:
    template <float SHUNT_RESISTANCE_OHMS, float MAX_CURRENT>
    static consteval InaCalibration generate() {
        constexpr float MAGIC_NUMBER_FROM_DATASHEET_EQUATION_1 = 0.00512F;
        constexpr float CURRENT_LSB = MAX_CURRENT / float(1 << 15);
        constexpr float CAL_AS_FLOAT = MAGIC_NUMBER_FROM_DATASHEET_EQUATION_1 / (CURRENT_LSB * SHUNT_RESISTANCE_OHMS);
        static_assert(CAL_AS_FLOAT <= std::numeric_limits<int16_t>::max(), "INA226 calibration results in a too large CAL register value(usually this happens because the MAX_CURRENT is too low)");
        constexpr auto CAL_VALUE = static_cast<uint16_t>(CAL_AS_FLOAT);
        constexpr float CORRECTED_CURRENT_LSB = MAGIC_NUMBER_FROM_DATASHEET_EQUATION_1 / (float(CAL_VALUE) * SHUNT_RESISTANCE_OHMS);
        return { CAL_VALUE, CORRECTED_CURRENT_LSB, SHUNT_RESISTANCE_OHMS };
    }

    [[nodiscard]] constexpr uint16_t get_cal_register_value() const {
        return cal_register_value_;
    }
    [[nodiscard]] constexpr float get_current_lsb() const {
        return current_lsb_;
    }
    [[nodiscard]] constexpr float get_shunt_resistance_ohms() const {
        return shunt_resistance_ohms_;
    }

private:
    constexpr InaCalibration(uint16_t cal_register_value, float current_lsb, float shunt_resistance_ohms) :
        cal_register_value_ { cal_register_value }, current_lsb_ { current_lsb }, shunt_resistance_ohms_ { shunt_resistance_ohms } {}
    uint16_t cal_register_value_;
    float current_lsb_;
    float shunt_resistance_ohms_;
};

class Ina226 {
public:
    Ina226(periphs::i2c::I2cMaster& i2c, uint8_t address, InaCalibration calibration, InaConfig config, InaAlertConfig alert_config = {});

    [[nodiscard]] float get_current_amps();
    [[nodiscard]] float get_bus_voltage_volts();
    [[nodiscard]] float get_shunt_voltage_volts();
    [[nodiscard]] float get_power_watts();

    [[nodiscard]] bool check_id();

private:
    void apply_config(InaConfig config);
    void apply_calibration(InaCalibration calibration);
    void apply_alert_config(InaAlertConfig alert_config);

    uint16_t read_reg(uint8_t reg);
    void write_reg(uint8_t reg, uint16_t data);

    periphs::i2c::I2cMaster& i2c_;
    uint8_t address_;
    InaCalibration calibration_;
};

} // namespace stm::drivers::ina226
