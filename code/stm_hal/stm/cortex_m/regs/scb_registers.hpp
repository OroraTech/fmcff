/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::scb {
using namespace stm::register_access;

namespace ICSR {
    using VECTACTIVE = RegSubValue<0, 9>;
    using RETTOBASE = RegSubValue<11>;
    using VECTPENDING = RegSubValue<12, 9>;
    using ISRPENDING = RegSubValue<22>;
    using ISRPREEMPT = RegSubValue<23>;
    using PENDSTCLR = RegSubValue<25>;
    using PENDSTSET = RegSubValue<26>;
    using PENDSVCLR = RegSubValue<27>;
    using PENDSVSET = RegSubValue<28>;
    using NMIPENDSET = RegSubValue<31>;
} // namespace ICSR

namespace AIRCR {
    using VECTRESET = RegSubValue<0>;
    using VECTCLRACTIVE = RegSubValue<1>;
    using SYSRESETREQ = RegSubValue<2>;
    using PRIGROUP = RegSubValue<8, 3>;
    using ENDIANNESS = RegSubValue<15>;
    using VECTKEY = RegSubValue<16, 16>;

    constexpr uint32_t VECTKEY_WRITEVALUE = 0x05FA;
}

namespace CPACR {
    using CP10 = RegSubValue<20, 2>;
    using CP11 = RegSubValue<22, 2>;
}

struct SCBStruct {
    Register CPUID;
    Register ICSR;
    Register VTOR;
    Register AIRCR;
    Register SCR;
    Register CCR;
    Register8 SHPR[12];
    Register SHCSR;
    Register CFSR;
    Register HFSR;
    Register DFSR;
    Register MMFAR;
    Register BFAR;
    Register AFSR;
    ReservedWord RESERVED0[0x12];
    Register CPACR;
    ReservedWord RESERVED1;
};

static_assert(sizeof(SCBStruct) == 0x90);

} // namespace stm::regs::scb
