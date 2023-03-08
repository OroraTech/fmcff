/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::can {
using namespace stm::register_access;

namespace MCR {
    using INRQ = RegSubValue<0>;
    using SLEEP = RegSubValue<1>;

    using TXFP = RegSubValue<2>;
    using RFLM = RegSubValue<3>;
    using NART = RegSubValue<4>;
    using AWUM = RegSubValue<5>;
    using ABOM = RegSubValue<6>;
    // using TTCM = RegSubValue<7>; //not availabe, see errata sheet
    using RESET = RegSubValue<15>;
    using DBF = RegSubValue<16>;
} // namespace MCR

namespace MSR {
    using INAK = RegSubValue<0>;
    using SLAK = RegSubValue<1>;
    using ERRI = RegSubValue<2>;
    using WKUI = RegSubValue<3>;
    using SLAKI = RegSubValue<4>;
    using TXM = RegSubValue<8>;
    using RXM = RegSubValue<9>;
    using SAMP = RegSubValue<10>;
    using RX = RegSubValue<11>;
} // namespace MSR

namespace TSR {
    using RQCP0 = RegSubValue<0>;
    using TXOK0 = RegSubValue<1>;
    using ALST0 = RegSubValue<2>;
    using TERR0 = RegSubValue<3>;
    using ABRQ0 = RegSubValue<7>;

    using RQCP1 = RegSubValue<8>;
    using TXOK1 = RegSubValue<9>;
    using ALST1 = RegSubValue<10>;
    using TERR1 = RegSubValue<11>;
    using ABRQ1 = RegSubValue<15>;

    using RQCP2 = RegSubValue<16>;
    using TXOK2 = RegSubValue<17>;
    using ALST2 = RegSubValue<18>;
    using TERR2 = RegSubValue<19>;
    using ABRQ2 = RegSubValue<23>;

    using CODE = RegSubValue<24, 2>;
    using TME0 = RegSubValue<26>;
    using TME1 = RegSubValue<27>;
    using TME2 = RegSubValue<28>;
    using LOW0 = RegSubValue<29>;
    using LOW1 = RegSubValue<30>;
    using LOW2 = RegSubValue<31>;
} // namespace TSR

namespace RFxR {
    using FMP = RegSubValue<0, 2>;
    using FULL = RegSubValue<3>;
    using FOVR = RegSubValue<4>;
    using RFOM = RegSubValue<5>;
}

namespace IER {
    using TMEIE = RegSubValue<0>;
    using FMPIE0 = RegSubValue<1>;
    using FFIE0 = RegSubValue<2>;
    using FOVIE0 = RegSubValue<3>;
    using FMPIE1 = RegSubValue<4>;
    using FFIE1 = RegSubValue<5>;
    using FOVIE1 = RegSubValue<6>;

    using EWGIE = RegSubValue<8>;
    using EPVIE = RegSubValue<9>;
    using BOFIE = RegSubValue<10>;
    using LECIE = RegSubValue<11>;

    using ERRIE = RegSubValue<15>;

    using WKUIE = RegSubValue<16>;
    using SLKIE = RegSubValue<17>;
} // namespace IER

namespace ESR {
    using EWGF = RegSubValue<0>;
    using EPVF = RegSubValue<1>;
    using BOFF = RegSubValue<2>;

    using LEC = RegSubValue<4, 3>;

    using TEC = RegSubValue<16, 8>;
    using REC = RegSubValue<24, 8>;
}

namespace BTR {
    using BRP = RegSubValue<0, 10>;
    using TS1 = RegSubValue<16, 4>;
    using TS2 = RegSubValue<20, 3>;
    using SJW = RegSubValue<24, 2>;
    using LBKM = RegSubValue<30>;
    using SILM = RegSubValue<31>;
}

namespace TIxR {
    using TXRQ = RegSubValue<0>;
    using RTR = RegSubValue<1>;
    using IDE = RegSubValue<2>;

    using STID = RegSubValue<21, 11>;
    using EXID = RegSubValue<3, 29>;
}

namespace TDTxR {
    using DLC = RegSubValue<0, 4>;
    // using TIME = RegSubValue<16,16>; // not available, see errata sheet
}

namespace RIxR {
    using RTR = RegSubValue<1>;
    using IDE = RegSubValue<2>;

    using STID = RegSubValue<21, 11>;
    using EXID = RegSubValue<3, 29>;
}

namespace RDTxR {
    using DLC = RegSubValue<0, 4>;
    using FMI = RegSubValue<8, 8>;
    // using TIME = RegSubValue<16,16>; // not available, see errata sheet
}

namespace FMR {
    using FINIT = RegSubValue<0>;
    using CANSB = RegSubValue<8, 6>;
}

namespace FiRx { // for now always used in the 32-bit identifier mask mode
    using EXID = RegSubValue<3, 29>;
    using STID = RegSubValue<21, 11>;
    using IDE = RegSubValue<2>;
    using RTR = RegSubValue<1>;
}

struct TXMailbox {
    Register TIxR;
    Register TDTxR;
    Register TDLxR;
    Register TDHxR;

    [[nodiscard]] bool isFull() const {
        return TIxR.read<TIxR::TXRQ>() != 0;
    }
};

struct RXFifo {
    Register RIxR;
    Register RDTxR;
    Register RDLxR;
    Register RDHxR;
};

struct FilterBank {
    Register FxR0;
    Register FxR1;
};

struct CANStruct {
    Register MCR;
    Register MSR;
    Register TSR;
    Register RF0R;
    Register RF1R;
    Register IER;
    Register ESR;
    Register BTR;
    ReservedWord RESERVED0[(0x180 - 0x020) / sizeof(uint32_t)];
    TXMailbox TX[3];
    RXFifo RX[2];
    ReservedWord RESERVED1[(0x200 - 0x1D0) / sizeof(uint32_t)];
    // perhaps it would be good to seperate the filter register map completely - they are only present on CAN1 but control the filters for both CANs
    Register FMR;
    Register FM1R;
    ReservedWord RESERVED2;
    Register FS1R;
    ReservedWord RESERVED3;
    Register FFA1R;
    ReservedWord RESERVED4;
    Register FA1R;
    ReservedWord RESERVED5[(0x240 - 0x220) / sizeof(uint32_t)];
    FilterBank filterBanks[2][14];
};

} // namespace stm::regs::can
