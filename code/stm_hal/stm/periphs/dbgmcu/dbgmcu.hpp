/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/regs/dbgmcu_registers.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::dbgmcu {
inline void enable_debugging() {
    using namespace stm;
    using namespace stm::regs::dbgmcu::CR;

    __PERIPHERAL_DBGMCU__.CR.set(DBG_SLEEP(1), DBG_STOP(1), DBG_STANDBY(1));
}
} // namespace stm::dbgmcu
