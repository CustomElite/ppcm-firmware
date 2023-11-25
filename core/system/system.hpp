#pragma once

#include "types.hpp"
#include "constants.hpp"
#include "serial.hpp"

#include "mcu/gpio.hpp"
#include "mcu/rcc.hpp"
#include "mcu/sys_tick.hpp"

#include <cstdint>

namespace System
{
    class Core
    {
    public:
        constexpr Core() noexcept = default;

        static uint64_t Ticks() noexcept
        {
            return s_core.sysTick.Ticks();
        }
        static void Wait(uint32_t const msecs) noexcept
        {
            SystemTick_t::Wait(msecs);
        }
        static void StatusGood() noexcept
        {
            for (uint8_t i = 0; i < 2u; ++i)
            {
                s_core.statusLED = MCU::IO::State::Low;
                s_core.sysTick.Wait(0.15_sec);
                s_core.statusLED = MCU::IO::State::High;
                s_core.sysTick.Wait(0.15_sec);
            }
        }
        static void StatusBad() noexcept
        {
            for (uint8_t i = 0; i < 2u; ++i)
            {
                s_core.statusLED = MCU::IO::State::Low;
                s_core.sysTick.Wait(1_sec);
                s_core.statusLED = MCU::IO::State::High;
                s_core.sysTick.Wait(0.15_sec);
            }
        }
        static auto & Serial() noexcept
        {
            static auto serial
            {
                System::Serial<Core>
                (
                    &StatusGood,
                    &StatusBad
                )
            };
            return serial;
        }

    private:
        struct CoreModules
        {
            SystemBus_t sysBus;
            SystemTick_t sysTick;
            Pins::STATUS_LED statusLED;

            CoreModules() noexcept :
                sysBus{},
                sysTick{ SystemBus_t::CoreClockFreq(), 1_KHz },
                statusLED{ MCU::IO::Output::PushPull, MCU::IO::State::High }
            {}
        };

        inline static CoreModules s_core{};
    };

    inline Core CreateSystem() noexcept
    {
        Core sys_core;
        auto & serial{ sys_core.Serial() };
        ((void)serial);
        return sys_core;
    }
}