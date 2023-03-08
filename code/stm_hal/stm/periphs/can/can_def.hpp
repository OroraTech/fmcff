/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/can/timing_config.hpp"
#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/regs/can_registers.hpp"
#include <cstdint>

namespace stm::periphs::can {
struct CanDef {
    rcc::RccPeriph rcc_periph {};
    regs::can::CANStruct& periph;
    regs::can::FilterBank (&filter_banks)[14];
    uint8_t irq_n {};
    uint32_t input_clock {};
    TimingConfig timing_config {};

    [[nodiscard]] constexpr uint32_t get_max_baudrate() const {
        return input_clock / timing_config.get_bit_time();
    }
};
} // namespace stm::periphs::can
