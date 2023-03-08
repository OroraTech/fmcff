/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "rcc_config.hpp"
#include "stm/regs/peripherals.hpp"

// NOLINTBEGIN(readability-magic-numbers) all the magic numbers here are just datasheet values. Putting them into const does not make it more readable IMHO.
namespace stm::periphs::rcc {
using namespace stm::regs::rcc;
using namespace stm::regs::pwr;

class VCORERangeManager {
public:
    static constexpr uint32_t VOLTAGE_RANGE = VCORERangeConfig::VOLTAGE_RANGE;
    static_assert(VOLTAGE_RANGE == 1 || VOLTAGE_RANGE == 2);

    static constexpr uint32_t MAX_MSI_FREQ = (VOLTAGE_RANGE == 1) ? 48'000'000 : 24'000'000;
    static constexpr uint32_t MAX_HSE_FREQ = (VOLTAGE_RANGE == 1) ? 48'000'000 : 26'000'000;
    static constexpr uint32_t MAX_PLL_FREQ = (VOLTAGE_RANGE == 1) ? 80'000'000 : 26'000'000;
    static constexpr uint32_t MAX_PLLVCO_FREQ = (VOLTAGE_RANGE == 1) ? 344'000'000 : 128'000'000;

    static inline void init() {
        __PERIPHERAL_PWR__.CR1.set(CR1::VOS(VOLTAGE_RANGE));
    }
};

class LSE {
public:
    static constexpr bool ENABLE = LSEConfig::ENABLE;
    static constexpr uint32_t FREQ = ENABLE ? 32'768 : 0;

    static inline bool is_ready() { return __PERIPHERAL_RCC__.BDCR.read<BDCR::LSERDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
};

class MSI {
private:
    static constexpr uint8_t RANGE = MSIConfig::RANGE;
    static constexpr bool USE_PLL_MODE = MSIConfig::USE_PLL_MODE;

    static constexpr uint32_t FREQ_RANGE_TABLE[12] = {
        100'000UL,
        200'000UL,
        400'000UL,
        800'000UL,
        1'000'000UL,
        2'000'000UL,
        4'000'000UL,
        8'000'000UL,
        16'000'000UL,
        24'000'000UL,
        32'000'000UL,
        48'000'000UL,
    };

    static_assert(RANGE < sizeof(FREQ_RANGE_TABLE));

public:
    static constexpr bool ENABLE = MSIConfig::ENABLE;

    static constexpr uint32_t FREQ = ENABLE ? FREQ_RANGE_TABLE[RANGE] : 0;
    static_assert(!ENABLE || (FREQ <= VCORERangeManager::MAX_MSI_FREQ));

    static_assert(!USE_PLL_MODE || LSE::ENABLE);

    static inline bool is_ready() { return __PERIPHERAL_RCC__.CR.read<CR::MSIRDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
    static void disable_clock();
};

class HSE {
public:
    static constexpr bool ENABLE = HSEConfig::ENABLE;
    static constexpr uint32_t FREQ = ENABLE ? HSEConfig::FREQ : 0;

    static_assert(!ENABLE || (FREQ <= VCORERangeManager::MAX_HSE_FREQ));

    static inline bool is_ready() { return __PERIPHERAL_RCC__.CR.read<CR::HSERDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
};

class HSI16 {
public:
    static constexpr bool ENABLE = HSI16Config::ENABLE;
    static constexpr uint32_t FREQ = ENABLE ? 16'000'000UL : 0;

    static inline bool is_ready() { return __PERIPHERAL_RCC__.CR.read<CR::HSIRDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
};

class PLL {
private:
    static void set_main_parameters();
    static void init_outputs();

public:
    static constexpr bool ENABLE = PLLConfig::ENABLE;
    static constexpr PLLSource SOURCE = PLLConfig::SOURCE;
    static constexpr uint32_t PLLM_CONFIG = PLLConfig::PLLM;
    static constexpr uint32_t PLLN_CONFIG = PLLConfig::PLLN;

    static constexpr bool ENABLE_PLLSAI3CLK = PLLConfig::ENABLE_PLLSAI3CLK;
    static constexpr uint32_t PLLP_REG_VALUE = PLLConfig::PLLP_REG_VALUE;
    static constexpr uint32_t PLLPDIV_CONFIG = PLLConfig::PLLPDIV;

    static constexpr bool ENABLE_PLL48M1CLK = PLLConfig::ENABLE_PLL48M1CLK;
    static constexpr uint32_t PLLQ_REG_VALUE = PLLConfig::PLLQ_REG_VALUE;

    static constexpr bool ENABLE_PLLCLK = PLLConfig::ENABLE_PLLCLK;
    static constexpr uint32_t PLLR_REG_VALUE = PLLConfig::PLLR_REG_VALUE;

    static constexpr uint32_t INPUT_FREQ = [] {
        switch (SOURCE) {
        case PLLSource::MSI:
            return MSI::FREQ;
        case PLLSource::HSI16:
            return HSI16::FREQ;
        case PLLSource::HSE:
            return HSE::FREQ;
        default:
            return uint32_t(0);
        }
    }();
    static_assert(!ENABLE || (INPUT_FREQ > 0));

    static constexpr uint32_t PLLM_REG_VALUE = PLLM_CONFIG - 1;
    static_assert(1 <= PLLM_CONFIG && PLLM_CONFIG <= 8);
    static constexpr uint32_t VCO_INPUT_FREQ = INPUT_FREQ / PLLM_CONFIG;
    static_assert(!ENABLE || (4'000'000UL <= VCO_INPUT_FREQ && VCO_INPUT_FREQ <= 16'000'000UL));

    static_assert((8 <= PLLN_CONFIG && PLLN_CONFIG <= 86));
    static constexpr uint32_t VCO_OUTPUT_FREQ = VCO_INPUT_FREQ * PLLN_CONFIG;
    static_assert(!ENABLE || (64'000'000UL <= VCO_OUTPUT_FREQ && VCO_OUTPUT_FREQ <= VCORERangeManager::MAX_PLLVCO_FREQ));

    static_assert(ENABLE || !ENABLE_PLLSAI3CLK);
    static constexpr uint32_t PLLP_TABLE[2] = {
        7,
        17
    };
    static_assert(PLLP_REG_VALUE < sizeof(PLLP_TABLE));
    static constexpr uint32_t PLLP_VALUE = PLLP_TABLE[PLLP_REG_VALUE];

    static_assert(PLLPDIV_CONFIG == 0 || (PLLPDIV_CONFIG >= 2 && PLLPDIV_CONFIG <= 31));
    static constexpr uint32_t PLLSAI3CLKDIV = PLLPDIV_CONFIG != 0U ? PLLPDIV_CONFIG : PLLP_VALUE;
    static constexpr uint32_t FREQ_PLLSAI3CLK = ENABLE_PLLSAI3CLK ? VCO_OUTPUT_FREQ / PLLSAI3CLKDIV : 0;
    static_assert(!ENABLE_PLLSAI3CLK || FREQ_PLLSAI3CLK <= VCORERangeManager::MAX_PLL_FREQ);

    static_assert(ENABLE || !ENABLE_PLL48M1CLK);
    static constexpr uint32_t PLLQ_TABLE[4] = {
        2,
        4,
        6,
        8
    };
    static_assert(PLLQ_REG_VALUE < sizeof(PLLQ_TABLE));
    static constexpr uint32_t PLLQ_VALUE = PLLQ_TABLE[PLLQ_REG_VALUE];
    static constexpr uint32_t FREQ_PLL48M1CLK = ENABLE_PLL48M1CLK ? VCO_OUTPUT_FREQ / PLLQ_VALUE : 0;
    static_assert(!ENABLE_PLL48M1CLK || FREQ_PLL48M1CLK <= VCORERangeManager::MAX_PLL_FREQ);

    static_assert(ENABLE || !ENABLE_PLLCLK);
    static constexpr uint32_t PLLR_TABLE[4] = {
        2,
        4,
        6,
        8
    };
    static_assert(PLLR_REG_VALUE < sizeof(PLLR_TABLE));
    static constexpr uint32_t PLLR_VALUE = PLLR_TABLE[PLLR_REG_VALUE];

    static constexpr uint32_t FREQ_PLLCLK = VCO_OUTPUT_FREQ / PLLR_VALUE;
    static_assert(!ENABLE_PLLCLK || FREQ_PLLCLK <= VCORERangeManager::MAX_PLL_FREQ);

    static inline bool is_ready() { return __PERIPHERAL_RCC__.CR.read<CR::PLLRDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
};

class LSI {
public:
    static constexpr bool ENABLE = LSIConfig::ENABLE;
    static constexpr uint32_t FREQ = ENABLE ? 32'000UL : 0;

    static inline bool is_ready() { return __PERIPHERAL_RCC__.CSR.read<CSR::LSIRDY>() != 0U; }
    static void wait_until_ready() {
        while (!is_ready()) {
            ;
        }
    }
    static void init_clock();
};

class SYSCLK {
public:
    static constexpr SYSCLKSource SOURCE = SYSCLKConfig::SOURCE;

    static constexpr uint32_t FREQ = [] {
        switch (SOURCE) {
        case SYSCLKSource::MSI:
            return MSI::FREQ;
        case SYSCLKSource::HSI16:
            return HSI16::FREQ;
        case SYSCLKSource::HSE:
            return HSE::FREQ;
        case SYSCLKSource::PLL:
            return PLL::FREQ_PLLCLK;
        default:
            return uint32_t(0);
        }
    }();
    static_assert(FREQ > 0);

    static void init_source();
};

class HCLK {
private:
    static constexpr uint32_t HPRE_TABLE[16] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        2,
        4,
        8,
        16,
        64,
        128,
        256,
        512
    };

public:
    static constexpr uint32_t HPRE_CONFIG = BusClockConfig::HPRE;
    static_assert(HPRE_CONFIG < sizeof(HPRE_TABLE));
    static constexpr uint32_t AHB_PRESC = HPRE_TABLE[HPRE_CONFIG];
    static constexpr uint32_t FREQ = SYSCLK::FREQ / AHB_PRESC;
};

class PCLK {
    static constexpr uint32_t PPRE_TABLE[8] = {
        1, 1, 1, 1,
        2,
        4,
        8,
        16
    };

public:
    static constexpr uint32_t PPRE1_CONFIG = BusClockConfig::PPRE1;
    static constexpr uint32_t PPRE2_CONFIG = BusClockConfig::PPRE2;
    static_assert(PPRE1_CONFIG < sizeof(PPRE_TABLE));

    static constexpr uint32_t FREQ1 = HCLK::FREQ / PPRE_TABLE[PPRE1_CONFIG];
    static constexpr uint32_t FREQ2 = HCLK::FREQ / PPRE_TABLE[PPRE2_CONFIG];
};

class BusClockManager {
public:
    static void init_prescalers();
};

class ClockManager {
private:
    static void init_clock_sources();
    static void init_sys_clock();
    static void wait_until_all_clocks_ready();

public:
    static void init_clocks();
    static void reset_clocks();
};

} // namespace stm::periphs::rcc
// NOLINTEND(readability-magic-numbers)
