#pragma once

#include "register.hpp"
#include "tools.hpp"

#include "mcu_config.hpp"

namespace Peripherals::IO
{
    using namespace Common;

    namespace Settings
    {
        enum class InputMode : uint8_t
        {
            Analog = 0b00,
            Floating = 0b01,
            PuPd = 0b10
        };
        enum class OutputMode : uint8_t
        {
            PushPull = 0b00,
            OpenDrain = 0b01
        };
        enum class OutputSpeed : uint8_t
        {
            _10MHz = 0b01,
            _2MHz = 0b10,
            _50MHz = 0b11
        };
        enum class Alternate : uint8_t
        {
            PushPull = 0b10,
            OpenDrain = 0b11
        };
        enum class PullResistor : uint8_t
        {
            PullDown = 0,
            PullUp
        };
    }

    enum class Port : uint8_t
    {
        A = 0u,
        B,
        C,
        D,
        E
    };

    constexpr static uint32_t GetBase(Port port) noexcept
    {
        switch (port)
        {
            case Port::A: return GPIOA_BASE;
            case Port::B: return GPIOB_BASE;
            case Port::C: return GPIOC_BASE;
            case Port::D: return GPIOD_BASE;
            case Port::E: return GPIOE_BASE;
        };
    }

    namespace RegisterMap
    {
        using namespace Settings;

        template <Port PORT, uint8_t PIN, uint32_t ADDR = GetBase(PORT) + offsetof(GPIO_TypeDef, CRL)>
        struct CRL : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        protected:
            auto MODE7() { return reg_t::template Bits<GPIO_CRL_MODE7>(); }
            auto CNF7() { return reg_t::template Bits<GPIO_CRL_CNF7>(); }
            auto MODE6() { return reg_t::template Bits<GPIO_CRL_MODE6>(); }
            auto CNF6() { return reg_t::template Bits<GPIO_CRL_CNF6>(); }
            auto MODE5() { return reg_t::template Bits<GPIO_CRL_MODE5>(); }
            auto CNF5() { return reg_t::template Bits<GPIO_CRL_CNF5>(); }
            auto MODE4() { return reg_t::template Bits<GPIO_CRL_MODE4>(); }
            auto CNF4() { return reg_t::template Bits<GPIO_CRL_CNF4>(); }
            auto MODE3() { return reg_t::template Bits<GPIO_CRL_MODE3>(); }
            auto CNF3() { return reg_t::template Bits<GPIO_CRL_CNF3>(); }
            auto MODE2() { return reg_t::template Bits<GPIO_CRL_MODE2>(); }
            auto CNF2() { return reg_t::template Bits<GPIO_CRL_CNF2>(); }
            auto MODE1() { return reg_t::template Bits<GPIO_CRL_MODE1>(); }
            auto CNF1() { return reg_t::template Bits<GPIO_CRL_CNF1>(); }
            auto MODE0() { return reg_t::template Bits<GPIO_CRL_MODE0>(); }
            auto CNF0() { return reg_t::template Bits<GPIO_CRL_CNF0>(); }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR = GetBase(PORT) + offsetof(GPIO_TypeDef, CRH)>
        struct CRH : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        protected:
            auto MODE15() { return reg_t::template Bits<GPIO_CRH_MODE15>(); }
            auto CNF15() { return reg_t::template Bits<GPIO_CRH_CNF15>(); }
            auto MODE14() { return reg_t::template Bits<GPIO_CRH_MODE14>(); }
            auto CNF14() { return reg_t::template Bits<GPIO_CRH_CNF14>(); }
            auto MODE13() { return reg_t::template Bits<GPIO_CRH_MODE13>(); }
            auto CNF13() { return reg_t::template Bits<GPIO_CRH_CNF13>(); }
            auto MODE12() { return reg_t::template Bits<GPIO_CRH_MODE12>(); }
            auto CNF12() { return reg_t::template Bits<GPIO_CRH_CNF12>(); }
            auto MODE11() { return reg_t::template Bits<GPIO_CRH_MODE11>(); }
            auto CNF11() { return reg_t::template Bits<GPIO_CRH_CNF11>(); }
            auto MODE10() { return reg_t::template Bits<GPIO_CRH_MODE10>(); }
            auto CNF10() { return reg_t::template Bits<GPIO_CRH_CNF10>(); }
            auto MODE9() { return reg_t::template Bits<GPIO_CRH_MODE9>(); }
            auto CNF9() { return reg_t::template Bits<GPIO_CRH_CNF9>(); }
            auto MODE8() { return reg_t::template Bits<GPIO_CRH_MODE8>(); }
            auto CNF8() { return reg_t::template Bits<GPIO_CRH_CNF8>(); }      
        };

        template <Port PORT, uint8_t PIN>
        struct CRx : private CRL<PORT, PIN>, private CRH<PORT, PIN>
        {
            using CRL_t = CRL<PORT, PIN>;
            using CRH_t = CRH<PORT, PIN>;

            auto MODE()
            {
                // CRL
                if constexpr (PIN == 7) return CRL_t::MODE7();
                if constexpr (PIN == 6) return CRL_t::MODE6();
                if constexpr (PIN == 5) return CRL_t::MODE5();
                if constexpr (PIN == 4) return CRL_t::MODE4();
                if constexpr (PIN == 3) return CRL_t::MODE3();
                if constexpr (PIN == 2) return CRL_t::MODE2();
                if constexpr (PIN == 1) return CRL_t::MODE1();
                if constexpr (PIN == 0) return CRL_t::MODE0();

                // CRH
                if constexpr (PIN == 15) return CRH_t::MODE15();
                if constexpr (PIN == 14) return CRH_t::MODE14();
                if constexpr (PIN == 13) return CRH_t::MODE13();
                if constexpr (PIN == 12) return CRH_t::MODE12();
                if constexpr (PIN == 11) return CRH_t::MODE11();
                if constexpr (PIN == 10) return CRH_t::MODE10();
                if constexpr (PIN == 9) return CRH_t::MODE9();
                if constexpr (PIN == 8) return CRH_t::MODE8();
            }
            auto CNF()
            {
                // CRL
                if constexpr (PIN == 7) return CRL_t::CNF7();
                if constexpr (PIN == 6) return CRL_t::CNF6();
                if constexpr (PIN == 5) return CRL_t::CNF5();
                if constexpr (PIN == 4) return CRL_t::CNF4();
                if constexpr (PIN == 3) return CRL_t::CNF3();
                if constexpr (PIN == 2) return CRL_t::CNF2();
                if constexpr (PIN == 1) return CRL_t::CNF1();
                if constexpr (PIN == 0) return CRL_t::CNF0();
                // CRH
                if constexpr (PIN == 15) return CRH_t::CNF15();
                if constexpr (PIN == 14) return CRH_t::CNF14();
                if constexpr (PIN == 13) return CRH_t::CNF13();
                if constexpr (PIN == 12) return CRH_t::CNF12();
                if constexpr (PIN == 11) return CRH_t::CNF11();
                if constexpr (PIN == 10) return CRH_t::CNF10();
                if constexpr (PIN == 9) return CRH_t::CNF9();
                if constexpr (PIN == 8) return CRH_t::CNF8();
            }

            void ConfigureInput(InputMode input) noexcept
            {
                MODE() = false;
                CNF() = Tools::EnumValue(input);
            }
            void ConfigureOutput(OutputMode output) noexcept
            {
                MODE() = Tools::EnumValue(OutputSpeed::_10MHz);
                CNF() = Tools::EnumValue(output);
            }
            void ConfigureAlternate(Alternate alternate) noexcept
            {
                MODE() = Tools::EnumValue(OutputSpeed::_10MHz);
                CNF() = Tools::EnumValue(alternate);
            }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR>
        struct IDR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto ID()
            {
                if constexpr (PIN == 15) return reg_t::template Bits<GPIO_IDR_IDR15>();
                if constexpr (PIN == 14) return reg_t::template Bits<GPIO_IDR_IDR14>();
                if constexpr (PIN == 13) return reg_t::template Bits<GPIO_IDR_IDR13>();
                if constexpr (PIN == 12) return reg_t::template Bits<GPIO_IDR_IDR12>();
                if constexpr (PIN == 11) return reg_t::template Bits<GPIO_IDR_IDR11>();
                if constexpr (PIN == 10) return reg_t::template Bits<GPIO_IDR_IDR10>();
                if constexpr (PIN == 9) return reg_t::template Bits<GPIO_IDR_IDR9>();
                if constexpr (PIN == 8) return reg_t::template Bits<GPIO_IDR_IDR8>();
                if constexpr (PIN == 7) return reg_t::template Bits<GPIO_IDR_IDR7>();
                if constexpr (PIN == 6) return reg_t::template Bits<GPIO_IDR_IDR6>();
                if constexpr (PIN == 5) return reg_t::template Bits<GPIO_IDR_IDR5>();
                if constexpr (PIN == 4) return reg_t::template Bits<GPIO_IDR_IDR4>();
                if constexpr (PIN == 3) return reg_t::template Bits<GPIO_IDR_IDR3>();
                if constexpr (PIN == 2) return reg_t::template Bits<GPIO_IDR_IDR2>();
                if constexpr (PIN == 1) return reg_t::template Bits<GPIO_IDR_IDR1>();
                if constexpr (PIN == 0) return reg_t::template Bits<GPIO_IDR_IDR0>();
            }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR>
        struct ODR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto OD()
            {
                if constexpr (PIN == 15) return reg_t::template Bits<GPIO_ODR_ODR15>();
                if constexpr (PIN == 14) return reg_t::template Bits<GPIO_ODR_ODR14>();
                if constexpr (PIN == 13) return reg_t::template Bits<GPIO_ODR_ODR13>();
                if constexpr (PIN == 12) return reg_t::template Bits<GPIO_ODR_ODR12>();
                if constexpr (PIN == 11) return reg_t::template Bits<GPIO_ODR_ODR11>();
                if constexpr (PIN == 10) return reg_t::template Bits<GPIO_ODR_ODR10>();
                if constexpr (PIN == 9) return reg_t::template Bits<GPIO_ODR_ODR9>();
                if constexpr (PIN == 8) return reg_t::template Bits<GPIO_ODR_ODR8>();
                if constexpr (PIN == 7) return reg_t::template Bits<GPIO_ODR_ODR7>();
                if constexpr (PIN == 6) return reg_t::template Bits<GPIO_ODR_ODR6>();
                if constexpr (PIN == 5) return reg_t::template Bits<GPIO_ODR_ODR5>();
                if constexpr (PIN == 4) return reg_t::template Bits<GPIO_ODR_ODR4>();
                if constexpr (PIN == 3) return reg_t::template Bits<GPIO_ODR_ODR3>();
                if constexpr (PIN == 2) return reg_t::template Bits<GPIO_ODR_ODR2>();
                if constexpr (PIN == 1) return reg_t::template Bits<GPIO_ODR_ODR1>();
                if constexpr (PIN == 0) return reg_t::template Bits<GPIO_ODR_ODR0>();
            }

            void SetPullResistor(PullResistor input) noexcept
            {
                OD() = Tools::EnumValue(input);
            }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR>
        struct BSRR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            void Set() noexcept
            {
                if constexpr (PIN == 15) reg_t::template Bits<GPIO_BSRR_BS15>() = true;
                if constexpr (PIN == 14) reg_t::template Bits<GPIO_BSRR_BS14>() = true;
                if constexpr (PIN == 13) reg_t::template Bits<GPIO_BSRR_BS13>() = true;
                if constexpr (PIN == 12) reg_t::template Bits<GPIO_BSRR_BS12>() = true;
                if constexpr (PIN == 11) reg_t::template Bits<GPIO_BSRR_BS11>() = true;
                if constexpr (PIN == 10) reg_t::template Bits<GPIO_BSRR_BS10>() = true;
                if constexpr (PIN == 9) reg_t::template Bits<GPIO_BSRR_BS9>() = true;
                if constexpr (PIN == 8) reg_t::template Bits<GPIO_BSRR_BS8>() = true;
                if constexpr (PIN == 7) reg_t::template Bits<GPIO_BSRR_BS7>() = true;
                if constexpr (PIN == 6) reg_t::template Bits<GPIO_BSRR_BS6>() = true;
                if constexpr (PIN == 5) reg_t::template Bits<GPIO_BSRR_BS5>() = true;
                if constexpr (PIN == 4) reg_t::template Bits<GPIO_BSRR_BS4>() = true;
                if constexpr (PIN == 3) reg_t::template Bits<GPIO_BSRR_BS3>() = true;
                if constexpr (PIN == 2) reg_t::template Bits<GPIO_BSRR_BS2>() = true;
                if constexpr (PIN == 1) reg_t::template Bits<GPIO_BSRR_BS1>() = true;
                if constexpr (PIN == 0) reg_t::template Bits<GPIO_BSRR_BS0>() = true;
            }
            void Reset() noexcept
            {
                if constexpr (PIN == 15) reg_t::template Bits<GPIO_BSRR_BR15>() = true;
                if constexpr (PIN == 14) reg_t::template Bits<GPIO_BSRR_BR14>() = true;
                if constexpr (PIN == 13) reg_t::template Bits<GPIO_BSRR_BR13>() = true;
                if constexpr (PIN == 12) reg_t::template Bits<GPIO_BSRR_BR12>() = true;
                if constexpr (PIN == 11) reg_t::template Bits<GPIO_BSRR_BR11>() = true;
                if constexpr (PIN == 10) reg_t::template Bits<GPIO_BSRR_BR10>() = true;
                if constexpr (PIN == 9) reg_t::template Bits<GPIO_BSRR_BR9>() = true;
                if constexpr (PIN == 8) reg_t::template Bits<GPIO_BSRR_BR8>() = true;
                if constexpr (PIN == 7) reg_t::template Bits<GPIO_BSRR_BR7>() = true;
                if constexpr (PIN == 6) reg_t::template Bits<GPIO_BSRR_BR6>() = true;
                if constexpr (PIN == 5) reg_t::template Bits<GPIO_BSRR_BR5>() = true;
                if constexpr (PIN == 4) reg_t::template Bits<GPIO_BSRR_BR4>() = true;
                if constexpr (PIN == 3) reg_t::template Bits<GPIO_BSRR_BR3>() = true;
                if constexpr (PIN == 2) reg_t::template Bits<GPIO_BSRR_BR2>() = true;
                if constexpr (PIN == 1) reg_t::template Bits<GPIO_BSRR_BR1>() = true;
                if constexpr (PIN == 0) reg_t::template Bits<GPIO_BSRR_BR0>() = true;
            }
            BSRR& operator = (bool input) noexcept
            {
                (input) ? Set() : Reset();
                return *this;
            }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR>
        struct BRR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            void Reset() noexcept
            {
                if constexpr (PIN == 15) reg_t::template Bits<GPIO_BRR_BR15>() = true;
                if constexpr (PIN == 14) reg_t::template Bits<GPIO_BRR_BR14>() = true;
                if constexpr (PIN == 13) reg_t::template Bits<GPIO_BRR_BR13>() = true;
                if constexpr (PIN == 12) reg_t::template Bits<GPIO_BRR_BR12>() = true;
                if constexpr (PIN == 11) reg_t::template Bits<GPIO_BRR_BR11>() = true;
                if constexpr (PIN == 10) reg_t::template Bits<GPIO_BRR_BR10>() = true;
                if constexpr (PIN == 9) reg_t::template Bits<GPIO_BRR_BR9>() = true;
                if constexpr (PIN == 8) reg_t::template Bits<GPIO_BRR_BR8>() = true;
                if constexpr (PIN == 7) reg_t::template Bits<GPIO_BRR_BR7>() = true;
                if constexpr (PIN == 6) reg_t::template Bits<GPIO_BRR_BR6>() = true;
                if constexpr (PIN == 5) reg_t::template Bits<GPIO_BRR_BR5>() = true;
                if constexpr (PIN == 4) reg_t::template Bits<GPIO_BRR_BR4>() = true;
                if constexpr (PIN == 3) reg_t::template Bits<GPIO_BRR_BR3>() = true;
                if constexpr (PIN == 2) reg_t::template Bits<GPIO_BRR_BR2>() = true;
                if constexpr (PIN == 1) reg_t::template Bits<GPIO_BRR_BR1>() = true;
                if constexpr (PIN == 0) reg_t::template Bits<GPIO_BRR_BR0>() = true;
            }
        };

        template <Port PORT, uint8_t PIN, uint32_t ADDR>
        struct LCKR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        private:
            auto LCKK() noexcept { return reg_t::template Bits<GPIO_LCKR_LCKK>(); }

        public:
            auto LCK() noexcept
            {
                if constexpr (PIN == 15) return reg_t::template Bits<GPIO_LCKR_LCK15>();
                if constexpr (PIN == 14) return reg_t::template Bits<GPIO_LCKR_LCK14>();
                if constexpr (PIN == 13) return reg_t::template Bits<GPIO_LCKR_LCK13>();
                if constexpr (PIN == 12) return reg_t::template Bits<GPIO_LCKR_LCK12>();
                if constexpr (PIN == 11) return reg_t::template Bits<GPIO_LCKR_LCK11>();
                if constexpr (PIN == 10) return reg_t::template Bits<GPIO_LCKR_LCK10>();
                if constexpr (PIN == 9) return reg_t::template Bits<GPIO_LCKR_LCK9>();
                if constexpr (PIN == 8) return reg_t::template Bits<GPIO_LCKR_LCK8>();
                if constexpr (PIN == 7) return reg_t::template Bits<GPIO_LCKR_LCK7>();
                if constexpr (PIN == 6) return reg_t::template Bits<GPIO_LCKR_LCK6>();
                if constexpr (PIN == 5) return reg_t::template Bits<GPIO_LCKR_LCK5>();
                if constexpr (PIN == 4) return reg_t::template Bits<GPIO_LCKR_LCK4>();
                if constexpr (PIN == 3) return reg_t::template Bits<GPIO_LCKR_LCK3>();
                if constexpr (PIN == 2) return reg_t::template Bits<GPIO_LCKR_LCK2>();
                if constexpr (PIN == 1) return reg_t::template Bits<GPIO_LCKR_LCK1>();
                if constexpr (PIN == 0) return reg_t::template Bits<GPIO_LCKR_LCK0>();
            }
            bool IsLocked() noexcept
            {
                return LCKK();
            }
            bool Lock() noexcept
            {
                if (IsLocked()) { return false; }

                // Lock key write sequence
                LCKK() = 1u;
                LCKK() = 0u;
                LCKK() = 1u;
                auto temp = LCKK();
                (void)temp;
                return (LCKK()) ? true : false;
            }
        };

        template <Port PORT, uint8_t PIN>
        struct Registers
        {
            using CRx_t = CRx<PORT, PIN>;
            using IDR_t = IDR<PORT, PIN, GetBase(PORT) + offsetof(GPIO_TypeDef, IDR)>;
            using ODR_t = ODR<PORT, PIN, GetBase(PORT) + offsetof(GPIO_TypeDef, ODR)>;
            using BSRR_t = BSRR<PORT, PIN, GetBase(PORT) + offsetof(GPIO_TypeDef, BSRR)>;
            using BRR_t = BRR<PORT, PIN, GetBase(PORT) + offsetof(GPIO_TypeDef, BRR)>;
            using LCKR_t = LCKR<PORT, PIN, GetBase(PORT) + offsetof(GPIO_TypeDef, LCKR)>;
        };
    }
}