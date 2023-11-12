#pragma once

#include "interrupt.hpp"
#include "rcc.hpp"
#include "usart.hpp"
#include "usart_registers.hpp"

namespace Peripherals::USART 
{
    enum class Module : uint8_t
    {
        USART_1 = 1u,
        USART_2,
        USART_3
    };

    template <Module M>
    constexpr auto GetInterruptSource() noexcept
    {
        if constexpr (M == Module::USART_1) { return Peripherals::ISR::InterruptSource::eUSART1; }
        if constexpr (M == Module::USART_2) { return Peripherals::ISR::InterruptSource::eUSART2; }
        if constexpr (M == Module::USART_3) { return Peripherals::ISR::InterruptSource::eUSART3; }
    }

    template <Module M>
    class Kernal
    {
    private:
        static constexpr auto GetPeriphClock() noexcept
        {
            if constexpr (M == Module::USART_1) { return CLK::PeriphClock::APB2_USART1; }
            if constexpr (M == Module::USART_2) { return CLK::PeriphClock::APB1_USART2; }
            if constexpr (M == Module::USART_3) { return CLK::PeriphClock::APB1_USART3; }
        }

        using clk_t = CLK::ClockControl<GetPeriphClock()>;

    public:
        static void Construct() noexcept
        {
            clk_t::Power();
        }
        static void Destruct() noexcept
        {
            if (!clk_t::Reset()) { clk_t::Power(CLK::State::Off); }
        }
    };

}