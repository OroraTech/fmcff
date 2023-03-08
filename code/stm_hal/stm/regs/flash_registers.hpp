/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::flash {
using namespace stm::register_access;

namespace ACR {
    using LATENCY = RegSubValue<0, 3>;
    using PRFTEN = RegSubValue<8>;
    using ICEN = RegSubValue<9>;
    using DCEN = RegSubValue<10>;
    using ICRST = RegSubValue<11>;
    using DCRST = RegSubValue<12>;
    using RUN_PD = RegSubValue<13>;
    using SLEEP_PD = RegSubValue<14>;
}

namespace KEYR {
    constexpr uint32_t KEY1 { 0x4567'0123 };
    constexpr uint32_t KEY2 { 0xCDEF'89AB };
}

namespace SR {
    using EOP = RegSubValue<0, 1>;
    using OPERR = RegSubValue<1, 1>;
    using PROGERR = RegSubValue<3, 1>;
    using WRPERR = RegSubValue<4, 1>;
    using PGAERR = RegSubValue<5, 1>;
    using SIZERR = RegSubValue<6, 1>;
    using PGSERR = RegSubValue<7, 1>;
    using MISSERR = RegSubValue<8, 1>;
    using FASTERR = RegSubValue<9, 1>;
    using RDERR = RegSubValue<14, 1>;
    using OPTVERR = RegSubValue<15, 1>;
    using BSY = RegSubValue<16, 1>;
}

namespace CR {
    using PG = RegSubValue<0>;
    using PER = RegSubValue<1>;
    using MER1 = RegSubValue<2>;
    using PNB = RegSubValue<3, 7>;
    using BKER = RegSubValue<11>;
    using MER2 = RegSubValue<15>;
    using STRT = RegSubValue<16>;
    using OPTSTRT = RegSubValue<17>;
    using FSTPG = RegSubValue<18>;
    using EOPIE = RegSubValue<24>;
    using ERRIE = RegSubValue<25>;
    using RDERRIE = RegSubValue<26>;
    using OBL_LAUNCH = RegSubValue<27>;
    using OPTLOCK = RegSubValue<30>;
    using LOCK = RegSubValue<31>;

}

namespace WRPxyR {
    using WRPxy_START = RegSubValue<0, 8>;
    using WRPxy_END = RegSubValue<16, 8>;
}

struct FLASHStruct {
    Register ACR;
    Register PDKEYR;
    Register KEYR;
    Register OPTKEYR;
    Register SR;
    Register CR;
    Register ECCR;
    Register OPTR;
    Register PCROP1SR;
    Register PCROP1ER;
    Register WRP1AR;
    Register WRP1BR;
    Register PCROP2SR;
    Register PCROP2ER;
    Register WRP2AR;
    Register WRP2BR;
};

} // namespace stm::regs::flash
