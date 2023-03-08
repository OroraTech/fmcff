/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

inline void enable_interrupts() {
    asm volatile inline("cpsie i");
}

inline void disable_interrupts() {
    asm volatile inline("cpsid i");
}
