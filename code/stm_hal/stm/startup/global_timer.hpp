/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

namespace stm::support {
extern volatile uint64_t g_timer_overflow_counter; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,bugprone-dynamic-static-initializers) Has to be globally accessible & modifiable
}