/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::syscfg {
using namespace stm::register_access;

struct SYSCFGStruct {
    Register MEMRMP;
    Register CFGR1;
    Register EXTICR[4];
    Register SCSR;
    Register CFGR2;
    Register SWPR;
    Register SKR;
    Register SWPR2;
};
static_assert(sizeof(SYSCFGStruct) == 0x2C); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::syscfg
