#pragma once

#include "macros.h"
#include "tools.hpp"

#include "gpio_registers.hpp"

namespace Peripherals::IO 
{
    using namespace Settings;

    enum class State : bool
    {
        Low = false,
        High = true
    };

    template <Port PORT>
    struct PortClockKernal
    {
        
        static void Construct() noexcept
        {
            
        }
    };

    template <Port PORT, uint8_t PIN>
    class Pin
    {
        static_assert((PIN >= 0) && (PIN <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");
    public:
        template <typename... Args>
        ALWAYS_INLINE Pin(Args... args) noexcept
        {
            RCC->APB2ENR |= clk_msk;
            Configure(args ...);
        }
        ~Pin() noexcept
        {
            RCC->APB2RSTR |= clk_msk;
            RCC->APB2RSTR &= ~clk_msk;
        }
        template <typename T>
        ALWAYS_INLINE Pin& operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE Pin& operator = (bool input) noexcept
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
        using REGS = RegisterMap::Registers<PORT, PIN>;
        using CRx = typename REGS::CRx_t;
        using IDR = typename REGS::IDR_t;
        using ODR = typename REGS::ODR_t;
        using BSRR = typename REGS::BSRR_t;
        using BRR = typename REGS::BRR_t;
        using LCKR = typename REGS::LCKR_t;

        constexpr static uint32_t clk_msk = (1u << (Common::Tools::EnumValue(PORT) + 2u));

        ALWAYS_INLINE static void Set(InputMode input) noexcept
        {
            CRx{}.ConfigureInput(input);
        }
        ALWAYS_INLINE static void Set(OutputMode input) noexcept
        {
            CRx{}.ConfigureOutput(input);
        }
        ALWAYS_INLINE static void Set(Alternate input) noexcept
        {
            CRx{}.ConfigureAlternate(input);
        }
        ALWAYS_INLINE static void Set(OutputSpeed input) noexcept
        {
            CRx{}.MODE() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(PullResistor input) noexcept
        {
            ODR{}.OD() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(bool input) noexcept
        {
            BSRR{} = input;
        }
        ALWAYS_INLINE static void Set(State input) noexcept
        {
            Set(input == State::High);
        }
    };
}