/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstdint>

namespace stm::register_access {
#ifndef __UNIT_TEST__

/**
 * Represents a single memory mapped IO register
 * Functions are using inline assembly because it wouldn't be possible to write with 32 bit and 16 bit instructions
 * to the same memory location without breaking C++ strict aliasing rules otherwise
 */
class MMIO {
private:
    volatile uint32_t reg_;

    ~MMIO() = delete;

public:
    using ValueT = uint32_t;
    inline void write(const uint32_t value) {
        asm volatile("str %1, %0"
                     : "=m"(reg_)
                     : "r"((uint32_t)value));
    }

    inline void write8(const uint8_t value) {
        asm volatile("strb %1, %0"
                     : "=m"(reg_)
                     : "r"((uint32_t)value));
    }

    inline void write16(const uint16_t value) {
        asm volatile("strh %1, %0"
                     : "=m"(reg_)
                     : "r"((uint32_t)value));
    }

    [[nodiscard]] inline uint32_t read() const {
        uint32_t result = 0;
        asm volatile("ldr %0, %1"
                     : "=r"(result)
                     : "m"(reg_));
        return result;
    }

    [[nodiscard]] inline uint8_t read8() const {
        uint32_t result = 0;
        asm volatile("ldrb %0, %1"
                     : "=r"(result)
                     : "m"(reg_));
        return ((uint8_t)result);
    }

    [[nodiscard]] inline uint16_t read16() const {
        uint32_t result = 0;
        asm volatile("ldrh %0, %1"
                     : "=r"(result)
                     : "m"(reg_));
        return ((uint16_t)result);
    }
};

class MMIO8 {
private:
    volatile uint8_t reg_;

    ~MMIO8() = delete;

public:
    using ValueT = uint8_t;
    inline void write(const ValueT value) {
        asm volatile("strb %1, %0"
                     : "=m"(reg_)
                     : "r"(value));
    }

    [[nodiscard]] inline ValueT read() const {
        uint32_t result = 0;
        asm volatile("ldrb %0, %1"
                     : "=r"(result)
                     : "m"(reg_));
        return static_cast<ValueT>(result);
    }
};

#else

/**
 *  Implementation of MMIO without assembly for use in unit tests.
 */
class MMIO {
public:
    using ValueT = uint32_t;
    void write(ValueT value);
    void write16(uint16_t value);
    void write8(uint8_t value);
    [[nodiscard]] ValueT read() const;
    [[nodiscard]] uint16_t read16() const;
    [[nodiscard]] uint8_t read8() const;

    volatile ValueT reg;
};
class MMIO8 {
public:
    using ValueT = uint8_t;
    void write(ValueT value);
    [[nodiscard]] ValueT read() const;

    volatile ValueT reg;
};

#endif
} // namespace stm::register_access
