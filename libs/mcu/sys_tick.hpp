#pragma once

#include "interrupt.hpp"

#include <cstdint>

namespace MCU::SYSTICK
{
    class Module
    {
    public:
        Module(uint32_t const core_clock, uint32_t const tick_frequency = 1'000u) noexcept
        {
            SysTick->LOAD = (uint32_t)((core_clock / tick_frequency) - 1ul);
            SysTick->VAL = 0ul;
            SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
        }
        static uint64_t Increment() noexcept
        { 
            return ++s_counter; 
        }
        static uint64_t Ticks() noexcept 
        { 
            return s_counter; 
        }
        static void Wait(uint32_t const ticks) noexcept
        {
            uint64_t const volatile end = Ticks() + ticks;
            while (Ticks() < end);
        }
        static void Interrupt() noexcept
        {
            Increment();
        }
    
    private:
        using interrupt_t = ISR::Interrupt<Module, ISR::InterruptSource::eSysTick, 1u>;

        interrupt_t const m_interrupt;

        inline static uint64_t volatile s_counter = 0;
    };

}