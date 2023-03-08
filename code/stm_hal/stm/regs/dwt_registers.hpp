/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::dwt {
using namespace stm::register_access;

namespace DWT_CTRL {
    using CYCCNTENA = RegSubValue<0>;
    using POSTPRESET = RegSubValue<1, 4>;
    using POSTINIT = RegSubValue<5, 4>;
    using CYCTAP = RegSubValue<9>;
    using SYNCTAP = RegSubValue<10, 2>;
    using PCSAMPLENA = RegSubValue<12>;
    using EXCTRCENA = RegSubValue<16>;
    using CPIEVTENA = RegSubValue<17>;
    using EXCEVTENA = RegSubValue<18>;
    using SLEEPEVTENA = RegSubValue<19>;
    using LSUEVTENA = RegSubValue<20>;
    using FOLDEVTENA = RegSubValue<21>;
    using CYCEVTENA = RegSubValue<22>;
    using NOPRFCNT = RegSubValue<24>;
    using NOCYCCNT = RegSubValue<25>;
    using NOEXTTRIG = RegSubValue<26>;
    using NOTRCPKT = RegSubValue<27>;
    using NUMCOMP = RegSubValue<28, 4>;
} // namespace DWT_CR

namespace DWT_CYCCNT {
    using CYCCNT = RegSubValue<0, 8>;
} // namespace DWT_CPICNT

namespace DWT_CPICNT {
    using CPICNT = RegSubValue<0, 8>;
} // namespace DWT_CPICNT

namespace DWT_EXCCNT {
    using EXCCNT = RegSubValue<0, 8>;
} // namespace DWT_EXCCNT

namespace DWT_SLEEPCNT {
    using SLEEPCNT = RegSubValue<0, 8>;
} // namespace DWT_SLEEPCNT

namespace DWT_LSUCNT {
    using LSUCNT = RegSubValue<0, 8>;
} // namespace DWT_LSUCNT

namespace DWT_FOLDCNT {
    using FOLDCNT = RegSubValue<0, 8>;
} // namespace DWT_FOLDCNT

namespace DWT_MASK {
    using MASK = RegSubValue<0, 8>;
} // namespace DWT_MASK

namespace DWT_FUNCTION {
    using FUNCTION = RegSubValue<0, 8>;
} // namespace DWT_FUNCTION

struct DWTStruct {
    Register CTRL;
    Register CYCCNT;
    Register CPICNT;
    Register EXCCNT;
    Register SLEEPCNT;
    Register LSUCNT;
    Register FOLDCNT;
    Register PCSR;
    Register COMP0;
    Register MASK0;
    Register FUNCTION0;
    ReservedWord Reserved0;
    Register COMP1;
    Register MASK1;
    Register FUNCTION1;
    ReservedWord Reserved1;
    Register COMP2;
    Register MASK2;
    Register FUNCTION2;
    ReservedWord Reserved2;
    Register COMP3;
    Register MASK3;
    Register FUNCTION3;
    ReservedWord Reserved3;
};

static_assert(sizeof(DWTStruct) == 0x60);

}