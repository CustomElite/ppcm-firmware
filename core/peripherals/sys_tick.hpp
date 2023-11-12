#pragma once

#include "interrupt.hpp"

#include <etl/private/delegate_cpp11.h>

namespace Peripherals::SYSTICK
{
    class Module
    {
    private:
        using interrupt_t = ISR::Interrupt<Module, ISR::InterruptSource::eSysTick, 1u>;

        inline static volatile uint64_t m_count = 0;

    public:
        Module(const uint32_t frequency) noexcept
        {
            SysTick->LOAD = static_cast<uint32_t>((SystemCoreClock / frequency) - 1ull);
            SysTick->VAL = 0ul;
            SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
        }
        static uint64_t Increment() noexcept
        { 
            return ++m_count; 
        }
        static uint64_t Tick() noexcept 
        { 
            return m_count; 
        }
        static void Wait(const uint32_t ticks) noexcept
        {
            const volatile uint64_t end = Tick() + ticks;
            while (Tick() < end);
        }
        static void Interrupt() noexcept
        {
            Increment();
        }
    
    private:
        interrupt_t const m_interrupt{};
    };

}