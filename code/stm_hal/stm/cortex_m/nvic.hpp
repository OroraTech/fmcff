/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/regs/peripherals.hpp"

namespace stm::nvic {

class Nvic {
    static constexpr size_t PRIORITY_BITS = 4; /// priority bits supported by STM32 CM4 uCs. See STM32 Cortex M4 Programming manual Table 47
public:
    static constexpr uint8_t LOWEST_PRIORITY = ((1 << PRIORITY_BITS) - 1);
    static constexpr uint8_t DEFAULT_PRIORITY = LOWEST_PRIORITY / 2;
    static constexpr uint8_t HIGHEST_PRIORITY = 0;

    static inline void enable_irq(uint8_t irq) {
        __PERIPHERAL_NVIC__.ISER[irq / 32].write(1UL << (irq % 32));
    }

    static inline void set_irq_priority(uint8_t irq, uint8_t priority) {
        using namespace regs::nvic::IPR;
        __PERIPHERAL_NVIC__.IPR[irq].write(PRIO(priority));
    }
};

} // namespace stm::nvic
