/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "rng.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"
#include "stm/regs/peripherals.hpp"

#include <limits>

namespace stm::periphs::rng {
    
Rng::Rng(){
    using namespace regs::rng::CR;
    using namespace regs::rcc::CRRCR;
    __PERIPHERAL_RCC__.CRRCR.set(HSI48ON(1)); // enable HSI48 clock for RNG (TODO: move this to clock configuration)
    while(__PERIPHERAL_RCC__.CRRCR.read<HSI48RDY>()!=1);

    rcc::enable_rcc_periph(stm::periphs::rcc::RNG_PERIPH);
    __PERIPHERAL_RNG__.CR.write(RNGEN(1));
}

uint32_t Rng::get_random_uint32(){
    using namespace regs::rng::SR;
    //TODO: error handling
    while(__PERIPHERAL_RNG__.SR.read<DRDY>() != 1);

    return __PERIPHERAL_RNG__.DR.read();
}

float Rng::get_random_float(){
    return float(get_random_uint32())/float(std::numeric_limits<uint32_t>::max());
}

} // namespace stm::periphs::rng
