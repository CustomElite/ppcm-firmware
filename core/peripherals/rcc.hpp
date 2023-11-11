#pragma once

#include "constants.hpp"
#include "rcc.hpp"
#include "rcc_register.hpp"

#include "mcu_config.hpp"

#include "tools.hpp"
#include <etl/functional.h>

namespace Peripherals::CLK
{
    using namespace Settings;

    enum class State : bool
    {
        Off = false,
        On = true
    };
    enum class Clock : uint8_t
    {
        APB1_TIM2 = 0,
        APB1_TIM3,
        APB1_TIM4,
        APB1_RTC, 
        APB1_WWDG,
        APB1_IWDG,
        APB1_SPI2,
        APB1_USART2,
        APB1_USART3,
        APB1_I2C1,
        APB1_I2C2,
        APB1_CAN1,
        APB1_BKP,
        APB1_PWR,
        APB1_USB,
        APB2_AFIO,
        APB2_EXTI, 
        APB2_GPIOA,
        APB2_GPIOB,
        APB2_GPIOC,
        APB2_GPIOD,
        APB2_GPIOE,
        APB2_ADC1,
        APB2_ADC2, 
        APB2_TIM1, 
        APB2_SPI1, 
        APB2_USART1,
        AHB_DMA1,
        AHB_RCC,
        AHB_CRC,
        AHB_FLASH,
        AHB_SRAM
    };

    template <Clock P>
    struct ClockWidget
    {
        static void Power(const State input = State::On) noexcept
        {
            using namespace Common::Tools;
            using namespace RegisterMap;
            
            if constexpr(P == Clock::APB2_AFIO)   { APB2ENR{}.AFIOEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_GPIOA)  { APB2ENR{}.IOPAEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_GPIOB)  { APB2ENR{}.IOPBEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_GPIOC)  { APB2ENR{}.IOPCEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_GPIOD)  { APB2ENR{}.IOPDEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_GPIOE)  { APB2ENR{}.IOPEEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_ADC1)   { APB2ENR{}.ADC1EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_ADC2)   { APB2ENR{}.ADC2EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_TIM1)   { APB2ENR{}.TIM1EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_SPI1)   { APB2ENR{}.SPI1EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB2_USART1) { APB2ENR{}.USART1EN() = EnumValue(input); }
            
            if constexpr(P == Clock::APB1_TIM2)   { APB1ENR{}.TIM2EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_TIM3)   { APB1ENR{}.TIM3EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_TIM4)   { APB1ENR{}.TIM4EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_WWDG)   { APB1ENR{}.WWDGEN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_SPI2)   { APB1ENR{}.SPI2EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_USART2) { APB1ENR{}.USART2EN() = EnumValue(input); }
            if constexpr(P == Clock::APB1_USART3) { APB1ENR{}.USART3EN() = EnumValue(input); }
            if constexpr(P == Clock::APB1_I2C1)   { APB1ENR{}.I2C1EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_I2C2)   { APB1ENR{}.I2C2EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_CAN1)   { APB1ENR{}.CAN1EN()   = EnumValue(input); }
            if constexpr(P == Clock::APB1_BKP)    { APB1ENR{}.BKPEN()    = EnumValue(input); }
            if constexpr(P == Clock::APB1_PWR)    { APB1ENR{}.PWREN()    = EnumValue(input); }
            if constexpr(P == Clock::APB1_USB)    { APB1ENR{}.USBEN()    = EnumValue(input); }

            if constexpr(P == Clock::AHB_DMA1)   { AHBENR{}.DMA1EN()    = EnumValue(input); }
            if constexpr(P == Clock::AHB_CRC)    { AHBENR{}.CRCEN()     = EnumValue(input); }
            if constexpr(P == Clock::AHB_FLASH)  { AHBENR{}.FLITFEN()   = EnumValue(input); }
            if constexpr(P == Clock::AHB_SRAM)   { AHBENR{}.SRAMEN()    = EnumValue(input); }
        }
        static bool Reset() noexcept
        {
            using namespace RegisterMap;

            if      constexpr(P == Clock::APB2_AFIO)   { APB2RSTR{}.AFIORST()   = true; APB2RSTR{}.AFIORST()   = false; return true; }
            else if constexpr(P == Clock::APB2_GPIOA)  { APB2RSTR{}.IOPARST()   = true; APB2RSTR{}.IOPARST()   = false; return true; }           
            else if constexpr(P == Clock::APB2_GPIOB)  { APB2RSTR{}.IOPBRST()   = true; APB2RSTR{}.IOPBRST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_GPIOC)  { APB2RSTR{}.IOPCRST()   = true; APB2RSTR{}.IOPCRST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_GPIOD)  { APB2RSTR{}.IOPDRST()   = true; APB2RSTR{}.IOPDRST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_GPIOE)  { APB2RSTR{}.IOPERST()   = true; APB2RSTR{}.IOPERST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_ADC1)   { APB2RSTR{}.ADC1RST()   = true; APB2RSTR{}.ADC1RST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_ADC2)   { APB2RSTR{}.ADC2RST()   = true; APB2RSTR{}.ADC2RST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_TIM1)   { APB2RSTR{}.TIM1RST()   = true; APB2RSTR{}.TIM1RST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_SPI1)   { APB2RSTR{}.SPI1RST()   = true; APB2RSTR{}.SPI1RST()   = false; return true; }            
            else if constexpr(P == Clock::APB2_USART1) { APB2RSTR{}.USART1RST() = true; APB2RSTR{}.USART1RST() = false; return true; }
            
            
            else if constexpr(P == Clock::APB1_TIM2)   { APB1RSTR{}.TIM2RST()   = true; APB1RSTR{}.TIM2RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_TIM3)   { APB1RSTR{}.TIM3RST()   = true; APB1RSTR{}.TIM3RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_TIM4)   { APB1RSTR{}.TIM4RST()   = true; APB1RSTR{}.TIM4RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_WWDG)   { APB1RSTR{}.WWDGRST()   = true; APB1RSTR{}.WWDGRST()   = false; return true; }
            else if constexpr(P == Clock::APB1_SPI2)   { APB1RSTR{}.SPI2RST()   = true; APB1RSTR{}.SPI2RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_USART2) { APB1RSTR{}.USART2RST() = true; APB1RSTR{}.USART2RST() = false; return true; }
            else if constexpr(P == Clock::APB1_USART3) { APB1RSTR{}.USART3RST() = true; APB1RSTR{}.USART3RST() = false; return true; }
            else if constexpr(P == Clock::APB1_I2C1)   { APB1RSTR{}.I2C1RST()   = true; APB1RSTR{}.I2C1RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_I2C2)   { APB1RSTR{}.I2C2RST()   = true; APB1RSTR{}.I2C2RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_CAN1)   { APB1RSTR{}.CAN1RST()   = true; APB1RSTR{}.CAN1RST()   = false; return true; }
            else if constexpr(P == Clock::APB1_BKP)    { APB1RSTR{}.BKPRST()    = true; APB1RSTR{}.BKPRST()    = false; return true; }
            else if constexpr(P == Clock::APB1_PWR)    { APB1RSTR{}.PWRRST()    = true; APB1RSTR{}.PWRRST()    = false; return true; }
            else if constexpr(P == Clock::APB1_USB)    { APB1RSTR{}.USBRST()    = true; APB1RSTR{}.USBRST()    = false; return true; }
            else { return false; }
        }
    };

    template 
    <
        SystemClockSource SysClock,
        HCLK_Prescaler AHB_Divider,
        PCLK_Prescaler APB2_Divider, 
        PCLK_Prescaler APB1_Divider,
        PLL_ClockSource PLL_Clock = PLL_ClockSource::HSI_DIV2,
        PLL_Multiplier PLL_Multi = PLL_Multiplier::X2
    >
    class SystemClock
    {
    public:
        constexpr SystemClock() noexcept
        {
            using namespace RegisterMap;

            LL_FLASH_SetLatency(LL_FLASH_LATENCY_0); // TODO: Add flash registers
            while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {} // TODO: 

            if constexpr(SysClock == SystemClockSource::HSI) { CR{}.EnableHSI(); }
            else if constexpr(SysClock == SystemClockSource::HSE) { CR{}.EnableHSE(); }
            else { ConfigurePLL(); }
            
            CFGR{}.SetBusPrescalers(AHB_Divider, APB2_Divider, APB1_Divider);
            CFGR{}.SetSystemClock(SysClock);

            SystemCoreClock = SYSCLK();
        }
        static constexpr uint32_t SYSCLK() noexcept
        {
            if constexpr (SysClock == SystemClockSource::HSI) { return ::System::HSI_Clock; }
            if constexpr (SysClock == SystemClockSource::HSE) { return ::System::HSE_Clock; }
            if constexpr (SysClock == SystemClockSource::PLL) { return 0; }
        }
        static constexpr uint32_t AHBCLK() noexcept
        {
            return (SYSCLK() / HCLK_Div());
        }
        static constexpr uint32_t APB2CLK() noexcept
        {
            return (AHBCLK() >> PCLK_Div<APB2_Divider>());
        }
        static constexpr uint32_t APB1CLK() noexcept
        {
            return (AHBCLK() >> PCLK_Div<APB1_Divider>());
        }
        static constexpr uint32_t PLLCLK() noexcept
        {
            return (PLL_SourceFreq() * (Common::Tools::EnumValue(PLL_Multi) + 2u));
        }

    private:
        static constexpr void ConfigurePLL() noexcept
        {
            using namespace RegisterMap;

            CR{}.DisablePLL();

            if constexpr(PLL_Clock == PLL_ClockSource::HSI_DIV2) { 
                CR{}.EnableHSI(); 
            }
            else { 
                CR{}.EnableHSE(); 
            }

            CFGR{}.SetPLL_Source(PLL_Clock);
            CFGR{}.SetPLL_Multiplier(PLL_Multi);

            CR{}.EnablePLL();
        }
        static constexpr uint32_t HCLK_Div() noexcept
        {
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV1) { return 1u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV2) { return 2u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV4) { return 4u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV8) { return 8u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV16) { return 16u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV64) { return 64u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV128) { return 128u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV256) { return 256u; }
            if constexpr (AHB_Divider == HCLK_Prescaler::SYSCLK_DIV512) { return 512u; }
        }
        template <PCLK_Prescaler PRE>
        static constexpr uint32_t PCLK_Div() noexcept
        {
            if constexpr (PRE == PCLK_Prescaler::HCLK_DIV1) { return 0u; }
            if constexpr (PRE == PCLK_Prescaler::HCLK_DIV2) { return 1u; }
            if constexpr (PRE == PCLK_Prescaler::HCLK_DIV4) { return 2u; }
            if constexpr (PRE == PCLK_Prescaler::HCLK_DIV8) { return 3u; }
            if constexpr (PRE == PCLK_Prescaler::HCLK_DIV16) { return 4u; }
        }
        static constexpr uint32_t PLL_SourceFreq() noexcept
        {
            if constexpr (PLL_Clock == PLL_ClockSource::HSI_DIV2) { return (::System::HSI_Clock >> 1u); }
            if constexpr (PLL_Clock == PLL_ClockSource::HSE) { return ::System::HSE_Clock; }
            if constexpr (PLL_Clock == PLL_ClockSource::HSE_DIV2) { return (::System::HSE_Clock >> 1u); }
        }
    };
}