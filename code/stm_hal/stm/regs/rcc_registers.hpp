/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::rcc {
using namespace stm::register_access;

namespace CR {
    using MSION = RegSubValue<0>;
    using MSIRDY = RegSubValue<1>;
    using MSIPLLEN = RegSubValue<2>;
    using MSIRGSEL = RegSubValue<3>;
    using MSIRANGE = RegSubValue<4, 4>;

    using HSION = RegSubValue<5, 4>;
    using HSIKERON = RegSubValue<9>;
    using HSIRDY = RegSubValue<10>;
    using HSIASFS = RegSubValue<11>;

    using HSEON = RegSubValue<16>;
    using HSERDY = RegSubValue<17>;
    using HSEBYP = RegSubValue<18>;
    using CSSON = RegSubValue<19>;

    using PLLON = RegSubValue<24>;
    using PLLRDY = RegSubValue<25>;
    using PPLSAI1ON = RegSubValue<26>;
    using PLLSAI1RDY = RegSubValue<27>;
    using PLLSAI2ON = RegSubValue<28>;
    using PLLSAI2RDY = RegSubValue<29>;
} // namespace CR

namespace CFGR {
    using SW = RegSubValue<0, 2>;
    using SWS = RegSubValue<2, 2>;

    using HPRE = RegSubValue<4, 4>;
    using PPRE1 = RegSubValue<8, 3>;
    using PPRE2 = RegSubValue<11, 3>;

    using STOPWUCK = RegSubValue<15>;

    using MCOSEL = RegSubValue<24, 4>;
    using MCOPRE = RegSubValue<28, 3>;
} // namespace CFGR

namespace PLLCFGR {
    using PLLSRC = RegSubValue<0, 2>;
    using PLLM = RegSubValue<4, 2>;
    using PLLN = RegSubValue<8, 7>;

    using PLLPEN = RegSubValue<16>;
    using PLLP = RegSubValue<17>;

    using PLLQEN = RegSubValue<20>;
    using PLLQ = RegSubValue<21, 2>;

    using PLLREN = RegSubValue<24>;
    using PLLR = RegSubValue<25, 2>;

    using PLLPDIV = RegSubValue<27, 5>;
} // namespace PLLCFGR

namespace CCIPR {
    using USART1SEL = RegSubValue<0, 2>;
    using USART2SEL = RegSubValue<2, 2>;
    using USART3SEL = RegSubValue<4, 2>;
    using UART4SEL = RegSubValue<6, 2>;
    using UART5SEL = RegSubValue<8, 2>;
    using LPUART1SEL = RegSubValue<10, 2>;
    using I2C1SEL = RegSubValue<12, 2>;
    using I2C2SEL = RegSubValue<14, 2>;
    using I2C3SEL = RegSubValue<16, 2>;
    using LPTIM1SEL = RegSubValue<18, 2>;
    using LPTIM2SEL = RegSubValue<20, 2>;
    using SAI1SEL = RegSubValue<22, 2>;
    using SAI2SEL = RegSubValue<24, 2>;
    using CLK48SEL = RegSubValue<26, 2>;
    using ADCSEL = RegSubValue<28, 2>;
    using SWPMI1SEL = RegSubValue<30>;
    using DFSDM1SEL = RegSubValue<31>;
} // namespace CCIPR

namespace BDCR {
    using LSEON = RegSubValue<0>;
    using LSERDY = RegSubValue<1>;
    using LSEBYP = RegSubValue<2>;
    using LSEDRV = RegSubValue<3, 2>;
    using LSECSSON = RegSubValue<5>;
    using LSECSSD = RegSubValue<6>;

    using RTCSEL = RegSubValue<8, 9>;
    using RTCEN = RegSubValue<15>;

    using BDRST = RegSubValue<16>;

    using LSCOEN = RegSubValue<24>;
    using LSCOSEL = RegSubValue<25>;
} // namespace BDCR

namespace CSR {
    using LSION = RegSubValue<0>;
    using LSIRDY = RegSubValue<1>;

    using MSISRANGE = RegSubValue<8, 4>;

    using RMVF = RegSubValue<23>;
    using FWRSTF = RegSubValue<24>;
    using OBLRSTF = RegSubValue<25>;
    using PINRSTF = RegSubValue<26>;
    using BORRSTF = RegSubValue<27>;
    using SFTRSTF = RegSubValue<28>;
    using IWWGRSTF = RegSubValue<29>;
    using WWDGRSTF = RegSubValue<30>;
    using LPWRRSTF = RegSubValue<31>;
} // namespace CSR

namespace CRRCR {
    using HSI48ON = RegSubValue<0>;
    using HSI48RDY = RegSubValue<1>;
    using HSI48CAL = RegSubValue<7, 8>;
} // namespace CRRCR

struct RCCStruct {
    Register CR;
    Register ICSCR;
    Register CFGR;
    Register PLLCFGR;
    Register PLLSAI1CFGR;
    Register PLLSAI2CFGR;
    Register CIER;
    Register CIFR;
    Register CICR;
    const uint32_t RESERVED0;
    Register AHB1RSTR;
    Register AHB2RSTR;
    Register AHB3RSTR;
    const uint32_t RESERVED1;
    Register APB1RSTR1;
    Register APB1RSTR2;
    Register APB2RSTR;
    const uint32_t RESERVED2;
    Register AHB1ENR;
    Register AHB2ENR;
    Register AHB3ENR;
    const uint32_t RESERVED3;
    Register APB1ENR1;
    Register APB1ENR2;
    Register APB2ENR;
    const uint32_t RESERVED4;
    Register AHB1SMENR;
    Register AHB2SMENR;
    Register AHB3SMENR;
    const uint32_t RESERVED5;
    Register APB1SMENR1;
    Register APB1SMENR2;
    Register APB2SMENR;
    const uint32_t RESERVED6;
    Register CCIPR;
    const uint32_t RESERVED7;
    Register BDCR;
    Register CSR;
    Register CRRCR;
    Register CCIPR2;
};

} // namespace stm::regs::rcc
