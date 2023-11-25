#pragma once

#include "common/register.hpp"
#include "common/tools.hpp"

#include "stm32f1xx.h"

namespace MCU::CLK 
{
    inline namespace Settings 
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
            DIV2 = 0,
            DIV4,
            DIV6,
            DIV8
        };
        enum class PCLK2_Prescaler : uint8_t
        {
            DIV1 = 0b000,
            DIV2 = 0b100,
            DIV4 = 0b101,
            DIV8 = 0b110,
            DIV16 = 0b111
        };
        enum class PCLK1_Prescaler : uint8_t
        {
            DIV1 = 0b000,
            DIV2 = 0b100,
            DIV4 = 0b101,
            DIV8 = 0b110,
            DIV16 = 0b111
        };
        enum class HCLK_Prescaler : uint8_t
        {
            DIV1 = 0b0000,
            DIV2 = 0b1000,
            DIV4 = 0b1001,
            DIV8 = 0b1010,
            DIV16 = 0b1011,
            DIV64 = 0b1100,
            DIV128 = 0b1101,
            DIV256 = 0b1110,
            DIV512 = 0b1111
        };
    }

    namespace MemoryMap
    {
        namespace { using namespace Common::Tools; }

        // Clock control register
        template <uint32_t tAddress>
        struct CR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto PLLRDY() { return reg_t::template GetBitfield<RCC_CR_PLLRDY>(); } // PLL clock ready flag
            auto PLLON() { return reg_t::template GetBitfield<RCC_CR_PLLON>(); } // PLL enable
            auto CSSON() { return reg_t::template GetBitfield<RCC_CR_CSSON>(); } // Clock security system enable
            auto HSEBYP() { return reg_t::template GetBitfield<RCC_CR_HSEBYP>(); } // External high-speed clock bypass
            auto HSERDY() { return reg_t::template GetBitfield<RCC_CR_HSERDY>(); } // External high-speed clock ready flag
            auto HSEON() { return reg_t::template GetBitfield<RCC_CR_HSEON>(); } // HSE clock enable
            auto HSICAL() { return reg_t::template GetBitfield<RCC_CR_HSICAL>(); } // Internal high-speed clock calibration
            auto HSITRIM() { return reg_t::template GetBitfield<RCC_CR_HSITRIM>(); } // Internal high-speed clock trimming
            auto HSIRDY() { return reg_t::template GetBitfield<RCC_CR_HSIRDY>(); } // Internal high-speed clock ready flag
            auto HSION() { return reg_t::template GetBitfield<RCC_CR_HSION>(); } // Internal high-speed clock enable

            void Enable(SystemClockSource const input) noexcept
            {
                switch (input)
                {
                case SystemClockSource::HSI:
                    if (!HSION().Read())
                    {
                        HSION() = true;
                        while(!HSIRDY().Read());
                    }
                    break;

                case SystemClockSource::HSE:
                    if (!HSEON().Read())
                    {
                        HSEON() = true;
                        while(!HSERDY().Read());
                    }
                    break;

                case SystemClockSource::PLL:
                    if (!PLLON().Read())
                    {
                        PLLON() = true;
                        while(!PLLRDY().Read());
                    }
                    break;
                }
            }
            void Disable(SystemClockSource const input) noexcept
            {
                switch (input)
                {
                case SystemClockSource::HSI:
                    if (HSION().Read())
                    {
                        HSION() = false;
                        while(HSIRDY().Read());
                    }
                    break;

                case SystemClockSource::HSE:
                    if (HSEON().Read())
                    {
                        HSEON() = false;
                        while(HSERDY().Read());
                    }
                    break;

                case SystemClockSource::PLL:
                    if (PLLON().Read())
                    {
                        PLLON() = false;
                        while(PLLRDY().Read());
                    }
                    break;
                }
            }
        };

        // Clock configuration register
        template <uint32_t tAddress>
        struct CFGR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto MCO() { return reg_t::template GetBitfield<RCC_CFGR_MCO>(); } // Microcontroller clock output
            auto USBPRE() { return reg_t::template GetBitfield<RCC_CFGR_USBPRE>(); } // USB prescaler
            auto PLLMUL() { return reg_t::template GetBitfield<RCC_CFGR_PLLMULL>(); } // PLL multiplication factor
            auto PLLXTPRE() { return reg_t::template GetBitfield<RCC_CFGR_PLLXTPRE>(); } // HSE divider for PLL entry
            auto PLLSRC() { return reg_t::template GetBitfield<RCC_CFGR_PLLSRC>(); } // PLL entry clock source
            auto ADCPRE() { return reg_t::template GetBitfield<RCC_CFGR_ADCPRE>(); } // ADC prescaler
            auto PPRE2() { return reg_t::template GetBitfield<RCC_CFGR_PPRE2>(); } // APB high-speed prescaler (APB2)
            auto PPRE1() { return reg_t::template GetBitfield<RCC_CFGR_PPRE1>(); } // APB low-speed prescaler (APB1)
            auto HPRE() { return reg_t::template GetBitfield<RCC_CFGR_HPRE>(); } // AHB prescaler
            auto SWS() { return reg_t::template GetBitfield<RCC_CFGR_SWS>(); } // System clock switch status
            auto SW() { return reg_t::template GetBitfield<RCC_CFGR_SW>(); } // System clock switch

            template <typename... tArgs>
            void Configure(tArgs... args) noexcept
            {
                ( Set(args), ... );
            }
            OutputClockSource GetOutputClockSrc() const noexcept
            {
                return OutputClockSource{ MCO().Read() };
            }
            PLL_Multiplier GetPLL_Multiplier() const noexcept
            {
                return PLL_Multiplier{ PLLMUL().Read() };
            }
            PLL_ClockSource GetPLL_ClockSrc() const noexcept
            {
                if (PLLSRC().Read())
                {
                    if (PLLXTPRE().Read()) { return PLL_ClockSource::HSE_DIV2; }

                    else { return PLL_ClockSource::HSE; }
                } 
                else 
                {
                    return PLL_ClockSource::HSI_DIV2;
                }
            }
            ADC_Prescaler GetADC_Prescaler() const noexcept
            {
                return ADC_Prescaler{ ADCPRE().Read() };
            }
            SystemClockSource GetSystemClockSrc() const noexcept
            {
                return SystemClockSource{ SWS().Read() };
            }
            HCLK_Prescaler GetAHB_Prescaler() const noexcept
            {
                return HCLK_Prescaler{ HPRE().Read() };
            }
            PCLK2_Prescaler GetAPB2_Prescaler() const noexcept
            {
                return PCLK2_Prescaler{ PPRE2().Read() };
            }
            PCLK1_Prescaler GetAPB1_Prescaler() const noexcept
            {
                return PCLK1_Prescaler{ PPRE1().Read() };
            }
        private:
            void Set(OutputClockSource const input) noexcept
            {
                MCO() = EnumValue(input);
            }
            void Set(SystemClockSource const input) noexcept
            {
                SW() = EnumValue(input);
                while(SWS().Read() != EnumValue(input));
            }
            void Set(ADC_Prescaler const input) noexcept
            {
                ADCPRE() = EnumValue(input);
            }
            void Set(HCLK_Prescaler const input) noexcept
            {
                HPRE() = EnumValue(input);
            }
            void Set(PCLK2_Prescaler const input) noexcept
            {
                PPRE2() = EnumValue(input);
            }
            void Set(PCLK1_Prescaler const input) noexcept
            {
                PPRE1() = EnumValue(input);
            }
            void Set(PLL_ClockSource const input) noexcept
            {
                switch (input)
                {
                case PLL_ClockSource::HSI_DIV2:
                    PLLXTPRE() = false;
                    PLLSRC() = false;
                    break;

                case PLL_ClockSource::HSE:
                    PLLXTPRE() = false;
                    PLLSRC() = true;
                    break;

                case PLL_ClockSource::HSE_DIV2:
                    PLLXTPRE() = true;
                    PLLSRC() = true;
                    break;
                }
            }
            void Set(PLL_Multiplier const input) noexcept
            {
                PLLMUL() = EnumValue(input);
            }
        };

        // Clock interrupt register
        template <uint32_t tAddress>
        struct CIR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            
            auto CSSC()  { return reg_t::template GetBitfield<RCC_CIR_CSSC>(); } // Clock security system interrupt clear            
            auto PLLRDYC() { return reg_t::template GetBitfield<RCC_CIR_PLLRDYC>(); } // PLL ready interrupt clear
            auto HSERDYC() { return reg_t::template GetBitfield<RCC_CIR_HSERDYC>(); } // HSE ready interrupt clear
            auto HSIRDYC() { return reg_t::template GetBitfield<RCC_CIR_HSIRDYC>(); } // HSI ready interrupt clear
            auto LSERDYC() { return reg_t::template GetBitfield<RCC_CIR_LSERDYC>(); } // LSE ready interrupt clear
            auto LSIRDYC() { return reg_t::template GetBitfield<RCC_CIR_LSIRDYC>(); } // LSI ready interrupt clear
            auto PLLRDYIE() { return reg_t::template GetBitfield<RCC_CIR_PLLRDYIE>(); } // PLL ready interrupt enable
            auto HSERDYIE() { return reg_t::template GetBitfield<RCC_CIR_HSERDYIE>(); } // HSE ready interrupt enable   
            auto HSIRDYIE() { return reg_t::template GetBitfield<RCC_CIR_HSIRDYIE>(); } // HSI ready interrupt enable
            auto LSERDYIE() { return reg_t::template GetBitfield<RCC_CIR_LSERDYIE>(); } // LSE ready interrupt enable
            auto LSIRDYIE() { return reg_t::template GetBitfield<RCC_CIR_LSIRDYIE>(); } // LSI ready interrupt enable  
            auto CSSF() { return reg_t::template GetBitfield<RCC_CIR_CSSF>(); } // Clock security system interrupt flag 
            auto PLLRDYF() { return reg_t::template GetBitfield<RCC_CIR_PLLRDYF>(); } // PLL ready interrupt flag
            auto HSERDYF() { return reg_t::template GetBitfield<RCC_CIR_HSERDYF>(); } // HSE ready interrupt flag
            auto HSIRDYF() { return reg_t::template GetBitfield<RCC_CIR_HSIRDYF>(); } // HSI ready interrupt flag
            auto LSERDYF() { return reg_t::template GetBitfield<RCC_CIR_LSERDYF>(); } // LSE ready interrupt flag
            auto LSIRDYF() { return reg_t::template GetBitfield<RCC_CIR_LSIRDYF>(); } // LSI ready interrupt flag
        };

        // APB2 peripheral reset register
        template <uint32_t tAddress>
        struct APB2RSTR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto USART1RST() { return reg_t::template GetBitfield<RCC_APB2RSTR_USART1RST>(); } // USART1 reset            
            auto SPI1RST() { return reg_t::template GetBitfield<RCC_APB2RSTR_SPI1RST>(); } // SPI1 reset            
            auto TIM1RST() { return reg_t::template GetBitfield<RCC_APB2RSTR_TIM1RST>(); } // TIM1 timer reset            
            auto ADC2RST() { return reg_t::template GetBitfield<RCC_APB2RSTR_ADC2RST>(); } // ADC 2 interface reset            
            auto ADC1RST() { return reg_t::template GetBitfield<RCC_APB2RSTR_ADC1RST>(); } // ADC 1 interface reset           
            auto IOPERST() { return reg_t::template GetBitfield<RCC_APB2RSTR_IOPERST>(); } // IO port E reset           
            auto IOPDRST() { return reg_t::template GetBitfield<RCC_APB2RSTR_IOPDRST>(); } // IO port D reset            
            auto IOPCRST() { return reg_t::template GetBitfield<RCC_APB2RSTR_IOPCRST>(); } // IO port C reset            
            auto IOPBRST() { return reg_t::template GetBitfield<RCC_APB2RSTR_IOPBRST>(); } // IO port B reset
            auto IOPARST() { return reg_t::template GetBitfield<RCC_APB2RSTR_IOPARST>(); } // IO port A reset
            auto AFIORST() { return reg_t::template GetBitfield<RCC_APB2RSTR_AFIORST>(); } // Alternate function IO reset
        };

        // APB1 peripheral reset register
        template <uint32_t tAddress>
        struct APB1RSTR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto PWRRST() { return reg_t::template GetBitfield<RCC_APB1RSTR_PWRRST>(); } // Power interface reset
            auto BKPRST() { return reg_t::template GetBitfield<RCC_APB1RSTR_BKPRST>(); } // Backup interface reset
            auto CAN1RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_CAN1RST>(); } // CAN1 reset
            auto USBRST() { return reg_t::template GetBitfield<RCC_APB1RSTR_USBRST>(); } // USB reset
            auto I2C2RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_I2C2RST>(); } // I2C 2 reset
            auto I2C1RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_I2C1RST>(); } // I2C 1 reset
            auto USART3RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_USART3RST>(); } // USART 3 reset
            auto USART2RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_USART2RST>(); } // USART 2 reset
            auto SPI2RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_SPI2RST>(); } // SPI2 reset
            auto WWDGRST() { return reg_t::template GetBitfield<RCC_APB1RSTR_WWDGRST>(); } // Window watchdog reset
            auto TIM4RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_TIM4RST>(); } // Timer 4 reset
            auto TIM3RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_TIM3RST>(); } // Timer 3 reset
            auto TIM2RST() { return reg_t::template GetBitfield<RCC_APB1RSTR_TIM2RST>(); } // Timer 2 reset
        };

        // AHB peripheral clock enable register
        template <uint32_t tAddress>
        struct AHBENR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto CRCEN() { return reg_t::template GetBitfield<RCC_AHBENR_CRCEN>(); } // CRC clock enable
            auto FLITFEN() { return reg_t::template GetBitfield<RCC_AHBENR_FLITFEN>(); } // FLITF clock enable
            auto SRAMEN() { return reg_t::template GetBitfield<RCC_AHBENR_SRAMEN>(); } // SRAM interface clock enable
            auto DMA1EN() { return reg_t::template GetBitfield<RCC_AHBENR_DMA1EN>(); } // DMA1 clock enable
        };

        // APB 2 peripheral clock enable register
        template <uint32_t tAddress>
        struct APB2ENR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto USART1EN() { return reg_t::template GetBitfield<RCC_APB2ENR_USART1EN>(); } // USART1 clock enable
            auto SPI1EN() { return reg_t::template GetBitfield<RCC_APB2ENR_SPI1EN>(); } // SPI 1 clock enable
            auto TIM1EN() { return reg_t::template GetBitfield<RCC_APB2ENR_TIM1EN>(); } // TIM1 Timer clock enable
            auto ADC2EN() { return reg_t::template GetBitfield<RCC_APB2ENR_ADC2EN>(); } // ADC 2 interface clock enable
            auto ADC1EN() { return reg_t::template GetBitfield<RCC_APB2ENR_ADC1EN>(); } // ADC 1 interface clock enable
            auto IOPEEN() { return reg_t::template GetBitfield<RCC_APB2ENR_IOPEEN>(); } // IO port E clock enable
            auto IOPDEN() { return reg_t::template GetBitfield<RCC_APB2ENR_IOPDEN>(); } // IO port D clock enable
            auto IOPCEN() { return reg_t::template GetBitfield<RCC_APB2ENR_IOPCEN>(); } // IO port C clock enable
            auto IOPBEN() { return reg_t::template GetBitfield<RCC_APB2ENR_IOPBEN>(); } // IO port B clock enable
            auto IOPAEN() { return reg_t::template GetBitfield<RCC_APB2ENR_IOPAEN>(); } // IO port A clock enable
            auto AFIOEN() { return reg_t::template GetBitfield<RCC_APB2ENR_AFIOEN>(); } // Alternate function IO clock enable
        };

        // APB1 peripheral clock enable register
        template <uint32_t tAddress>
        struct APB1ENR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto PWREN() { return reg_t::template GetBitfield<RCC_APB1ENR_PWREN>(); } // Power interface clock enable
            auto BKPEN() { return reg_t::template GetBitfield<RCC_APB1ENR_BKPEN>(); } // Backup interface clock enable
            auto CAN1EN() { return reg_t::template GetBitfield<RCC_APB1ENR_CAN1EN>(); } // CAN1 clock enable
            auto USBEN() { return reg_t::template GetBitfield<RCC_APB1ENR_USBEN>(); } // USB clock enable
            auto I2C2EN() { return reg_t::template GetBitfield<RCC_APB1ENR_I2C2EN>(); } // I2C 2 clock enable
            auto I2C1EN() { return reg_t::template GetBitfield<RCC_APB1ENR_I2C1EN>(); } // I2C 1 clock enable
            auto USART3EN() { return reg_t::template GetBitfield<RCC_APB1ENR_USART3EN>(); } // USART 3 clock enable
            auto USART2EN() { return reg_t::template GetBitfield<RCC_APB1ENR_USART2EN>(); } // USART 2 clock enable
            auto SPI2EN() { return reg_t::template GetBitfield<RCC_APB1ENR_SPI2EN>(); } // SPI 2 clock enable
            auto WWDGEN() { return reg_t::template GetBitfield<RCC_APB1ENR_WWDGEN>(); } // Window watchdog clock enable
            auto TIM4EN() { return reg_t::template GetBitfield<RCC_APB1ENR_TIM4EN>(); } // Timer 4 clock enable
            auto TIM3EN() { return reg_t::template GetBitfield<RCC_APB1ENR_TIM3EN>(); } // Timer 3 clock enable
            auto TIM2EN() { return reg_t::template GetBitfield<RCC_APB1ENR_TIM2EN>(); } // Timer 2 clock enable
        };

        // Backup domain control register
        template <uint32_t tAddress>
        struct BDCR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto BDRST() { return reg_t::template GetBitfield<RCC_BDCR_BDRST>(); } // Backup domain software reset
            auto RTCEN() { return reg_t::template GetBitfield<RCC_BDCR_RTCEN>(); } // RTC clock enable
            auto RTCSEL() { return reg_t::template GetBitfield<RCC_BDCR_RTCSEL>(); } // RTC clock source selection
            auto LSEBYP() { return reg_t::template GetBitfield<RCC_BDCR_LSEBYP>(); } // External Low Speed oscillator bypass
            auto LSERDY() { return reg_t::template GetBitfield<RCC_BDCR_LSERDY>(); } // External Low Speed oscillator ready
            auto LSEON() { return reg_t::template GetBitfield<RCC_BDCR_LSEON>(); } // External Low Speed oscillator enable

            void ConfigureRTC(RTC_ClockSource const input) noexcept
            {
                RTCSEL() = EnumValue(input);
                RTCEN() = true;
            }
            void ResetRTC() noexcept
            {
                BDRST() = true;
            }
            void EnableLSE() noexcept
            {
                if (!LSEON().Read())
                {
                    LSEON() = true;
                    while(!LSERDY().Read());
                }
            }
            void DisableLSE() noexcept
            {
                if (LSEON().Read())
                {
                    LSEON() = false;
                    while(LSERDY().Read());
                }
            }
        };

        // Control/status register
        template <uint32_t tAddress>
        struct CSR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto LPWRRSTF() { return reg_t::template GetBitfield<RCC_CSR_LPWRRSTF>(); } // Low-power reset flag
            auto WWDGRSTF() { return reg_t::template GetBitfield<RCC_CSR_WWDGRSTF>(); } // Window watchdog reset flag
            auto IWDGRSTF() { return reg_t::template GetBitfield<RCC_CSR_IWDGRSTF>(); } // Independent watchdog reset flag
            auto SFTRSTF() { return reg_t::template GetBitfield<RCC_CSR_SFTRSTF>(); } // Software reset flag
            auto PORRSTF() { return reg_t::template GetBitfield<RCC_CSR_PORRSTF>(); } // POR/PDR reset flag
            auto PINRSTF() { return reg_t::template GetBitfield<RCC_CSR_PINRSTF>(); } // PIN reset flag
            auto RMVF() { return reg_t::template GetBitfield<RCC_CSR_RMVF>(); } // Remove reset flag
            auto LSIRDY() { return reg_t::template GetBitfield<RCC_CSR_LSIRDY>(); } // Internal low speed oscillator ready
            auto LSION() { return reg_t::template GetBitfield<RCC_CSR_LSION>(); } // Internal low speed oscillator enable

            void ClearResetFlags() noexcept
            {
                RMVF() = true;
            }
            void EnableLSI() noexcept
            {
                if (!LSION().Read())
                {
                    LSION() = true;
                    while(!LSIRDY().Read());
                }
            }
            void DisableLSI() noexcept
            {
                if (LSION().Read())
                {
                    LSION() = false;
                    while(LSIRDY().Read());
                }
            }
        };

        //CR() -> CR<RCC_BASE + offsetof(RCC_TypeDef, CR)>;
        //CFGR() -> CFGR<RCC_BASE + offsetof(RCC_TypeDef, CFGR)>;
        //CIR() -> CIR<RCC_BASE + offsetof(RCC_TypeDef, CIR)>;
        //APB2RSTR() -> APB2RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR)>;
        //APB1RSTR() -> APB1RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR)>;
        //AHBENR() -> AHBENR<RCC_BASE + offsetof(RCC_TypeDef, AHBENR)>;
        //APB2ENR() -> APB2ENR<RCC_BASE + offsetof(RCC_TypeDef, APB2ENR)>;
        //APB1ENR() -> APB1ENR<RCC_BASE + offsetof(RCC_TypeDef, APB1ENR)>;
        //BDCR() -> BDCR<RCC_BASE + offsetof(RCC_TypeDef, BDCR)>;
        //CSR() -> CSR<RCC_BASE + offsetof(RCC_TypeDef, CSR)>;
    }

    struct Registers
    {
        using CR = MemoryMap::CR<RCC_BASE + offsetof(RCC_TypeDef, CR)>;
        using CFGR = MemoryMap::CFGR<RCC_BASE + offsetof(RCC_TypeDef, CFGR)>;
        using CIR = MemoryMap::CIR<RCC_BASE + offsetof(RCC_TypeDef, CIR)>;
        using APB2RSTR = MemoryMap::APB2RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB2RSTR)>;
        using APB1RSTR = MemoryMap::APB1RSTR<RCC_BASE + offsetof(RCC_TypeDef, APB1RSTR)>;
        using AHBENR = MemoryMap::AHBENR<RCC_BASE + offsetof(RCC_TypeDef, AHBENR)>;
        using APB2ENR = MemoryMap::APB2ENR<RCC_BASE + offsetof(RCC_TypeDef, APB2ENR)>;
        using APB1ENR = MemoryMap::APB1ENR<RCC_BASE + offsetof(RCC_TypeDef, APB1ENR)>;
        using BDCR = MemoryMap::BDCR<RCC_BASE + offsetof(RCC_TypeDef, BDCR)>;
        using CSR = MemoryMap::CSR<RCC_BASE + offsetof(RCC_TypeDef, CSR)>;
    };
}