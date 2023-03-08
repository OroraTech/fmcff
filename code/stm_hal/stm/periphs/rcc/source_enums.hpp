/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

namespace stm::periphs::rcc {
enum class SYSCLKSource {
    MSI = 0,
    HSI16,
    HSE,
    PLL
};

enum class PLLSource {
    NONE = 0,
    MSI,
    HSI16,
    HSE
};

enum class RTCSource {
    NONE = 0,
    LSE,
    LSI,
    HSE,
};

enum class MCOPrescaler {
    DIV_1 = 0b000,
    DIV_2 = 0b001,
    DIV_4 = 0b010,
    DIV_8 = 0b011,
    DIV_16 = 0b100
};

enum class MCOSelection {
    DISABLED = 0,
    SYSCLK = 1,
    MSI = 2,
    HSI16 = 3,
    HSE = 4,
    PLL = 5,
    LSI = 6,
    LSE = 7,
    HSI48 = 8
};
} // namespace stm::periphs::rcc
