/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"
#include "stm/cortex_m/register_access/reserved_bytes.hpp"

namespace stm::regs::exti {
using namespace stm::register_access;

struct EXTIStruct {
    Register IMR1;
    Register EMR1;
    Register RTSR1;
    Register FTSR1;
    Register SWIER1;
    Register PR1;
    Register IMR2;
    Register EMR2;
    Register RTSR2;
    Register FTSR2;
    Register SWIER2;
    Register PR2;
};

}
