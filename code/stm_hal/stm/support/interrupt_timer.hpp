/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <chrono>
#include <functional>

namespace stm::support {
class InterruptTimer {
public:
    InterruptTimer(std::function<void()> on_timer, std::chrono::milliseconds period);
    static std::function<void()> on_timer; // NOLINT(bugprone-dynamic-static-initializers, readability-identifier-naming, cppcoreguidelines-avoid-non-const-global-variables)
    static constexpr uint32_t INTERRUPT_NR = 55;
};
} // namespace stm::support
