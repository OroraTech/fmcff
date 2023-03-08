/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace bitfield {

template <typename IntegerT>
struct Integer {
public:
    using ValueT = IntegerT;
    ValueT value = 0;

    void write(const ValueT value) {
        this->value = value;
    }

    [[nodiscard]] ValueT read() const {
        return this->value;
    }
};

template <typename ValueT, size_t VAL_OFFSET, size_t VAL_LENGTH = 1>
struct SubValue {
    static_assert(VAL_OFFSET + VAL_LENGTH <= sizeof(ValueT) * 8);
    static constexpr int LENGTH = VAL_LENGTH;
    static constexpr int OFFSET = VAL_OFFSET;
    static constexpr ValueT bitmask() {
        return bitmask_unshifted() << OFFSET;
    }

    static constexpr ValueT bitmask_unshifted() {
        if constexpr (LENGTH < (sizeof(ValueT) * 8)) {
            return static_cast<ValueT>((ValueT(1) << LENGTH) - 1);
        }
        return static_cast<ValueT>(~ValueT(0));
    }

    static constexpr bool IS_SUB_VALUE { true };

    ValueT shifted_value;

    constexpr explicit SubValue(ValueT value) :
        shifted_value(static_cast<ValueT>(value << OFFSET)) {};
    constexpr explicit SubValue(std::byte value) :
        SubValue { std::to_integer<ValueT>(value) } {};

    template <ValueT VALUE>
    static constexpr SubValue from_const() {
        static_assert((VALUE & bitmask_unshifted()) == VALUE, "The given value can not be used as a SubValue here. Too big!");
        return SubValue(VALUE);
    }

    template <size_t OTHER_OFFSET, size_t OTHER_LENGTH>
    constexpr ValueT operator|(const SubValue<ValueT, OTHER_OFFSET, OTHER_LENGTH>& other_value) {
        return shifted_value | other_value.shiftedValue;
    }

    constexpr ValueT operator|(ValueT value) {
        return shifted_value | value;
    }

    constexpr friend ValueT operator|(ValueT lhs, SubValue<ValueT, OFFSET, LENGTH> rhs) {
        return rhs | lhs;
    }

    constexpr explicit operator ValueT() {
        return shifted_value;
    }
};

template <typename MemoryCell>
struct BitField : public MemoryCell {
public:
    using MemoryCell::read;
    using ValueT = typename MemoryCell::ValueT;
    template <size_t OFFSET, size_t LENGTH = 1>
    using SubValue = SubValue<ValueT, OFFSET, LENGTH>;

    void set_bits(const ValueT set_mask) {
        write(MemoryCell::read() | set_mask);
    }

    void clear_bits(const ValueT clear_mask) {
        write(MemoryCell::read() & (ValueT)(~clear_mask));
    }

    [[nodiscard]] ValueT read_bits(const ValueT read_mask) const {
        return MemoryCell::read() & read_mask;
    }

    void clear_and_set_bits(const ValueT clear_mask, const ValueT set_mask) {
        MemoryCell::write((MemoryCell::read() & (ValueT)(~clear_mask)) | set_mask);
    }

    /**
     * @brief does a read-modify-write sequence on the register, modifying the given subvalues and leaving all other bits unmodified
     */
    template <class... SubValues>
    void set(SubValues... args) {
        constexpr ValueT CLEAR_MASK = (SubValues::bitmask() | ...);
        ValueT set_mask = (args.shifted_value | ...);
        clear_and_set_bits(CLEAR_MASK, set_mask);
    }

    /**
     * @brief writes arg into the MemoryCell and overwrites any previous value
     */
    void write(ValueT arg) {
        MemoryCell::write(arg);
    }

    /**
     * @brief writes all of the given subvalues into the MemoryCell and sets all other bits to 0
     */
    template <class... SubValues, typename = typename std::enable_if_t<(SubValues::IS_SUB_VALUE && ...), void>>
    void write(SubValues... args) {
        MemoryCell::write((args.shifted_value | ...));
    }

    template <class SubValue>
    [[nodiscard]] ValueT read() const {
        return static_cast<ValueT>((MemoryCell::read() & SubValue::bitmask()) >> SubValue::OFFSET);
    }

    template <typename OtherMemoryCell>
    explicit operator BitField<OtherMemoryCell>() {
        return { MemoryCell::read() };
    }
};

using UInt8BitField = BitField<Integer<uint8_t>>;
using UInt16BitField = BitField<Integer<uint16_t>>;
using UInt32BitField = BitField<Integer<uint32_t>>;
using UInt64BitField = BitField<Integer<uint64_t>>;

template <uint8_t OFFSET, uint8_t LENGTH = 1>
using UInt8SubValue = UInt8BitField::SubValue<OFFSET, LENGTH>;
template <uint16_t OFFSET, uint8_t LENGTH = 1>
using UInt16SubValue = UInt16BitField::SubValue<OFFSET, LENGTH>;
template <uint32_t OFFSET, uint8_t LENGTH = 1>
using UInt32SubValue = UInt32BitField::SubValue<OFFSET, LENGTH>;
template <uint32_t OFFSET, uint8_t LENGTH = 1>
using UInt64SubValue = UInt64BitField::SubValue<OFFSET, LENGTH>;

} // namespace bitfield
