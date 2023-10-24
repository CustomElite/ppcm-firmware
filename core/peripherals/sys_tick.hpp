#pragma once

#include <etl/private/delegate_cpp11.h>
#include <stdint.h>

#include "interrupt.hpp"

namespace Peripheral 
{
    class SysTickModule
    {
    private:
        using interrupt_t = System::Interrupt<SysTickModule, System::InterruptSource::eSysTick, 1u>;
        using delegate_t = interrupt_t::delegate_t;

        inline static volatile uint64_t m_count = 0;

        interrupt_t m_interrupt;

    public:
        SysTickModule(const uint32_t frequency) noexcept
            : m_interrupt{ delegate_t::create<SysTickModule::Interrupt>() }
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