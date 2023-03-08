/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "bitfield/bitfield.hpp"
#include "mmio.hpp"

namespace stm::register_access {

using Register = bitfield::BitField<MMIO>;
using RegisterCopy = bitfield::UInt32BitField;

template <uint32_t OFFSET, uint8_t LENGTH = 1>
using RegSubValue = bitfield::UInt32SubValue<OFFSET, LENGTH>;

using Register8 = bitfield::BitField<MMIO8>;
using Register8Copy = bitfield::UInt8BitField;

template <uint8_t OFFSET, uint8_t LENGTH = 1>
using RegSubValue8 = bitfield::UInt8SubValue<OFFSET, LENGTH>;

} // namespace stm::register_access
