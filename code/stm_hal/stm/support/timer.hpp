/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <chrono>
#include <functional>

namespace stm::support {
class Timer {
public:
    Timer();
    [[nodiscard]] static std::chrono::nanoseconds current_time();
    [[nodiscard]] static uint16_t current_timer_count();
    static constexpr uint32_t INTERRUPT_NR = 54;
};
} // namespace stm::support