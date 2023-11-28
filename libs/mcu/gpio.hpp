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
        Module(Args... args) noexcept
        {
            Set(args...);
        }
        template <typename T>
        Module & operator = (T input) noexcept
        {
            regs_t::Set(input);
            return *this;
        }
        Module & operator = (bool const input) noexcept
        {
            regs_t::Set((State)input);
            return *this;
        }
        static void Toggle() noexcept
        {
            
        }
        template <typename... tArgs>
        static void Set(tArgs... args) noexcept
        {
            ( regs_t::Set(args), ... );
        }
        static bool Lock() noexcept
        {
            return regs_t::Lock();
        }
        static bool IsLocked() noexcept
        {
            return regs_t::IsLocked();
        }
        
    private:
        using regs_t = Registers<Common::Tools::EnumValue(tPort), tPin>;
        using CRx = typename regs_t::CRx;
        using IDR = typename regs_t::IDR;
        using ODR = typename regs_t::ODR;
        using BSRR = typename regs_t::BSRR;
        using LCKR = typename regs_t::LCKR;

        using clk_t = CLK::Kernal<GetClockID<tPort>()>;
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