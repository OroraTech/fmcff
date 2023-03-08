/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::systick {
using namespace stm::register_access;

namespace CSR {
    using ENABLE = RegSubValue<0>;
    using TICKINT = RegSubValue<1>;
    using CLKSOURCE = RegSubValue<2>;
    using COUNTFLAG = RegSubValue<16>;
}

struct SYSTICKStruct {
    Register CSR;
    Register RVR;
    Register CVR;
    Register CALIB;
};

static_assert(sizeof(SYSTICKStruct) == 0x10);

} // namespace stm::regs::systick
