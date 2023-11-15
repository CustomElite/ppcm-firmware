#pragma once

#include "rcc.hpp"

namespace System 
{
    struct BusProperties
    {
        static constexpr auto CoreClockSrc = ::Peripherals::CLK::SystemClockSource::HSE;
        static constexpr auto AHB_Prescale = ::Peripherals::CLK::HCLK_Prescaler::SYSCLK_DIV1;
        static constexpr auto APB2_Prescale = ::Peripherals::CLK::PCLK_Prescaler::HCLK_DIV4;
        static constexpr auto APB1_Prescale = ::Peripherals::CLK::PCLK_Prescaler::HCLK_DIV4;
        static constexpr auto PLL_ClockSrc = ::Peripherals::CLK::PLL_ClockSource::HSE;
        static constexpr auto PLL_Multi = ::Peripherals::CLK::PLL_Multiplier::X2;
    };

    using SystemBus_t = ::Peripherals::CLK::SystemBus<BusProperties>;

}