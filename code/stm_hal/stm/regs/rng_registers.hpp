/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::rng {
using namespace stm::register_access;

namespace CR {
    using RNGEN = RegSubValue<2>;
    using OE = RegSubValue<3>;
    using CED = RegSubValue<5>;
} // namespace CR

namespace SR {
    using DRDY = RegSubValue<0>;
    using CECS = RegSubValue<1>;
    using SECS = RegSubValue<2>;
    using CEIS = RegSubValue<5>;
    using SEIS = RegSubValue<6>;
} // namespace SR

struct RNGStruct {
    Register CR;
    Register SR;
    Register DR;
};

static_assert(sizeof(RNGStruct) == 0x0C); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::rng
