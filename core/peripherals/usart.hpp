#pragma once

#include "rcc.hpp"
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
    class Kernal
    {
    private:
        static constexpr auto GetClockWidget() noexcept
        {
            if constexpr (M == Module::USART_1) { return CLK::Clock::APB2_USART1; }
            if constexpr (M == Module::USART_2) { return CLK::Clock::APB1_USART2; }
            if constexpr (M == Module::USART_3) { return CLK::Clock::APB1_USART3; }
        }

        using clk_t = CLK::ClockWidget<GetClockWidget()>;

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