/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "bitfield.hpp"

#include <bit>

namespace bitfield {

/**
 * class meant for bitfield with that are divided into multiple
 * equally sized sections, where each section has a similar meaning
 * allows identical modifications to multiple such sections by setting a mask
 */
template <typename MemoryCell, uint32_t VALUE_LENGTH>
class MaskedBitField : public BitField<MemoryCell> {
    using ValueT = typename MemoryCell::ValueT;
    static constexpr size_t BITS = sizeof(ValueT) * 8;
    static_assert(VALUE_LENGTH > 0 && VALUE_LENGTH <= BITS);
    static_assert((BITS % VALUE_LENGTH) == 0);

    static constexpr uint64_t REG_MASK = SubValue<ValueT, 0, VALUE_LENGTH>::bitmask();

    static uint8_t find_next_bit_pos(ValueT& bit_mask) {
        auto pos = std::countr_zero(bit_mask);
        ValueT val { 1 };
        auto shifted = (ValueT)(val << pos);
        ValueT neg = ~shifted;
        bit_mask &= neg;
        return static_cast<uint8_t>(pos);
    }

public:
    inline void set_masked(ValueT bit_mask, ValueT value) {
        if constexpr (VALUE_LENGTH == 1) {
            BitField<MemoryCell>::clear_and_set_bits(bit_mask, value * bit_mask);
        } else {
            while (bit_mask != 0) {
                uint64_t pos = find_next_bit_pos(bit_mask);
                if (((pos * VALUE_LENGTH) + VALUE_LENGTH) <= (sizeof(ValueT) * 8)) {
                    auto clear_mask = (ValueT)(REG_MASK << (VALUE_LENGTH * pos));
                    auto set_mask = (ValueT)((value & REG_MASK) << (VALUE_LENGTH * pos));
                    BitField<MemoryCell>::clear_and_set_bits(clear_mask, set_mask);
                }
            }
        }
    }
};

template <uint32_t VALUE_LENGTH>
using UInt8MaskedBitField = MaskedBitField<Integer<uint8_t>, VALUE_LENGTH>;
template <uint32_t VALUE_LENGTH>
using UInt16MaskedBitField = MaskedBitField<Integer<uint16_t>, VALUE_LENGTH>;
template <uint32_t VALUE_LENGTH>
using UInt32MaskedBitField = MaskedBitField<Integer<uint32_t>, VALUE_LENGTH>;
template <uint32_t VALUE_LENGTH>
using UInt64MaskedBitField = MaskedBitField<Integer<uint64_t>, VALUE_LENGTH>;
} // namespace bitfield

