#pragma once

#include "interrupt.hpp"

namespace MCU::SYSTICK
{
    class Interface
    {
    private:
        using interrupt_t = ISR::Interrupt<Interface, ISR::InterruptSource::eSysTick, 1u>;

        inline static uint64_t volatile m_count = 0;

    public:
        Interface(uint32_t const frequency) noexcept
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
        static void Wait(uint32_t const ticks) noexcept
        {
            uint64_t const volatile end = Tick() + ticks;
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