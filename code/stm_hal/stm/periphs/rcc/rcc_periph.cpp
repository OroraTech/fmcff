/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "rcc_periph.hpp"

#include "stm/regs/peripherals.hpp"
#include "stm/regs/rcc_registers.hpp"

namespace stm::periphs::rcc {
using namespace stm::regs::rcc;

constexpr Register& get_enable_register(RccClockDomain domain) {
    constexpr RCCStruct& RCC = __PERIPHERAL_RCC__;
    switch (domain) {
    case RccClockDomain::AHB1:
        return RCC.AHB1ENR;
    case RccClockDomain::AHB2:
        return RCC.AHB2ENR;
    case RccClockDomain::AHB3:
        return RCC.AHB3ENR;
    case RccClockDomain::APB1_1:
        return RCC.APB1ENR1;
    case RccClockDomain::APB1_2:
        return RCC.APB1ENR2;
    case RccClockDomain::APB2:
        return RCC.APB2ENR;
    default:
        __builtin_trap();
    }
}

void enable_rcc_periph(const RccPeriph& periph) {
    Register& enable_register = get_enable_register(periph.domain);
    enable_register.set_bits(1 << periph.offset);
    (void)enable_register.read(); // dummy read to ensure a small wait
}

} // namespace stm::periphs::rcc
