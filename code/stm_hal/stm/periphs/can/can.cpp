/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/periphs/can/can.hpp"
#include "stm/periphs/can/can_interrupt.hpp"
#include <cstddef>
#include <cstdint>

namespace stm::periphs::can {

ot::Ref<Can> g_can1_ref {}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
ot::Ref<Can> g_can2_ref {}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void Can::send_sync(const CanMsg& msg) {
    using namespace stm::regs::can::TIxR;
    using namespace stm::regs::can::TDTxR;

    constexpr size_t MAILBOX_NUM = 0;
    regs::can::TXMailbox& mailbox = can_.TX[MAILBOX_NUM];
    while (mailbox.isFull()) {
        if (get_bus_off_state()) {
            return;
        }
    }

    if (msg.ext_id) {
        mailbox.TIxR.write(RTR((uint32_t)msg.rtr), IDE((uint32_t)msg.ext_id), EXID(msg.can_id));
    } else {
        mailbox.TIxR.write(RTR((uint32_t)msg.rtr), IDE((uint32_t)msg.ext_id), STID(msg.can_id));
    }
    mailbox.TDTxR.write(DLC(msg.len));
    mailbox.TDLxR.write(msg.data[0]);
    mailbox.TDHxR.write(msg.data[1]);
    mailbox.TIxR.set(TXRQ(1));
}

void Can::wait_until_msg_is_sent() {
    constexpr size_t MAILBOX_NUM = 0;
    regs::can::TXMailbox& mailbox = can_.TX[MAILBOX_NUM];
    while (mailbox.isFull()) {}
}

bool Can::get_bus_off_state() const {
    using namespace regs::can::ESR;
    return can_.ESR.read<BOFF>() != 0;
}

bool Can::recv(CanMsg& out) {
    using namespace regs::can::RFxR;
    using namespace regs::can::RIxR;
    using namespace regs::can::RDTxR;

    if (can_.RF0R.read<FOVR>() != 0) {
        can_.RF0R.write(FOVR(1));
        printf("CAN receive overrun!");
    }

    if (can_.RF0R.read<FMP>() == 0) {
        return false;
    }
    const register_access::RegisterCopy rixr_copy { can_.RX[0].RIxR.read() };
    const register_access::RegisterCopy rdtxr_copy { can_.RX[0].RDTxR.read() };
    const bool is_ext_id = (bool)rixr_copy.read<IDE>();

    out = {
        { can_.RX[0].RDLxR.read(), can_.RX[0].RDHxR.read() },
        is_ext_id ? rixr_copy.read<EXID>() : rixr_copy.read<STID>(),
        (uint8_t)rdtxr_copy.read<DLC>(),
        is_ext_id,
        (bool)rixr_copy.read<RTR>()
    };

    can_.RF0R.write(RFOM(1));

    for (uint32_t status = 1; status != 0;) {
        status = can_.RF0R.read<RFOM>();
    }
    return true;
}

void Can::tx_irq_handler() {
    using namespace regs::can::TSR;
    if (can_.TSR.read<RQCP0>() == 1) {
        if (tx_mailbox_0_empty_callback_ref_) {
            tx_mailbox_0_empty_callback_ref_.get()();
        }
    }

    can_.TSR.set(RQCP0(1), RQCP1(1), RQCP2(1));
}

void Can::rx_0_irq_handler() {
    CanMsg out {};
    while (recv(out)) {
        if (rx_0_new_msg_callback_ref_) {
            rx_0_new_msg_callback_ref_.get()(out);
        }
    }

    using namespace regs::can::RFxR;
    can_.RF0R.write(FOVR(1), FULL(1));
}

Can::Can(CanConfig config) :
    can_(config.can.periph),
    filter_banks_ { config.can.filter_banks } {
    if (&can_ == &__PERIPHERAL_CAN2__) {
        // CAN2 mailboxes require CAN1 rcc to be enabled.
        rcc::enable_rcc_periph(rcc::CAN1_PERIPH);
    }
    rcc::enable_rcc_periph(config.can.rcc_periph);
    set_init_mode(true);
    configure_baudrate(config.can.timing_config,
                       config.can.get_max_baudrate() / config.baudrate);
    set_loopback(config.loopback);
    set_init_mode(false);
    leave_sleep_mode();
    filter01_receive_all(); // TODO(issue #10) more sophisticated filter setup

    using namespace regs::can::TSR;
    can_.TSR.write(ABRQ0(1), ABRQ1(1), ABRQ2(1));
}

void Can::filter01_receive_all() {
    using namespace regs::can::FMR;
    using namespace regs::can::FiRx;

    constexpr uint32_t FILTER_32BIT_MODE_ALL = 0x0FFF'FFFFUL;
    constexpr uint32_t EXTID_FILTER_ALL = 0x1FFF'FFFFUL;
    constexpr uint32_t FILTER_ALL = 0x7FFUL;
    size_t filter_bank_1 = filter_bank_cnt_++;
    size_t filter_bank_2 = filter_bank_cnt_++; // TODO(#10) add proper flexible filter setup including handling overflow
    auto& filter = filter_banks_[filter_bank_1];
    auto& filter_ext_id = filter_banks_[filter_bank_2];
    __PERIPHERAL_CAN1__.FMR.set(FINIT(1));
    __PERIPHERAL_CAN1__.FS1R.set_bits(FILTER_32BIT_MODE_ALL);

    // Extended ID
    filter_ext_id.FxR0.write(EXID(0), IDE(1), RTR(0));
    filter_ext_id.FxR1.write(EXID(~EXTID_FILTER_ALL), IDE(1), RTR(1));

    // Non-extended ID
    filter.FxR0.write(STID(0), IDE(0), RTR(0));
    filter.FxR1.write(STID(~FILTER_ALL), IDE(1), RTR(1));

    __PERIPHERAL_CAN1__.FA1R.set_bits(1UL << filter_bank_1 | 1UL << (filter_bank_2));
    __PERIPHERAL_CAN1__.FMR.set(FINIT(0));
}

void Can::clear_interrupt(NewRx0MessageInterrupt& interrupt) {
    const auto* callback_address = static_cast<RxCallback*>(&interrupt.get_callback());
    if (rx_0_new_msg_callback_ref_.is_valid()) {
        RxCallback* current_callback_address = &rx_0_new_msg_callback_ref_.get();
        if (callback_address != current_callback_address) {
            return;
        }
    }
    set_interrupt_and_callback(interrupt, false);
}

void Can::clear_interrupt(TxMailbox0IsEmptyInterrupt& interrupt) {
    const auto* callback_address = static_cast<TxCallback*>(&interrupt.get_callback());
    if (tx_mailbox_0_empty_callback_ref_.is_valid()) {
        TxCallback* current_callback_address = &tx_mailbox_0_empty_callback_ref_.get();
        if (callback_address != current_callback_address) {
            return;
        }
    }
    set_interrupt_and_callback(interrupt, false);
}

void Can::set_interrupt_and_callback(NewRx0MessageInterrupt& interrupt, bool enable) {
    using namespace regs::can;

    can_.IER.set(IER::FMPIE0(enable ? 1 : 0));

    rx_0_new_msg_callback_ref_ = ot::Ref<RxCallback> { interrupt.get_callback() };
}

void Can::set_interrupt_and_callback(TxMailbox0IsEmptyInterrupt& interrupt, bool enable) {
    using namespace regs::can;

    can_.IER.set(IER::TMEIE(enable ? 1 : 0));

    tx_mailbox_0_empty_callback_ref_ = ot::Ref<TxCallback> { interrupt.get_callback() };
}

bool Can::tx_mailbox_0_empty_interrupt_is_enabled() const {
    using namespace regs::can;

    return static_cast<bool>(can_.IER.read<IER::TMEIE>());
}

bool Can::rx_0_new_msg_interrupt_is_enabled() const {
    using namespace regs::can;

    return static_cast<bool>(can_.IER.read<IER::FMPIE0>());
}

void Can::configure_baudrate(TimingConfig timing_config, uint32_t prescaler) {
    using namespace regs::can::BTR;
    can_.BTR.write(BRP(prescaler - 1),
                   TS1(timing_config.t_bs1 - 1),
                   TS2(timing_config.t_bs2 - 1),
                   SJW(timing_config.t_rjw - 1));
}

void Can::set_init_mode(bool enable) {
    using namespace regs::can::MCR;
    using namespace regs::can::MSR;
    auto enable_i = (unsigned int)enable;
    can_.MCR.set(INRQ(enable_i));
    while (can_.MSR.read<INAK>() != enable_i) {}
}

void Can::leave_sleep_mode() {
    using namespace regs::can::MCR;
    can_.MCR.set(SLEEP(0U));
}

void Can::set_loopback(bool enable) {
    using namespace regs::can::BTR;
    if (enable) {
        can_.BTR.set(LBKM(static_cast<unsigned int>(enable)));
    }
}
} // namespace stm::periphs::can
