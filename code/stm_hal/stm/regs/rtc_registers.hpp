/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::rtc {
using namespace stm::register_access;

namespace TR {
    using SU = RegSubValue<0, 4>;
    using ST = RegSubValue<4, 3>;

    using MNU = RegSubValue<8, 4>;
    using MNT = RegSubValue<12, 3>;

    using HU = RegSubValue<16, 4>;
    using HT = RegSubValue<20, 2>;

    using PM = RegSubValue<22>;
} // namespace TR

namespace DR {
    using DU = RegSubValue<0, 4>;
    using DT = RegSubValue<4, 2>;

    using MU = RegSubValue<8, 4>;
    using MT = RegSubValue<12>;

    using WDU = RegSubValue<13, 3>;

    using YU = RegSubValue<16, 4>;
    using YT = RegSubValue<20, 4>;
} // namespace DR

namespace CR {
    using WUCKSEL = RegSubValue<0, 3>;
    using TSEDGE = RegSubValue<3>;
    using REFCKON = RegSubValue<4>;

    using BYPSHAD = RegSubValue<5>;

    using FMT = RegSubValue<6>;

    using ALRAE = RegSubValue<8>;
    using ALRBE = RegSubValue<9>;
    using WUTE = RegSubValue<10>;
    using TSE = RegSubValue<11>;

    using ALRAIE = RegSubValue<12>;
    using ALRBIE = RegSubValue<13>;
    using WUTIE = RegSubValue<14>;
    using TSIE = RegSubValue<15>;

    using ADD1H = RegSubValue<16>;
    using SUB1H = RegSubValue<17>;

    using BKP = RegSubValue<18>;

    using COSEL = RegSubValue<19>;
    using POL = RegSubValue<20>;
    using OSEL = RegSubValue<21, 2>;
    using COE = RegSubValue<23>;

    using ITSE = RegSubValue<24>;
} // namespace CR

namespace ISR {
    using ALRAWF = RegSubValue<0>;
    using ALRBWF = RegSubValue<1>;
    using WUTWF = RegSubValue<2>;

    using SHPF = RegSubValue<3>;
    using INITS = RegSubValue<4>;
    using RSF = RegSubValue<5>;

    using INITF = RegSubValue<6>;
    using INIT = RegSubValue<7>;

    using ALRAF = RegSubValue<8>;
    using ALRBF = RegSubValue<9>;
    using WUTF = RegSubValue<10>;

    using TSF = RegSubValue<11>;
    using TSOVF = RegSubValue<12>;

    using TAMP1F = RegSubValue<13>;
    using TAMP2F = RegSubValue<14>;
    using TAMP3F = RegSubValue<15>;

    using RECALPF = RegSubValue<16>;

    using ITSF = RegSubValue<17>;
} // namespace ISR

namespace PRER {
    using PREDIV_S = RegSubValue<0, 15>;
    using REDIV_A = RegSubValue<16, 7>;
}

namespace WUTR {
    using WUT = RegSubValue<0, 16>;
}

namespace ALRMAR {
    using SU = RegSubValue<0, 4>;
    using ST = RegSubValue<4, 3>;

    using MSK1 = RegSubValue<7>;

    using MNU = RegSubValue<8, 4>;
    using MNT = RegSubValue<12, 3>;

    using MSK2 = RegSubValue<15>;

    using HU = RegSubValue<16, 4>;
    using HT = RegSubValue<20, 2>;

    using PM = RegSubValue<22>;

    using MSK3 = RegSubValue<23>;

    using DU = RegSubValue<24, 4>;
    using DT = RegSubValue<28, 2>;

    using WDSEL = RegSubValue<30>;

    using MSK4 = RegSubValue<31>;
} // namespace ALRMAR

namespace ALRMBR {
    using SU = RegSubValue<0, 4>;
    using ST = RegSubValue<4, 3>;

    using MSK1 = RegSubValue<7>;

    using MNU = RegSubValue<8, 4>;
    using MNT = RegSubValue<12, 3>;

    using MSK2 = RegSubValue<15>;

    using HU = RegSubValue<16, 4>;
    using HT = RegSubValue<20, 2>;

    using PM = RegSubValue<22>;

    using MSK3 = RegSubValue<23>;

    using DU = RegSubValue<24, 4>;
    using DT = RegSubValue<28, 2>;

    using WDSEL = RegSubValue<30>;

    using MSK4 = RegSubValue<31>;
} // namespace ALRMBR

namespace WPR {
    using KEY = RegSubValue<0, 8>;
}

namespace SSR {
    using SS = RegSubValue<0, 16>;
}

namespace SHIFTR {
    using SUBFS = RegSubValue<0, 15>;

    using ADD1S = RegSubValue<31>;
}

namespace TSTR {
    using SU = RegSubValue<0, 4>;
    using ST = RegSubValue<4, 3>;

    using MNU = RegSubValue<8, 4>;
    using MNT = RegSubValue<12, 3>;

    using HU = RegSubValue<16, 4>;
    using HT = RegSubValue<20, 2>;

    using PM = RegSubValue<22>;
} // namespace TSTR

namespace TSDR {
    using DU = RegSubValue<0, 4>;
    using DT = RegSubValue<4, 2>;

    using MU = RegSubValue<8, 4>;
    using MT = RegSubValue<12>;

    using WDU = RegSubValue<13, 3>;
}

namespace TSSSR {
    using SS = RegSubValue<0, 16>;
}

namespace CALR {
    using CALM = RegSubValue<0, 9>;
    using CALW16 = RegSubValue<13>;
    using CALW8 = RegSubValue<14>;
    using CALP = RegSubValue<15>;
}

namespace TAMPCR {
    using TAMP1E = RegSubValue<0>;
    using TAMP1TRG = RegSubValue<1>;

    using TAMPIE = RegSubValue<2>;

    using TAMP2E = RegSubValue<3>;
    using TAMP2TRG = RegSubValue<4>;

    using TAMP3E = RegSubValue<5>;
    using TAMP3TRG = RegSubValue<6>;

    using TAMPTS = RegSubValue<7>;
    using TAMPFREQ = RegSubValue<8, 3>;
    using TAMPFLT = RegSubValue<11, 2>;
    using TAMPPRCH = RegSubValue<13, 2>;
    using TAMPPUDIS = RegSubValue<15>;

    using TAMP1IE = RegSubValue<16>;
    using TAMP1NOERASE = RegSubValue<17>;
    using TAMP1MF = RegSubValue<18>;

    using TAMP2IE = RegSubValue<19>;
    using TAMP2NOERASE = RegSubValue<20>;
    using TAMP2MF = RegSubValue<21>;

    using TAMP3IE = RegSubValue<22>;
    using TAMP3NOERASE = RegSubValue<23>;
    using TAMP3MF = RegSubValue<24>;
} // namespace TAMPCR

namespace ALRMASSR {
    using SS = RegSubValue<0, 15>;
    using MASKSS = RegSubValue<24, 4>;
}

namespace ALRMBSSR {
    using SS = RegSubValue<0, 15>;
    using MASKSS = RegSubValue<24, 4>;
}

namespace OR {
    using RTC_ALARM_TYPE = RegSubValue<0>;
    using RTC_OUT_RMP = RegSubValue<1>;
}

struct RTCStruct {
    Register TR;
    Register DR;
    Register CR;
    Register ISR;
    Register PRER;
    Register WUTR;
    const uint32_t RESERVED0;
    Register ALRMAR;
    Register ALRMBR;
    Register WPR;
    Register SSR;
    Register SHIFTR;
    Register TSTR;
    Register TSDR;
    Register TSSSR;
    Register CALR;
    Register TAMPCR;
    Register ALRMASSR;
    Register ALRMBSSR;
    Register OR;
    Register BKPR[32];
};
static_assert(sizeof(RTCStruct) == 0xD0); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::rtc
