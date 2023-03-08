/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::dbgmcu {
using namespace stm::register_access;

namespace CR {
    using DBG_SLEEP = RegSubValue<0>;
    using DBG_STOP = RegSubValue<1>;
    using DBG_STANDBY = RegSubValue<2>;
    using TRACE_IOEN = RegSubValue<5>;
    using TRACE_MODE = RegSubValue<6>;
}

struct DBGMCUStruct {
    Register CR;
    Register APB1FZR1;
    Register APB1FZR2;
    Register APB2FZR;
};
static_assert(sizeof(DBGMCUStruct) == 0x10); // NOLINT(readability-magic-numbers)
} // namespace stm::regs::dbgmcu
