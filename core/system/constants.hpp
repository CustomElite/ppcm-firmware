#pragma once

#include "literals.hpp"

#include "mcu/gpio.hpp"

#include <cstdint>

namespace System
{
    namespace Constants
    {
        constexpr uint32_t const LSI_Clock = 40_KHz;
        constexpr uint32_t const LSE_Clock = 32.768_KHz;
        constexpr uint32_t const RTC_Clock = LSE_Clock;
        constexpr uint32_t const HSI_Clock = 8_MHz;
        constexpr uint32_t const HSE_Clock = 8_MHz;

        constexpr float const VDD_Voltage = 3.3_v;
    }

    namespace Pins
    {
        namespace { using namespace MCU; }

        using ADC_CS = IO::Module<IO::Port::B, 12>;
        using ADC_BUSY = IO::Module<IO::Port::B, 11>;
        using DAC_SYNC = IO::Module<IO::Port::B, 10>;
        using STATUS_LED = IO::Module<IO::Port::C, 13>;

        using USART_TX = IO::Module<IO::Port::A, 9>;
        using USART_RX = IO::Module<IO::Port::A, 10>;

        using SPI1_SCLK = IO::Module<IO::Port::A, 5>;
        using SPI1_MOSI = IO::Module<IO::Port::A, 7>;
    }
}