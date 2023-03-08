/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "board_defines.hpp"
#include "stm/periphs/uart/uart.hpp"
#include <new>

namespace stm {

extern "C" {
// slightly ugly way to define a uart object without initializing it
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
[[gnu::used]] constinit char g_uart_stdout_memory alignas(stm::periphs::uart::Uart)[sizeof(stm::periphs::uart::Uart)] {};
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,readability-identifier-naming)
[[gnu::alias("g_uart_stdout_memory")]] extern stm::periphs::uart::Uart uart_stdout;
}

/**
 * @brief inits the stdout uart object
 *
 * Done this way so that the UART can already be used in global constructors
 */
void init_stdout() {
    new (&uart_stdout) stm::periphs::uart::Uart(stm::periphs::uart::Uart::init<target_specific::STDOUT>());
}

// NOLINTNEXTLINE(readability-identifier-naming) has to be named like this for the printf library
extern "C" void putchar_(char c) {
    uart_stdout.write_sync(static_cast<std::byte>(c));
}

extern "C" int getchar() {
    return to_integer<int>(uart_stdout.read_byte_blocking());
}

} // namespace stm
