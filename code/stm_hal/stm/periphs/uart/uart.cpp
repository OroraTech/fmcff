/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/periphs/uart/uart.hpp"
#include "stm/regs/peripherals.hpp"

namespace stm::periphs::uart {
Uart::Uart(UartConfig config) :
    uart_(config.uart.periph) {
    rcc::enable_rcc_periph(config.uart.rcc_periph);
    configure_baudrate(config.baudrate, config.uart.input_clock);
    enable_periph_and_transmit();
}

void Uart::enable_periph_and_transmit() {
    using namespace regs::uart::CR1;
    uart_.CR1.set(UE(1), TE(1), RE(1));
}

void Uart::configure_baudrate(uint32_t baudrate, uint32_t input_clock) {
    const uint32_t mult = (&uart_ == &__PERIPHERAL_LPUART1__) ? 256 : 1;
    const uint32_t baudrate_divider = (input_clock / baudrate) * mult;

    uart_.BRR.write(baudrate_divider);
}

void Uart::write_sync(const std::byte* bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        const std::byte& c = bytes[i]; // NOLINT (cppcoreguidelines-pro-bounds-pointer-arithmetic)
        write_sync(c);
    }
}

void Uart::write_sync(const std::byte byte) {
    using namespace regs::uart::ISR;
    while (uart_.ISR.read<TXE>() == 0) {}
    uart_.TDR.write(static_cast<uint32_t>(byte));
}

size_t Uart::readline_blocking(std::byte* buffer, size_t maxsize, bool feedback) {
    std::byte cur {};
    size_t size = 0;
    while (size < maxsize - 1 && (char)cur != '\r') {
        cur = read_byte_blocking(feedback);
        buffer[size++] = cur; // NOLINT (cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    if (feedback) {
        write_sync(std::byte { '\n' });
    }
    return size - 1;
}

std::byte Uart::read_byte_blocking(bool feedback) {
    using namespace regs::uart::ISR;
    while (uart_.ISR.read<RXNE>() == 0) {}
    auto byte = static_cast<std::byte>(uart_.RDR.read());
    if (feedback) {
        write_sync(byte);
    }
    return byte;
}

std::optional<std::byte> Uart::read_byte(bool feedback) {
    using namespace regs::uart::ISR;
    if (uart_.ISR.read<RXNE>() == 0) {
        return {};
    }
    auto byte = static_cast<std::byte>(uart_.RDR.read());
    if (feedback) {
        write_sync(byte);
    }
    return { byte };
}

} // namespace stm::periphs::uart
