/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::pwr {
using namespace stm::register_access;

namespace CR1 {
    using LPMS = RegSubValue<0, 3>;
    using DBP = RegSubValue<8>;
    using VOS = RegSubValue<9, 2>;
    using LPR = RegSubValue<14>;
}

namespace CR2 {
    using PVDE = RegSubValue<0>;
    using PLS = RegSubValue<1, 3>;
    using PVME1 = RegSubValue<4>;
    using PVME2 = RegSubValue<5>;
    using PVME3 = RegSubValue<6>;
    using PVME4 = RegSubValue<7>;

    using IOSV = RegSubValue<9>;
    using USV = RegSubValue<10>;
} // namespace CR2

struct PWRStruct {
    Register CR1;
    Register CR2;
    Register CR3;
    Register CR4;
    Register SR1;
    Register SR2;
    Register SCR;
    const uint32_t RESERVED;
    Register PUCRA;
    Register PDCRA;
    Register PUCRB;
    Register PDCRB;
    Register PUCRC;
    Register PDCRC;
    Register PUCRD;
    Register PDCRD;
    Register PUCRE;
    Register PDCRE;
    Register PUCRF;
    Register PDCRF;
    Register PUCRG;
    Register PDCRG;
    Register PUCRH;
    Register PDCRH;
    Register PUCRI;
    Register PDCRI;
};

} // namespace stm::regs::pwr
