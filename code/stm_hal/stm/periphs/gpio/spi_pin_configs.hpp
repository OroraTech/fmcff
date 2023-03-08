/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/periphs/gpio/pin_config.hpp"
#include "stm/periphs/spi/periphs.hpp"

namespace stm::periphs::gpio {

enum class SpiPinFunction {
    MISO,
    MOSI,
    SCK,
    NSS
};

template <Pin PIN, AlternateFunction AF>
// NOLINTNEXTLINE(bugprone-dynamic-static-initializers) warning makes no sense here
constexpr PinConfig SPI_PIN_CONF {
    .pin = PIN,
    .mode = Mode::ALTERNATE_FUNCTION,
    .alternate_function = AF,
    .output_type = OutputType::PUSHPULL,
    .speed = OutputSpeed::VERY_HIGH,
    .pupd = PullUpPullDown::NONE,
};

template <spi::SpiDef, Pin PIN, SpiPinFunction>
constexpr PinConfig SPI_PIN_CONFIG = [] { // NOLINT(bugprone-dynamic-static-initializers) warning make no sense here
    static_assert(PIN == NULL_PIN, "Spi pin is neither NULL_PIN nor valid for it's function.");
    return SPI_PIN_CONF<NULL_PIN, AF::AF0>;
}();

template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA11, SpiPinFunction::MISO> = SPI_PIN_CONF<PA11, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA6, SpiPinFunction::MISO> = SPI_PIN_CONF<PA6, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PB4, SpiPinFunction::MISO> = SPI_PIN_CONF<PB4, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PE14, SpiPinFunction::MISO> = SPI_PIN_CONF<PE14, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PG3, SpiPinFunction::MISO> = SPI_PIN_CONF<PG3, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA12, SpiPinFunction::MOSI> = SPI_PIN_CONF<PA12, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA7, SpiPinFunction::MOSI> = SPI_PIN_CONF<PA7, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PB5, SpiPinFunction::MOSI> = SPI_PIN_CONF<PB5, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PE15, SpiPinFunction::MOSI> = SPI_PIN_CONF<PE15, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PG4, SpiPinFunction::MOSI> = SPI_PIN_CONF<PG4, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA15, SpiPinFunction::NSS> = SPI_PIN_CONF<PA15, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA4, SpiPinFunction::NSS> = SPI_PIN_CONF<PA4, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PB0, SpiPinFunction::NSS> = SPI_PIN_CONF<PB0, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PE12, SpiPinFunction::NSS> = SPI_PIN_CONF<PE12, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PG5, SpiPinFunction::NSS> = SPI_PIN_CONF<PG5, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA1, SpiPinFunction::SCK> = SPI_PIN_CONF<PA1, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PA5, SpiPinFunction::SCK> = SPI_PIN_CONF<PA5, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PB3, SpiPinFunction::SCK> = SPI_PIN_CONF<PB3, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PE13, SpiPinFunction::SCK> = SPI_PIN_CONF<PE13, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI1DEF, PG2, SpiPinFunction::SCK> = SPI_PIN_CONF<PG2, AF::AF5>;

template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB14, SpiPinFunction::MISO> = SPI_PIN_CONF<PB14, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PC2, SpiPinFunction::MISO> = SPI_PIN_CONF<PC2, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PD3, SpiPinFunction::MISO> = SPI_PIN_CONF<PD3, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PI2, SpiPinFunction::MISO> = SPI_PIN_CONF<PI2, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB15, SpiPinFunction::MOSI> = SPI_PIN_CONF<PB15, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PC1, SpiPinFunction::MOSI> = SPI_PIN_CONF<PC1, AF::AF3>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PC3, SpiPinFunction::MOSI> = SPI_PIN_CONF<PC3, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PD4, SpiPinFunction::MOSI> = SPI_PIN_CONF<PD4, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PI3, SpiPinFunction::MOSI> = SPI_PIN_CONF<PI3, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB12, SpiPinFunction::NSS> = SPI_PIN_CONF<PB12, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB9, SpiPinFunction::NSS> = SPI_PIN_CONF<PB9, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PD0, SpiPinFunction::NSS> = SPI_PIN_CONF<PD0, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PI0, SpiPinFunction::NSS> = SPI_PIN_CONF<PI0, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PA9, SpiPinFunction::SCK> = SPI_PIN_CONF<PA9, AF::AF3>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB10, SpiPinFunction::SCK> = SPI_PIN_CONF<PB10, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PB13, SpiPinFunction::SCK> = SPI_PIN_CONF<PB13, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PD1, SpiPinFunction::SCK> = SPI_PIN_CONF<PD1, AF::AF5>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PD3, SpiPinFunction::SCK> = SPI_PIN_CONF<PD3, AF::AF3>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI2DEF, PI1, SpiPinFunction::SCK> = SPI_PIN_CONF<PI1, AF::AF5>;

template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PB4, SpiPinFunction::MISO> = SPI_PIN_CONF<PB4, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PC11, SpiPinFunction::MISO> = SPI_PIN_CONF<PC11, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PG10, SpiPinFunction::MISO> = SPI_PIN_CONF<PG10, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PB5, SpiPinFunction::MOSI> = SPI_PIN_CONF<PB5, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PC12, SpiPinFunction::MOSI> = SPI_PIN_CONF<PC12, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PG11, SpiPinFunction::MOSI> = SPI_PIN_CONF<PG11, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PA15, SpiPinFunction::NSS> = SPI_PIN_CONF<PA15, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PA4, SpiPinFunction::NSS> = SPI_PIN_CONF<PA4, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PG12, SpiPinFunction::NSS> = SPI_PIN_CONF<PG12, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PB3, SpiPinFunction::SCK> = SPI_PIN_CONF<PB3, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PC10, SpiPinFunction::SCK> = SPI_PIN_CONF<PC10, AF::AF6>;
template <>
constexpr PinConfig SPI_PIN_CONFIG<spi::SPI3DEF, PG9, SpiPinFunction::SCK> = SPI_PIN_CONF<PG9, AF::AF6>;

} // namespace stm::periphs::gpio
