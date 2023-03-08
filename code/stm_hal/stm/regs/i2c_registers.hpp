/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::i2c {
using namespace stm::register_access;

namespace CR1 {
    using PE = RegSubValue<0>;
    using TXIE = RegSubValue<1>;
    using RXIE = RegSubValue<2>;
    using ADDRIE = RegSubValue<3>;
    using NACKIE = RegSubValue<4>;
    using STOPIE = RegSubValue<5>;
    using TCIE = RegSubValue<6>;
    using ERRIE = RegSubValue<7>;
    using DNF = RegSubValue<8, 4>;
    using ANFOFF = RegSubValue<12>;

    using TXDMAEN = RegSubValue<14>;
    using RXDMAEN = RegSubValue<15>;

    using SBC = RegSubValue<16>;
    using NOSTRETCH = RegSubValue<17>;
    using WUPEN = RegSubValue<18>;
    using GCEN = RegSubValue<19>;
    using SMBHEN = RegSubValue<20>;
    using SMBDEN = RegSubValue<21>;
    using ALERTEN = RegSubValue<22>;
    using PECEN = RegSubValue<23>;
} // namespace CR1

namespace CR2 {
    using SADD_10 = RegSubValue<0, 10>;
    using SADD_7 = RegSubValue<1, 7>;
    using RD_WRN = RegSubValue<10>;
    using ADD10 = RegSubValue<11>;
    using HEAD10R = RegSubValue<12>;
    using START = RegSubValue<13>;
    using STOP = RegSubValue<14>;
    using NACK = RegSubValue<15>;
    using NBYTES = RegSubValue<16, 8>;

    using RELOAD = RegSubValue<24>;
    using AUTOEND = RegSubValue<25>;
    using PECBYTE = RegSubValue<26>;
} // namespace CR2

namespace OAR1 {
    using OA1_10 = RegSubValue<0, 10>;
    using OA1_7 = RegSubValue<1, 7>;
    using OA1MODE = RegSubValue<10>;
    using OA1EN = RegSubValue<15>;
}

namespace OAR2 {
    using OA2 = RegSubValue<1, 7>;
    using OA2MSK = RegSubValue<8, 3>;
    using OA2EN = RegSubValue<15>;
}

namespace TIMINGR {
    using SCLL = RegSubValue<0, 8>;
    using SCLH = RegSubValue<8, 8>;
    using SDADEL = RegSubValue<16, 4>;
    using SCLDEL = RegSubValue<20, 4>;
    using PRESC = RegSubValue<28, 4>;
}

namespace TIMEOUTR {
    using TIMEOUTA = RegSubValue<0, 12>;
    using TIDLE = RegSubValue<12>;
    using TIMOUTEN = RegSubValue<15>;
    using TIMEOUTB = RegSubValue<16, 12>;
    using TEXTEN = RegSubValue<31>;
}

namespace ISR {
    using TXE = RegSubValue<0>;
    using TXIS = RegSubValue<1>;
    using RXNE = RegSubValue<2>;
    using ADDR = RegSubValue<3>;
    using NACKF = RegSubValue<4>;
    using STOPF = RegSubValue<5>;
    using TC = RegSubValue<6>;
    using TCR = RegSubValue<7>;
    using BERR = RegSubValue<8>;
    using ARLO = RegSubValue<9>;
    using OVR = RegSubValue<10>;
    using PECERR = RegSubValue<11>;
    using TIMEOUT = RegSubValue<12>;
    using ALERT = RegSubValue<13>;

    using BUSY = RegSubValue<15>;
    using DIR = RegSubValue<16>;
    using ADDCODE = RegSubValue<17, 7>;
} // namespace ISR

namespace ICR {
    using ADDRCF = RegSubValue<3>;
    using NACKCF = RegSubValue<4>;
    using STOPCF = RegSubValue<5>;

    using BERRCF = RegSubValue<8>;
    using ARLOCF = RegSubValue<9>;
    using OVRCF = RegSubValue<10>;
    using PECCF = RegSubValue<11>;
    using TIMOUTCF = RegSubValue<12>;
    using ALERTCF = RegSubValue<13>;
} // namespace ICR

struct I2CStruct {
    Register CR1;
    Register CR2;
    Register OAR1;
    Register OAR2;
    Register TIMINGR;
    Register TIMEOUTR;
    Register ISR;
    Register ICR;
    Register PECR;
    Register RXDR;
    Register TXDR;
};

static_assert(sizeof(I2CStruct) == 0x2C); // NOLINT(readability-magic-numbers)

} // namespace stm::regs::i2c
