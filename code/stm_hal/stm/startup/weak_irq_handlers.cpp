/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/startup/irq_handlers.hpp"
#include <cstdint>

extern "C" {
void default_handler() { // NOLINT (readability-identifier-naming)
    while (true) {}
}
void NMI_Handler() __attribute__((weak, alias("default_handler")));
void HardFault_Handler() __attribute__((weak, alias("default_handler")));
void MemManage_Handler() __attribute__((weak, alias("default_handler")));
void BusFault_Handler() __attribute__((weak, alias("default_handler")));
void UsageFault_Handler() __attribute__((weak, alias("default_handler")));
void SVC_Handler() __attribute__((weak, alias("default_handler")));
void DebugMon_Handler() __attribute__((weak, alias("default_handler")));
void PendSV_Handler() __attribute__((weak, alias("default_handler")));
void SysTick_Handler() __attribute__((weak, alias("default_handler")));
void WWDG_IRQHandler() __attribute__((weak, alias("default_handler")));
void PVD_PVM_IRQHandler() __attribute__((weak, alias("default_handler")));
void TAMP_STAMP_IRQHandler() __attribute__((weak, alias("default_handler")));
void RTC_WKUP_IRQHandler() __attribute__((weak, alias("default_handler")));
void FLASH_IRQHandler() __attribute__((weak, alias("default_handler")));
void RCC_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI0_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI1_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI2_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI3_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI4_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel1_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel2_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel3_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel4_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel5_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel6_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA1_Channel7_IRQHandler() __attribute__((weak, alias("default_handler")));
void ADC1_2_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN1_TX_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN1_RX0_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN1_RX1_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN1_SCE_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI9_5_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM1_BRK_TIM15_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM1_UP_TIM16_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM1_TRG_COM_TIM17_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM2_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM3_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM4_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C2_EV_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C2_ER_IRQHandler() __attribute__((weak, alias("default_handler")));
void SPI1_IRQHandler() __attribute__((weak, alias("default_handler")));
void SPI2_IRQHandler() __attribute__((weak, alias("default_handler")));
void USART1_IRQHandler() __attribute__((weak, alias("default_handler")));
void USART2_IRQHandler() __attribute__((weak, alias("default_handler")));
void USART3_IRQHandler() __attribute__((weak, alias("default_handler")));
void EXTI15_10_IRQHandler() __attribute__((weak, alias("default_handler")));
void RTC_Alarm_IRQHandler() __attribute__((weak, alias("default_handler")));
void DFSDM1_FLT3_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM8_BRK_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM8_UP_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM8_TRG_COM_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM8_CC_IRQHandler() __attribute__((weak, alias("default_handler")));
void ADC3_IRQHandler() __attribute__((weak, alias("default_handler")));
void FMC_IRQHandler() __attribute__((weak, alias("default_handler")));
void SDMMC1_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM5_IRQHandler() __attribute__((weak, alias("default_handler")));
void SPI3_IRQHandler() __attribute__((weak, alias("default_handler")));
void UART4_IRQHandler() __attribute__((weak, alias("default_handler")));
void UART5_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM6_DAC_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM7_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel1_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel2_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel3_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel4_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel5_IRQHandler() __attribute__((weak, alias("default_handler")));
void DFSDM1_FLT0_IRQHandler() __attribute__((weak, alias("default_handler")));
void DFSDM1_FLT1_IRQHandler() __attribute__((weak, alias("default_handler")));
void DFSDM1_FLT2_IRQHandler() __attribute__((weak, alias("default_handler")));
void COMP_IRQHandler() __attribute__((weak, alias("default_handler")));
void LPTIM1_IRQHandler() __attribute__((weak, alias("default_handler")));
void LPTIM2_IRQHandler() __attribute__((weak, alias("default_handler")));
void OTG_FS_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel6_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2_Channel7_IRQHandler() __attribute__((weak, alias("default_handler")));
void LPUART1_IRQHandler() __attribute__((weak, alias("default_handler")));
void QUADSPI_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, alias("default_handler")));
void SAI1_IRQHandler() __attribute__((weak, alias("default_handler")));
void SAI2_IRQHandler() __attribute__((weak, alias("default_handler")));
void SWPMI1_IRQHandler() __attribute__((weak, alias("default_handler")));
void TSC_IRQHandler() __attribute__((weak, alias("default_handler")));
void LCD_IRQHandler() __attribute__((weak, alias("default_handler")));
void RNG_IRQHandler() __attribute__((weak, alias("default_handler")));
void FPU_IRQHandler() __attribute__((weak, alias("default_handler")));
void AES_IRQHandler() __attribute__((weak, alias("default_handler")));
void CRS_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C4_EV_IRQHandler() __attribute__((weak, alias("default_handler")));
void I2C4_ER_IRQHandler() __attribute__((weak, alias("default_handler")));
void DCMI_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN2_TX_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN2_RX0_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN2_RX1_IRQHandler() __attribute__((weak, alias("default_handler")));
void CAN2_SCE_IRQHandler() __attribute__((weak, alias("default_handler")));
void DMA2D_IRQHandler() __attribute__((weak, alias("default_handler")));
void USB_IRQHandler() __attribute__((weak, alias("default_handler")));
void TIM1_TRG_COM_IRQHandler() __attribute__((weak, alias("default_handler")));
void ADC1_IRQHandler() __attribute__((weak, alias("default_handler")));
}
