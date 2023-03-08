/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/masked_register.hpp"
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::gpio {
using namespace stm::register_access;

namespace BSRR {
    using BS = RegSubValue<0, 16>;
    using BR = RegSubValue<16, 16>;
}

struct GPIOStruct {
    MaskedRegister<2> MODER;
    MaskedRegister<1> OTYPER;
    MaskedRegister<2> OSPEEDR;
    MaskedRegister<2> PUPDR;
    MaskedRegister<1> IDR;
    MaskedRegister<1> ODR;
    Register BSRR;
    MaskedRegister<1> LCKR;
    MaskedRegister<4> AFRL;
    MaskedRegister<4> AFRH;
    MaskedRegister<1> BRR;
    MaskedRegister<1> ASCR;

    const uint32_t SPACE_BETWEEN_PORTS[0x100 - 12];
};
static_assert(sizeof(GPIOStruct) == 0x400); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::gpio
