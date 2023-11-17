#pragma once

#include "mcu/bus.hpp"

namespace System 
{
    struct BusProperties
    {
        static constexpr auto CoreClockSrc = MCU::CLK::SystemClockSource::HSE;
        static constexpr auto AHB_Prescale = MCU::CLK::HCLK_Prescaler::SYSCLK_DIV1;
        static constexpr auto APB2_Prescale = MCU::CLK::PCLK_Prescaler::HCLK_DIV4;
        static constexpr auto APB1_Prescale = MCU::CLK::PCLK_Prescaler::HCLK_DIV4;
        static constexpr auto PLL_ClockSrc = MCU::CLK::PLL_ClockSource::HSE;
        static constexpr auto PLL_Multi = MCU::CLK::PLL_Multiplier::X2;
        static constexpr auto HSI_Clock = System::HSI_Clock;
        static constexpr auto HSE_Clock = System::HSE_Clock;
    };

    using SystemBus_t = MCU::BUS::SystemBus<BusProperties>;
}