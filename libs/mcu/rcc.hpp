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
        ALWAYS_INLINE static constexpr void Power(const State input = State::On) noexcept
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
        ALWAYS_INLINE static constexpr bool Reset() noexcept
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
}