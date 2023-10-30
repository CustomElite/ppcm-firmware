#pragma once

#include <cstdint>

#include "macros.h"
#include "meta_tools.hpp"

#include "stm32f103xb.h"
#include "stm32f1xx.h"
//#include "stm32f1xx_ll_gpio.h"

namespace Peripheral::GPIO 
{
    static constexpr std::uint32_t BaseAddress = 0x040010800;
    static constexpr std::uint32_t AddrOffset  = 0x000000400;

    enum class Port : std::uint32_t
    {
        A = 0,
        B,
        C,
        D,
        E
    };
    enum class OutputState : bool
    {
        Low = false,
        High = true
    };
    enum class Mode : std::uint32_t
    {
        Analog = 0,
        Output = 0b0001,
        Floating = 0b0100,
        Input = 0b1000,
        Alternate = 0b1001
    };
    enum class OutputType : std::uint32_t
    {
        PushPull = 0,
        OpenDrain = 0b01
    };
    enum class OutputSpeed : std::uint32_t
    {
        Medium = 0b01,
        Low = 0b10,
        High = 0b11
    };
    enum class InputResistors : std::uint16_t
    {
        PullDown = 0,
        PullUp = 0b1
    };

    template <Port port, std::uint8_t pin>
    class GPIO_Module
    {
    public:
        static_assert((pin >= 0) && (pin <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");

        template <typename... Args>
        ALWAYS_INLINE GPIO_Module(Args... args) noexcept
        {
            RCC->APB2ENR |= clk_msk;
            Configure(args ...);
        }
        ~GPIO_Module() noexcept
        {
            RCC->APB2ENR &= ~clk_msk;
        }
        template <typename T>
        ALWAYS_INLINE GPIO_Module& operator=(T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE GPIO_Module& operator=(const bool input) noexcept
        {
            Set((OutputState)input);
            return *this;
        }
        ALWAYS_INLINE static void Write(bool input) noexcept
        {
            Set((OutputState)input);
        }
        ALWAYS_INLINE static void Write(OutputState input) noexcept
        {
            Set(input);
        }
        template <typename... Args>
        ALWAYS_INLINE static void Configure(Args... args) noexcept
        {
            ( GPIO_Module::Set(args), ... );
        }

    private:
        static constexpr std::uint32_t clk_msk = (1u << ((General::EnumValue(port)) + 2u));
        static constexpr std::uint32_t pin_msk = (1u << pin);
        static constexpr std::uint32_t cr_offset = (pin > 7u) ? 4u : 0;
        static constexpr std::uint32_t cr_shift = ((pin % 8u) * 4u);

        inline static volatile std::uint32_t* const PortReg = (std::uint32_t*)(BaseAddress + (AddrOffset * General::EnumValue(port)));

        ALWAYS_INLINE static constexpr GPIO_TypeDef* GPIOx() noexcept
        {
            return (GPIO_TypeDef*)(GPIOA_BASE + (AddrOffset * General::EnumValue(port)));
        }
        ALWAYS_INLINE static constexpr GPIO_TypeDef* CRx() noexcept
        {
            return (GPIOx() + cr_offset);
        }
        ALWAYS_INLINE static void Set(Mode input) noexcept
        {
            volatile std::uint32_t* const CRx = (std::uint32_t*)((std::uint32_t)(GPIOx()) + cr_offset);

            auto tmp = *CRx;
            tmp &= ~((0b1111) << cr_shift);
            tmp |= (General::EnumValue(input) << cr_shift);

            *CRx = tmp;
        }
        ALWAYS_INLINE static void Set(OutputType input) noexcept
        {
            volatile std::uint32_t* const CRx = (std::uint32_t*)((std::uint32_t)(GPIOx()) + cr_offset);

            auto tmp = *CRx;
            tmp &= ~(0b1100 << cr_shift);
            tmp |= ((General::EnumValue(input) << GPIO_CRL_CNF_Pos) << cr_shift);
            
            *CRx = tmp;
        }
        ALWAYS_INLINE static void Set(OutputSpeed input) noexcept
        {
            volatile std::uint32_t* const CRx = (std::uint32_t*)((std::uint32_t)(GPIOx()) + cr_offset);

            auto tmp = *CRx;
            tmp &= ~(0b0011 << cr_shift);
            tmp |= (General::EnumValue(input) << cr_shift);
            
            *CRx = tmp;
        }
        ALWAYS_INLINE static void Set(InputResistors input) noexcept
        {
            volatile std::uint32_t* const ODR = (std::uint32_t*)((std::uint32_t)(GPIOx()) + 12u);

            auto tmp = *ODR;
            tmp &= ~pin_msk;
            tmp |= (General::EnumValue(input) << pin);
            
            *ODR = tmp;
        }
        ALWAYS_INLINE static void Set(bool input) noexcept
        {
            volatile std::uint32_t* const BSRR = (std::uint32_t*)((std::uint32_t)(GPIOx()) + 16u);
            volatile std::uint32_t* const BRR = (std::uint32_t*)((std::uint32_t)(GPIOx()) + 20u);

            if (input) { *BSRR = pin_msk; }
            else { *BRR = pin_msk; }
        }
        ALWAYS_INLINE static void Set(OutputState input) noexcept
        {
            Set(input == OutputState::High);
        }
    };
}