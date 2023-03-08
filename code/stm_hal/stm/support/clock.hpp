/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <chrono>
#include <functional>

namespace stm::support {

using namespace std::chrono_literals;

void set_system_time(std::chrono::nanoseconds reference);
std::chrono::nanoseconds get_system_time();

// NOLINTBEGIN(readability-identifier-naming) the naming is required to remain compatible with std::chrono

/**
 * @defgroup clock Clock
 *
 * @brief Time, sleep and await implementations strongly following std::chrono
 */

/**
 * @ingroup clock
 * @brief Strongly monotonic with constant time between ticks. Usually returns the uptime, but don't count on that.
 *
 * Just use ot::clock::SteadyClock::now() to retrieve the time. This is also the function downstream implementations need
 * to implement.
 */
class SteadyClock {
public:
    using rep = int64_t;
    using period = std::nano;
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<SteadyClock>;

    static constexpr bool is_steady = true;

    /**
     * @brief Get the current time of the SteadyClock.
     * @return the current time as std::chrono::time_point
     */
    static time_point now();
};
static_assert(std::chrono::is_clock_v<SteadyClock>, "ot::SteadyClock it not compatible with std::chrono");

/**
 * @ingroup clock
 * @brief System time, usually UTC, returning the absolute time since Unix epoch (1.1.1970 00:00)
 *
 * Just use ot::clock::SystemClock::now() to retrieve the time. This is also the function downstream implementations need
 * to implement.
 */
class SystemClock {
public:
    using rep = int64_t;
    using period = std::nano;
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<SystemClock>;

    static constexpr bool is_steady = false;

    /**
     * @brief Get the current time of the SystemClock. Should be UTC.
     * @return the current time as std::chrono::time_point with Unix epoch as base (since 1.1.1970 00:00)
     */
    static time_point now();
};
static_assert(std::chrono::is_clock_v<SteadyClock>, "ot::SystemClock it not compatible with std::chrono");
// NOLINTEND(readability-identifier-naming)

/**
 * @ingroup clock
 * @brief Sleep until now() + duration
 *
 * @param duration the time to sleep for
 */
void sleep_for(std::chrono::milliseconds duration);

/**
 * @ingroup clock
 * @brief Sleep until time_point
 *
 * @param time_point the time to sleep until (Unix epoch)
 */
void sleep_until(SystemClock::time_point time_point);

/**
 * @ingroup clock
 * @brief Trigger a global event that other can wait for. Implemented on Linux using a condition variable to mimic ARM wait-for-interrupt (wfi) behaviour
 */
void global_trigger();

/**
 * @ingroup clock
 * @brief Wait for a global trigger event to happen. On ARM this is implemented using wait-for-interrupt (wfi)
 * @param timeout Stop waiting after <timeout> time
 */
void await_global_trigger(SteadyClock::duration timeout);

using AwaitConditionCallback = std::function<bool()>;

/**
 * @ingroup clock
 * @brief Repeatedly call await_global_trigger until a condition is reached
 * @param timeout Stop waiting after this time and return false
 * @param await_condition A function returning the condition state, if the function returns true await_trigger will return true
 * @return returns true if the condition returned true in time, false if the timeout was reached
 */
inline bool await_triggered(SteadyClock::duration timeout, const AwaitConditionCallback& await_condition) {
    auto start = SteadyClock::now();
    SteadyClock::duration used_time {};
    do {
        if (await_condition()) {
            return true;
        }
        await_global_trigger(timeout - used_time);
        used_time = SteadyClock::now() - start;
    } while (used_time < timeout);
    return false;
}

/**
 * @ingroup clock
 * @brief helper class to provide timeout functionality
 *
 * @tparam ClockT the clock to which the timeout shall be referenced
 */
template <class ClockT = SteadyClock>
class Timeout {
public:
    explicit Timeout(typename ClockT::duration time, typename ClockT::time_point start_time = ClockT::now()) :
        end_time_ { start_time + time } {}

    [[nodiscard]] bool has_passed() const {
        return ClockT::now() >= end_time_;
    }

    [[nodiscard]] typename ClockT::duration get_remaining_time() const {
        return end_time_ - ClockT::now();
    }

private:
    typename ClockT::time_point end_time_;
};

}
