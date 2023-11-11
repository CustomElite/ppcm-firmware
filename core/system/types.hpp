#pragma once

#include "gpio.hpp"
#include "gpio_registers.hpp"
#include "rcc.hpp"
#include "serial.hpp"

namespace System
{
    using namespace Peripherals;

    using serial_t = etl::singleton<System::Serial>;
    using sysclk_t = CLK::SystemClock<CLK::SystemClockSource::HSE, CLK::HCLK_Prescaler::SYSCLK_DIV1, CLK::PCLK_Prescaler::HCLK_DIV2, CLK::PCLK_Prescaler::HCLK_DIV2>;

    using ADC_CS = IO::Module<IO::Port::B, 12>;
    using ADC_BUSY = IO::Module<IO::Port::B, 11>;
    using DAC_SYNC = IO::Module<IO::Port::B, 10>;
    using STATUS_LED = IO::Module<IO::Port::C, 13>;
}