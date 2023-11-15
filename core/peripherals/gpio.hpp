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
    class PowerKernal
    {
    private:
        static constexpr auto GetClockModule() noexcept
        {
            if constexpr (P == Port::A) { return CLK::Module::APB2_GPIOA; }
            if constexpr (P == Port::B) { return CLK::Module::APB2_GPIOB; }
            if constexpr (P == Port::C) { return CLK::Module::APB2_GPIOC; }
            if constexpr (P == Port::D) { return CLK::Module::APB2_GPIOD; }
            if constexpr (P == Port::E) { return CLK::Module::APB2_GPIOE; }
        }

        using clk_t = CLK::Control<GetClockModule()>;

    public:
        static void Construct() noexcept
        {
            clk_t::Power(CLK::State::On);
        }
        static void Destruct() noexcept
        {
            if (!clk_t::Reset()) { clk_t::Power(CLK::State::Off); }
        }
    };

    template <Port PORT, size_t PIN>
    class Interface
    {
        static_assert((PIN >= 0) && (PIN <= 15u), "Pin number does not exist. Only pins 0-15 are valid.");

    public:
        template <typename... Args>
        ALWAYS_INLINE Interface(Args... args) noexcept
        {
            Configure(args ...);
        }
        template <typename T>
        ALWAYS_INLINE Interface & operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE Interface & operator = (bool input) noexcept
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
        using REGS = MemoryMap::Registers<Tools::EnumValue(PORT), PIN>;
        using CRx = typename REGS::CRx_t;
        using IDR = typename REGS::IDR_t;
        using ODR = typename REGS::ODR_t;
        using BSRR = typename REGS::BSRR_t;
        using BRR = typename REGS::BRR_t;
        using LCKR = typename REGS::LCKR_t;

        Common::RunOnce<PowerKernal<PORT>> m_kernal{};

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