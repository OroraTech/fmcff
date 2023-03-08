/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/can/can_def.hpp"
#include "stm/periphs/rcc/clock_manager.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::can {

constexpr can::CanDef CAN1DEF {
    .rcc_periph = rcc::CAN1_PERIPH,
    .periph = __PERIPHERAL_CAN1__,
    .filter_banks = __PERIPHERAL_CAN1__.filterBanks[0],
    .irq_n = 19,
    .input_clock = rcc::PCLK::FREQ1,
};

constexpr can::CanDef CAN2DEF {
    .rcc_periph = rcc::CAN2_PERIPH,
    .periph = __PERIPHERAL_CAN2__,
    .filter_banks = __PERIPHERAL_CAN1__.filterBanks[1],
    .irq_n = 86,
    .input_clock = rcc::PCLK::FREQ1,
};

} // namespace stm::periphs::can
