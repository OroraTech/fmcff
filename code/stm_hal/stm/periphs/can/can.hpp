/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/cortex_m/nvic.hpp"
#include "stm/periphs/can/can_config.hpp"
#include "stm/periphs/can/can_msg.hpp"
#include "stm/periphs/gpio/can_pin_configs.hpp"

#include "generic/shared.hpp"

#include <functional>

namespace stm::periphs::can {

class NewRx0MessageInterrupt;
class TxMailbox0IsEmptyInterrupt;

using RxCallback = std::function<void(CanMsg&)>;
using TxCallback = std::function<void()>;

/**
 * @brief Initialize and use a CAN peripheral.
 * Use init() to construct a Can object and initialize the peripheral.
 */
class Can {
public:
    /**
     * @brief Initialize the CAN peripheral described by CONFIG. Does NOT initialize pins.
     *
     * @param CONFIG A CanConfig struct containing at least the desired module and baudrate.
     */
    template <CanConfig CONFIG>
    static Can init();

    template <CanConfig CONFIG>
    static ot::Shared<Can> init_shared();

    /**
     * @brief Send a CanMsg on the CAN-Bus
     * @note This function blocks until msg has been successfully put into the TX mailbox
     *
     * @param msg A CAN message
     */
    void send_sync(const CanMsg& msg);

    void wait_until_msg_is_sent();

    /**
     * @brief returns true if the CAN is in bus-off state
     */
    [[nodiscard]] bool get_bus_off_state() const;

    /**
     * @brief Receive a CanMsg from the CAN-Bus
     * @note Immediately returns, check return if a message has been received
     *
     * @param out The received CAN message, if any
     *
     * @return true if a message has been received, false if not
     */
    [[nodiscard]] bool recv(CanMsg& out);

    // TODO(issue #13) sender and receiver may be split in the future

    /**
     * @brief Checks if the receive fifo 0 new message interrupt is enabled.
     */
    [[nodiscard]] bool tx_mailbox_0_empty_interrupt_is_enabled() const;

    /**
     * @brief Checks if the receive fifo 0 new message interrupt is enabled.
     */
    [[nodiscard]] bool rx_0_new_msg_interrupt_is_enabled() const;

    /**
     * @brief Called whenever a tx mailbox becomes empty.
     */
    void tx_irq_handler();

    /**
     * @brief Called whenever receive fifo 0 creates an interrupt, usually on receiving a new message.
     */
    void rx_0_irq_handler();

private:
    friend class NewRx0MessageInterrupt;
    friend class TxMailbox0IsEmptyInterrupt;

    explicit Can(CanConfig config);
    void filter01_receive_all();

    /**
     * @brief Enables the receive fifo 0 new message received interrupt and sets the callback.
     *
     * @note Only called by CanInterrupt::CanInterrupt
     *
     * @param interrupt Interrupt to be set.
     */
    inline void set_interrupt(NewRx0MessageInterrupt& interrupt) {
        set_interrupt_and_callback(interrupt, true);
    }
    inline void set_interrupt(TxMailbox0IsEmptyInterrupt& interrupt) {
        set_interrupt_and_callback(interrupt, true);
    }

    /**
     * @brief Disables the receive fifo 0 new message received interrupt. Cleares the callback,
     *        if the callback has not been changed.
     *
     * @note Only called by CanInterrupt::~CanInterrupt
     *
     * @param interrupt Interrupt to be cleared.
     */
    void clear_interrupt(NewRx0MessageInterrupt& interrupt);
    void clear_interrupt(TxMailbox0IsEmptyInterrupt& interrupt);

    void set_interrupt_and_callback(NewRx0MessageInterrupt& interrupt, bool enable);
    void set_interrupt_and_callback(TxMailbox0IsEmptyInterrupt& interrupt, bool enable);
    void configure_baudrate(TimingConfig timing_config, uint32_t prescaler);
    void set_init_mode(bool enable);
    void leave_sleep_mode();
    void set_loopback(bool enable);

    ot::Ref<TxCallback> tx_mailbox_0_empty_callback_ref_;
    ot::Ref<RxCallback> rx_0_new_msg_callback_ref_;
    regs::can::CANStruct& can_;
    regs::can::FilterBank (&filter_banks_)[14];
    size_t filter_bank_cnt_ = 0;
};

extern ot::Ref<Can> g_can1_ref; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, bugprone-dynamic-static-initializers)
extern ot::Ref<Can> g_can2_ref; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables, bugprone-dynamic-static-initializers)

template <CanConfig CONFIG>
Can Can::init() {
    constexpr TimingConfig TC = CONFIG.can.timing_config;

    static_assert(TC.get_bit_time() > 0, "Bit time cannot be 0.");
    static_assert((CONFIG.can.get_max_baudrate() % CONFIG.baudrate) == 0,
                  "CAN maximum baudrate must be a multiple of the desired baudrate.");

    constexpr gpio::PinConfig TX_CONFIG = gpio::CAN_PIN_CONFIG<CONFIG.can, CONFIG.tx, gpio::CanPinFunction::TX>;
    gpio::apply_pin_config(TX_CONFIG);
    constexpr gpio::PinConfig RX_CONFIG = gpio::CAN_PIN_CONFIG<CONFIG.can, CONFIG.rx, gpio::CanPinFunction::RX>;
    gpio::apply_pin_config(RX_CONFIG);

    constexpr uint8_t TX_IRQ_N = CONFIG.can.irq_n;
    nvic::Nvic::enable_irq(TX_IRQ_N);

    constexpr uint8_t RX_0_IRQ_N = TX_IRQ_N + 1;
    nvic::Nvic::enable_irq(RX_0_IRQ_N);

    return Can(CONFIG);
}

template <CanConfig CONFIG>
ot::Shared<Can> Can::init_shared() {
    ot::Shared<Can> shared { ot::Shared<Can> { init<CONFIG>() } };

    if (&CONFIG.can.periph == &__PERIPHERAL_CAN1__) {
        g_can1_ref = ot::Ref<Can> { shared };
        return shared;
    }

    if (&CONFIG.can.periph == &__PERIPHERAL_CAN2__) {
        g_can2_ref = ot::Ref<Can> { shared };
        return shared;
    }

    ot::abort();
}

} // namespace stm::periphs::can
