#pragma once

#include "register.hpp"
#include "tools.hpp"

#include "stm32f1xx.h"

namespace Peripherals::ResetClockControl 
{
    namespace Settings 
    {
        enum class SystemClockSource : uint8_t
        {
            HSI = 0,
            HSE,
            PLL
        };
        enum class PLL_ClockSource : uint8_t
        {
            HSI_DIV2 = 0,
            HSE,
            HSE_DIV2 
        };
        enum class RTC_ClockSource : uint8_t
        {
            Disabled = 0,
            LSE,
            LSI,
            HSE
        };
        enum class OutputClockSource : uint8_t
        {
            Disabled = 0b000,
            SYSCLK = 0b100,
            HSI = 0b101,
            HSE = 0b110,
            PLL_DIV2 = 0b111
        };
        enum class PLL_Multiplier : uint8_t
        {
            X2 = 0,
            X3,
            X4,
            X5,
            X6,
            X7,
            X8,
            X9,
            X10,
            X11,
            X12,
            X13,
            X14,
            X15,
            X16
        };
        enum class ADC_Prescaler : uint8_t
        {
            PCLK2_DIV2 = 0,
            PCLK2_DIV4,
            PCLK2_DIV6,
            PCLK2_DIV8
        };
        enum class PCLK_Prescaler : uint8_t
        {
            HCLK_DIV1 = 0b000,
            HCLK_DIV2 = 0b100,
            HCLK_DIV4 = 0b101,
            HCLK_DIV8 = 0b110,
            HCLK_DIV16 = 0b111
        };
        enum class HCLK_Prescaler : uint8_t
        {
            SYSCLK_DIV1 = 0b0000,
            SYSCLK_DIV2 = 0b1000,
            SYSCLK_DIV4 = 0b1001,
            SYSCLK_DIV8 = 0b1010,
            SYSCLK_DIV16 = 0b1011,
            SYSCLK_DIV64 = 0b1100,
            SYSCLK_DIV128 = 0b1101,
            SYSCLK_DIV256 = 0b1110,
            SYSCLK_DIV512 = 0b1111
        };
    }

    namespace Registers
    {
        using namespace Settings;

        template <uint32_t ADDR>
        struct CR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto PLLRDY() { return reg_t::template Bits<RCC_CR_PLLRDY>(); }
            auto PLLON() { return reg_t::template Bits<RCC_CR_PLLON>(); }
            auto CSSON() { return reg_t::template Bits<RCC_CR_CSSON>(); }
            auto HSEBYP() { return reg_t::template Bits<RCC_CR_HSEBYP>(); }
            auto HSERDY() { return reg_t::template Bits<RCC_CR_HSERDY>(); }
            auto HSEON() { return reg_t::template Bits<RCC_CR_HSEON>(); }
            auto HSICAL() { return reg_t::template Bits<RCC_CR_HSICAL>(); }
            auto HSITRIM() { return reg_t::template Bits<RCC_CR_HSITRIM>(); }
            auto HSIRDY() { return reg_t::template Bits<RCC_CR_HSIRDY>(); }
            auto HSION() { return reg_t::template Bits<RCC_CR_HSION>(); }

            void EnablePLL() noexcept
            {
                if (!PLLON().Get())
                {
                    PLLON() = true;
                    while(!PLLRDY().Get());
                }
            }
            void DisablePLL() noexcept
            {
                if (PLLON().Get())
                {
                    PLLON() = false;
                    while(PLLRDY().Get());
                }
            }
            void EnableHSE() noexcept
            {
                if (!HSEON().Get())
                {
                    HSEON() = true;
                    while(!HSERDY().Get());
                }
            }
            void DisableHSE() noexcept
            {
                if (HSEON().Get())
                {
                    HSEON() = false;
                    while(HSERDY().Get());
                }
            }
            void EnableHSI() noexcept
            {
                if (!HSION().Get())
                {
                    HSION() = true;
                    while(!HSIRDY().Get());
                }
            }
            void DisableHSI() noexcept
            {
                if (HSION().Get())
                {
                    HSION() = false;
                    while(HSIRDY().Get());
                }
            }
        };

        template <uint32_t ADDR>
        struct CFGR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto MCO() { return reg_t::template Bits<RCC_CFGR_MCO>(); }
            auto USBPRE() { return reg_t::template Bits<RCC_CFGR_USBPRE>(); }
            auto PLLMUL() { return reg_t::template Bits<RCC_CFGR_PLLMULL>(); }
            auto PLLXTPRE() { return reg_t::template Bits<RCC_CFGR_PLLXTPRE>(); }
            auto PLLSRC() { return reg_t::template Bits<RCC_CFGR_PLLSRC>(); }
            auto ADCPRE() { return reg_t::template Bits<RCC_CFGR_ADCPRE>(); }
            auto PPRE2() { return reg_t::template Bits<RCC_CFGR_PPRE2>(); }
            auto PPRE1() { return reg_t::template Bits<RCC_CFGR_PPRE1>(); }
            auto HPRE() { return reg_t::template Bits<RCC_CFGR_HPRE>(); }
            auto SWS() { return reg_t::template Bits<RCC_CFGR_SWS>(); }
            auto SW() { return reg_t::template Bits<RCC_CFGR_SW>(); }

            void SetOutputClock(OutputClockSource const input) noexcept
            {
                MCO() = Common::Tools::EnumValue(input);
            }
            void SetPLL_Multiplier(PLL_Multiplier const input) noexcept
            {
                PLLMUL() = Common::Tools::EnumValue(input);
            }
            void SetPLL_Source(PLL_ClockSource const input) noexcept
            {
                if (input == PLL_ClockSource::HSI_DIV2)
                {
                    PLLXTPRE() = false;
                    PLLSRC() = false;
                }
                else {
                    if (input == PLL_ClockSource::HSE_DIV2)
                    {
                        PLLXTPRE() = true;
                        PLLSRC() = true;
                    }
                    else {
                        PLLXTPRE() = false;
                        PLLSRC() = true;
                    }
                }
            }
            void SetADC_Prescaler(ADC_Prescaler const input) noexcept
            {
                ADCPRE() = Common::Tools::EnumValue(input);
            }
            void SetSystemClock(SystemClockSource const input) noexcept
            {
                SW() = Common::Tools::EnumValue(input);
                while(SWS().Get() != Common::Tools::EnumValue(input));
            }
            void SetBusPrescalers(HCLK_Prescaler const AHB, PCLK_Prescaler const APB2, PCLK_Prescaler const APB1) noexcept
            {
                HPRE() = Common::Tools::EnumValue(AHB);
                PPRE2() = Common::Tools::EnumValue(APB2);
                PPRE1() = Common::Tools::EnumValue(APB1);
            }
        };

        template <uint32_t ADDR>
        struct CIR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto CSSC()  { return reg_t::template Bits<RCC_CIR_CSSC>(); }
            auto PLLRDYC() { return reg_t::template Bits<RCC_CIR_PLLRDYC>(); }
            auto HSERDYC() { return reg_t::template Bits<RCC_CIR_HSERDYC>(); }
            auto HSIRDYC() { return reg_t::template Bits<RCC_CIR_HSIRDYC>(); }
            auto LSERDYC() { return reg_t::template Bits<RCC_CIR_LSERDYC>(); }
            auto LSIRDYC() { return reg_t::template Bits<RCC_CIR_LSIRDYC>(); }
            auto PLLRDYIE() { return reg_t::template Bits<RCC_CIR_PLLRDYIE>(); }
            auto HSERDYIE() { return reg_t::template Bits<RCC_CIR_HSERDYIE>(); }
            auto HSIRDYIE() { return reg_t::template Bits<RCC_CIR_HSIRDYIE>(); }
            auto LSERDYIE() { return reg_t::template Bits<RCC_CIR_LSERDYIE>(); }
            auto LSIRDYIE() { return reg_t::template Bits<RCC_CIR_LSIRDYIE>(); }
            auto CSSF() { return reg_t::template Bits<RCC_CIR_CSSF>(); }
            auto PLLRDYF() { return reg_t::template Bits<RCC_CIR_PLLRDYF>(); }
            auto HSERDYF() { return reg_t::template Bits<RCC_CIR_HSERDYF>(); }
            auto HSIRDYF() { return reg_t::template Bits<RCC_CIR_HSIRDYF>(); }
            auto LSERDYF() { return reg_t::template Bits<RCC_CIR_LSERDYF>(); }
            auto LSIRDYF() { return reg_t::template Bits<RCC_CIR_LSIRDYF>(); }
        };



        template <uint32_t ADDR>
        struct APB2RSTR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto USART1RST() { return reg_t::template Bits<RCC_APB2RSTR_USART1RST>(); }
            auto SPI1RST() { return reg_t::template Bits<RCC_APB2RSTR_SPI1RST>(); }
            auto TIM1RST() { return reg_t::template Bits<RCC_APB2RSTR_TIM1RST>(); }
            auto ADC2RST() { return reg_t::template Bits<RCC_APB2RSTR_ADC2RST>(); }
            auto ADC1RST() { return reg_t::template Bits<RCC_APB2RSTR_ADC1RST>(); }
            auto IOPERST() { return reg_t::template Bits<RCC_APB2RSTR_IOPERST>(); }
            auto IOPDRST() { return reg_t::template Bits<RCC_APB2RSTR_IOPDRST>(); }
            auto IOPCRST() { return reg_t::template Bits<RCC_APB2RSTR_IOPCRST>(); }
            auto IOPBRST() { return reg_t::template Bits<RCC_APB2RSTR_IOPBRST>(); }
            auto IOPARST() { return reg_t::template Bits<RCC_APB2RSTR_IOPARST>(); }
            auto AFIORST() { return reg_t::template Bits<RCC_APB2RSTR_AFIORST>(); }
        };

        template <uint32_t ADDR>
        struct APB1RSTR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto PWRRST() { return reg_t::template Bits<RCC_APB1RSTR_PWRRST>(); }
            auto BKPRST() { return reg_t::template Bits<RCC_APB1RSTR_BKPRST>(); }
            auto CAN1RST() { return reg_t::template Bits<RCC_APB1RSTR_CAN1RST>(); }
            auto USBRST() { return reg_t::template Bits<RCC_APB1RSTR_USBRST>(); }
            auto I2C2RST() { return reg_t::template Bits<RCC_APB1RSTR_I2C2RST>(); }
            auto I2C1RST() { return reg_t::template Bits<RCC_APB1RSTR_I2C1RST>(); }
            auto USART3RST() { return reg_t::template Bits<RCC_APB1RSTR_USART3RST>(); }
            auto USART2RST() { return reg_t::template Bits<RCC_APB1RSTR_USART2RST>(); }
            auto SPI2RST() { return reg_t::template Bits<RCC_APB1RSTR_SPI2RST>(); }
            auto WWDGRST() { return reg_t::template Bits<RCC_APB1RSTR_WWDGRST>(); }
            auto TIM4RST() { return reg_t::template Bits<RCC_APB1RSTR_TIM4RST>(); }
            auto TIM3RST() { return reg_t::template Bits<RCC_APB1RSTR_TIM3RST>(); }
            auto TIM2RST() { return reg_t::template Bits<RCC_APB1RSTR_TIM2RST>(); }
        };

        template <uint32_t ADDR>
        struct AHBENR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto CRCEN() { return reg_t::template Bits<RCC_AHBENR_CRCEN>(); }
            auto FLITFEN() { return reg_t::template Bits<RCC_AHBENR_FLITFEN>(); }
            auto SRAMEN() { return reg_t::template Bits<RCC_AHBENR_SRAMEN>(); }
            auto DMA1EN() { return reg_t::template Bits<RCC_AHBENR_DMA1EN>(); }
        };

        template <uint32_t ADDR>
        struct APB2ENR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto USART1EN() { return reg_t::template Bits<RCC_APB2ENR_USART1EN>(); }
            auto SPI1EN() { return reg_t::template Bits<RCC_APB2ENR_SPI1EN>(); }
            auto TIM1EN() { return reg_t::template Bits<RCC_APB2ENR_TIM1EN>(); }
            auto ADC2EN() { return reg_t::template Bits<RCC_APB2ENR_ADC2EN>(); }
            auto ADC1EN() { return reg_t::template Bits<RCC_APB2ENR_ADC1EN>(); }
            auto IOPEEN() { return reg_t::template Bits<RCC_APB2ENR_IOPEEN>(); }
            auto IOPDEN() { return reg_t::template Bits<RCC_APB2ENR_IOPDEN>(); }
            auto IOPCEN() { return reg_t::template Bits<RCC_APB2ENR_IOPCEN>(); }
            auto IOPBEN() { return reg_t::template Bits<RCC_APB2ENR_IOPBEN>(); }
            auto IOPAEN() { return reg_t::template Bits<RCC_APB2ENR_IOPAEN>(); }
            auto AFIOEN() { return reg_t::template Bits<RCC_APB2ENR_AFIOEN>(); }
        };

        template <uint32_t ADDR>
        struct APB1ENR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto PWREN() { return reg_t::template Bits<RCC_APB1ENR_PWREN>(); }
            auto BKPEN() { return reg_t::template Bits<RCC_APB1ENR_BKPEN>(); }
            auto CAN1EN() { return reg_t::template Bits<RCC_APB1ENR_CAN1EN>(); }
            auto USBEN() { return reg_t::template Bits<RCC_APB1ENR_USBEN>(); }
            auto I2C2EN() { return reg_t::template Bits<RCC_APB1ENR_I2C2EN>(); }
            auto I2C1EN() { return reg_t::template Bits<RCC_APB1ENR_I2C1EN>(); }
            auto USART3EN() { return reg_t::template Bits<RCC_APB1ENR_USART3EN>(); }
            auto USART2EN() { return reg_t::template Bits<RCC_APB1ENR_USART2EN>(); }
            auto SPI2EN() { return reg_t::template Bits<RCC_APB1ENR_SPI2EN>(); }
            auto WWDGEN() { return reg_t::template Bits<RCC_APB1ENR_WWDGEN>(); }
            auto TIM4EN() { return reg_t::template Bits<RCC_APB1ENR_TIM4EN>(); }
            auto TIM3EN() { return reg_t::template Bits<RCC_APB1ENR_TIM3EN>(); }
            auto TIM2EN() { return reg_t::template Bits<RCC_APB1ENR_TIM2EN>(); }
        };

        template <uint32_t ADDR>
        struct BDCR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto BDRST() { return reg_t::template Bits<RCC_BDCR_BDRST>(); }
            auto RTCEN() { return reg_t::template Bits<RCC_BDCR_RTCEN>(); }
            auto RTCSEL() { return reg_t::template Bits<RCC_BDCR_RTCSEL>(); }
            auto LSEBYP() { return reg_t::template Bits<RCC_BDCR_LSEBYP>(); }
            auto LSERDY() { return reg_t::template Bits<RCC_BDCR_LSERDY>(); }
            auto LSEON() { return reg_t::template Bits<RCC_BDCR_LSEON>(); }

            void ConfigureRTC(RTC_ClockSource const input) noexcept
            {
                RTCSEL() = Common::Tools::EnumValue(input);
                RTCEN() = true;
            }
            void ResetRTC() noexcept
            {
                BDRST() = true;
            }
            void EnableLSE() noexcept
            {
                if (!LSEON().Get())
                {
                    LSEON() = true;
                    while(!LSERDY().Get());
                }
            }
            void DisableLSE() noexcept
            {
                if (LSEON().Get())
                {
                    LSEON() = false;
                    while(LSERDY().Get());
                }
            }
        };

        template <uint32_t ADDR>
        struct CSR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto LPWRRSTF() { return reg_t::template Bits<RCC_CSR_LPWRRSTF>(); }
            auto WWDGRSTF() { return reg_t::template Bits<RCC_CSR_WWDGRSTF>(); }
            auto IWDGRSTF() { return reg_t::template Bits<RCC_CSR_IWDGRSTF>(); }
            auto SFTRSTF() { return reg_t::template Bits<RCC_CSR_SFTRSTF>(); }
            auto PORRSTF() { return reg_t::template Bits<RCC_CSR_PORRSTF>(); }
            auto PINRSTF() { return reg_t::template Bits<RCC_CSR_PINRSTF>(); }
            auto RMVF() { return reg_t::template Bits<RCC_CSR_RMVF>(); }
            auto LSIRDY() { return reg_t::template Bits<RCC_CSR_LSIRDY>(); }
            auto LSION() { return reg_t::template Bits<RCC_CSR_LSION>(); }

            void ClearResetFlags() noexcept
            {
                RMVF() = true;
            }
            void EnableLSI() noexcept
            {
                if (!LSION().Get())
                {
                    LSION() = true;
                    while(!LSIRDY().Get());
                }
            }
            void DisableLSI() noexcept
            {
                if (LSION().Get())
                {
                    LSION() = false;
                    while(LSIRDY().Get());
                }
            }
        };

        CR() -> CR<RCC_BASE + offsetof(RCC_TypeDef, CR)>;
        CFGR() -> CFGR<RCC_BASE + offsetof(RCC_TypeDef, CFGR)>;
        CIR() -> CIR<RCC_BASE + offsetof(RCC_TypeDef, CIR)>;
        APB2RSTR() -> APB2RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR)>;
        APB1RSTR() -> APB1RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR)>;
        AHBENR() -> AHBENR<RCC_BASE + offsetof(RCC_TypeDef, AHBENR)>;
        APB2ENR() -> APB2ENR<RCC_BASE + offsetof(RCC_TypeDef, APB2ENR)>;
        APB1ENR() -> APB1ENR<RCC_BASE + offsetof(RCC_TypeDef, APB1ENR)>;
        BDCR() -> BDCR<RCC_BASE + offsetof(RCC_TypeDef, BDCR)>;
        CSR() -> CSR<RCC_BASE + offsetof(RCC_TypeDef, CSR)>;
    }
}