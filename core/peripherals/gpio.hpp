#pragma once

#include "gpio.hpp"
#include "macros.h"
#include "tools.hpp"

#include "gpio_registers.hpp"

namespace Peripheral::GPIO 
{
    enum class Port : uint8_t
    {
        A = 0u,
        B,
        C,
        D,
        E
    };
    enum class State : bool
    {
        Low = false,
        High = true
    };
    enum class Input : uint8_t
    {
        Analog = 0u,
        Floating,
        PullResistor
    };
    enum class InputResistor : uint8_t
    {
        PullDown = 0,
        PullUp
    };
    enum class PushPull : uint8_t
    {
        _10MHz = 1u,
        _2MHz,
        _50MHz
    };
    enum class OpenDrain : uint8_t
    {
        _10MHz = 1u,
        _2MHz,
        _50MHz
    };
    enum class Alternate : uint8_t
    {
        PushPull = 2u,
        OpenDrain
    };

    template <Port port, uint8_t pin>
    class Module
    {
    public:
        static_assert((pin >= 0) && (pin <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");

        template <typename... Args>
        ALWAYS_INLINE Module(Args... args) noexcept
        {
            RCC->APB2ENR |= clk_msk;
            Configure(args ...);
        }
        ~Module() noexcept
        {
            RCC->APB2RSTR |= clk_msk;
            RCC->APB2RSTR &= ~clk_msk;
        }
        template <typename T>
        ALWAYS_INLINE Module& operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE Module& operator = (const bool input) noexcept
        {
            Set((State)input);
            return *this;
        }
        ALWAYS_INLINE static void Write(bool input) noexcept
        {
            Set((State)input);
        }
        ALWAYS_INLINE static void Write(State input) noexcept
        {
            Set(input);
        }
        ALWAYS_INLINE static void Toggle() noexcept
        {

        }
        template <typename... Args>
        ALWAYS_INLINE static void Configure(Args... args) noexcept
        {
            ( Set(args), ... );
        }

    private:
        using REGS = RegisterMap::GPIOx<General::EnumValue(port), pin>;
        using CRx = typename REGS::CRx_t;
        using IDR = typename REGS::IDR_t;
        using ODR = typename REGS::ODR_t;
        using BSRR = typename REGS::BSRR_t;
        using BRR = typename REGS::BRR_t;
        using LCKR = typename REGS::LCKR_t;

        constexpr static uint32_t clk_msk = (1u << (General::EnumValue(port) + 2u));

        ALWAYS_INLINE static void Set(Input input) noexcept
        {
            CRx().MODE() = false;
            CRx().CNF() = General::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(PushPull input) noexcept
        {
            CRx().MODE() = General::EnumValue(input);
            CRx().CNF() = false;
        }
        ALWAYS_INLINE static void Set(OpenDrain input) noexcept
        {
            CRx().MODE() = General::EnumValue(input);
            CRx().CNF() = true;
        }
        ALWAYS_INLINE static void Set(Alternate input) noexcept
        {
            CRx().MODE() = true;
            CRx().CNF() = General::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(InputResistor input) noexcept
        {
            ODR().OD() = General::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(bool input) noexcept
        {
            BSRR() = input;
        }
        ALWAYS_INLINE static void Set(State input) noexcept
        {
            Set(input == State::High);
        }
    };
}