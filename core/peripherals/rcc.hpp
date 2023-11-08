#pragma once

#include "constants.hpp"
#include "rcc_register.hpp"

#include "mcu_config.hpp"

#include "tools.hpp"
#include <etl/functional.h>

namespace Peripherals::ResetClockControl
{
    using namespace Settings;

    enum class State : bool
    {
        Off = false,
        On = true
    };
    enum class Peripheral : uint8_t
    {
        eTIM2 = 0,
        eTIM3,
        eTIM4,
        eRTC, 
        eWWDG,
        eIWDG,
        eSPI2,
        eUSART2,
        eUSART3,
        eI2C1,
        eI2C2,
        eCAN1,
        eBKP,
        ePWR,
        eAFIO,
        eEXTI, 
        eGPIOA,
        eGPIOB,
        eGPIOC,
        eGPIOD,
        eGPIOE,
        eADC1,
        eADC2, 
        eTIM1, 
        eSPI1, 
        eUSART1,
        eDMA1,
        eRCC,
        eCRC,
        eUSB,
        eFLASH,
        eSRAM
    };

    template <Peripheral P>
    struct PeripheralClockControl
    {
        static void Power(const State input = State::On) noexcept
        {
            using namespace Common::Tools;
            using namespace Registers;

            if constexpr(P == Peripheral::eCRC)    { AHBENR{}.CRCEN()     = EnumValue(input); }
            if constexpr(P == Peripheral::eFLASH)  { AHBENR{}.FLITFEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eSRAM)   { AHBENR{}.SRAMEN()    = EnumValue(input); }
            if constexpr(P == Peripheral::eDMA1)   { AHBENR{}.DMA1EN()    = EnumValue(input); }
            if constexpr(P == Peripheral::eUSART1) { APB2ENR{}.USART1EN() = EnumValue(input); }
            if constexpr(P == Peripheral::eSPI1)   { APB2ENR{}.SPI1EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eTIM1)   { APB2ENR{}.TIM1EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eADC2)   { APB2ENR{}.ADC2EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eADC1)   { APB2ENR{}.ADC1EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eGPIOE)  { APB2ENR{}.IOPEEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eGPIOD)  { APB2ENR{}.IOPDEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eGPIOC)  { APB2ENR{}.IOPCEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eGPIOB)  { APB2ENR{}.IOPBEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eGPIOA)  { APB2ENR{}.IOPAEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eAFIO)   { APB2ENR{}.AFIOEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::ePWR)    { APB1ENR{}.PWREN()    = EnumValue(input); }
            if constexpr(P == Peripheral::eBKP)    { APB1ENR{}.BKPEN()    = EnumValue(input); }
            if constexpr(P == Peripheral::eCAN1)   { APB1ENR{}.CAN1EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eUSB)    { APB1ENR{}.USBEN()    = EnumValue(input); }
            if constexpr(P == Peripheral::eI2C2)   { APB1ENR{}.I2C2EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eI2C1)   { APB1ENR{}.I2C1EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eUSART3) { APB1ENR{}.USART3EN() = EnumValue(input); }
            if constexpr(P == Peripheral::eUSART2) { APB1ENR{}.USART2EN() = EnumValue(input); }
            if constexpr(P == Peripheral::eSPI2)   { APB1ENR{}.SPI2EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eWWDG)   { APB1ENR{}.WWDGEN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eTIM4)   { APB1ENR{}.TIM4EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eTIM3)   { APB1ENR{}.TIM3EN()   = EnumValue(input); }
            if constexpr(P == Peripheral::eTIM2)   { APB1ENR{}.TIM2EN()   = EnumValue(input); }
        }
        static bool Reset() noexcept
        {
            using namespace Registers;

            if      constexpr(P == Peripheral::eUSART1) { APB2RSTR{}.USART1RST() = true; APB2RSTR{}.USART1RST() = false; return true; }
            else if constexpr(P == Peripheral::eSPI1)   { APB2RSTR{}.SPI1RST()   = true; APB2RSTR{}.SPI1RST()   = false; return true; }
            else if constexpr(P == Peripheral::eTIM1)   { APB2RSTR{}.TIM1RST()   = true; APB2RSTR{}.TIM1RST()   = false; return true; }
            else if constexpr(P == Peripheral::eADC2)   { APB2RSTR{}.ADC2RST()   = true; APB2RSTR{}.ADC2RST()   = false; return true; }
            else if constexpr(P == Peripheral::eADC1)   { APB2RSTR{}.ADC1RST()   = true; APB2RSTR{}.ADC1RST()   = false; return true; }
            else if constexpr(P == Peripheral::eGPIOE)  { APB2RSTR{}.IOPERST()   = true; APB2RSTR{}.IOPERST()   = false; return true; }
            else if constexpr(P == Peripheral::eGPIOD)  { APB2RSTR{}.IOPDRST()   = true; APB2RSTR{}.IOPDRST()   = false; return true; }
            else if constexpr(P == Peripheral::eGPIOC)  { APB2RSTR{}.IOPCRST()   = true; APB2RSTR{}.IOPCRST()   = false; return true; }
            else if constexpr(P == Peripheral::eGPIOB)  { APB2RSTR{}.IOPBRST()   = true; APB2RSTR{}.IOPBRST()   = false; return true; }
            else if constexpr(P == Peripheral::eGPIOA)  { APB2RSTR{}.IOPARST()   = true; APB2RSTR{}.IOPARST()   = false; return true; }
            else if constexpr(P == Peripheral::eAFIO)   { APB2RSTR{}.AFIORST()   = true; APB2RSTR{}.AFIORST()   = false; return true; }
            else if constexpr(P == Peripheral::ePWR)    { APB1RSTR{}.PWRRST()    = true; APB1RSTR{}.PWRRST()    = false; return true; }
            else if constexpr(P == Peripheral::eBKP)    { APB1RSTR{}.BKPRST()    = true; APB1RSTR{}.BKPRST()    = false; return true; }
            else if constexpr(P == Peripheral::eCAN1)   { APB1RSTR{}.CAN1RST()   = true; APB1RSTR{}.CAN1RST()   = false; return true; }
            else if constexpr(P == Peripheral::eUSB)    { APB1RSTR{}.USBRST()    = true; APB1RSTR{}.USBRST()    = false; return true; }
            else if constexpr(P == Peripheral::eI2C2)   { APB1RSTR{}.I2C2RST()   = true; APB1RSTR{}.I2C2RST()   = false; return true; }
            else if constexpr(P == Peripheral::eI2C1)   { APB1RSTR{}.I2C1RST()   = true; APB1RSTR{}.I2C1RST()   = false; return true; }
            else if constexpr(P == Peripheral::eUSART3) { APB1RSTR{}.USART3RST() = true; APB1RSTR{}.USART3RST() = false; return true; }
            else if constexpr(P == Peripheral::eUSART2) { APB1RSTR{}.USART2RST() = true; APB1RSTR{}.USART2RST() = false; return true; }
            else if constexpr(P == Peripheral::eSPI2)   { APB1RSTR{}.SPI2RST()   = true; APB1RSTR{}.SPI2RST()   = false; return true; }
            else if constexpr(P == Peripheral::eWWDG)   { APB1RSTR{}.WWDGRST()   = true; APB1RSTR{}.WWDGRST()   = false; return true; }
            else if constexpr(P == Peripheral::eTIM4)   { APB1RSTR{}.TIM4RST()   = true; APB1RSTR{}.TIM4RST()   = false; return true; }
            else if constexpr(P == Peripheral::eTIM3)   { APB1RSTR{}.TIM3RST()   = true; APB1RSTR{}.TIM3RST()   = false; return true; }
            else if constexpr(P == Peripheral::eTIM2)   { APB1RSTR{}.TIM2RST()   = true; APB1RSTR{}.TIM2RST()   = false; return true; }
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
            using namespace Registers;

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
            using namespace Registers;

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