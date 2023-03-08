/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "irq_handlers.hpp"
#include <cstdint>

namespace stm {

extern "C" [[noreturn]] void _start(); // NOLINT(readability-identifier-naming)
extern "C" const char __stack_end__[]; // NOLINT(bugprone-reserved-identifier, readability-identifier-naming,bugprone-dynamic-static-initializers)

struct IRQTable {
    const void* sp = __stack_end__;
    void (*reset_handler)() = _start;
    void (*nmi_handler)() = NMI_Handler;
    void (*hardfault_handler)() = HardFault_Handler;
    void (*memmanage_handler)() = MemManage_Handler;
    void (*busfault_handler)() = BusFault_Handler;
    void (*usagefault_handler)() = UsageFault_Handler;
    void (*empty_001c)() = nullptr;
    void (*empty_0020)() = nullptr;
    void (*empty_0024)() = nullptr;
    void (*empty_0028)() = nullptr;
    void (*svc_handler)() = SVC_Handler;
    void (*dbug_mon_handler)() = DebugMon_Handler;
    void (*empty_0034)() = nullptr;
    void (*pend_sv_handler)() = PendSV_Handler;
    void (*sys_tick_handler)() = SysTick_Handler;

    void (*wwdg_irq_handler)() = WWDG_IRQHandler;
    void (*pvd_pvm_irq_handler)() = PVD_PVM_IRQHandler;
    void (*tamp_stamp_irq_handler)() = TAMP_STAMP_IRQHandler;
    void (*rtc_wkup_irq_handler)() = RTC_WKUP_IRQHandler;
    void (*flash_irq_handler)() = FLASH_IRQHandler;
    void (*rcc_irq_handler)() = RCC_IRQHandler;
    void (*exti0_irq_handler)() = EXTI0_IRQHandler;
    void (*exti1_irq_handler)() = EXTI1_IRQHandler;
    void (*exti2_irq_handler)() = EXTI2_IRQHandler;
    void (*exti3_irq_handler)() = EXTI3_IRQHandler;
    void (*exti4_irq_handler)() = EXTI4_IRQHandler;
    void (*dma1_channel_1_irq_handler)() = DMA1_Channel1_IRQHandler;
    void (*dma1_channel_2_irq_handler)() = DMA1_Channel2_IRQHandler;
    void (*dma1_channel_3_irq_handler)() = DMA1_Channel3_IRQHandler;
    void (*dma1_channel_4_irq_handler)() = DMA1_Channel4_IRQHandler;
    void (*dma1_channel_5_irq_handler)() = DMA1_Channel5_IRQHandler;
    void (*dma1_channel_6_irq_handler)() = DMA1_Channel6_IRQHandler;
    void (*dma1_channel_7_irq_handler)() = DMA1_Channel7_IRQHandler;
    void (*adc1_2_irq_handler)() = ADC1_2_IRQHandler;
    void (*can1_tx_irq_handler)() = CAN1_TX_IRQHandler;
    void (*can1_rx0_irq_handler)() = CAN1_RX0_IRQHandler;
    void (*can1_rx1_irq_handler)() = CAN1_RX1_IRQHandler;
    void (*can1_sce_irq_handler)() = CAN1_SCE_IRQHandler;
    void (*exti9_5_irq_handler)() = EXTI9_5_IRQHandler;
    void (*tim1_brk_tim15_irq_handler)() = TIM1_BRK_TIM15_IRQHandler;
    void (*tim1_up_tum16_irq_handler)() = TIM1_UP_TIM16_IRQHandler;
    void (*tim1_trg_com_tim17_irq_handler)() = TIM1_TRG_COM_TIM17_IRQHandler;
    void (*tim1_cc_irq_handler)() = TIM1_CC_IRQHandler;
    void (*tim2_irq_handler)() = TIM2_IRQHandler;
    void (*tim3_irq_handler)() = TIM3_IRQHandler;
    void (*tim4_irq_handler)() = TIM4_IRQHandler;
    void (*i2c_1_ev_irq_handler)() = I2C1_EV_IRQHandler;
    void (*i2c_1_er_irq_handler)() = I2C1_ER_IRQHandler;
    void (*i2c_2_ev_irq_handler)() = I2C2_EV_IRQHandler;
    void (*i2c_2_er_irq_handler)() = I2C2_ER_IRQHandler;
    void (*spi1_irq_handler)() = SPI1_IRQHandler;
    void (*spi2_irq_handler)() = SPI2_IRQHandler;
    void (*usart1_irq_handler)() = USART1_IRQHandler;
    void (*usart2_irq_handler)() = USART2_IRQHandler;
    void (*usart3_irq_handler)() = USART3_IRQHandler;
    void (*exti15_10_irq_handler)() = EXTI15_10_IRQHandler;
    void (*rtc_alarm_irq_handler)() = RTC_Alarm_IRQHandler;
    void (*dfsdm1_flt3_irq_handler)() = DFSDM1_FLT3_IRQHandler;
    void (*tim8_brk_irq_handler)() = TIM8_BRK_IRQHandler;
    void (*tim8_up_irq_handler)() = TIM8_UP_IRQHandler;
    void (*tim8_trg_irq_handler)() = TIM8_TRG_COM_IRQHandler;
    void (*tim8_cc_irq_handler)() = TIM8_CC_IRQHandler;
    void (*adc3_irq_handler)() = ADC3_IRQHandler;
    void (*fmc_irq_handler)() = FMC_IRQHandler;
    void (*sdmmc1_irq_handler)() = SDMMC1_IRQHandler;
    void (*tim5_irq_handler)() = TIM5_IRQHandler;
    void (*spi3_irq_handler)() = SPI3_IRQHandler;
    void (*uart4_irq_handler)() = UART4_IRQHandler;
    void (*uart5_irq_handler)() = UART5_IRQHandler;
    void (*tim6_dac_irq_handler)() = TIM6_DAC_IRQHandler;
    void (*tim7_irq_handler)() = TIM7_IRQHandler;
    void (*dma2_channel1_irq_handler)() = DMA2_Channel1_IRQHandler;
    void (*dma2_channel2_irq_handler)() = DMA2_Channel2_IRQHandler;
    void (*dma2_channel3_irq_handler)() = DMA2_Channel3_IRQHandler;
    void (*dma2_channel4_irq_handler)() = DMA2_Channel4_IRQHandler;
    void (*dma2_channel5_irq_handler)() = DMA2_Channel5_IRQHandler;
    void (*dfsdm1_flt0_irq_handler)() = DFSDM1_FLT0_IRQHandler;
    void (*dfsdm1_flt1_irq_handler)() = DFSDM1_FLT1_IRQHandler;
    void (*dfsdm1_flt2_irq_handler)() = DFSDM1_FLT2_IRQHandler;
    void (*comp_irq_handler)() = COMP_IRQHandler;
    void (*lptim1_irq_handler)() = LPTIM1_IRQHandler;
    void (*lptim2_irq_handler)() = LPTIM2_IRQHandler;
    void (*otg_fs_irq_handler)() = OTG_FS_IRQHandler;
    void (*dma2_channel6_irq_handler)() = DMA2_Channel6_IRQHandler;
    void (*dma2_channel7_irq_handler)() = DMA2_Channel7_IRQHandler;
    void (*lpuart1_irq_handler)() = LPUART1_IRQHandler;
    void (*quadspi_irq_handler)() = QUADSPI_IRQHandler;
    void (*i2c3_ev_irq_handler)() = I2C3_EV_IRQHandler;
    void (*i2c3_er_irq_handler)() = I2C3_ER_IRQHandler;
    void (*sai1_irq_handler)() = SAI1_IRQHandler;
    void (*sai2_irq_handler)() = SAI2_IRQHandler;
    void (*swpmi1_irq_handler)() = SWPMI1_IRQHandler;
    void (*tsc_irq_handler)() = TSC_IRQHandler;
    void (*lcd_irq_handler)() = LCD_IRQHandler;
    void (*aes_irq_handler)() = AES_IRQHandler;
    void (*rng_irq_handler)() = RNG_IRQHandler;
    void (*fpu_irq_handler)() = FPU_IRQHandler;
    void (*crs_irq_handler)() = CRS_IRQHandler;
    void (*ic24_ev_irq_handler)() = I2C4_EV_IRQHandler;
    void (*ic24_er_irq_handler)() = I2C4_ER_IRQHandler;
    void (*dcmi_irq_handler)() = DCMI_IRQHandler;
    void (*can2_tx_irq_handler)() = CAN2_TX_IRQHandler;
    void (*can2_rx0_irq_handler)() = CAN2_RX0_IRQHandler;
    void (*can2_rx1_irq_handler)() = CAN2_RX1_IRQHandler;
    void (*can2_sce_irq_handler)() = CAN2_SCE_IRQHandler;
};
extern "C" [[gnu::section(".isr_vector")]] const constinit IRQTable IRQ_TABLE; // NOLINT(bugprone-dynamic-static-initializers)

} // namespace stm
