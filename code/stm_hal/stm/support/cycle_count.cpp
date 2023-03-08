/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "cycle_count.hpp"
#include "stm/cortex_m/irq.hpp"
#include "stm/cortex_m/nvic.hpp"
#include "stm/regs/dwt_registers.hpp"
#include "stm/startup/irq_handlers.hpp"

#include <cstdio>

CycleCount::CycleCount() {
    using namespace stm::regs::dbg::DEMCR;
    using namespace stm::regs::dwt::DWT_CTRL;
    __PERIPHERAL_DBG__.DEMCR.set(TRCENA(0x1));   // Enable DWT
    __PERIPHERAL_DWT__.CYCCNT.write(0x0);        // Set cyccnt to 0
    __PERIPHERAL_DWT__.CTRL.set(CYCCNTENA(0x1)); // Enable cycle count in timer
}

CycleCount::~CycleCount() {
    using namespace stm::regs::dbg::DEMCR;
    using namespace stm::regs::dwt::DWT_CTRL;
    __PERIPHERAL_DWT__.CTRL.set(CYCCNTENA(0x0)); // Disable cycle count in timer
    __PERIPHERAL_DWT__.CYCCNT.write(0x0);        // Set cyccnt to 0
    __PERIPHERAL_DBG__.DEMCR.set(TRCENA(0x0));   // Disable DWT
}

void CycleCount::register_tick() {
    ticks_[index_] = __PERIPHERAL_DWT__.CYCCNT.read();
    index_ += 1;
}

void CycleCount::print_ticks() {
    for (size_t i = 0; i < index_; i++) {
        printf("Tick #%d is %lu, %luus\r\n", i, (unsigned long)ticks_[i], (unsigned long)ticks_[i] / 80'000);
    }
    printf("\r\n");
}

std::span<uint32_t> CycleCount::get_ticks() {
    return std::span { ticks_, index_ };
}
