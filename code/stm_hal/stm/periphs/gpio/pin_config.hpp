/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include <compare>
#include <concepts>
#include <cstdint>
#include <type_traits>

#include "stm/regs/gpio_registers.hpp"

namespace stm::periphs::gpio {
enum class Mode : uint8_t {
    INPUT = 0,
    OUTPUT,
    ALTERNATE_FUNCTION,
    ANALOG
};

enum class OutputType : uint8_t {
    PUSHPULL = 0,
    OPENDRAIN = 1
};

enum class OutputSpeed : uint8_t {
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

enum class PullUpPullDown : uint8_t {
    NONE,
    PULLUP,
    PULLDOWN
};

enum class OutputState : uint8_t {
    LOW = 0,
    HIGH = 1
};

enum class PortPin : uint8_t {
    PX0,
    PX1,
    PX2,
    PX3,
    PX4,
    PX5,
    PX6,
    PX7,
    PX8,
    PX9,
    PX10,
    PX11,
    PX12,
    PX13,
    PX14,
    PX15
};

enum class AlternateFunction : uint8_t {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
};

using AF = AlternateFunction;

enum class Port : uint8_t {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I
};

struct Pin {
    uint8_t pin_number = -1;

    constexpr Pin() = default;

    constexpr Pin(Port port, PortPin pin) :
        pin_number { static_cast<uint8_t>(static_cast<uint8_t>(port) * 16 + static_cast<uint8_t>(pin)) } {}

    constexpr auto operator<=>(const Pin&) const = default;

    [[nodiscard]] constexpr uint8_t get_port_number() const {
        return static_cast<uint8_t>(pin_number / 16);
    }

    [[nodiscard]] constexpr uint8_t get_port_pin_number() const {
        return static_cast<uint8_t>(pin_number % 16);
    }

    [[nodiscard]] constexpr Port get_port() const {
        return static_cast<Port>(pin_number / 16);
    }

    [[nodiscard]] constexpr PortPin get_port_pin() const {
        return static_cast<PortPin>(pin_number % 16);
    }

    [[nodiscard]] constexpr uint16_t get_pin_mask() const {
        return 1 << get_port_pin_number();
    }
};

struct PinConfig {
    Pin pin;
    Mode mode = Mode::ANALOG;
    AlternateFunction alternate_function = AlternateFunction::AF0;
    OutputType output_type = OutputType::PUSHPULL;
    OutputSpeed speed = OutputSpeed::LOW;
    PullUpPullDown pupd = PullUpPullDown::NONE;
    OutputState initial_output_state = OutputState::LOW;
};

void apply_pin_config(const PinConfig& pin_config);

template <size_t SIZE>
void apply_pin_configs(const PinConfig (&pin_configs)[SIZE]) {
    for (size_t i = 0; i < SIZE; i++) {
        apply_pin_config(pin_configs[i]);
    }
}

constexpr Pin NULL_PIN {};

constexpr Pin PA0 { Port::A, PortPin::PX0 };
constexpr Pin PA1 { Port::A, PortPin::PX1 };
constexpr Pin PA2 { Port::A, PortPin::PX2 };
constexpr Pin PA3 { Port::A, PortPin::PX3 };
constexpr Pin PA4 { Port::A, PortPin::PX4 };
constexpr Pin PA5 { Port::A, PortPin::PX5 };
constexpr Pin PA6 { Port::A, PortPin::PX6 };
constexpr Pin PA7 { Port::A, PortPin::PX7 };
constexpr Pin PA8 { Port::A, PortPin::PX8 };
constexpr Pin PA9 { Port::A, PortPin::PX9 };
constexpr Pin PA10 { Port::A, PortPin::PX10 };
constexpr Pin PA11 { Port::A, PortPin::PX11 };
constexpr Pin PA12 { Port::A, PortPin::PX12 };
constexpr Pin PA13 { Port::A, PortPin::PX13 };
constexpr Pin PA14 { Port::A, PortPin::PX14 };
constexpr Pin PA15 { Port::A, PortPin::PX15 };

constexpr Pin PB0 { Port::B, PortPin::PX0 };
constexpr Pin PB1 { Port::B, PortPin::PX1 };
constexpr Pin PB2 { Port::B, PortPin::PX2 };
constexpr Pin PB3 { Port::B, PortPin::PX3 };
constexpr Pin PB4 { Port::B, PortPin::PX4 };
constexpr Pin PB5 { Port::B, PortPin::PX5 };
constexpr Pin PB6 { Port::B, PortPin::PX6 };
constexpr Pin PB7 { Port::B, PortPin::PX7 };
constexpr Pin PB8 { Port::B, PortPin::PX8 };
constexpr Pin PB9 { Port::B, PortPin::PX9 };
constexpr Pin PB10 { Port::B, PortPin::PX10 };
constexpr Pin PB11 { Port::B, PortPin::PX11 };
constexpr Pin PB12 { Port::B, PortPin::PX12 };
constexpr Pin PB13 { Port::B, PortPin::PX13 };
constexpr Pin PB14 { Port::B, PortPin::PX14 };
constexpr Pin PB15 { Port::B, PortPin::PX15 };

constexpr Pin PC0 { Port::C, PortPin::PX0 };
constexpr Pin PC1 { Port::C, PortPin::PX1 };
constexpr Pin PC2 { Port::C, PortPin::PX2 };
constexpr Pin PC3 { Port::C, PortPin::PX3 };
constexpr Pin PC4 { Port::C, PortPin::PX4 };
constexpr Pin PC5 { Port::C, PortPin::PX5 };
constexpr Pin PC6 { Port::C, PortPin::PX6 };
constexpr Pin PC7 { Port::C, PortPin::PX7 };
constexpr Pin PC8 { Port::C, PortPin::PX8 };
constexpr Pin PC9 { Port::C, PortPin::PX9 };
constexpr Pin PC10 { Port::C, PortPin::PX10 };
constexpr Pin PC11 { Port::C, PortPin::PX11 };
constexpr Pin PC12 { Port::C, PortPin::PX12 };
constexpr Pin PC13 { Port::C, PortPin::PX13 };
constexpr Pin PC14 { Port::C, PortPin::PX14 };
constexpr Pin PC15 { Port::C, PortPin::PX15 };

constexpr Pin PD0 { Port::D, PortPin::PX0 };
constexpr Pin PD1 { Port::D, PortPin::PX1 };
constexpr Pin PD2 { Port::D, PortPin::PX2 };
constexpr Pin PD3 { Port::D, PortPin::PX3 };
constexpr Pin PD4 { Port::D, PortPin::PX4 };
constexpr Pin PD5 { Port::D, PortPin::PX5 };
constexpr Pin PD6 { Port::D, PortPin::PX6 };
constexpr Pin PD7 { Port::D, PortPin::PX7 };
constexpr Pin PD8 { Port::D, PortPin::PX8 };
constexpr Pin PD9 { Port::D, PortPin::PX9 };
constexpr Pin PD10 { Port::D, PortPin::PX10 };
constexpr Pin PD11 { Port::D, PortPin::PX11 };
constexpr Pin PD12 { Port::D, PortPin::PX12 };
constexpr Pin PD13 { Port::D, PortPin::PX13 };
constexpr Pin PD14 { Port::D, PortPin::PX14 };
constexpr Pin PD15 { Port::D, PortPin::PX15 };

constexpr Pin PE0 { Port::E, PortPin::PX0 };
constexpr Pin PE1 { Port::E, PortPin::PX1 };
constexpr Pin PE2 { Port::E, PortPin::PX2 };
constexpr Pin PE3 { Port::E, PortPin::PX3 };
constexpr Pin PE4 { Port::E, PortPin::PX4 };
constexpr Pin PE5 { Port::E, PortPin::PX5 };
constexpr Pin PE6 { Port::E, PortPin::PX6 };
constexpr Pin PE7 { Port::E, PortPin::PX7 };
constexpr Pin PE8 { Port::E, PortPin::PX8 };
constexpr Pin PE9 { Port::E, PortPin::PX9 };
constexpr Pin PE10 { Port::E, PortPin::PX10 };
constexpr Pin PE11 { Port::E, PortPin::PX11 };
constexpr Pin PE12 { Port::E, PortPin::PX12 };
constexpr Pin PE13 { Port::E, PortPin::PX13 };
constexpr Pin PE14 { Port::E, PortPin::PX14 };
constexpr Pin PE15 { Port::E, PortPin::PX15 };

constexpr Pin PF0 { Port::F, PortPin::PX0 };
constexpr Pin PF1 { Port::F, PortPin::PX1 };
constexpr Pin PF2 { Port::F, PortPin::PX2 };
constexpr Pin PF3 { Port::F, PortPin::PX3 };
constexpr Pin PF4 { Port::F, PortPin::PX4 };
constexpr Pin PF5 { Port::F, PortPin::PX5 };
constexpr Pin PF6 { Port::F, PortPin::PX6 };
constexpr Pin PF7 { Port::F, PortPin::PX7 };
constexpr Pin PF8 { Port::F, PortPin::PX8 };
constexpr Pin PF9 { Port::F, PortPin::PX9 };
constexpr Pin PF10 { Port::F, PortPin::PX10 };
constexpr Pin PF11 { Port::F, PortPin::PX11 };
constexpr Pin PF12 { Port::F, PortPin::PX12 };
constexpr Pin PF13 { Port::F, PortPin::PX13 };
constexpr Pin PF14 { Port::F, PortPin::PX14 };
constexpr Pin PF15 { Port::F, PortPin::PX15 };

constexpr Pin PG0 { Port::G, PortPin::PX0 };
constexpr Pin PG1 { Port::G, PortPin::PX1 };
constexpr Pin PG2 { Port::G, PortPin::PX2 };
constexpr Pin PG3 { Port::G, PortPin::PX3 };
constexpr Pin PG4 { Port::G, PortPin::PX4 };
constexpr Pin PG5 { Port::G, PortPin::PX5 };
constexpr Pin PG6 { Port::G, PortPin::PX6 };
constexpr Pin PG7 { Port::G, PortPin::PX7 };
constexpr Pin PG8 { Port::G, PortPin::PX8 };
constexpr Pin PG9 { Port::G, PortPin::PX9 };
constexpr Pin PG10 { Port::G, PortPin::PX10 };
constexpr Pin PG11 { Port::G, PortPin::PX11 };
constexpr Pin PG12 { Port::G, PortPin::PX12 };
constexpr Pin PG13 { Port::G, PortPin::PX13 };
constexpr Pin PG14 { Port::G, PortPin::PX14 };
constexpr Pin PG15 { Port::G, PortPin::PX15 };

constexpr Pin PH0 { Port::H, PortPin::PX0 };
constexpr Pin PH1 { Port::H, PortPin::PX1 };
constexpr Pin PH2 { Port::H, PortPin::PX2 };
constexpr Pin PH3 { Port::H, PortPin::PX3 };
constexpr Pin PH4 { Port::H, PortPin::PX4 };
constexpr Pin PH5 { Port::H, PortPin::PX5 };
constexpr Pin PH6 { Port::H, PortPin::PX6 };
constexpr Pin PH7 { Port::H, PortPin::PX7 };
constexpr Pin PH8 { Port::H, PortPin::PX8 };
constexpr Pin PH9 { Port::H, PortPin::PX9 };
constexpr Pin PH10 { Port::H, PortPin::PX10 };
constexpr Pin PH11 { Port::H, PortPin::PX11 };
constexpr Pin PH12 { Port::H, PortPin::PX12 };
constexpr Pin PH13 { Port::H, PortPin::PX13 };
constexpr Pin PH14 { Port::H, PortPin::PX14 };
constexpr Pin PH15 { Port::H, PortPin::PX15 };

constexpr Pin PI0 { Port::I, PortPin::PX0 };
constexpr Pin PI1 { Port::I, PortPin::PX1 };
constexpr Pin PI2 { Port::I, PortPin::PX2 };
constexpr Pin PI3 { Port::I, PortPin::PX3 };
constexpr Pin PI4 { Port::I, PortPin::PX4 };
constexpr Pin PI5 { Port::I, PortPin::PX5 };
constexpr Pin PI6 { Port::I, PortPin::PX6 };
constexpr Pin PI7 { Port::I, PortPin::PX7 };
constexpr Pin PI8 { Port::I, PortPin::PX8 };
constexpr Pin PI9 { Port::I, PortPin::PX9 };
constexpr Pin PI10 { Port::I, PortPin::PX10 };
constexpr Pin PI11 { Port::I, PortPin::PX11 };
constexpr Pin PI12 { Port::I, PortPin::PX12 };
constexpr Pin PI13 { Port::I, PortPin::PX13 };
constexpr Pin PI14 { Port::I, PortPin::PX14 };
constexpr Pin PI15 { Port::I, PortPin::PX15 };
} // namespace stm::periphs::gpio
