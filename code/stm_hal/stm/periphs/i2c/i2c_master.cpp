/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/periphs/i2c/i2c_master.hpp"
#include "generic/abort.hpp"
#include "stm/regs/peripherals.hpp"
#include <bit>

namespace stm::periphs::i2c {

I2cMaster::I2cMaster(I2cConfig config, uint32_t timing_reg_value) :
    i2c_ { config.i2c.periph } {
    using namespace regs::i2c::CR1;
    rcc::enable_rcc_periph(config.i2c.rcc_periph);

    i2c_.TIMINGR.write(timing_reg_value);
    i2c_.CR1.write(PE(1));
}

I2cError I2cMaster::transfer(uint8_t addr, std::span<const std::byte> tx_data, std::span<std::byte> rx_data, support::Timeout<> timeout) {
    I2cError write_error = send_bytes(addr, tx_data, false, timeout);
    if (write_error != I2cError::SUCCESS) {
        return write_error;
    }
    return recv_bytes(addr, rx_data, timeout);
}

void I2cMaster::end_transfer(support::Timeout<> timeout) {
    using namespace regs::i2c::ICR;
    using namespace regs::i2c::ISR;
    using namespace regs::i2c::CR2;
    i2c_.CR2.write(STOP(1));
    while (i2c_.ISR.read<STOPF>() == 0 && !timeout.has_passed()) {}
    i2c_.ICR.write(STOPCF(1));
    i2c_.CR2.write(0UL);
}

I2cError I2cMaster::send_bytes(uint8_t addr, std::span<const std::byte> tx_data, bool stop_after_transfer, support::Timeout<> timeout) {
    using namespace regs::i2c::ISR;
    using namespace regs::i2c::ICR;
    using namespace regs::i2c::CR2;

    constexpr size_t MAX_SUPPORTED_TX_SIZE = 255;
    if (tx_data.size() > MAX_SUPPORTED_TX_SIZE) {
        return I2cError::NOT_SUPPORTED;
    }
    i2c_.CR2.write(SADD_7(addr), START(1), NBYTES(tx_data.size()), AUTOEND(stop_after_transfer ? 1 : 0));
    size_t tx_index = 0;
    do {
        register_access::RegisterCopy isr { i2c_.ISR.read() };
        if (isr.read<NACKF>() != 0) {
            i2c_.ICR.write(NACKF(1));
            end_transfer(timeout);
            return I2cError::NACK;
        }
        if (isr.read<BERR>() != 0) {
            i2c_.ICR.write(BERRCF(1));
            end_transfer(timeout);
            return I2cError::BUS_ERROR;
        }
        if (isr.read<ARLO>() != 0) {
            i2c_.ICR.write(ARLOCF(1));
            end_transfer(timeout);
            return I2cError::ARBITRATION_LOSS;
        }
        if (isr.read<TXIS>() != 0) {
            if (tx_index >= tx_data.size()) { // this should never happen because the hardware handles the correct amount of bytes to be sent
                end_transfer(timeout);
                return I2cError::UNKOWN;
            }
            i2c_.TXDR.write(std::to_integer<uint32_t>(tx_data[tx_index++]));
        }
        if (stop_after_transfer) {
            if (isr.read<STOPF>() != 0) {
                i2c_.ICR.write(STOPCF(1));
                i2c_.CR2.write(0UL);
                break;
            }
        } else {
            if (isr.read<TC>() != 0) {
                break;
            }
        }
        if (timeout.has_passed()) {
            end_transfer(timeout);
            return I2cError::TIMEOUT;
        }
    } while (true);
    return I2cError::SUCCESS;
}

I2cError I2cMaster::recv_bytes(uint8_t addr, std::span<std::byte> rx_data, support::Timeout<> timeout) {
    using namespace regs::i2c::ISR;
    using namespace regs::i2c::ICR;
    using namespace regs::i2c::CR2;

    constexpr size_t MAX_SUPPORTED_RX_SIZE = 255;
    if (rx_data.size() > MAX_SUPPORTED_RX_SIZE) {
        return I2cError::NOT_SUPPORTED;
    }
    i2c_.CR2.write(SADD_7(addr), RD_WRN(1), AUTOEND(1), START(1), NBYTES(rx_data.size()));

    size_t rx_index = 0;
    do {
        register_access::RegisterCopy isr { i2c_.ISR.read() };
        if (isr.read<NACKF>() != 0) {
            i2c_.ICR.write(NACKCF(1));
            end_transfer(timeout);
            return I2cError::NACK;
        }
        if (isr.read<BERR>() != 0) {
            i2c_.ICR.write(BERRCF(1));
            end_transfer(timeout);
            return I2cError::BUS_ERROR;
        }
        if (isr.read<ARLO>() != 0) {
            i2c_.ICR.write(ARLOCF(1));
            end_transfer(timeout);
            return I2cError::ARBITRATION_LOSS;
        }
        if (isr.read<RXNE>() != 0) {
            if (rx_index >= rx_data.size()) { // this should never happen because the hardware handles the correct amount of bytes to be sent
                end_transfer(timeout);
                return I2cError::UNKOWN;
            }
            rx_data[rx_index++] = std::byte { (uint8_t)i2c_.RXDR.read() };
        }
        if (isr.read<STOPF>() != 0) {
            i2c_.ICR.write(STOPCF(1));
            break;
        }
        if (timeout.has_passed()) {
            end_transfer(timeout);
            return I2cError::TIMEOUT;
        }
    } while (true);
    i2c_.CR2.write(0UL);
    return I2cError::SUCCESS;
}

} // namespace stm::periphs::i2c
