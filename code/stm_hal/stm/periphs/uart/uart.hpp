/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once

#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/gpio/uart_pin_configs.hpp"
#include "stm/periphs/uart/uart_config.hpp"
#include "stm/regs/uart_registers.hpp"
#include <optional>

namespace stm::periphs::uart {
/**
 * @brief Initialize and use an UART peripheral.
 * Use init() to construct an Uart object and initialize the peripheral.
 */
class Uart {
public:
    /**
     * @brief Initialize the UART peripheral described by CONFIG.
     *
     * @param CONFIG A UartConfig struct containing at least the desired module and baudrate.
     */
    template <UartConfig CONFIG>
    static Uart init();

    /**
     * @brief Write a full fixed size byte array to TX
     * @note This function blocks until the write has completed
     *
     * @param bytes A fixed size array
     */
    template <size_t LENGTH>
    void write_sync(const std::byte (&bytes)[LENGTH]) { write_sync(bytes, LENGTH); }

    /**
     * @brief Write a full fixed size character array to TX
     * @note This function blocks until the write has completed
     * @note If the last character is a '\0' it will assume zero-termination. Use the std::byte version if you don't want this.
     *
     * @param str A fixed size array
     */
    template <size_t LENGTH>
    void write_sync(const char (&str)[LENGTH]) {
        if (str[LENGTH - 1] == '\0') {
            write_sync((const std::byte(&)[LENGTH - 1]) str);
        } else {
            write_sync((const std::byte(&)[LENGTH])str);
        }
    }

    /**
     * @brief Write a dynamic byte array with a given size to TX
     * @note This function blocks until the write has completed
     *
     * @param str A pointer to a byte array
     * @param size The amount of bytes to write to TX
     */
    void write_sync(const std::byte* bytes, size_t size);

    /**
     * @brief Write a single byte to TX
     * @note This function blocks until the write has completed
     *
     * @param byte A single byte
     */
    void write_sync(std::byte byte);

    /**
     * @brief Block and read a line from RX until receiving '\r' to a fixed size buffer.
     * @note The output does not contain newline characters.
     *
     * @param buffer A fixed size array for buffering
     * @param feedback Echo each received byte immediately to TX
     *
     * @return The amount of bytes read
     */
    template <size_t LENGTH>
    size_t readline_blocking(std::byte (&buffer)[LENGTH], bool feedback = false) { return readline_blocking(buffer, LENGTH, feedback); }

    /**
     * @brief Block and read a line from RX until receiving '\r' to a given pointer location
     * The output does not contain newline characters.
     *
     * @param buffer A pointer to buffer to
     * @param maxsize The available space at the pointed to location
     * @param feedback Echo each received byte immediately to TX
     *
     * @return The amount of bytes read
     */
    size_t readline_blocking(std::byte* buffer, size_t maxsize, bool feedback = false);

    /**
     * @brief Block and read a single byte from RX
     *
     * @param feedback Echo each received byte immediately to TX
     *
     * @return A single byte
     */
    std::byte read_byte_blocking(bool feedback = false);

    /**
     * @brief Try to instantly read a single byte from RX
     *
     * @param feedback Echo each received byte immediately to TX
     *
     * @return A single byte if one was input, empty optional if not
     */
    std::optional<std::byte> read_byte(bool feedback = false);

private:
    explicit Uart(UartConfig config);

    void enable_periph_and_transmit();
    void configure_baudrate(uint32_t baudrate, uint32_t input_clock);

    regs::uart::UARTStruct& uart_;
};

template <UartConfig CONFIG>
Uart Uart::init() {
    constexpr gpio::PinConfig TX_CONFIG = gpio::UART_PIN_CONFIG<CONFIG.uart, CONFIG.tx, gpio::UartPinFunction::TX>;
    gpio::apply_pin_config(TX_CONFIG);
    constexpr gpio::PinConfig RX_CONFIG = gpio::UART_PIN_CONFIG<CONFIG.uart, CONFIG.rx, gpio::UartPinFunction::RX>;
    gpio::apply_pin_config(RX_CONFIG);
    return Uart(CONFIG);
}
} // namespace stm::periphs::uart
