/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#ifdef __UNIT_TEST__
#include "mmio.hpp"

namespace stm::register_access {
[[gnu::weak]] void MMIO::write(ValueT value) { reg = value; }
[[nodiscard, gnu::weak]] MMIO::ValueT MMIO::read() const { return reg; };
[[gnu::weak]] void MMIO8::write(ValueT value) { reg = value; };
[[nodiscard, gnu::weak]] MMIO8::ValueT MMIO8::read() const { return reg; };
}
#endif
