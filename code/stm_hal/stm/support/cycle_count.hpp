/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <chrono>
#include <functional>
#include <span>

class CycleCount {
public:
    CycleCount();
    ~CycleCount();
    void register_tick();
    void print_ticks();
    std::span<uint32_t> get_ticks();

private:
    uint32_t ticks_[64] = { 0 };
    size_t index_ = 0;
};
