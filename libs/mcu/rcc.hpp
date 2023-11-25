#pragma once

#include "common/run_once.hpp"
#include "mcu/rcc_register.hpp"
#include "mcu_config.hpp"

#include "rcc_register.hpp"

#include "common/tools.hpp"

namespace MCU::CLK
{
    enum class State : bool
    {
        Off = false,
        On = true
    };

    enum class ClockID : uint8_t
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

    template <ClockID tClockID>
    struct Kernal : public Common::RunOnce<Kernal<tClockID>>
    {
        static void Construct() noexcept
        {
            ClockState(State::On);
        }
        static void Destruct() noexcept
        {
            ResetPeripheral();
            ClockState(State::Off);
        }
        ALWAYS_INLINE
        static constexpr void ClockState(State const input) noexcept
        {
            using namespace Common::Tools;
            using namespace MemoryMap;
            
            if constexpr(tClockID == ClockID::APB2_AFIO)   { Registers::APB2ENR{}.AFIOEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOA)  { Registers::APB2ENR{}.IOPAEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOB)  { Registers::APB2ENR{}.IOPBEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOC)  { Registers::APB2ENR{}.IOPCEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOD)  { Registers::APB2ENR{}.IOPDEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOE)  { Registers::APB2ENR{}.IOPEEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_ADC1)   { Registers::APB2ENR{}.ADC1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_ADC2)   { Registers::APB2ENR{}.ADC2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_TIM1)   { Registers::APB2ENR{}.TIM1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_SPI1)   { Registers::APB2ENR{}.SPI1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_USART1) { Registers::APB2ENR{}.USART1EN() = EnumValue(input); }
            
            if constexpr(tClockID == ClockID::APB1_TIM2)   { Registers::APB1ENR{}.TIM2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_TIM3)   { Registers::APB1ENR{}.TIM3EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_TIM4)   { Registers::APB1ENR{}.TIM4EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_WWDG)   { Registers::APB1ENR{}.WWDGEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_SPI2)   { Registers::APB1ENR{}.SPI2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USART2) { Registers::APB1ENR{}.USART2EN() = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USART3) { Registers::APB1ENR{}.USART3EN() = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_I2C1)   { Registers::APB1ENR{}.I2C1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_I2C2)   { Registers::APB1ENR{}.I2C2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_CAN1)   { Registers::APB1ENR{}.CAN1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_BKP)    { Registers::APB1ENR{}.BKPEN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_PWR)    { Registers::APB1ENR{}.PWREN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USB)    { Registers::APB1ENR{}.USBEN()    = EnumValue(input); }

            if constexpr(tClockID == ClockID::AHB_DMA1)   { Registers::AHBENR{}.DMA1EN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_CRC)    { Registers::AHBENR{}.CRCEN()     = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_FLASH)  { Registers::AHBENR{}.FLITFEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_SRAM)   { Registers::AHBENR{}.SRAMEN()    = EnumValue(input); }
        }
        ALWAYS_INLINE
        static constexpr void ResetPeripheral() noexcept
        {
            using namespace MemoryMap;

            if constexpr(tClockID == ClockID::APB2_AFIO)   { Registers::APB2RSTR{}.AFIORST()   = true; Registers::APB2RSTR{}.AFIORST()   = false; }
            if constexpr(tClockID == ClockID::APB2_GPIOA)  { Registers::APB2RSTR{}.IOPARST()   = true; Registers::APB2RSTR{}.IOPARST()   = false; }           
            if constexpr(tClockID == ClockID::APB2_GPIOB)  { Registers::APB2RSTR{}.IOPBRST()   = true; Registers::APB2RSTR{}.IOPBRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOC)  { Registers::APB2RSTR{}.IOPCRST()   = true; Registers::APB2RSTR{}.IOPCRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOD)  { Registers::APB2RSTR{}.IOPDRST()   = true; Registers::APB2RSTR{}.IOPDRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOE)  { Registers::APB2RSTR{}.IOPERST()   = true; Registers::APB2RSTR{}.IOPERST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_ADC1)   { Registers::APB2RSTR{}.ADC1RST()   = true; Registers::APB2RSTR{}.ADC1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_ADC2)   { Registers::APB2RSTR{}.ADC2RST()   = true; Registers::APB2RSTR{}.ADC2RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_TIM1)   { Registers::APB2RSTR{}.TIM1RST()   = true; Registers::APB2RSTR{}.TIM1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_SPI1)   { Registers::APB2RSTR{}.SPI1RST()   = true; Registers::APB2RSTR{}.SPI1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_USART1) { Registers::APB2RSTR{}.USART1RST() = true; Registers::APB2RSTR{}.USART1RST() = false; }
        
            if constexpr(tClockID == ClockID::APB1_TIM2)   { Registers::APB1RSTR{}.TIM2RST()   = true; Registers::APB1RSTR{}.TIM2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_TIM3)   { Registers::APB1RSTR{}.TIM3RST()   = true; Registers::APB1RSTR{}.TIM3RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_TIM4)   { Registers::APB1RSTR{}.TIM4RST()   = true; Registers::APB1RSTR{}.TIM4RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_WWDG)   { Registers::APB1RSTR{}.WWDGRST()   = true; Registers::APB1RSTR{}.WWDGRST()   = false; }
            if constexpr(tClockID == ClockID::APB1_SPI2)   { Registers::APB1RSTR{}.SPI2RST()   = true; Registers::APB1RSTR{}.SPI2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_USART2) { Registers::APB1RSTR{}.USART2RST() = true; Registers::APB1RSTR{}.USART2RST() = false; }
            if constexpr(tClockID == ClockID::APB1_USART3) { Registers::APB1RSTR{}.USART3RST() = true; Registers::APB1RSTR{}.USART3RST() = false; }
            if constexpr(tClockID == ClockID::APB1_I2C1)   { Registers::APB1RSTR{}.I2C1RST()   = true; Registers::APB1RSTR{}.I2C1RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_I2C2)   { Registers::APB1RSTR{}.I2C2RST()   = true; Registers::APB1RSTR{}.I2C2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_CAN1)   { Registers::APB1RSTR{}.CAN1RST()   = true; Registers::APB1RSTR{}.CAN1RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_BKP)    { Registers::APB1RSTR{}.BKPRST()    = true; Registers::APB1RSTR{}.BKPRST()    = false; }
            if constexpr(tClockID == ClockID::APB1_PWR)    { Registers::APB1RSTR{}.PWRRST()    = true; Registers::APB1RSTR{}.PWRRST()    = false; }
            if constexpr(tClockID == ClockID::APB1_USB)    { Registers::APB1RSTR{}.USBRST()    = true; Registers::APB1RSTR{}.USBRST()    = false; }
        }
    };

    template
    <
        SystemClockSource tAHB_ClockSource,
        HCLK_Prescaler tAHB_Prescale,
        PCLK2_Prescaler tAPB2_Prescale,
        PCLK1_Prescaler tAPB1_Prescale,
        PLL_ClockSource tPLL_ClockSource,
        PLL_Multiplier tPLL_Multipler,
        uint32_t tHSI_ClockFreq,
        uint32_t tHSE_ClockFreq
    >
    struct Properties
    {
        static constexpr auto CoreClockSrc = tAHB_ClockSource;
        static constexpr auto AHB_Prescale = tAHB_Prescale;
        static constexpr auto APB2_Prescale = tAPB2_Prescale;
        static constexpr auto APB1_Prescale = tAPB1_Prescale;
        static constexpr auto PLL_ClockSrc = tPLL_ClockSource;
        static constexpr auto PLL_Multi = tPLL_Multipler;
        static constexpr auto HSI_ClockFreq = tHSI_ClockFreq;
        static constexpr auto HSE_ClockFreq = tHSE_ClockFreq;
    };

    template <typename tProperties>
    class SystemBus : public tProperties
    {
    public:
        SystemBus() noexcept
        {
            LL_FLASH_SetLatency(LL_FLASH_LATENCY_0); // TODO: Add flash registers
            while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {} // TODO: 

            if constexpr (CoreClockSrc == SystemClockSource::PLL)
            {
                if constexpr (PLL_ClockSrc == PLL_ClockSource::HSI_DIV2)
                { 
                    Registers::CR{}.Enable(SystemClockSource::HSI);
                }
                else { 
                    Registers::CR{}.Enable(SystemClockSource::HSE);
                }

                Registers::CFGR{}.Configure(PLL_ClockSrc, PLL_Multi);
            }
            else {
                Registers::CR{}.Enable(CoreClockSrc);
            }
            
            Registers::CFGR{}.Configure(CoreClockSrc, AHB_Prescale, APB2_Prescale, APB1_Prescale);

            SystemCoreClock = CoreClockFreq();
        }
        ALWAYS_INLINE
        static constexpr uint32_t CoreClockFreq() noexcept
        {
            if constexpr (CoreClockSrc == SystemClockSource::HSI) { return HSI_ClockFreq; }
            if constexpr (CoreClockSrc == SystemClockSource::HSE) { return HSE_ClockFreq; }
            if constexpr (CoreClockSrc == SystemClockSource::PLL) { return PLL_ClockFreq(); }
        }
        ALWAYS_INLINE
        static constexpr uint32_t AHB_ClockFreq() noexcept
        {
            return (CoreClockFreq() >> HCLK_DivShift());
        }
        ALWAYS_INLINE
        static constexpr uint32_t APB2_ClockFreq() noexcept
        {
            return (AHB_ClockFreq() >> PCLK2_DivShift());
        }
        ALWAYS_INLINE
        static constexpr uint32_t APB1_ClockFreq() noexcept
        {
            return (AHB_ClockFreq() >> PCLK1_DivShift());
        }
        ALWAYS_INLINE
        static constexpr uint32_t PLL_ClockFreq() noexcept
        {
            return (PLL_SrcFreq() * (Common::Tools::EnumValue(PLL_Multi) + 2u));
        }

    private:
        using
            tProperties::CoreClockSrc,
            tProperties::AHB_Prescale,
            tProperties::APB2_Prescale,
            tProperties::APB1_Prescale,
            tProperties::PLL_ClockSrc,
            tProperties::PLL_Multi,
            tProperties::HSI_ClockFreq,
            tProperties::HSE_ClockFreq;

        ALWAYS_INLINE
        static constexpr uint32_t HCLK_DivShift() noexcept
        {
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV1) { return 0u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV2) { return 1u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV4) { return 2u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV8) { return 3u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV16) { return 4u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV64) { return 6u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV128) { return 7u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV256) { return 8u; }
            if constexpr (AHB_Prescale == HCLK_Prescaler::DIV512) { return 9u; }
        }
        ALWAYS_INLINE
        static constexpr uint32_t PCLK2_DivShift() noexcept
        {
            if constexpr (APB2_Prescale == PCLK2_Prescaler::DIV1) { return 0u; }
            if constexpr (APB2_Prescale == PCLK2_Prescaler::DIV2) { return 1u; }
            if constexpr (APB2_Prescale == PCLK2_Prescaler::DIV4) { return 2u; }
            if constexpr (APB2_Prescale == PCLK2_Prescaler::DIV8) { return 3u; }
            if constexpr (APB2_Prescale == PCLK2_Prescaler::DIV16) { return 4u; }
        }
        ALWAYS_INLINE
        static constexpr uint32_t PCLK1_DivShift() noexcept
        {
            if constexpr (APB1_Prescale == PCLK1_Prescaler::DIV1) { return 0u; }
            if constexpr (APB1_Prescale == PCLK1_Prescaler::DIV2) { return 1u; }
            if constexpr (APB1_Prescale == PCLK1_Prescaler::DIV4) { return 2u; }
            if constexpr (APB1_Prescale == PCLK1_Prescaler::DIV8) { return 3u; }
            if constexpr (APB1_Prescale == PCLK1_Prescaler::DIV16) { return 4u; }
        }
        ALWAYS_INLINE
        static constexpr uint32_t PLL_SrcFreq() noexcept
        {
            if constexpr (PLL_ClockSrc == PLL_ClockSource::HSI_DIV2) { return (HSI_ClockFreq >> 1u); }
            if constexpr (PLL_ClockSrc == PLL_ClockSource::HSE) { return HSE_ClockFreq; }
            if constexpr (PLL_ClockSrc == PLL_ClockSource::HSE_DIV2) { return (HSE_ClockFreq >> 1u); }
        }
    };
}