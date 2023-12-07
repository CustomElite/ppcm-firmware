#pragma once

#include "rcc.hpp"
#include "gpio_registers.hpp"

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
        constexpr auto ClockID() noexcept
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
        static constexpr size_t Port = Common::Tools::EnumValue(tPort);
        static constexpr size_t Pin = tPin;

    public:
        template <typename... Args>
        Module(Args... args) noexcept
        {
            ( HAL::Set(args), ... );
        }
        template <typename T>
        Module & operator = (T input) noexcept
        {
            HAL::Set(input);
            return *this;
        }
        Module & operator = (bool const input) noexcept
        {
            HAL::Set((State)input);
            return *this;
        }
        static void Toggle() noexcept
        {
            
        }
        static bool Lock() noexcept
        {
            return HAL::Lock();
        }
        static bool IsLocked() noexcept
        {
            return HAL::IsLocked();
        }
        
    private:
        using HAL = IPeripheral<Port, Pin>;

        using CLK_t = CLK::Kernal<ClockID<tPort>()>;
    private:
        CLK_t const m_clk{};
    };

    struct NoPin
    {
        NoPin(...) {}
        operator bool() const { return false; }
        void operator =(bool const) {}
    };
}