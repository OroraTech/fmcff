/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::nvic {
using namespace stm::register_access;

namespace IPR {
    using PRIO = RegSubValue8<4, 4>;
}

struct NVICStruct {
    Register ISER[16];
    ReservedWord RESERVED0[0x10];
    Register ICER[16];
    ReservedWord RESERVED1[0x10];
    Register ISPR[16];
    ReservedWord RESERVED2[0x10];
    Register ICPR[16];
    ReservedWord RESERVED3[0x10];
    Register IABR[16];
    ReservedWord RESERVED4[0x30];
    Register8 IPR[496];
    ReservedWord RESERVED5[0x1c4];
};

static_assert(sizeof(NVICStruct) == 0xC00);

} // namespace stm::regs::nvic
