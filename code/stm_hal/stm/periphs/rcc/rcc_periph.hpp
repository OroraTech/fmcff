/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstdint>

namespace stm::periphs::rcc {

/**
 * @brief type for all of the clock domains in which clocks can be enabled/disabled
 */
enum class RccClockDomain {
    AHB1,
    AHB2,
    AHB3,
    APB1_1,
    APB1_2,
    APB2,
};

struct RccPeriph {
    RccClockDomain domain;
    uint8_t offset;
};

void enable_rcc_periph(const RccPeriph& periph);

} // namespace stm::periphs::rcc
