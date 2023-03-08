/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include <cstdio>

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <span>
#include <type_traits>

#include "value.hpp"

namespace fmcff {

class ValueRange {
public:
    constexpr ValueRange() = default;

    explicit constexpr ValueRange(int id) :
        id { id } {}

    template <typename T>
    constexpr ValueRange(int id, T min, T max) :
        id { id } {
        value_min.set(min);
        value_max.set(max);
    }

    template <typename T>
    requires FMCFFValueType<T> // necessary so that this doesn't accidentally get picked for pointers(where you would want the other overload)
    constexpr bool is_in_range(T val, size_t value_size = sizeof(T)) const {
        if (sizeof(T) != value_size) {
            /* technically this is not necessary, but otherwise the compiler does not believe me this is safe */
            return false;
        }

        T min_val = value_min.get<T>();
        T max_val = value_max.get<T>();

        return val >= min_val && val <= max_val;
    }

    bool is_in_range(const void* anonymous_value, size_t value_size, ValueType type) const {
        if (type != value_min.get_type()) {
            printf("Checking range for %s value, but range was created for %s\r\n", to_string(type), to_string(value_min.get_type()));
            return false;
        }
        switch (type) {
        case ValueType::INT32: {
            anonymous_value = std::assume_aligned<4>(anonymous_value);
            return is_in_range(*(const int32_t*)anonymous_value, value_size);
        }
        case ValueType::INT64: {
            anonymous_value = std::assume_aligned<8>(anonymous_value);
            return is_in_range(*(const int64_t*)anonymous_value, value_size);
        }
        case ValueType::FLOAT: {
            anonymous_value = std::assume_aligned<4>(anonymous_value);
            return is_in_range(*(const float*)anonymous_value, value_size);
        }
        case ValueType::DOUBLE: {
            anonymous_value = std::assume_aligned<8>(anonymous_value);
            return is_in_range(*(const double*)anonymous_value, value_size);
        }
        }
        return false;
    }

    constexpr bool operator==(const ValueRange& other) { return other.id == id; }

private:
    int id {}; /* Literally any ID, e.g. Cyphal Port */

    Value value_min {};
    Value value_max {};
};
} // namespace fmcff
