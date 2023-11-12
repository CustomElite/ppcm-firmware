#pragma once

#include "macros.h"
#include "rcc.hpp"
#include "run_once.hpp"
#include "tools.hpp"

#include "gpio_registers.hpp"

namespace Peripherals::IO 
{
    using namespace Settings;

    enum class Port : uint8_t
    {
        A = 0u,
        B,
        C,
        D,
        E
    };

    enum class State : bool
    {
        Low = false,
        High = true
    };

    template <Port P>
    struct PortClockHelper{};

    template <>
    struct PortClockHelper<Port::A>
    {
        using type = CLK::ClockControl<CLK::PeriphClock::APB2_GPIOA>;
    };
    template <>
    struct PortClockHelper<Port::B>
    {
        using type = CLK::ClockControl<CLK::PeriphClock::APB2_GPIOB>;
    };
    template <>
    struct PortClockHelper<Port::C>
    {
        using type = CLK::ClockControl<CLK::PeriphClock::APB2_GPIOC>;
    };
    template <>
    struct PortClockHelper<Port::D>
    {
        using type = CLK::ClockControl<CLK::PeriphClock::APB2_GPIOD>;
    };
    template <>
    struct PortClockHelper<Port::E>
    {
        using type = CLK::ClockControl<CLK::PeriphClock::APB2_GPIOE>;
    };

    template <Port P>
    class Kernal
    {
    public:
        static void Construct() noexcept
        {
            clk_t::Power(CLK::State::On);
        }
        static void Destruct() noexcept
        {
            if (!clk_t::Reset()) { clk_t::Power(CLK::State::Off); }
        }

    private:
        static constexpr auto GetClockWidget() noexcept
        {
            if constexpr (P == Port::A) { return CLK::PeriphClock::APB2_GPIOA; }
            if constexpr (P == Port::B) { return CLK::PeriphClock::APB2_GPIOB; }
            if constexpr (P == Port::C) { return CLK::PeriphClock::APB2_GPIOC; }
            if constexpr (P == Port::D) { return CLK::PeriphClock::APB2_GPIOD; }
            if constexpr (P == Port::E) { return CLK::PeriphClock::APB2_GPIOE; }
        }

        using clk_t = CLK::ClockControl<GetClockWidget()>;
    };

    template <Port PORT, size_t PIN>
    class Module
    {
        static_assert((PIN >= 0) && (PIN <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");

    public:
        template <typename... Args>
        ALWAYS_INLINE Module(Args... args) noexcept
        {
            Configure(args ...);
        }
        template <typename T>
        ALWAYS_INLINE Module& operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE Module& operator = (bool input) noexcept
        {
            Set((State)input);
            return *this;
        }
        ALWAYS_INLINE static void Write(bool input) noexcept
        {
            Set((State)input);
        }
        ALWAYS_INLINE static void Write(State input) noexcept
        {
            Set(input);
        }
        ALWAYS_INLINE static void Toggle() noexcept
        {

        }
        template <typename... Args>
        ALWAYS_INLINE static void Configure(Args... args) noexcept
        {
            ( Set(args), ... );
        }

    private:
        using REGS = RegisterMap::Registers<Tools::EnumValue(PORT), PIN>;
        using CRx = typename REGS::CRx_t;
        using IDR = typename REGS::IDR_t;
        using ODR = typename REGS::ODR_t;
        using BSRR = typename REGS::BSRR_t;
        using BRR = typename REGS::BRR_t;
        using LCKR = typename REGS::LCKR_t;

        Common::RunOnce<Kernal<PORT>> m_clk{};
        //constexpr static uint32_t clk_msk = (1u << (Common::Tools::EnumValue(PORT) + 2u));

        ALWAYS_INLINE static void Set(Input input) noexcept
        {
            CRx{}.ConfigureMode(input);
        }
        ALWAYS_INLINE static void Set(Output input) noexcept
        {
            CRx{}.ConfigureMode(input);
        }
        ALWAYS_INLINE static void Set(Alternate input) noexcept
        {
            CRx{}.ConfigureMode(input);
        }
        ALWAYS_INLINE static void Set(OutputSpeed input) noexcept
        {
            CRx{}.MODE() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(PullResistor input) noexcept
        {
            ODR{}.OD() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE static void Set(bool input) noexcept
        {
            BSRR{} = input;
        }
        ALWAYS_INLINE static void Set(State input) noexcept
        {
            Set(input == State::High);
        }
    };
}