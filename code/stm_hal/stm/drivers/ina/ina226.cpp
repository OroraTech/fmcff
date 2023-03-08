/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "ina226.hpp"
#include <array>
#include <cstdio>
#include <span>

namespace stm::drivers::ina226 {

constexpr uint8_t CONFIGURATION_REG = 0x00;
constexpr uint8_t SHUNT_VOLTAGE_REG = 0x01;
constexpr uint8_t BUS_VOLTAGE_REG = 0x02;
constexpr uint8_t POWER_REG = 0x03;
constexpr uint8_t CURRENT_REG = 0x04;
constexpr uint8_t CALIBRATION_REG = 0x05;
constexpr uint8_t MASK_ENABLE_REG = 0x06;
constexpr uint8_t ALERT_LIMIT_REG = 0x07;
constexpr uint8_t MANUFACTURER_ID_REG = 0xFE;
constexpr uint8_t DIE_ID_REG = 0xFF;

Ina226::Ina226(periphs::i2c::I2cMaster& i2c, uint8_t address, InaCalibration calibration, InaConfig config, InaAlertConfig alert_config) :
    i2c_ { i2c }, address_ { address }, calibration_ { calibration } {
    if (!check_id()) {
        printf("Error while reading the ID of INA226 %02x\r\n", address);
        return;
    }
    apply_config(config);
    apply_calibration(calibration);
    apply_alert_config(alert_config);
}

float Ina226::get_current_amps() {
    auto current_register = int16_t(read_reg(CURRENT_REG));
    return static_cast<float>(current_register) * calibration_.get_current_lsb();
}
float Ina226::get_bus_voltage_volts() {
    constexpr float BUS_VOLTAGE_LSB = 1.25F / 1'000.0F; // Datasheet 7.6.3
    auto bus_voltage_register = int16_t(read_reg(BUS_VOLTAGE_REG));
    return static_cast<float>(bus_voltage_register) * BUS_VOLTAGE_LSB;
}
float Ina226::get_shunt_voltage_volts() {
    constexpr float SHUNT_VOLTAGE_LSB = 2.5F / 1'000'000.0F; // Datasheet 7.6.2
    auto shunt_voltage_register = int16_t(read_reg(SHUNT_VOLTAGE_REG));
    return static_cast<float>(shunt_voltage_register) * SHUNT_VOLTAGE_LSB;
}
float Ina226::get_power_watts() {
    constexpr float POWER_CONVERSION_FACTOR = 25.0F; // Datasheet 7.6.4
    auto power_register = int16_t(read_reg(POWER_REG));
    return static_cast<float>(power_register) * calibration_.get_current_lsb() * POWER_CONVERSION_FACTOR;
}

bool Ina226::check_id() {
    constexpr uint16_t EXPECTED_MANUFACTURER_ID = 0x5449;
    constexpr uint16_t EXPECTED_DIE_ID = 0x2260;
    uint16_t manufacturer_id_value = read_reg(MANUFACTURER_ID_REG);
    uint16_t die_id_value = read_reg(DIE_ID_REG);
    return manufacturer_id_value == EXPECTED_MANUFACTURER_ID && die_id_value == EXPECTED_DIE_ID;
}

void Ina226::apply_config(InaConfig config) {
    write_reg(CONFIGURATION_REG, config.to_register_value());
}
void Ina226::apply_calibration(InaCalibration calibration) {
    write_reg(CALIBRATION_REG, calibration.get_cal_register_value());
}
void Ina226::apply_alert_config(InaAlertConfig alert_config) {
    constexpr float SHUNT_VOLTAGE_LSB = 2.5F / 1'000'000.0F; // Datasheet 7.6.2
    if (alert_config.threshold_current_amps == 0) {
        return;
    }
    float shunt_voltage_limit = alert_config.threshold_current_amps * calibration_.get_shunt_resistance_ohms();
    float alert_limit_value = shunt_voltage_limit / SHUNT_VOLTAGE_LSB;
    if (alert_limit_value > std::numeric_limits<int16_t>::max()) {
        printf("Configured alert threshold current is too large\r\n");
    }
    auto alert_limit_register_value = static_cast<uint16_t>(alert_limit_value);
    write_reg(ALERT_LIMIT_REG, alert_limit_register_value);
    constexpr uint16_t SHUNT_OVER_VOLTAGE_FLAG { 0x8000 };
    write_reg(MASK_ENABLE_REG, SHUNT_OVER_VOLTAGE_FLAG);
}

uint16_t Ina226::read_reg(uint8_t reg) {
    std::array<uint8_t, 2> buffer {};
    periphs::i2c::I2cError transfer_result = i2c_.transfer(address_, std::as_bytes(std::span { &reg, 1 }), std::as_writable_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        printf("Error 0x%02x during I2c read with INA226 0x%02x\r\n", (uint8_t)transfer_result, address_);
    }
    return uint16_t((buffer[0] << 8) + buffer[1]);
}

void Ina226::write_reg(uint8_t reg, uint16_t data) {
    std::array<uint8_t, 3> buffer { reg, static_cast<uint8_t>(data >> 8), static_cast<uint8_t>(data) };
    periphs::i2c::I2cError transfer_result = i2c_.send_bytes(address_, std::as_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        printf("Error 0x%02x during I2c write with INA226 0x%02x\r\n", (uint8_t)transfer_result, address_);
    }
}

} // namespace stm::drivers::ina226
