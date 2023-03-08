/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::iwdg {
using namespace stm::register_access;

namespace KR {
    using KEY = RegSubValue<0, 16>;

    constexpr uint32_t KEY_START = 0xCCCC;
    constexpr uint32_t KEY_RELOAD = 0xAAAA;
    constexpr uint32_t KEY_UNLOCK = 0x5555;
}

namespace PR {
    using PR = RegSubValue<0, 3>;

    constexpr PR PR_DIV_4 = PR(0);
    constexpr PR PR_DIV_8 = PR(1);
    constexpr PR PR_DIV_16 = PR(2);
    constexpr PR PR_DIV_32 = PR(3);
    constexpr PR PR_DIV_64 = PR(4);
    constexpr PR PR_DIV_128 = PR(5);
    constexpr PR PR_DIV_256 = PR(6);
    // 7 is also /256
} // namespace PR

namespace RLR {
    using RL = RegSubValue<0, 12>;

    constexpr uint32_t RL_MAX = 0xFFF;
}

namespace SR {
    using PVU = RegSubValue<0>;
    using RVU = RegSubValue<1>;
    using WVU = RegSubValue<2>;
}

namespace WINR {
    using WIN = RegSubValue<0, 12>;
}

struct IWDGStruct {
    Register KR;
    Register PR;
    Register RLR;
    Register SR;
    Register WINR;

    uint8_t padding[0x3ec];
};

static_assert(sizeof(IWDGStruct) == 0x400); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::iwdg
