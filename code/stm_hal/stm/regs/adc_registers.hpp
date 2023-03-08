/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::adc {
using namespace stm::register_access;

namespace ISR {
    using ADRDY = RegSubValue<0>;
    using EOSMP = RegSubValue<1>;
    using EOC = RegSubValue<2>;
    using EOS = RegSubValue<3>;
    using OVR = RegSubValue<4>;
    using JEOC = RegSubValue<5>;
    using JEOS = RegSubValue<6>;
    using AWD1 = RegSubValue<7>;
    using AWD2 = RegSubValue<8>;
    using AWD3 = RegSubValue<9>;
    using JQOVF = RegSubValue<10>;
} // namespace ISR
namespace IER {
    using ADRDYIE = RegSubValue<0>;
    using EOSMPIE = RegSubValue<1>;
    using EOCIE = RegSubValue<2>;
    using EOSIE = RegSubValue<3>;
    using OVRIE = RegSubValue<4>;
    using JEOCIE = RegSubValue<5>;
    using JEOSIE = RegSubValue<6>;
    using AWD1IE = RegSubValue<7>;
    using AWD2IE = RegSubValue<8>;
    using AWD3IE = RegSubValue<9>;
    using JQOVFIE = RegSubValue<10>;
} // namespace IER
namespace CR {
    using ADEN = RegSubValue<0>;
    using ADDIS = RegSubValue<1>;
    using ADSTART = RegSubValue<2>;
    using JADSTART = RegSubValue<3>;
    using ADSTP = RegSubValue<4>;
    using JADSTP = RegSubValue<5>;
    using ADVREGEN = RegSubValue<28>;
    using DEEPPWD = RegSubValue<29>;
    using ADCALDIF = RegSubValue<30>;
    using ADCAL = RegSubValue<31>;
} // namespace CR
namespace CFGR {
    using DMAEN = RegSubValue<0>;
    using DMACFG = RegSubValue<1>;
    using DFSDMCFG = RegSubValue<2>;
    using RES = RegSubValue<3, 2>;
    using ALIGN = RegSubValue<5>;
    using EXTSEL = RegSubValue<6, 4>;
    using EXTEN = RegSubValue<10, 2>;
    using OVRMOD = RegSubValue<12>;
    using CONT = RegSubValue<13>;
    using AUTDLY = RegSubValue<14>;
    using DISCEN = RegSubValue<16>;
    using DISCNUM = RegSubValue<17, 19>;
    using JDISCEN = RegSubValue<20>;
    using JQM = RegSubValue<21>;
    using AWD1SGL = RegSubValue<22>;
    using AWD1EN = RegSubValue<23>;
    using JAWD1EN = RegSubValue<24>;
    using JAUTO = RegSubValue<25>;
    using AWD1CH = RegSubValue<26, 5>;
    using JQDIS = RegSubValue<31>;
} // namespace CFGR
namespace CFGR2 {
    using ROVSE = RegSubValue<0>;
    using JOVSE = RegSubValue<1>;
    using OVSR = RegSubValue<2, 3>;
    using OVSS = RegSubValue<5, 4>;
    using TROVS = RegSubValue<9>;
    using ROVSM = RegSubValue<10>;
}
namespace SMPR1 {
    using SMP0 = RegSubValue<0, 3>;
    using SMP1 = RegSubValue<3, 3>;
    using SMP2 = RegSubValue<6, 3>;
    using SMP3 = RegSubValue<6, 3>;
    using SMP4 = RegSubValue<12, 3>;
    using SMP5 = RegSubValue<15, 3>;
    using SMP6 = RegSubValue<18, 3>;
    using SMP7 = RegSubValue<21, 3>;
    using SMP8 = RegSubValue<24, 3>;
    using SMP9 = RegSubValue<27, 3>;
    using SMPPLUS = RegSubValue<31>;
} // namespace SMPR1
namespace SMPR2 {
    using SMP10 = RegSubValue<0, 3>;
    using SMP11 = RegSubValue<3, 3>;
    using SMP12 = RegSubValue<6, 3>;
    using SMP13 = RegSubValue<9, 3>;
    using SMP14 = RegSubValue<12, 3>;
    using SMP15 = RegSubValue<15, 3>;
    using SMP16 = RegSubValue<18, 3>;
    using SMP17 = RegSubValue<21, 3>;
    using SMP18 = RegSubValue<24, 3>;
} // namespace SMPR2
namespace TR1 {
    using LT1 = RegSubValue<0, 12>;
    using HT1 = RegSubValue<16, 12>;
}
namespace TR2 {
    using LT2 = RegSubValue<0, 12>;
    using HT2 = RegSubValue<16, 12>;
}
namespace TR3 {
    using LT3 = RegSubValue<0, 12>;
    using HT3 = RegSubValue<16, 12>;
}
namespace SQR1 {
    using L = RegSubValue<0, 4>;
    using SQ1 = RegSubValue<6, 5>;
    using SQ2 = RegSubValue<12, 5>;
    using SQ3 = RegSubValue<18, 5>;
    using SQ4 = RegSubValue<24, 5>;
}
namespace SQR2 {
    using SQ5 = RegSubValue<0, 5>;
    using SQ6 = RegSubValue<6, 5>;
    using SQ7 = RegSubValue<12, 5>;
    using SQ8 = RegSubValue<18, 5>;
    using SQ9 = RegSubValue<24, 5>;
}
namespace SQR3 {
    using SQ10 = RegSubValue<0, 5>;
    using SQ11 = RegSubValue<6, 5>;
    using SQ12 = RegSubValue<12, 5>;
    using SQ13 = RegSubValue<18, 5>;
    using SQ14 = RegSubValue<24, 5>;
}
namespace SQR4 {
    using SQ15 = RegSubValue<0, 5>;
    using SQ16 = RegSubValue<6, 5>;
}
namespace DR {
    using RDATA = RegSubValue<0, 16>;
}
namespace JSQR {
    using JL = RegSubValue<0, 2>;
    using JEXTSEL = RegSubValue<2, 4>;
    using JEXTEN = RegSubValue<6, 2>;
    using JSQ1 = RegSubValue<8, 5>;
    using JSQ2 = RegSubValue<14, 5>;
    using JSQ3 = RegSubValue<20, 5>;
    using JSQ4 = RegSubValue<26, 5>;
}
namespace OFR {
    using OFFSETy = RegSubValue<0, 12>;
    using OFFSETy_CH = RegSubValue<26, 5>;
    using OFFSETy_EN = RegSubValue<31>;
}
namespace JDR {
    using JDATA = RegSubValue<0, 16>;
}
namespace AWD2CR {
    using AWD2CH = RegSubValue<0, 19>;
}
namespace AWD3CR {
    using AWD3CH = RegSubValue<0, 19>;
}
namespace DIFSEL {
    using DIFSEL = RegSubValue<0, 19>;
}
namespace CALFACT {
    using CALFACT_S = RegSubValue<0, 7>;
    using CALFACT_D = RegSubValue<17, 7>;
}
namespace CSR {
    using ADRDY_MST = RegSubValue<0>;
    using EOSMP_MST = RegSubValue<1>;
    using EOC_MST = RegSubValue<2>;
    using EOS_MST = RegSubValue<3>;
    using OVR_MST = RegSubValue<4>;
    using JEOC_MST = RegSubValue<5>;
    using JEOS_MST = RegSubValue<6>;
    using AWD1_MST = RegSubValue<7>;
    using AWD2_MST = RegSubValue<8>;
    using AWD3_MST = RegSubValue<9>;
    using JQOVF_MST = RegSubValue<10>;
    using ADRDY_SLV = RegSubValue<16>;
    using EOSMP_SLV = RegSubValue<17>;
    using EOC_SLV = RegSubValue<18>;
    using EOS_SLV = RegSubValue<19>;
    using OVR_SLV = RegSubValue<20>;
    using JEOC_SLV = RegSubValue<21>;
    using JEOS_SLV = RegSubValue<22>;
    using AWD1_SLV = RegSubValue<23>;
    using AWD2_SLV = RegSubValue<24>;
    using AWD3_SLV = RegSubValue<25>;
    using JQOVF_SLV = RegSubValue<26>;
} // namespace CSR
namespace CCR {
    using DUAL = RegSubValue<0, 5>;
    using DELAY = RegSubValue<8, 4>;
    using DMACFG = RegSubValue<13>;
    using MDMA = RegSubValue<14, 2>;
    using CKMODE = RegSubValue<16, 2>;
    using PRESC = RegSubValue<18, 4>;
    using VREFEN = RegSubValue<22>;
    using CH17SEL = RegSubValue<23>;
    using CH18SEL = RegSubValue<24>;
} // namespace CCR
namespace CDR {
    using RDATA_MST = RegSubValue<0, 16>;
    using RDATA_SLV = RegSubValue<17, 16>;
}

struct SingleADCStruct {
    Register ISR;
    Register IER;
    Register CR;
    Register CFGR;
    Register CFGR2;
    Register SMPR1;
    Register SMPR2;
    ReservedWord RESERVED0;
    Register TR1;
    Register TR2;
    Register TR3;
    ReservedWord RESERVED1;
    Register SQR1;
    Register SQR2;
    Register SQR3;
    Register SQR4;
    Register DR;
    ReservedWord RESERVED2[2];
    Register JSQR;
    ReservedWord RESERVED3[4];
    Register OFR[4];
    ReservedWord RESERVED4[4];
    Register JDR[4];
    ReservedWord RESERVED5[4];
    Register AWD2CR;
    Register AWD3CR;
    ReservedWord RESERVED6[2];
    Register DIFSEL;
    Register CALFACT;
    ReservedWord RESERVED7[(0x100 - 0x0B8) / sizeof(ReservedWord)];
};

static_assert(sizeof(SingleADCStruct) == 0x100); // NOLINT(readability-magic-numbers)

struct CommonADCRegisters {
    Register CSR;
    ReservedWord RESERVED_ADC_COMMON;
    Register CCR;
    Register CDR;
};

struct ADCStruct {
    SingleADCStruct adcX[3];
    CommonADCRegisters commonRegisters;
};

static_assert(sizeof(ADCStruct) == 0x310); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::adc
