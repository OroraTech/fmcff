/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <cstdint>

namespace stm::periphs::rng {

/**
 * @brief provides a handle for the internal true random number generator peripheral
 */
class Rng {
public:
    Rng();

    uint32_t get_random_uint32();
    float get_random_float();
};

} // namespace stm::periphs::rng
