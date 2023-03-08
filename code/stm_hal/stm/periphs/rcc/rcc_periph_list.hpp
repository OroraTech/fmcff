/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

/**
 * @file rcc_periph_list.hpp
 *
 * This file lists all of the RccPeriph objects that we need.
 * See descriptions of all RCC_AxByENR registers in the reference manual.
 */

#pragma once
#include "stm/periphs/rcc/rcc_periph.hpp"
namespace stm::periphs::rcc {

constexpr RccPeriph DMA1_PERIPH {
    .domain = RccClockDomain::AHB1,
    .offset = 0,
};
constexpr RccPeriph DMA2_PERIPH {
    .domain = RccClockDomain::AHB1,
    .offset = 1,
};
constexpr RccPeriph FLASH_PERIPH {
    .domain = RccClockDomain::AHB1,
    .offset = 8,
};
constexpr RccPeriph CRC_PERIPH {
    .domain = RccClockDomain::AHB1,
    .offset = 12,
};

constexpr RccPeriph get_gpio_rcc_periph(uint8_t port) {
    return {
        .domain = RccClockDomain::AHB2,
        .offset = port
    };
}

constexpr RccPeriph ADC_PERIPH {
    .domain = RccClockDomain::AHB2,
    .offset = 13,
};
constexpr RccPeriph DCMI_PERIPH {
    .domain = RccClockDomain::AHB2,
    .offset = 14,
};
constexpr RccPeriph RNG_PERIPH {
    .domain = RccClockDomain::AHB2,
    .offset = 18,
};

constexpr RccPeriph FMC_PERIPH {
    .domain = RccClockDomain::AHB3,
    .offset = 0,
};
constexpr RccPeriph QSPI_PERIPH {
    .domain = RccClockDomain::AHB3,
    .offset = 8,
};

constexpr RccPeriph TIM2_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 0,
};
constexpr RccPeriph TIM3_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 1,
};
constexpr RccPeriph TIM4_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 2,
};
constexpr RccPeriph TIM5_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 3,
};
constexpr RccPeriph TIM6_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 4,
};
constexpr RccPeriph TIM7_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 5,
};
constexpr RccPeriph RTC_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 10,
};
constexpr RccPeriph WWDG_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 11,
};
constexpr RccPeriph SPI2_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 14,
};
constexpr RccPeriph SPI3_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 15,
};
constexpr RccPeriph USART2_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 17,
};
constexpr RccPeriph USART3_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 18,
};
constexpr RccPeriph UART4_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 19,
};
constexpr RccPeriph UART5_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 20,
};
constexpr RccPeriph I2C1_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 21,
};
constexpr RccPeriph I2C2_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 22,
};
constexpr RccPeriph I2C3_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 23,
};
constexpr RccPeriph CAN1_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 25,
};
constexpr RccPeriph CAN2_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 26,
};
constexpr RccPeriph PWR_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 28,
};
constexpr RccPeriph DAC1_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 29,
};
constexpr RccPeriph OPAMP_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 30,
};
constexpr RccPeriph LPTIM1_PERIPH {
    .domain = RccClockDomain::APB1_1,
    .offset = 31,
};

constexpr RccPeriph LPUART1_PERIPH {
    .domain = RccClockDomain::APB1_2,
    .offset = 0,
};
constexpr RccPeriph I2C4_PERIPH {
    .domain = RccClockDomain::APB1_2,
    .offset = 1,
};
constexpr RccPeriph SWPMI1_PERIPH {
    .domain = RccClockDomain::APB1_2,
    .offset = 2,
};
constexpr RccPeriph LPTIM2_PERIPH {
    .domain = RccClockDomain::APB1_2,
    .offset = 5,
};

constexpr RccPeriph SYSCFG_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 0,
};
constexpr RccPeriph SDMMC1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 10,
};
constexpr RccPeriph TIM1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 11,
};
constexpr RccPeriph SPI1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 12,
};
constexpr RccPeriph TIM8_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 13,
};
constexpr RccPeriph USART1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 14,
};
constexpr RccPeriph TIM15_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 16,
};
constexpr RccPeriph TIM16_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 17,
};
constexpr RccPeriph TIM17_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 18,
};
constexpr RccPeriph SAI1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 21,
};
constexpr RccPeriph SAI2_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 22,
};
constexpr RccPeriph DFSDM1_PERIPH {
    .domain = RccClockDomain::APB2,
    .offset = 24,
};
} // namespace stm::periphs::rcc
