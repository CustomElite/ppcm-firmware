#pragma once

#include <stdint.h>

#include "interrupt.hpp"

namespace Peripheral 
{
    class SysTickModule
    {
    private:
        inline static volatile uint64_t m_count = 0;
        System::Interrupt<SysTickModule, System::InterruptSource::eSysTick> m_interrupt;

    public:
        SysTickModule(const uint32_t frequency) noexcept
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
    };

}