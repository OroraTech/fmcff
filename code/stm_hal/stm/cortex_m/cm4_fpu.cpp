/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "cm4_fpu.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::fpu {
extern "C" void setup_fpu() {
    using namespace stm::regs::scb::CPACR;
    __PERIPHERAL_SCB__.CPACR.write(CP10(3), CP11(3));
}
} // namespace stm::fpu
