/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

namespace stm::support {
#ifndef __UNIT_TEST__

/**
 * @brief a token that disables all interrupts except for fault handlers for it's lifetime.
 */
class CriticalSectionToken {
public:
    CriticalSectionToken() :
        cached_primask_ { read_current_primask() } {
        asm volatile("cpsid i");
    }

    ~CriticalSectionToken() {
        release();
    }

    CriticalSectionToken(CriticalSectionToken&&) = delete;
    CriticalSectionToken(const CriticalSectionToken&) = delete;
    CriticalSectionToken operator=(CriticalSectionToken&&) = delete;
    CriticalSectionToken operator=(const CriticalSectionToken&) = delete;

    /**
     * releases the token early
     */
    void release() const {
        write_primask(cached_primask_);
    }

private:
    static uint32_t read_current_primask() {
        uint32_t result = 0;
        asm volatile("mrs %0,PRIMASK"
                     : "=r"(result));
        return result;
    }

    static void write_primask(uint32_t value) {
        asm volatile("msr PRIMASK, %0"
                     :
                     : "r"((uint32_t)value));
    }

    uint32_t cached_primask_;
};
#else
class CriticalSectionToken {};
#endif

} // namespace stm::support
