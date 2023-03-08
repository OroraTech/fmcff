/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "ina209.hpp"
#include <cstdio>

namespace stm::drivers::ina209 {

[[maybe_unused]] constexpr uint8_t CONFIGURATION_REG = 0x00;
[[maybe_unused]] constexpr uint8_t STATUS_REG = 0x01;
[[maybe_unused]] constexpr uint8_t SMBUS_ALERT_REG = 0x02;
[[maybe_unused]] constexpr uint8_t SHUNT_VOLTAGE_REG = 0x03;
[[maybe_unused]] constexpr uint8_t BUS_VOLTAGE_REG = 0x04;
[[maybe_unused]] constexpr uint8_t POWER_REG = 0x05;
[[maybe_unused]] constexpr uint8_t CURRENT_REG = 0x06;
[[maybe_unused]] constexpr uint8_t SHUNT_VOLTAGE_POSITIVE_PEAK_REG = 0x07;
[[maybe_unused]] constexpr uint8_t SHUNT_VOLTAGE_NEGATIVE_PEAK_REG = 0x08;
[[maybe_unused]] constexpr uint8_t BUS_VOLTAGE_MAXIMUM_PEAK_REG = 0x09;
[[maybe_unused]] constexpr uint8_t BUS_VOLTAGE_MINIMUM_PEAK_REG = 0x0A;
[[maybe_unused]] constexpr uint8_t POWER_PEAK_REG = 0x0B;
[[maybe_unused]] constexpr uint8_t SHUNT_VOLTAGE_POSITIVE_WARNING_REG = 0x0C;
[[maybe_unused]] constexpr uint8_t SHUNT_VOLTAGE_NEGATIVE_WARNING_REG = 0x0D;
[[maybe_unused]] constexpr uint8_t POWER_WARNING_REG = 0x0E;
[[maybe_unused]] constexpr uint8_t BUS_OVERVOLTAGE_WARNING_REG = 0x0F;
[[maybe_unused]] constexpr uint8_t BUS_UNDERVOLTAGE_WARNING_REG = 0x10;
[[maybe_unused]] constexpr uint8_t POWER_OVER_LIMIT_REG = 0x11;
[[maybe_unused]] constexpr uint8_t BUS_OVERVOLTAGE_OVERLIMIT_REG = 0x12;
[[maybe_unused]] constexpr uint8_t BUS_UNDERVOLTAGE_OVERLIMIT_REG = 0x13;
[[maybe_unused]] constexpr uint8_t CRITICAL_DACPLUS_REG = 0x14;
[[maybe_unused]] constexpr uint8_t CRITICAL_DACMINMUS_REG = 0x15;
[[maybe_unused]] constexpr uint8_t CALIBRATION_REG = 0x16;

Ina209::Ina209(periphs::i2c::I2cMaster& i2c, uint8_t address, const Ina209Config& config, uint16_t cal, float current_lsb) :
    i2c_ { i2c }, address_ { address }, config_ { config }, current_lsb_ { current_lsb } {
    reset();
    apply_config(config);
    apply_calibration(cal);
}

void Ina209::reset() {
    constexpr uint16_t RESET_BIT = 15;
    write_reg(CONFIGURATION_REG, uint16_t(1 << RESET_BIT));
}

void Ina209::apply_config(const Ina209Config& config) {
    write_reg(CONFIGURATION_REG, config.to_register_value());
}

void Ina209::apply_calibration(uint16_t calibration) {
    write_reg(CALIBRATION_REG, calibration);
}

uint16_t Ina209::read_reg(uint8_t reg) {
    std::array<uint8_t, 2> buffer {};
    periphs::i2c::I2cError transfer_result = i2c_.transfer(address_, std::as_bytes(std::span { &reg, 1 }), std::as_writable_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        printf("Error 0x%02x during I2c read with INA209 0x%02x", (uint8_t)transfer_result, address_);
    }
    return uint16_t((buffer[0] << 8) + buffer[1]);
}

void Ina209::write_reg(uint8_t reg, uint16_t data) {
    std::array<uint8_t, 3> buffer { reg, static_cast<uint8_t>(data >> 8), static_cast<uint8_t>(data) };
    periphs::i2c::I2cError transfer_result = i2c_.send_bytes(address_, std::as_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        printf("Error 0x%02x during I2c write with INA209 0x%02x", (uint8_t)transfer_result, address_);
    }
}

float Ina209::convert_to_current(int16_t register_value) const {
    return float(register_value) * current_lsb_;
}

float Ina209::convert_to_power(uint16_t register_value) const {
    float power_lsb = 20.0F * current_lsb_; // NOLINT(readability-magic-numbers)
    return float(register_value) * power_lsb;
}

float Ina209::convert_to_bus_voltage(uint16_t register_value) {
    constexpr float BUS_VOLTAGE_SCALING = 0.5F / 1'000.0F;
    return float(register_value) * BUS_VOLTAGE_SCALING;
}

float Ina209::convert_to_shunt_voltage(int16_t register_value) {
    constexpr float SHUNT_VOLTAGE_SCALING = 10.0F / 1'000'000.0F;
    return float(register_value) * SHUNT_VOLTAGE_SCALING;
}

float Ina209::get_current_amps() {
    auto current_register = int16_t(read_reg(CURRENT_REG));
    return convert_to_current(current_register);
}

float Ina209::get_bus_voltage_volts() {
    uint16_t bus_voltage_register = read_reg(BUS_VOLTAGE_REG);
    return convert_to_bus_voltage(bus_voltage_register);
}

float Ina209::get_shunt_voltage_volts() {
    auto shunt_voltage_register = int16_t(read_reg(SHUNT_VOLTAGE_REG));
    return convert_to_shunt_voltage(shunt_voltage_register);
}

float Ina209::get_power_watts() {
    uint16_t power_register = read_reg(POWER_REG);
    return convert_to_power(power_register);
}

float Ina209::get_shunt_voltage_positive_peak() {
    auto register_value = int16_t(read_reg(SHUNT_VOLTAGE_POSITIVE_PEAK_REG));
    return convert_to_shunt_voltage(register_value);
}

float Ina209::get_shunt_voltage_negative_peak() {
    auto register_value = int16_t(read_reg(SHUNT_VOLTAGE_NEGATIVE_PEAK_REG));
    return convert_to_shunt_voltage(register_value);
}

float Ina209::get_bus_voltage_positive_peak() {
    uint16_t register_value = read_reg(BUS_VOLTAGE_MAXIMUM_PEAK_REG);
    return convert_to_bus_voltage(register_value);
}

float Ina209::get_bus_voltage_negative_peak() {
    uint16_t register_value = read_reg(BUS_VOLTAGE_MINIMUM_PEAK_REG);
    return convert_to_bus_voltage(register_value);
}

float Ina209::get_power_peak() {
    uint16_t register_value = read_reg(POWER_PEAK_REG);
    return convert_to_power(register_value);
}

} // namespace stm::drivers::ina209
