/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "clock.hpp"
#include "clock.hpp"
#include "critical_section.hpp"
#include "timer.hpp"
#include <chrono>
#include <condition_variable>
#include <thread>

namespace stm::support {

// The reference time needs to be globally accessible but non-const, as this needs to be settable
std::chrono::nanoseconds REFERENCE_TIME = 0ns; // NOLINT
void set_system_time(std::chrono::nanoseconds reference) {
    CriticalSectionToken critical_section {};
    REFERENCE_TIME = reference;
}

std::chrono::nanoseconds get_system_time() {
    return REFERENCE_TIME;
}

// dummy values for unused parameter of clock lib
static constexpr SteadyClock::duration DEFAULT_DURATION { 100 };

SteadyClock::time_point SteadyClock::now() {
    using namespace stm::support;
    auto now = Timer::current_time();
    return SteadyClock::time_point { now };
}
SystemClock::time_point SystemClock::now() {
    using namespace stm::support;
    auto now = Timer::current_time();
    return SystemClock::time_point { now + get_system_time() };
}

void sleep_for(std::chrono::milliseconds duration) {
    auto start = SteadyClock::now();
    while (SteadyClock::now() - start < duration) {
        await_global_trigger(DEFAULT_DURATION);
    }
}
void sleep_until(SystemClock::time_point time_point) {
    while (SystemClock::now() < time_point) {
        await_global_trigger(DEFAULT_DURATION);
    }
}
void await_global_trigger([[maybe_unused]] SteadyClock::duration timeout) {
    asm volatile("wfi");
}
} // namespace stm::support
