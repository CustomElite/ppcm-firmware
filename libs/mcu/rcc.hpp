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
            using REGS = HardwareKernal::Registers;
            
            if constexpr(tClockID == ClockID::APB2_AFIO)   { REGS::APB2ENR().AFIOEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOA)  { REGS::APB2ENR().IOPAEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOB)  { REGS::APB2ENR().IOPBEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOC)  { REGS::APB2ENR().IOPCEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOD)  { REGS::APB2ENR().IOPDEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_GPIOE)  { REGS::APB2ENR().IOPEEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_ADC1)   { REGS::APB2ENR().ADC1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_ADC2)   { REGS::APB2ENR().ADC2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_TIM1)   { REGS::APB2ENR().TIM1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_SPI1)   { REGS::APB2ENR().SPI1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB2_USART1) { REGS::APB2ENR().USART1EN() = EnumValue(input); }
            
            if constexpr(tClockID == ClockID::APB1_TIM2)   { REGS::APB1ENR().TIM2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_TIM3)   { REGS::APB1ENR().TIM3EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_TIM4)   { REGS::APB1ENR().TIM4EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_WWDG)   { REGS::APB1ENR().WWDGEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_SPI2)   { REGS::APB1ENR().SPI2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USART2) { REGS::APB1ENR().USART2EN() = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USART3) { REGS::APB1ENR().USART3EN() = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_I2C1)   { REGS::APB1ENR().I2C1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_I2C2)   { REGS::APB1ENR().I2C2EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_CAN1)   { REGS::APB1ENR().CAN1EN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_BKP)    { REGS::APB1ENR().BKPEN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_PWR)    { REGS::APB1ENR().PWREN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::APB1_USB)    { REGS::APB1ENR().USBEN()    = EnumValue(input); }

            if constexpr(tClockID == ClockID::AHB_DMA1)   { REGS::AHBENR().DMA1EN()    = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_CRC)    { REGS::AHBENR().CRCEN()     = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_FLASH)  { REGS::AHBENR().FLITFEN()   = EnumValue(input); }
            if constexpr(tClockID == ClockID::AHB_SRAM)   { REGS::AHBENR().SRAMEN()    = EnumValue(input); }
        }
        ALWAYS_INLINE
        static constexpr void ResetPeripheral() noexcept
        {
            using REGS = HardwareKernal::Registers;

            if constexpr(tClockID == ClockID::APB2_AFIO)   { REGS::APB2RSTR().AFIORST()   = true; REGS::APB2RSTR().AFIORST()   = false; }
            if constexpr(tClockID == ClockID::APB2_GPIOA)  { REGS::APB2RSTR().IOPARST()   = true; REGS::APB2RSTR().IOPARST()   = false; }           
            if constexpr(tClockID == ClockID::APB2_GPIOB)  { REGS::APB2RSTR().IOPBRST()   = true; REGS::APB2RSTR().IOPBRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOC)  { REGS::APB2RSTR().IOPCRST()   = true; REGS::APB2RSTR().IOPCRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOD)  { REGS::APB2RSTR().IOPDRST()   = true; REGS::APB2RSTR().IOPDRST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_GPIOE)  { REGS::APB2RSTR().IOPERST()   = true; REGS::APB2RSTR().IOPERST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_ADC1)   { REGS::APB2RSTR().ADC1RST()   = true; REGS::APB2RSTR().ADC1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_ADC2)   { REGS::APB2RSTR().ADC2RST()   = true; REGS::APB2RSTR().ADC2RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_TIM1)   { REGS::APB2RSTR().TIM1RST()   = true; REGS::APB2RSTR().TIM1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_SPI1)   { REGS::APB2RSTR().SPI1RST()   = true; REGS::APB2RSTR().SPI1RST()   = false; }            
            if constexpr(tClockID == ClockID::APB2_USART1) { REGS::APB2RSTR().USART1RST() = true; REGS::APB2RSTR().USART1RST() = false; }
        
            if constexpr(tClockID == ClockID::APB1_TIM2)   { REGS::APB1RSTR().TIM2RST()   = true; REGS::APB1RSTR().TIM2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_TIM3)   { REGS::APB1RSTR().TIM3RST()   = true; REGS::APB1RSTR().TIM3RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_TIM4)   { REGS::APB1RSTR().TIM4RST()   = true; REGS::APB1RSTR().TIM4RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_WWDG)   { REGS::APB1RSTR().WWDGRST()   = true; REGS::APB1RSTR().WWDGRST()   = false; }
            if constexpr(tClockID == ClockID::APB1_SPI2)   { REGS::APB1RSTR().SPI2RST()   = true; REGS::APB1RSTR().SPI2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_USART2) { REGS::APB1RSTR().USART2RST() = true; REGS::APB1RSTR().USART2RST() = false; }
            if constexpr(tClockID == ClockID::APB1_USART3) { REGS::APB1RSTR().USART3RST() = true; REGS::APB1RSTR().USART3RST() = false; }
            if constexpr(tClockID == ClockID::APB1_I2C1)   { REGS::APB1RSTR().I2C1RST()   = true; REGS::APB1RSTR().I2C1RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_I2C2)   { REGS::APB1RSTR().I2C2RST()   = true; REGS::APB1RSTR().I2C2RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_CAN1)   { REGS::APB1RSTR().CAN1RST()   = true; REGS::APB1RSTR().CAN1RST()   = false; }
            if constexpr(tClockID == ClockID::APB1_BKP)    { REGS::APB1RSTR().BKPRST()    = true; REGS::APB1RSTR().BKPRST()    = false; }
            if constexpr(tClockID == ClockID::APB1_PWR)    { REGS::APB1RSTR().PWRRST()    = true; REGS::APB1RSTR().PWRRST()    = false; }
            if constexpr(tClockID == ClockID::APB1_USB)    { REGS::APB1RSTR().USBRST()    = true; REGS::APB1RSTR().USBRST()    = false; }
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
        std::uint32_t tHSI_ClockFreq,
        std::uint32_t tHSE_ClockFreq
    >
    struct Properties
    {
        static constexpr auto s_SysClockSrc = tAHB_ClockSource;
        static constexpr auto s_AHB_Prescale = tAHB_Prescale;
        static constexpr auto s_APB2_Prescale = tAPB2_Prescale;
        static constexpr auto s_APB1_Prescale = tAPB1_Prescale;
        static constexpr auto s_PLL_ClockSrc = tPLL_ClockSource;
        static constexpr auto s_PLL_Multi = tPLL_Multipler;
        static constexpr auto s_HSI_ClockFreq = tHSI_ClockFreq;
        static constexpr auto s_HSE_ClockFreq = tHSE_ClockFreq;
    };

    template <typename tProperties>
    class SystemBus : public tProperties
    {
    public:
        SystemBus() noexcept
        {
            LL_FLASH_SetLatency(LL_FLASH_LATENCY_0); // TODO: Add flash registers
            while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {} // TODO:

            if constexpr ((s_SysClockSrc == SystemClockSource::HSE) || (s_PLL_ClockSrc != PLL_ClockSource::HSI_Div_2))
            {
                HW::Enable(Clocks::HSE);
            }
            else 
            {
                HW::Enable(Clocks::HSI);
            }

            if constexpr (s_SysClockSrc == SystemClockSource::PLL)
            {
                HW::Configure(s_PLL_ClockSrc, s_PLL_Multi);
            }

            HW::Configure(s_SysClockSrc, s_AHB_Prescale, s_APB2_Prescale, s_APB1_Prescale);

            SystemCoreClock = SystemClockFreq();
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t SystemClockFreq() noexcept
        {
            if constexpr (s_SysClockSrc == SystemClockSource::HSI) { return s_HSI_ClockFreq; }
            if constexpr (s_SysClockSrc == SystemClockSource::HSE) { return s_HSE_ClockFreq; }
            if constexpr (s_SysClockSrc == SystemClockSource::PLL) { return PLL_ClockFreq(); }
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t AHB_ClockFreq() noexcept
        {
            return (SystemClockFreq() >> HCLK_DivShift());
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t APB2_ClockFreq() noexcept
        {
            return (AHB_ClockFreq() >> PCLK2_DivShift());
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t APB1_ClockFreq() noexcept
        {
            return (AHB_ClockFreq() >> PCLK1_DivShift());
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t PLL_ClockFreq() noexcept
        {
            return (PLL_SrcFreq() * (Common::Tools::EnumValue(s_PLL_Multi) + 2u));
        }

    private:
        using HW = HardwareKernal;

        using tProperties::s_SysClockSrc
            , tProperties::s_AHB_Prescale
            , tProperties::s_APB2_Prescale
            , tProperties::s_APB1_Prescale
            , tProperties::s_PLL_ClockSrc
            , tProperties::s_PLL_Multi
            , tProperties::s_HSI_ClockFreq
            , tProperties::s_HSE_ClockFreq;

        ALWAYS_INLINE
        static constexpr std::uint32_t HCLK_DivShift() noexcept
        {
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_1) { return 0u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_2) { return 1u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_4) { return 2u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_8) { return 3u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_16) { return 4u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_64) { return 6u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_128) { return 7u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_256) { return 8u; }
            if constexpr (s_AHB_Prescale == HCLK_Prescaler::Div_512) { return 9u; }
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t PCLK2_DivShift() noexcept
        {
            if constexpr (s_APB2_Prescale == PCLK2_Prescaler::Div_1) { return 0u; }
            if constexpr (s_APB2_Prescale == PCLK2_Prescaler::Div_2) { return 1u; }
            if constexpr (s_APB2_Prescale == PCLK2_Prescaler::Div_4) { return 2u; }
            if constexpr (s_APB2_Prescale == PCLK2_Prescaler::Div_8) { return 3u; }
            if constexpr (s_APB2_Prescale == PCLK2_Prescaler::Div_16) { return 4u; }
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t PCLK1_DivShift() noexcept
        {
            if constexpr (s_APB1_Prescale == PCLK1_Prescaler::Div_1) { return 0u; }
            if constexpr (s_APB1_Prescale == PCLK1_Prescaler::Div_2) { return 1u; }
            if constexpr (s_APB1_Prescale == PCLK1_Prescaler::Div_4) { return 2u; }
            if constexpr (s_APB1_Prescale == PCLK1_Prescaler::Div_8) { return 3u; }
            if constexpr (s_APB1_Prescale == PCLK1_Prescaler::Div_16) { return 4u; }
        }
        ALWAYS_INLINE
        static constexpr std::uint32_t PLL_SrcFreq() noexcept
        {
            if constexpr (s_PLL_ClockSrc == PLL_ClockSource::HSI_Div_2) { return (s_HSI_ClockFreq >> 1u); }
            if constexpr (s_PLL_ClockSrc == PLL_ClockSource::HSE) { return s_HSE_ClockFreq; }
            if constexpr (s_PLL_ClockSrc == PLL_ClockSource::HSE_Div_2) { return (s_HSE_ClockFreq >> 1u); }
        }
    };
}