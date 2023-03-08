/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/gpio/i2c_pin_configs.hpp"
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/i2c/i2c_config.hpp"
#include "stm/periphs/i2c/i2c_timings.hpp"
#include "stm/regs/i2c_registers.hpp"
#include "stm/support/clock.hpp"
#include <chrono>
#include <span>

namespace stm::periphs::i2c {

enum class I2cError : uint8_t {
    SUCCESS = 0,
    BUS_ERROR,        // No idea when this can happen, look into the stm32l4 reference manual if you get this
    ARBITRATION_LOSS, // Another master transmits at the same time and uses an id with a higher priority
    TIMEOUT,          // transfer took too long and was aborted. Usually a hardware error(e.g. missing pull-ups)
    NACK,             // transfer was not acknowledged by the slave
    NOT_SUPPORTED,    // generic error for things not supported by the I2cMaster class. See warnings for the individual functions
    UNKOWN            // If you get this, only god, satan or gdb can help you.
};

using namespace std::literals::chrono_literals;
class I2cMaster {
public:
    template <I2cConfig CONFIG>
    static I2cMaster init();

    /**
     * @brief do a transaction with a start condition, transmit the address and tx data, do a restart condition, read data into the rx buffer and then stop the transfer
     *
     * @param addr I2C address of the slave
     * @param tx_data span containing the data to be written
     * @param rx_data span pointing to the buffer into which data should be read
     * @param timeout maximum time the transfer is allowed to take
     *
     * @warning currently tx_data and rx_data must be no larger than 255 bytes or you will get a NOT_SUPPORTED error
     */
    I2cError transfer(uint8_t addr, std::span<const std::byte> tx_data, std::span<std::byte> rx_data, support::Timeout<> timeout = support::Timeout<> { DEFAULT_I2C_TIMEOUT });
    /**
     * @brief do a transaction with a start condition, transmit the address and tx data and then stop the transfer
     *
     * @param addr I2C address of the slave
     * @param tx_data span containing the data to be written
     * @param timeout maximum time the transfer is allowed to take
     *
     * @warning currently tx_data must be no larger than 255 bytes or you will get a NOT_SUPPORTED error
     */
    I2cError send_bytes(uint8_t addr, std::span<const std::byte> tx_data, bool stop_after_transfer = true, support::Timeout<> timeout = support::Timeout<> { DEFAULT_I2C_TIMEOUT });
    /**
     * @brief do a transaction with a start condition, transmit the address and read data into the rx buffer then stop the transfer
     *
     * @param addr I2C address of the slave
     * @param rx_data span pointing to the buffer into which data should be read
     * @param timeout maximum time the transfer is allowed to take
     *
     * @warning currently and rx_data must be no larger than 255 bytes or you will get a NOT_SUPPORTED error
     */
    I2cError recv_bytes(uint8_t addr, std::span<std::byte> rx_data, support::Timeout<> timeout = support::Timeout<> { DEFAULT_I2C_TIMEOUT });

private:
    static constexpr std::chrono::nanoseconds DEFAULT_I2C_TIMEOUT = 5ms; ///<< timeout for a single read or write transaction

    void configure_timing(uint32_t speed);
    void end_transfer(support::Timeout<> timeout);

    explicit I2cMaster(I2cConfig config, uint32_t timing_reg_value);
    regs::i2c::I2CStruct& i2c_;
};

template <I2cConfig CONFIG>
I2cMaster I2cMaster::init() {
    constexpr gpio::PinConfig SCL_CONFIG = gpio::I2C_PIN_CONFIG<CONFIG.i2c, CONFIG.scl, gpio::I2cPinFunction::SCL>;
    gpio::apply_pin_config(SCL_CONFIG);
    constexpr gpio::PinConfig SDA_CONFIG = gpio::I2C_PIN_CONFIG<CONFIG.i2c, CONFIG.sda, gpio::I2cPinFunction::SDA>;
    gpio::apply_pin_config(SDA_CONFIG);
    return I2cMaster(CONFIG, I2C_TIMING_REG_VALUE<CONFIG.i2c.input_clock, CONFIG.baudrate>);
}
} // namespace stm::periphs::i2c
