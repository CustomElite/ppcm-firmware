#pragma once

#include "constants.hpp"
#include "mcu_config.hpp"

#include "rcc_register.hpp"

#include "common/tools.hpp"

namespace MCU::CLK
{
    using namespace Settings;

    enum class State : bool
    {
        Off = false,
        On = true
    };
    enum class Peripheral : uint8_t
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

    template <Peripheral M>
    struct Control
    {
        static void Power(const State input = State::On) noexcept
        {
            using namespace Common::Tools;
            using namespace MemoryMap;
            
            if constexpr(M == Peripheral::APB2_AFIO)   { APB2ENR{}.AFIOEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_GPIOA)  { APB2ENR{}.IOPAEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_GPIOB)  { APB2ENR{}.IOPBEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_GPIOC)  { APB2ENR{}.IOPCEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_GPIOD)  { APB2ENR{}.IOPDEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_GPIOE)  { APB2ENR{}.IOPEEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_ADC1)   { APB2ENR{}.ADC1EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_ADC2)   { APB2ENR{}.ADC2EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_TIM1)   { APB2ENR{}.TIM1EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_SPI1)   { APB2ENR{}.SPI1EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB2_USART1) { APB2ENR{}.USART1EN() = EnumValue(input); }
            
            if constexpr(M == Peripheral::APB1_TIM2)   { APB1ENR{}.TIM2EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_TIM3)   { APB1ENR{}.TIM3EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_TIM4)   { APB1ENR{}.TIM4EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_WWDG)   { APB1ENR{}.WWDGEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_SPI2)   { APB1ENR{}.SPI2EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_USART2) { APB1ENR{}.USART2EN() = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_USART3) { APB1ENR{}.USART3EN() = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_I2C1)   { APB1ENR{}.I2C1EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_I2C2)   { APB1ENR{}.I2C2EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_CAN1)   { APB1ENR{}.CAN1EN()   = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_BKP)    { APB1ENR{}.BKPEN()    = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_PWR)    { APB1ENR{}.PWREN()    = EnumValue(input); }
            if constexpr(M == Peripheral::APB1_USB)    { APB1ENR{}.USBEN()    = EnumValue(input); }

            if constexpr(M == Peripheral::AHB_DMA1)   { AHBENR{}.DMA1EN()    = EnumValue(input); }
            if constexpr(M == Peripheral::AHB_CRC)    { AHBENR{}.CRCEN()     = EnumValue(input); }
            if constexpr(M == Peripheral::AHB_FLASH)  { AHBENR{}.FLITFEN()   = EnumValue(input); }
            if constexpr(M == Peripheral::AHB_SRAM)   { AHBENR{}.SRAMEN()    = EnumValue(input); }
        }
        static bool Reset() noexcept
        {
            using namespace MemoryMap;

            if      constexpr(M == Peripheral::APB2_AFIO)   { APB2RSTR{}.AFIORST()   = true; APB2RSTR{}.AFIORST()   = false; return true; }
            else if constexpr(M == Peripheral::APB2_GPIOA)  { APB2RSTR{}.IOPARST()   = true; APB2RSTR{}.IOPARST()   = false; return true; }           
            else if constexpr(M == Peripheral::APB2_GPIOB)  { APB2RSTR{}.IOPBRST()   = true; APB2RSTR{}.IOPBRST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_GPIOC)  { APB2RSTR{}.IOPCRST()   = true; APB2RSTR{}.IOPCRST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_GPIOD)  { APB2RSTR{}.IOPDRST()   = true; APB2RSTR{}.IOPDRST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_GPIOE)  { APB2RSTR{}.IOPERST()   = true; APB2RSTR{}.IOPERST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_ADC1)   { APB2RSTR{}.ADC1RST()   = true; APB2RSTR{}.ADC1RST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_ADC2)   { APB2RSTR{}.ADC2RST()   = true; APB2RSTR{}.ADC2RST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_TIM1)   { APB2RSTR{}.TIM1RST()   = true; APB2RSTR{}.TIM1RST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_SPI1)   { APB2RSTR{}.SPI1RST()   = true; APB2RSTR{}.SPI1RST()   = false; return true; }            
            else if constexpr(M == Peripheral::APB2_USART1) { APB2RSTR{}.USART1RST() = true; APB2RSTR{}.USART1RST() = false; return true; }
            
            else if constexpr(M == Peripheral::APB1_TIM2)   { APB1RSTR{}.TIM2RST()   = true; APB1RSTR{}.TIM2RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_TIM3)   { APB1RSTR{}.TIM3RST()   = true; APB1RSTR{}.TIM3RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_TIM4)   { APB1RSTR{}.TIM4RST()   = true; APB1RSTR{}.TIM4RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_WWDG)   { APB1RSTR{}.WWDGRST()   = true; APB1RSTR{}.WWDGRST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_SPI2)   { APB1RSTR{}.SPI2RST()   = true; APB1RSTR{}.SPI2RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_USART2) { APB1RSTR{}.USART2RST() = true; APB1RSTR{}.USART2RST() = false; return true; }
            else if constexpr(M == Peripheral::APB1_USART3) { APB1RSTR{}.USART3RST() = true; APB1RSTR{}.USART3RST() = false; return true; }
            else if constexpr(M == Peripheral::APB1_I2C1)   { APB1RSTR{}.I2C1RST()   = true; APB1RSTR{}.I2C1RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_I2C2)   { APB1RSTR{}.I2C2RST()   = true; APB1RSTR{}.I2C2RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_CAN1)   { APB1RSTR{}.CAN1RST()   = true; APB1RSTR{}.CAN1RST()   = false; return true; }
            else if constexpr(M == Peripheral::APB1_BKP)    { APB1RSTR{}.BKPRST()    = true; APB1RSTR{}.BKPRST()    = false; return true; }
            else if constexpr(M == Peripheral::APB1_PWR)    { APB1RSTR{}.PWRRST()    = true; APB1RSTR{}.PWRRST()    = false; return true; }
            else if constexpr(M == Peripheral::APB1_USB)    { APB1RSTR{}.USBRST()    = true; APB1RSTR{}.USBRST()    = false; return true; }
            else { return false; }
        }
    };

    template <typename Properties>
    class SystemBus : public Properties
    {
    public:
        using Properties::CoreClockSrc;
        using Properties::AHB_Prescale;
        using Properties::APB2_Prescale;
        using Properties::APB1_Prescale;
        using Properties::PLL_ClockSrc;
        using Properties::PLL_Multi;

        SystemBus() noexcept
        {
            using namespace MemoryMap;

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
                case SystemClockSource::HSI: return ::System::HSI_Clock;
                case SystemClockSource::HSE: return ::System::HSE_Clock;
                case SystemClockSource::PLL: return PLL_Clock();
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
        static void configure_pll() noexcept
        {
            using namespace MemoryMap;

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
                case HCLK_Prescaler::SYSCLK_DIV1: return 0u;
                case HCLK_Prescaler::SYSCLK_DIV2: return 1u;
                case HCLK_Prescaler::SYSCLK_DIV4: return 2u;
                case HCLK_Prescaler::SYSCLK_DIV8: return 3u;
                case HCLK_Prescaler::SYSCLK_DIV16: return 4u;
                case HCLK_Prescaler::SYSCLK_DIV64: return 6u;
                case HCLK_Prescaler::SYSCLK_DIV128: return 7u;
                case HCLK_Prescaler::SYSCLK_DIV256: return 8u;
                case HCLK_Prescaler::SYSCLK_DIV512: return 9u;
            }
        }
        static constexpr uint32_t pclk_prescaler(PCLK_Prescaler const input) noexcept
        {
            switch(input)
            {
                case PCLK_Prescaler::HCLK_DIV1: return 0u;
                case PCLK_Prescaler::HCLK_DIV2: return 1u;
                case PCLK_Prescaler::HCLK_DIV4: return 2u;
                case PCLK_Prescaler::HCLK_DIV8: return 3u;
                case PCLK_Prescaler::HCLK_DIV16: return 4u;
            }
        }
        static constexpr uint32_t pll_source_freq() noexcept
        {
            switch (PLL_ClockSrc)
            {
                case PLL_ClockSource::HSI_DIV2: return (::System::HSI_Clock >> 1u);
                case PLL_ClockSource::HSE: return ::System::HSE_Clock;
                case PLL_ClockSource::HSE_DIV2: return (::System::HSE_Clock >> 1u);
            }
        }
    };
}