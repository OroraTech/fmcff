/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/startup/irq_table.hpp"

namespace stm {

extern "C" {
#ifndef STM_BOOTLOADER
[[gnu::used]] constinit const IRQTable IRQ_TABLE; // NOLINT(bugprone-dynamic-static-initializers)
#else
[[noreturn, gnu::used, gnu::section(".text_rom")]] void _prestart(); // NOLINT(readability-identifier-naming)
[[gnu::used, gnu::section(".isr_vector")]] constinit const stm::IRQTable IRQ_TABLE {
    .reset_handler = _prestart
};
#endif
}

} // namespace stm
