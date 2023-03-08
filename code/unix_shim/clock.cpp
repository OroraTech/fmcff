/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/support/clock.hpp"
#include <chrono>
#include <condition_variable>
#include <thread>

namespace stm::support {

SteadyClock::time_point SteadyClock::now() {
    return SteadyClock::time_point { std::chrono::steady_clock::now().time_since_epoch() };
}
SystemClock::time_point SystemClock::now() {
    return SystemClock::time_point { std::chrono::system_clock::now().time_since_epoch() };
}

void sleep_for(std::chrono::milliseconds duration) {
    std::this_thread::sleep_for(duration);
}
void sleep_until(SystemClock::time_point time_point) {
    std::this_thread::sleep_until(time_point);
}
void await_global_trigger([[maybe_unused]] SteadyClock::duration timeout) {
}
} // namespace stm::support
