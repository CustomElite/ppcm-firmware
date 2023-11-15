#pragma once

#include "gpio.hpp"

#include "serial.hpp"
#include "sys_tick.hpp"
#include "pin_defs.hpp"
#include "constants.hpp"

#include <cstdint>

namespace System
{
    using namespace Peripherals;

    class SystemCore
    {
    public:
        SystemCore() noexcept
        {}

        static uint64_t Tick() noexcept
        {
            return m_system.sysTick.Tick();
        }
        static void Wait(uint32_t const msecs) noexcept
        {
            m_system.sysTick.Wait(msecs);
        }
        static auto & Serial() noexcept
        {
            static auto serial
            {
                System::Serial<SystemCore>
                (
                    &StatusGood,
                    &StatusBad
                )
            };

            return serial;
        }
    private:
        using SystemTick_t = SYSTICK::Interface;

        struct Components
        {
            SystemBus_t sysBus;
            SystemTick_t sysTick;
            STATUS_LED statusLED;

            Components() noexcept :
                sysBus{},
                sysTick{ 1000_u32 },
                statusLED{ IO::Output::PushPull, IO::State::High }
            {}
        };

        inline static Components m_system{};

    public:
        static void StatusGood() noexcept
        {
            for (uint8_t i = 0; i < 4u; ++i)
            {
                m_system.statusLED = IO::State::Low;
                m_system.sysTick.Wait(0.15_sec);
                m_system.statusLED = IO::State::High;
                m_system.sysTick.Wait(0.15_sec);
            }
        }
        static void StatusBad() noexcept
        {
            for (uint8_t i = 0; i < 4u; ++i)
            {
                m_system.statusLED = IO::State::Low;
                m_system.sysTick.Wait(1_sec);
                m_system.statusLED = IO::State::High;
                m_system.sysTick.Wait(0.15_sec);
            }
        }
    };

    inline SystemCore CreateSystem() noexcept
    {
        SystemCore core;
        auto & serial{ core.Serial() };
        ((void)serial);
        return core;
    }
}