/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "bitfield/masked_bitfield.hpp"
#include "mmio.hpp"

namespace stm::register_access {

/**
 * class meant for registers with that are divided into multiple
 * equally sized sections, where each section has a similar meaning
 * allows identical modifications to multiple such sections by setting a mask
 */
template <uint32_t VALUE_LENGTH>
using MaskedRegister = bitfield::MaskedBitField<MMIO, VALUE_LENGTH>;

} // namespace stm::register_access
