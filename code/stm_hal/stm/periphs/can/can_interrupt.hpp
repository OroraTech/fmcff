/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "generic/shared.hpp"
#include "stm/periphs/can/can.hpp"
#include "stm/periphs/can/can_msg.hpp"

namespace stm::periphs::can {

/**
 * @brief Interrupt that is called when a new element enters the CAN receive 0 fifo.
 *
 * @note Intended to be used by the Can class which calls the interrupt
 * every time the source creates an interrupt.
 */
class NewRx0MessageInterrupt {
public:
    NewRx0MessageInterrupt(Can& can, const RxCallback& callback) :
        can_ { can }, callback_ { callback } {
        can_.set_interrupt(*this);
    }

    NewRx0MessageInterrupt(NewRx0MessageInterrupt&& other) = default;
    NewRx0MessageInterrupt(const NewRx0MessageInterrupt& other) = delete;

    NewRx0MessageInterrupt& operator=(const NewRx0MessageInterrupt& other) = delete;
    NewRx0MessageInterrupt& operator=(NewRx0MessageInterrupt&& other) = delete;

    ~NewRx0MessageInterrupt() {
        can_.clear_interrupt(*this);
    }

    ot::Shared<RxCallback>& get_callback() {
        return callback_;
    }

private:
    Can& can_;
    ot::Shared<RxCallback> callback_;
};

/**
 * @brief Interrupt that is called when the CAN transmit mailbox 0 becomes empty.
 *
 * @note Intended to be used by the Can class which calls the interrupt
 * every time the source creates an interrupt.
 */
class TxMailbox0IsEmptyInterrupt {
public:
    TxMailbox0IsEmptyInterrupt(Can& can, const TxCallback& callback) :
        can_ { can }, callback_ { callback } {
        can_.set_interrupt(*this);
    }

    TxMailbox0IsEmptyInterrupt(TxMailbox0IsEmptyInterrupt&& other) = default;
    TxMailbox0IsEmptyInterrupt(const TxMailbox0IsEmptyInterrupt& other) = delete;

    TxMailbox0IsEmptyInterrupt& operator=(const TxMailbox0IsEmptyInterrupt& other) = delete;
    TxMailbox0IsEmptyInterrupt& operator=(TxMailbox0IsEmptyInterrupt&& other) = delete;

    ~TxMailbox0IsEmptyInterrupt() {
        can_.clear_interrupt(*this);
    }

    ot::Shared<TxCallback>& get_callback() {
        return callback_;
    }

private:
    Can& can_;
    ot::Shared<TxCallback> callback_;
};

} // namespace stm::periphs::can
