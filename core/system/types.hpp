#pragma once

#include "constants.hpp"

#include "mcu/rcc.hpp"
#include "mcu/gpio.hpp"
#include "mcu/spi.hpp"
#include "mcu/usart.hpp"
#include "mcu/sys_tick.hpp"

namespace System 
{
    namespace { using namespace MCU; }

    using BusProperties = CLK::Properties< CLK::SystemClockSource::HSE, 
                                           CLK::HCLK_Prescaler::DIV1, 
                                           CLK::PCLK2_Prescaler::DIV4, 
                                           CLK::PCLK1_Prescaler::DIV4,
                                           CLK::PLL_ClockSource::HSE, 
                                           CLK::PLL_Multiplier::X2, 
                                           Constants::HSI_Clock, 
                                           Constants::HSE_Clock >;

    using SystemBus_t = CLK::SystemBus<BusProperties>;
    using SystemTick_t = SYSTICK::Module;

    using USART1_Config = USART::Configuration<USART::Peripheral::USART_1, Pins::USART_TX, Pins::USART_RX, SystemBus_t::APB2_ClockFreq(), 19200_u32>;

    using SPI1_Config = SPI::Configuration<SPI::Peripheral::SPI_1, Pins::SPI1_SCLK, Pins::SPI1_MOSI, IO::NoPin>;
}