/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include <cstdint>

namespace stm::periphs::can {
struct TimingConfig {
    uint8_t t_rjw = 1;
    uint8_t t_sync = 1;
    uint8_t t_bs1 = 13;
    uint8_t t_bs2 = 2;

    [[nodiscard]] constexpr uint8_t get_bit_time() const {
        return (uint8_t)(t_sync + t_bs1 + t_bs2);
    }
};
} // namespace stm::periphs::can
