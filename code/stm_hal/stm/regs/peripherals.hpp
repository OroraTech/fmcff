/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/regs/nvic_registers.hpp"
#include "stm/cortex_m/regs/scb_registers.hpp"
#include "stm/cortex_m/regs/systick_registers.hpp"
#include "stm/regs/adc_registers.hpp"
#include "stm/regs/can_registers.hpp"
#include "stm/regs/dbg_registers.hpp"
#include "stm/regs/dbgmcu_registers.hpp"
#include "stm/regs/dwt_registers.hpp"
#include "stm/regs/flash_registers.hpp"
#include "stm/regs/gpio_registers.hpp"
#include "stm/regs/i2c_registers.hpp"
#include "stm/regs/iwdg_registers.hpp"
#include "stm/regs/pwr_registers.hpp"
#include "stm/regs/rcc_registers.hpp"
#include "stm/regs/rtc_registers.hpp"
#include "stm/regs/rng_registers.hpp"
#include "stm/regs/spi_registers.hpp"
#include "stm/regs/syscfg_registers.hpp"
#include "stm/regs/tim_registers.hpp"
#include "stm/regs/uart_registers.hpp"
#include "stm/regs/uid_registers.hpp"

extern "C" stm::regs::rtc::RTCStruct __PERIPHERAL_RTC__;
extern "C" stm::regs::iwdg::IWDGStruct __PERIPHERAL_IWDG__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_LPUART1__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_USART1__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_USART2__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_USART3__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_UART4__;
extern "C" stm::regs::uart::UARTStruct __PERIPHERAL_UART5__;
extern "C" stm::regs::i2c::I2CStruct __PERIPHERAL_I2C1__;
extern "C" stm::regs::i2c::I2CStruct __PERIPHERAL_I2C2__;
extern "C" stm::regs::i2c::I2CStruct __PERIPHERAL_I2C3__;
extern "C" stm::regs::i2c::I2CStruct __PERIPHERAL_I2C4__;
extern "C" stm::regs::can::CANStruct __PERIPHERAL_CAN1__;
extern "C" stm::regs::can::CANStruct __PERIPHERAL_CAN2__;
extern "C" stm::regs::pwr::PWRStruct __PERIPHERAL_PWR__;
extern "C" stm::regs::syscfg::SYSCFGStruct __PERIPHERAL_SYSCFG__;
extern "C" stm::regs::spi::SPIStruct __PERIPHERAL_SPI1__;
extern "C" stm::regs::spi::SPIStruct __PERIPHERAL_SPI2__;
extern "C" stm::regs::spi::SPIStruct __PERIPHERAL_SPI3__;
extern "C" stm::regs::spi::SPIStruct __PERIPHERAL_SPI4__;
extern "C" stm::regs::rcc::RCCStruct __PERIPHERAL_RCC__;
extern "C" stm::regs::flash::FLASHStruct __PERIPHERAL_FLASH__;
extern "C" stm::regs::adc::ADCStruct __PERIPHERAL_ADC__;
extern "C" stm::regs::gpio::GPIOStruct __PERIPHERAL_GPIOS__[9];
extern "C" stm::regs::dbgmcu::DBGMCUStruct __PERIPHERAL_DBGMCU__;
extern "C" stm::regs::uid::UIDStruct __PERIPHERAL_UID__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM1__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM2__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM3__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM4__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM5__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM6__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM7__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM8__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM15__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM16__;
extern "C" stm::regs::tim::TIMStruct __PERIPHERAL_TIM17__;
extern "C" stm::regs::rng::RNGStruct __PERIPHERAL_RNG__;

extern "C" stm::regs::scb::SCBStruct __PERIPHERAL_SCB__;
extern "C" stm::regs::nvic::NVICStruct __PERIPHERAL_NVIC__;
extern "C" stm::regs::systick::SYSTICKStruct __PERIPHERAL_SYSTICK__;
extern "C" stm::regs::dwt::DWTStruct __PERIPHERAL_DWT__;
extern "C" stm::regs::dbg::DBGStruct __PERIPHERAL_DBG__;
