/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstdint>

namespace stm::periphs::can {
struct CanMsg {
    uint32_t data[2];
    uint32_t can_id;
    uint8_t len;
    bool ext_id;
    bool rtr;

    [[nodiscard]] uint8_t* get_data_as_bytes() {
        return reinterpret_cast<uint8_t*>(&data); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
    [[nodiscard]] const uint8_t* get_data_as_bytes() const {
        return reinterpret_cast<const uint8_t*>(&data); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
};
} // namespace stm::periphs::can
