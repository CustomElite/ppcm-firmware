#pragma once

#include "macros.h"

#include "rcc.hpp"
#include "gpio_registers.hpp"

#include "common/run_once.hpp"

namespace MCU::IO 
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

    namespace {
        template <Port tPort>
        constexpr auto GetClockID() noexcept
        {
            if constexpr (tPort == Port::A) { return CLK::ClockID::APB2_GPIOA; }
            if constexpr (tPort == Port::B) { return CLK::ClockID::APB2_GPIOB; }
            if constexpr (tPort == Port::C) { return CLK::ClockID::APB2_GPIOC; }
            if constexpr (tPort == Port::D) { return CLK::ClockID::APB2_GPIOD; }
            if constexpr (tPort == Port::E) { return CLK::ClockID::APB2_GPIOE; }
        }
    }

    template <Port tPort, size_t tPin>
    class Module
    {
        static_assert((tPin >= 0) && (tPin <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");

    public:
        template <typename... Args>
        ALWAYS_INLINE 
        Module(Args... args) noexcept
        {
            Configure(args ...);
        }
        template <typename T>
        ALWAYS_INLINE 
        Module & operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE 
        Module & operator = (bool const input) noexcept
        {
            Set((State)input);
            return *this;
        }
        ALWAYS_INLINE 
        static void Write(bool const input) noexcept
        {
            Set((State)input);
        }
        ALWAYS_INLINE 
        static void Write(State const input) noexcept
        {
            Set(input);
        }
        ALWAYS_INLINE 
        static void Toggle() noexcept
        {
            
        }
        template <typename... tArgs>
        ALWAYS_INLINE 
        static void Configure(tArgs... args) noexcept
        {
            ( Set(args), ... );
        }

    private:
        using regs_t = Registers<Common::Tools::EnumValue(tPort), tPin>;
        using CRx = typename regs_t::CRx;
        using ODR = typename regs_t::ODR;
        using BSRR = typename regs_t::BSRR;

        using clk_t = CLK::Kernal<GetClockID<tPort>()>;

        ALWAYS_INLINE 
        static void Set(Input input) noexcept
        {
            CRx{}.SetMode(input);
        }
        ALWAYS_INLINE 
        static void Set(Output input) noexcept
        {
            CRx{}.SetMode(input);
        }
        ALWAYS_INLINE 
        static void Set(Alternate input) noexcept
        {
            CRx{}.SetMode(input);
        }
        ALWAYS_INLINE 
        static void Set(OutputSpeed input) noexcept
        {
            CRx{}.MODE() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(PullResistor input) noexcept
        {
            ODR{}.OD() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(bool input) noexcept
        {
            BSRR{} = input;
        }
        ALWAYS_INLINE 
        static void Set(State input) noexcept
        {
            Set(input == State::High);
        }

    private:
        clk_t const m_kernal{};
    };

    struct NoPin
    {
        NoPin(...) {}
        operator bool() const { return false; }
        void operator =(bool const) {}
    };
}