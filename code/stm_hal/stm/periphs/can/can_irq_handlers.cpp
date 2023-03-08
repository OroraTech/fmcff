/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "generic/abort.hpp"
#include "stm/periphs/can/can.hpp"
#include "stm/startup/irq_handlers.hpp"

extern "C" {

[[gnu::used]] void CAN1_TX_IRQHandler() {
    using stm::periphs::can::g_can1_ref;
    if (g_can1_ref) {
        g_can1_ref->tx_irq_handler();
    } else {
        ot::abort();
    }
}

[[gnu::used]] void CAN1_RX0_IRQHandler() {
    using stm::periphs::can::g_can1_ref;
    if (g_can1_ref) {
        g_can1_ref->rx_0_irq_handler();
    } else {
        ot::abort();
    }
}

[[gnu::used]] void CAN2_TX_IRQHandler() {
    using stm::periphs::can::g_can2_ref;
    if (g_can2_ref) {
        g_can2_ref->tx_irq_handler();
    } else {
        ot::abort();
    }
}

[[gnu::used]] void CAN2_RX0_IRQHandler() {
    using stm::periphs::can::g_can2_ref;
    if (g_can2_ref) {
        g_can2_ref->rx_0_irq_handler();
    } else {
        ot::abort();
    }
}
}
