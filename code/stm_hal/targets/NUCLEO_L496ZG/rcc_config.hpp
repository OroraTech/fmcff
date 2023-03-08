/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/rcc/source_enums.hpp"
#include <cstdint>

// Note: currently there is no support for the SMPS voltage ranges
// See sections 5.1.8 and 6.2.9 in the STM32L496 reference Manual

namespace stm {
class VCORERangeConfig {
public:
    static constexpr uint32_t VOLTAGE_RANGE = 1;
};

class LSEConfig {
public:
    static constexpr bool ENABLE = false;
};

class MSIConfig {
public:
    static constexpr bool ENABLE = true;
    static constexpr uint8_t RANGE = 6;
    static constexpr bool USE_PLL_MODE = false;
};

class HSI16Config {
public:
    static constexpr bool ENABLE = false;
};

class HSEConfig {
public:
    static constexpr bool ENABLE = false;
    static constexpr uint32_t FREQ = 8'000'000;
};

class PLLConfig {
public:
    static constexpr bool ENABLE = true;
    static constexpr periphs::rcc::PLLSource SOURCE = periphs::rcc::PLLSource::MSI;
    static constexpr uint32_t PLLM = 1;
    static constexpr uint32_t PLLN = 40;

    static constexpr bool ENABLE_PLLSAI3CLK = false;
    static constexpr uint32_t PLLP_REG_VALUE = 0;
    static constexpr uint32_t PLLPDIV = 0;

    static constexpr bool ENABLE_PLL48M1CLK = false;
    static constexpr uint32_t PLLQ_REG_VALUE = 0;

    static constexpr bool ENABLE_PLLCLK = true;
    static constexpr uint32_t PLLR_REG_VALUE = 0;
};

class LSIConfig {
public:
    static constexpr bool ENABLE = true;
};

class SYSCLKConfig {
public:
    static constexpr periphs::rcc::SYSCLKSource SOURCE = periphs::rcc::SYSCLKSource::PLL;
};

class BusClockConfig {
public:
    static constexpr uint32_t HPRE = 0;
    static constexpr uint32_t PPRE1 = 0;
    static constexpr uint32_t PPRE2 = 0;
};
} // namespace stm
