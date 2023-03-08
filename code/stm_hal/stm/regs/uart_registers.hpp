/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::uart {
using namespace stm::register_access;

namespace CR1 {
    using UE = RegSubValue<0>;
    using UESM = RegSubValue<1>;
    using RE = RegSubValue<2>;
    using TE = RegSubValue<3>;
    using IDLEIE = RegSubValue<4>;
    using RXNEIE = RegSubValue<5>;
    using TCIE = RegSubValue<6>;
    using TXEIE = RegSubValue<7>;
    using PEIE = RegSubValue<8>;
    using PS = RegSubValue<9>;
    using PCE = RegSubValue<10>;
    using WAKE = RegSubValue<11>;
    using M0 = RegSubValue<12>;
    using MME = RegSubValue<13>;
    using CMIE = RegSubValue<14>;
    using OVER8 = RegSubValue<15>;
    using DEDT = RegSubValue<16, 5>;
    using DEAT = RegSubValue<21, 5>;
    using RTOIE = RegSubValue<26>;
    using EOBIE = RegSubValue<27>;
    using M1 = RegSubValue<28>;
} // namespace CR1

namespace CR2 {
    using ADD7M = RegSubValue<4>;
    using LBDL = RegSubValue<5>;
    using LBDIE = RegSubValue<6>;
    using LBCL = RegSubValue<8>;

    using CPHA = RegSubValue<9>;
    using CPOL = RegSubValue<10>;
    using CLKEN = RegSubValue<11>;
    using STOP = RegSubValue<12, 2>;
    using LINEN = RegSubValue<14>;
    using SWAP = RegSubValue<15>;
    using RXINV = RegSubValue<16>;
    using TXINV = RegSubValue<17>;
    using DATAINV = RegSubValue<18>;
    using MSBFIRST = RegSubValue<19>;
    using ABREN = RegSubValue<20>;
    using ABRMOD = RegSubValue<21, 2>;
    using RTOEN = RegSubValue<23>;

    using ADD = RegSubValue<24, 8>;
} // namespace CR2

namespace CR3 {
    using EIE = RegSubValue<0>;
    using IREN = RegSubValue<1>;
    using IRLP = RegSubValue<2>;
    using HDSEL = RegSubValue<3>;
    using NACK = RegSubValue<4>;
    using SCEN = RegSubValue<5>;
    using DMAR = RegSubValue<6>;
    using DMAEN = RegSubValue<7>;
    using RTSE = RegSubValue<8>;
    using CTSE = RegSubValue<9>;
    using CTSIE = RegSubValue<10>;
    using ONEBIT = RegSubValue<11>;
    using OVRDIS = RegSubValue<12>;
    using DDRE = RegSubValue<13>;
    using DEM = RegSubValue<14>;
    using DEP = RegSubValue<15>;
    using SCARCNT = RegSubValue<17, 3>;
    using WUS = RegSubValue<20, 2>;
    using WUFIE = RegSubValue<22>;
    using UCESM = RegSubValue<23>;
    using TCBGTIE = RegSubValue<24>;
} // namespace CR3

namespace GTPR {
    using PSC = RegSubValue<0, 8>;
    using GT = RegSubValue<8, 8>;
}

namespace RTOR {
    using RTO = RegSubValue<0, 24>;
    using BLEN = RegSubValue<24, 8>;
}

namespace RQR {
    using ABRRQ = RegSubValue<0>;
    using SBKRQ = RegSubValue<1>;
    using MMRQ = RegSubValue<2>;
    using RXFRQ = RegSubValue<3>;
    using TXFRQ = RegSubValue<4>;
}

namespace ISR {
    using PE = RegSubValue<0>;
    using FE = RegSubValue<1>;
    using NF = RegSubValue<2>;
    using ORE = RegSubValue<3>;
    using IDLE = RegSubValue<4>;
    using RXNE = RegSubValue<5>;
    using TC = RegSubValue<6>;
    using TXE = RegSubValue<7>;
    using LBDF = RegSubValue<8>;
    using CTSIF = RegSubValue<9>;
    using CTS = RegSubValue<10>;
    using RTOF = RegSubValue<11>;
    using EOBF = RegSubValue<12>;
    using ABRE = RegSubValue<14>;
    using ABRF = RegSubValue<15>;
    using BUSY = RegSubValue<16>;
    using CMF = RegSubValue<17>;
    using SBKF = RegSubValue<18>;
    using RWU = RegSubValue<19>;
    using WUF = RegSubValue<20>;
    using TEACK = RegSubValue<21>;
    using REACK = RegSubValue<22>;
    using TCBGT = RegSubValue<25>;
} // namespace ISR

namespace ICR {
    using PECF = RegSubValue<0>;
    using FECF = RegSubValue<1>;
    using NCF = RegSubValue<2>;
    using ORECF = RegSubValue<3>;
    using IDLECF = RegSubValue<4>;
    using TCCF = RegSubValue<6>;
    using TXECF = RegSubValue<7>;
    using LBDFCF = RegSubValue<8>;
    using CTSCF = RegSubValue<9>;
    using RTOCF = RegSubValue<11>;
    using EOBCF = RegSubValue<12>;
    using CMCF = RegSubValue<17>;
    using WUCF = RegSubValue<20>;
} // namespace ICR

struct UARTStruct {
    Register CR1;
    Register CR2;
    Register CR3;
    Register BRR;
    Register GTPR;
    Register RTOR;
    Register RQR;
    Register ISR;
    Register ICR;
    Register RDR;
    Register TDR;
};

static_assert(sizeof(UARTStruct) == 0x2C); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::uart
