/*
 © Copyright 2023 OroraTech GmbH
 * Licensed under the terms and conditions of the Apache 2.0 license.
*/

#pragma once
#include "stm/cortex_m/register_access/register.hpp"

namespace stm::regs::spi {
using namespace stm::register_access;

namespace CR1 {
    using CPHA = RegSubValue<0>;
    using CPOL = RegSubValue<1>;

    using MODE = RegSubValue<0, 2>; // the values of the CPHA bits correspond to the binary numbers 0-3 when it comes to the SPI mode

    using MSTR = RegSubValue<2>;
    using BR = RegSubValue<3, 3>;
    using SPE = RegSubValue<6>;
    using LSBFIRST = RegSubValue<7>;
    using SSI = RegSubValue<8>;
    using SSM = RegSubValue<9>;
    using RXONLY = RegSubValue<10>;
    using CRCL = RegSubValue<11>;
    using CRCNEXT = RegSubValue<12>;
    using CRCEN = RegSubValue<13>;
    using BIDIOE = RegSubValue<14>;
    using BIDIMODE = RegSubValue<15>;
} // namespace CR1

namespace CR2 {
    using RXDMAEN = RegSubValue<0>;
    using TXDMAEN = RegSubValue<1>;
    using SSOE = RegSubValue<2>;
    using NSSP = RegSubValue<3>;
    using FRF = RegSubValue<4>;
    using ERRIE = RegSubValue<5>;
    using RXNEIE = RegSubValue<6>;
    using TXEIE = RegSubValue<7>;
    using DS = RegSubValue<8, 4>;
    using FRXTH = RegSubValue<12>;
    using LDMA_RX = RegSubValue<13>;
    using LDMA_TX = RegSubValue<14>;
} // namespace CR2

namespace SR {
    using RXNE = RegSubValue<0>;
    using TXE = RegSubValue<1>;
    using CRCERR = RegSubValue<4>;
    using MODF = RegSubValue<5>;
    using OVR = RegSubValue<6>;
    using BSY = RegSubValue<7>;
    using FRE = RegSubValue<8>;
    using FRLVL = RegSubValue<9, 2>;
    using FTLVL = RegSubValue<11, 2>;

    constexpr uint8_t SPI_FIFO_FULL_VALUE = 0b11;
} // namespace SR

struct SPIStruct {
    Register CR1;
    Register CR2;
    Register SR;
    Register DR;
    Register CRCPR;
    Register RXCRCR;
    Register TXCRCR;
};

} // namespace stm::regs::spi
