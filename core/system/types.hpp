#pragma once

#include "rcc.hpp"
#include "serial.hpp"

namespace System
{
    using namespace Peripherals::ResetClockControl;
    using namespace Settings;

    using serial_t = etl::singleton<System::Serial>;
    using sysclk_t = SystemClock<SystemClockSource::HSE, HCLK_Prescaler::SYSCLK_DIV1, PCLK_Prescaler::HCLK_DIV2, PCLK_Prescaler::HCLK_DIV2>;
}