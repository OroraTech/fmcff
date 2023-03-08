/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/uart/uart.hpp"

namespace stm {

extern "C" {
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables, bugprone-dynamic-static-initializers, readability-identifier-naming)
extern stm::periphs::uart::Uart uart_stdout;
}

/**
 * @brief inits the stdout UART
 *
 * @warning NEVER call this outside the startup code
 */
void init_stdout();

} // namespace stm
