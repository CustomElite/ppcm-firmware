#pragma once

#include "mcu/gpio.hpp"

namespace System
{
    using namespace MCU;

    using ADC_CS = IO::Interface<IO::Port::B, 12>;
    using ADC_BUSY = IO::Interface<IO::Port::B, 11>;
    using DAC_SYNC = IO::Interface<IO::Port::B, 10>;
    using STATUS_LED = IO::Interface<IO::Port::C, 13>;

    using USART_TX = IO::Interface<IO::Port::A, 9>;
    using USART_RX = IO::Interface<IO::Port::A, 10>;
}