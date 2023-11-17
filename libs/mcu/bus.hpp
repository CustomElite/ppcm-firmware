#pragma once

#include "rcc.hpp"

namespace MCU::BUS 
{
    template <typename Properties>
    class SystemBus : public Properties
    {
    public:
        SystemBus() noexcept
        {
            using namespace CLK::MemoryMap;

            LL_FLASH_SetLatency(LL_FLASH_LATENCY_0); // TODO: Add flash registers
            while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {} // TODO: 

            switch (CoreClockSrc)
            {
                case SystemClockSource::HSI: CR{}.EnableHSI(); break;
                case SystemClockSource::HSE: CR{}.EnableHSE(); break;
                case SystemClockSource::PLL: configure_pll(); break;
            }
            
            CFGR{}.SetBusPrescalers(AHB_Prescale, APB2_Prescale, APB1_Prescale);
            CFGR{}.SetSystemClock(CoreClockSrc);

            SystemCoreClock = CoreClock();
        }
        static constexpr uint32_t CoreClock() noexcept
        {
            switch (CoreClockSrc)
            {
                case CLK::SystemClockSource::HSI: return HSI_Clock;
                case CLK::SystemClockSource::HSE: return HSE_Clock;
                case CLK::SystemClockSource::PLL: return PLL_Clock();
            }
        }
        static constexpr uint32_t AHB_Clock() noexcept
        {
            return (CoreClock() >> hclk_prescaler());
        }
        static constexpr uint32_t APB2_Clock() noexcept
        {
            return (AHB_Clock() >> pclk_prescaler(APB2_Prescale));
        }
        static constexpr uint32_t APB1_Clock() noexcept
        {
            return (AHB_Clock() >> pclk_prescaler(APB1_Prescale));
        }
        static constexpr uint32_t PLL_Clock() noexcept
        {
            return (pll_source_freq() * (Common::Tools::EnumValue(PLL_Multi) + 2u));
        }

    private:
        using Properties::HSI_Clock;
        using Properties::HSE_Clock;
        using Properties::CoreClockSrc;
        using Properties::AHB_Prescale;
        using Properties::APB2_Prescale;
        using Properties::APB1_Prescale;
        using Properties::PLL_ClockSrc;
        using Properties::PLL_Multi;
        
        static void configure_pll() noexcept
        {
            using namespace CLK::MemoryMap;

            CR{}.DisablePLL();

            if constexpr(PLL_ClockSrc == PLL_ClockSource::HSI_DIV2)
            { 
                CR{}.EnableHSI();
            }
            else { 
                CR{}.EnableHSE();
            }

            CFGR{}.SetPLL_Source(PLL_ClockSrc);
            CFGR{}.SetPLL_Multiplier(PLL_Multi);

            CR{}.EnablePLL();
        }
        static constexpr uint32_t hclk_prescaler() noexcept
        {
            switch (AHB_Prescale)
            {
                case CLK::HCLK_Prescaler::SYSCLK_DIV1: return 0u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV2: return 1u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV4: return 2u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV8: return 3u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV16: return 4u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV64: return 6u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV128: return 7u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV256: return 8u;
                case CLK::HCLK_Prescaler::SYSCLK_DIV512: return 9u;
            }
        }
        static constexpr uint32_t pclk_prescaler(CLK::PCLK_Prescaler const input) noexcept
        {
            switch(input)
            {
                case CLK::PCLK_Prescaler::HCLK_DIV1: return 0u;
                case CLK::PCLK_Prescaler::HCLK_DIV2: return 1u;
                case CLK::PCLK_Prescaler::HCLK_DIV4: return 2u;
                case CLK::PCLK_Prescaler::HCLK_DIV8: return 3u;
                case CLK::PCLK_Prescaler::HCLK_DIV16: return 4u;
            }
        }
        static constexpr uint32_t pll_source_freq() noexcept
        {
            switch (PLL_ClockSrc)
            {
                case CLK::PLL_ClockSource::HSI_DIV2: return (::System::HSI_Clock >> 1u);
                case CLK::PLL_ClockSource::HSE: return ::System::HSE_Clock;
                case CLK::PLL_ClockSource::HSE_DIV2: return (::System::HSE_Clock >> 1u);
            }
        }
    };
}