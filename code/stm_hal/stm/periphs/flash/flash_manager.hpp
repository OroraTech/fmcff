/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/rcc/clock_manager.hpp"

// NOLINTBEGIN(readability-magic-numbers) the magic numbers here are just datasheet values. Putting them into const does not make it more readable IMHO.
namespace stm::periphs::flash {
class FlashManager {
public:
    static inline void set_latency(uint32_t latency) {
        using namespace stm::regs::flash::ACR;
        do {
            __PERIPHERAL_FLASH__.ACR.set(LATENCY(latency));
        } while (__PERIPHERAL_FLASH__.ACR.read<LATENCY>() != latency);
    }

private:
    static constexpr auto GET_MIN_LATENCY = [](uint32_t freq) {
        switch (rcc::VCORERangeManager::VOLTAGE_RANGE) {
        case 1:
            if (freq <= 16'000'000) {
                return 0;
            } else if (freq <= 32'000'000) {
                return 1;
            } else if (freq <= 48'000'000) {
                return 2;
            } else if (freq <= 64'000'000) {
                return 3;
            } else {
                return 4;
            }
        case 2:
            if (freq <= 6'000'000) {
                return 0;
            } else if (freq <= 12'000'000) {
                return 1;
            } else if (freq <= 18'000'000) {
                return 2;
            } else {
                return 3;
            }
        default:
            __builtin_trap();
        }
    };

    static constexpr uint32_t MIN_LATENCY_MSI = GET_MIN_LATENCY(rcc::MSI::FREQ);
    static constexpr uint32_t MIN_LATENCY_SYSCLK = GET_MIN_LATENCY(rcc::HCLK::FREQ);

public:
    static inline void init_latency_pre_msi_init() {
        if constexpr (MIN_LATENCY_MSI > 0) {
            set_latency(MIN_LATENCY_MSI);
        }
    }
    static inline void init_latency_pre_syscl_kswitch() {
        if constexpr (MIN_LATENCY_SYSCLK > MIN_LATENCY_MSI) {
            set_latency(MIN_LATENCY_SYSCLK);
        }
    }
    static void init_latency_post_syscl_kswitch() {
        if constexpr (MIN_LATENCY_SYSCLK < MIN_LATENCY_MSI) {
            set_latency(MIN_LATENCY_SYSCLK);
        }
    }
    static inline void init_cache() {
        using namespace stm::regs::flash::ACR;
        __PERIPHERAL_FLASH__.ACR.set(PRFTEN(1), ICEN(1), DCEN(1));
    }
};

} // namespace stm::periphs::flash
// NOLINTEND(readability-magic-numbers)
