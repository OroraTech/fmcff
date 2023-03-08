/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <bit>
#include <concepts>
#include <cstdint>
#include <memory>
#include <type_traits>

namespace fmcff {
enum class ValueType {
    INT32,
    INT64,
    FLOAT,
    DOUBLE
    /* ... TODO more? */
};

constexpr const char* to_string(ValueType value_type) {
    switch (value_type) {
    case ValueType::INT32:
        return "INT32";
    case ValueType::INT64:
        return "INT64";
    case ValueType::FLOAT:
        return "FLOAT";
    case ValueType::DOUBLE:
        return "DOUBLE";
    }
    return "UNKNOWN_TYPE";
}

template <typename T>
ValueType VALUE_TYPE; // should generate a warning if ever used
template <>
constexpr ValueType VALUE_TYPE<int32_t> = ValueType::INT32; // NOLINT
template <>
constexpr ValueType VALUE_TYPE<int64_t> = ValueType::INT64; // NOLINT
template <>
constexpr ValueType VALUE_TYPE<float> = ValueType::FLOAT; // NOLINT
template <>
constexpr ValueType VALUE_TYPE<double> = ValueType::DOUBLE; // NOLINT

template <typename T>
concept FMCFFValueType = std::is_same_v<T, int32_t> || std::is_same_v<T, int64_t> || std::is_same_v<T, float> || std::is_same_v<T, double>;

class Value {
public:
    constexpr Value() = default;

    template <typename T>
    requires FMCFFValueType<T>
    constexpr void set(T val) {
        type = VALUE_TYPE<T>;
        if constexpr (sizeof(T) == 2) {
            value_[0][0] = std::bit_cast<Value2ByteT>(val);
        } else if constexpr (sizeof(T) == 4) {
            value_[0] = std::bit_cast<Value4ByteT>(val);
        } else if constexpr (sizeof(T) == 8) {
            value_ = std::bit_cast<Value8ByteT>(val);
        }
    }

    template <typename T>
    requires FMCFFValueType<T>
    constexpr T get() const {
        if (type != VALUE_TYPE<T>) {
            printf("%s: Getting wrong type: %s\r\n", __PRETTY_FUNCTION__, to_string(VALUE_TYPE<T>));
        }
        if constexpr (sizeof(T) == 2) {
            auto bufferptr = std::assume_aligned<2>(&value_[0][0]);
            return std::bit_cast<T>(*bufferptr);
        } else if constexpr (sizeof(T) == 4) {
            auto bufferptr = std::assume_aligned<4>(&value_[0]);
            return std::bit_cast<T>(*bufferptr);
        } else if constexpr (sizeof(T) == 8) {
            auto bufferptr = std::assume_aligned<8>(&value_);
            return std::bit_cast<T>(*bufferptr);
        }
    }

    constexpr ValueType get_type() const {
        return type;
    }

private:
    using Value2ByteT = std::array<char, 2>;
    using Value4ByteT = std::array<Value2ByteT, 2>;
    using Value8ByteT = std::array<Value4ByteT, 2>;
    using ValueT = Value8ByteT;

    ValueT value_ alignas(8) {};
    ValueType type {};
};
} // namespace fmcff
