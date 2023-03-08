/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#include "stm/periphs/rcc/rcc_periph.hpp"
#include "stm/periphs/rcc/rcc_periph_list.hpp"

#include "stm/periphs/flash/flash_manager.hpp"
#include "stm/periphs/rcc/clock_manager.hpp"

// NOLINTBEGIN(readability-magic-numbers) all the magic numbers here are just datasheet values. Putting them into const does not make it more readable IMHO.
namespace stm::periphs::rcc {
void LSE::init_clock() {
    using namespace CR1;
    using namespace BDCR;
    if (!is_ready()) { // LSE may still be active after a reset
        rcc::enable_rcc_periph(rcc::PWR_PERIPH);
        __PERIPHERAL_PWR__.CR1.set(DBP(1));
        __PERIPHERAL_RCC__.BDCR.set(LSEDRV(3)); // high drive capability for faster startup
        __PERIPHERAL_RCC__.BDCR.set(LSEON(1));
        wait_until_ready();
        __PERIPHERAL_RCC__.BDCR.set(LSEDRV(0)); // lower drive capability for lower power consumption
    }
}

void MSI::init_clock() {
    using namespace CR;
    __PERIPHERAL_RCC__.CR.set(MSIRANGE(RANGE), MSIRGSEL(1));
    if constexpr (USE_PLL_MODE) {
        __PERIPHERAL_RCC__.CR.set(MSIPLLEN(1));
    }
    wait_until_ready();
}
void MSI::disable_clock() {
    using namespace CR;
    __PERIPHERAL_RCC__.CR.set(MSION(0));
}

void HSI16::init_clock() {
    using namespace CR;
    __PERIPHERAL_RCC__.CR.set(HSION(1));
    wait_until_ready();
}

void HSE::init_clock() {
    using namespace CR;
    __PERIPHERAL_RCC__.CR.set(HSEON(1));
    wait_until_ready();
}

void LSI::init_clock() {
    using namespace CSR;
    __PERIPHERAL_RCC__.CSR.set(LSION(1));
    wait_until_ready();
}

void PLL::set_main_parameters() {
    using namespace PLLCFGR;
    __PERIPHERAL_RCC__.PLLCFGR.set(PLLSRC(static_cast<uint32_t>(SOURCE)), PLLM(PLLM_REG_VALUE), PLLN(PLLN_CONFIG));
}

void PLL::init_outputs() {
    using namespace PLLCFGR;
    __PERIPHERAL_RCC__.PLLCFGR.set(
        PLLPEN(static_cast<unsigned int>(ENABLE_PLLSAI3CLK)), PLLP(PLLP_REG_VALUE), PLLPDIV(PLLPDIV_CONFIG),
        PLLQEN(static_cast<unsigned int>(ENABLE_PLL48M1CLK)), PLLQ(PLLQ_REG_VALUE),
        PLLREN(static_cast<unsigned int>(ENABLE_PLLCLK)), PLLR(PLLR_REG_VALUE));
}

void PLL::init_clock() {
    using namespace CR;
    set_main_parameters();
    __PERIPHERAL_RCC__.CR.set(PLLON(1));
    init_outputs();
    wait_until_ready();
}

void SYSCLK::init_source() {
    using namespace CFGR;
    __PERIPHERAL_RCC__.CFGR.set(SW(static_cast<uint32_t>(SOURCE)));
    while (__PERIPHERAL_RCC__.CFGR.read<SWS>() != static_cast<uint32_t>(SOURCE)) {}
}

void BusClockManager::init_prescalers() {
    using namespace CFGR;
    __PERIPHERAL_RCC__.CFGR.set(
        HPRE(HCLK::HPRE_CONFIG),
        PPRE1(PCLK::PPRE1_CONFIG),
        PPRE2(PCLK::PPRE2_CONFIG));
}

void ClockManager::init_clock_sources() {
    if constexpr (LSI::ENABLE) {
        LSI::init_clock();
    }
    if constexpr (LSE::ENABLE) {
        LSE::init_clock();
    }
    if constexpr (HSI16::ENABLE) {
        HSI16::init_clock();
    }
    if constexpr (HSE::ENABLE) {
        HSE::init_clock();
    }
    flash::FlashManager::init_latency_pre_msi_init();
    if constexpr (MSI::ENABLE) {
        MSI::init_clock();
    }
    if constexpr (PLL::ENABLE) {
        PLL::init_clock();
    }
}

void ClockManager::init_sys_clock() {
    BusClockManager::init_prescalers();

    flash::FlashManager::init_latency_pre_syscl_kswitch();
    SYSCLK::init_source();
    flash::FlashManager::init_latency_post_syscl_kswitch();
}

void ClockManager::reset_clocks() {
    using namespace CR;
    using namespace CFGR;
    flash::FlashManager::set_latency(4);
    __PERIPHERAL_RCC__.CR.set(MSION(1));
    MSI::wait_until_ready();
    __PERIPHERAL_RCC__.CFGR.write(0);
    while (__PERIPHERAL_RCC__.CFGR.read<SWS>() != 0) {}
    __PERIPHERAL_RCC__.CR.write(0x0000'0063); // reset value
    MSI::wait_until_ready();
    __PERIPHERAL_RCC__.PLLCFGR.write(0x0000'1000); // reset value
    flash::FlashManager::set_latency(0);
}

void ClockManager::init_clocks() {
    using namespace CR;
    init_clock_sources();
    init_sys_clock();
    if constexpr (!MSI::ENABLE) {
        MSI::disable_clock();
    }
}
} // namespace stm::periphs::rcc
// NOLINTEND(readability-magic-numbers)
