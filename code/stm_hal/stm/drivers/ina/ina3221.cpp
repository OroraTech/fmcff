/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "ina3221.hpp"
#include "logging/logging.hpp"
#include <array>
#include <span>

namespace stm::drivers::ina3221 {

Ina3221::Ina3221(periphs::i2c::I2cMaster& i2c, uint8_t address, Ina3221Config config, float shunt_resistance_ohms) :
    i2c_ { i2c }, address_ { address }, shunt_resistance_ohms_ { shunt_resistance_ohms } {
    if (!check_id()) {
        ot::logging::log().error(ot::logging::ALL, "Error while reading the ID of INA3221 %02x", address);
        return;
    }
    apply_config(config);
}

float Ina3221::get_current_amps(int channel) {
    return get_shunt_voltage_volts(channel) / shunt_resistance_ohms_;
}

float Ina3221::get_bus_voltage_volts(int channel) {
    constexpr float BUS_VOLTAGE_SCALING = 1.0F / 1'000.0F; // Datasheet 8.6.2.3
    int reg = BUS_VOLTAGE_REG(channel);
    if (reg == -1) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    auto bus_voltage_register = int16_t(read_reg(uint8_t(reg)));
    return static_cast<float>(bus_voltage_register) * BUS_VOLTAGE_SCALING;
}
float Ina3221::get_shunt_voltage_volts(int channel) {
    constexpr float SHUNT_VOLTAGE_SCALING = 5.0F / 1'000'000.0F; // Datasheet 8.6.2.4
    int reg = SHUNT_VOLTAGE_REG(channel);
    if (reg == -1) {
        return std::numeric_limits<float>::quiet_NaN();
    }
    auto shunt_voltage_register = int16_t(read_reg(uint8_t(reg)));
    return static_cast<float>(shunt_voltage_register) * SHUNT_VOLTAGE_SCALING;
}

bool Ina3221::check_id() {
    constexpr uint16_t EXPECTED_MANUFACTURER_ID = 0x5449;
    constexpr uint16_t EXPECTED_DIE_ID = 0x3220;
    uint16_t manufacturer_id_value = read_reg(MANUFACTURER_ID_REG);
    uint16_t die_id_value = read_reg(DIE_ID_REG);
    return manufacturer_id_value == EXPECTED_MANUFACTURER_ID && die_id_value == EXPECTED_DIE_ID;
}

void Ina3221::apply_config(const Ina3221Config& config) {
    write_reg(CONFIGURATION_REG, config.to_register_value());
}

uint16_t Ina3221::read_reg(uint8_t reg) {
    std::array<uint8_t, 2> buffer {};
    periphs::i2c::I2cError transfer_result = i2c_.transfer(address_, std::as_bytes(std::span { &reg, 1 }), std::as_writable_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        ot::logging::log().error(ot::logging::ALL, "Error 0x%02x during I2c read with INA226 0x%02x", (uint8_t)transfer_result, address_);
    }
    return uint16_t((buffer[0] << 8) + buffer[1]);
}

void Ina3221::write_reg(uint8_t reg, uint16_t data) {
    // Note: the way to write a register is correctly documented in text in chapter 8.5.2 in the datasheet, but incorrectly in figure 28
    std::array<uint8_t, 3> buffer { reg, static_cast<uint8_t>(data >> 8), static_cast<uint8_t>(data) };
    periphs::i2c::I2cError transfer_result = i2c_.send_bytes(address_, std::as_bytes(std::span { buffer }));
    if (transfer_result != periphs::i2c::I2cError::SUCCESS) {
        ot::logging::log().error(ot::logging::ALL, "Error 0x%02x during I2c write with INA226 0x%02x", (uint8_t)transfer_result, address_);
    }
}

} // namespace stm::drivers::ina3221
