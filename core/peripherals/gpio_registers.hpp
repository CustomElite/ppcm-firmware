#pragma once

#include "register.hpp"
#include "tools.hpp"

#include "stm32f1xx.h"

#include <stddef.h>
#include <stdint.h>
#include <type_traits>

namespace RegisterMap
{
    constexpr uint32_t GetPortBase(uint8_t port) noexcept
    {
        switch (port)
        {
            case 0: return GPIOA_BASE;
            case 1: return GPIOB_BASE;
            case 2: return GPIOC_BASE;
            case 3: return GPIOD_BASE;
            case 4: return GPIOE_BASE;
            default: return 0;
        };
    }

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress = GetPortBase(Port) + offsetof(GPIO_TypeDef, CRL)>
    struct CRL : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

    protected:
        auto MODE0() noexcept { return reg_t::template Bits<GPIO_CRL_MODE0_Msk>(); }
        auto CNF0() noexcept { return reg_t::template Bits<GPIO_CRL_CNF0_Msk>(); }
        auto MODE1() noexcept { return reg_t::template Bits<GPIO_CRL_MODE1_Msk>(); }
        auto CNF1() noexcept { return reg_t::template Bits<GPIO_CRL_CNF1_Msk>(); }
        auto MODE2() noexcept { return reg_t::template Bits<GPIO_CRL_MODE2_Msk>(); }
        auto CNF2() noexcept { return reg_t::template Bits<GPIO_CRL_CNF2_Msk>(); }
        auto MODE3() noexcept { return reg_t::template Bits<GPIO_CRL_MODE3_Msk>(); }
        auto CNF3() noexcept { return reg_t::template Bits<GPIO_CRL_CNF3_Msk>(); }
        auto MODE4() noexcept { return reg_t::template Bits<GPIO_CRL_MODE4_Msk>(); }
        auto CNF4() noexcept { return reg_t::template Bits<GPIO_CRL_CNF4_Msk>(); }
        auto MODE5() noexcept { return reg_t::template Bits<GPIO_CRL_MODE5_Msk>(); }
        auto CNF5() noexcept { return reg_t::template Bits<GPIO_CRL_CNF5_Msk>(); }
        auto MODE6() noexcept { return reg_t::template Bits<GPIO_CRL_MODE6_Msk>(); }
        auto CNF6() noexcept { return reg_t::template Bits<GPIO_CRL_CNF6_Msk>(); }
        auto MODE7() noexcept { return reg_t::template Bits<GPIO_CRL_MODE7_Msk>(); }
        auto CNF7() noexcept { return reg_t::template Bits<GPIO_CRL_CNF7_Msk>(); }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress = GetPortBase(Port) + offsetof(GPIO_TypeDef, CRH)>
    struct CRH : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

    protected:
        auto MODE8() noexcept { return reg_t::template Bits<GPIO_CRH_MODE8_Msk>(); }
        auto CNF8() noexcept { return reg_t::template Bits<GPIO_CRH_CNF8_Msk>(); }
        auto MODE9() noexcept { return reg_t::template Bits<GPIO_CRH_MODE9_Msk>(); }
        auto CNF9() noexcept { return reg_t::template Bits<GPIO_CRH_CNF9_Msk>(); }
        auto MODE10() noexcept { return reg_t::template Bits<GPIO_CRH_MODE10_Msk>(); }
        auto CNF10() noexcept { return reg_t::template Bits<GPIO_CRH_CNF10_Msk>(); }
        auto MODE11() noexcept { return reg_t::template Bits<GPIO_CRH_MODE11_Msk>(); }
        auto CNF11() noexcept { return reg_t::template Bits<GPIO_CRH_CNF11_Msk>(); }
        auto MODE12() noexcept { return reg_t::template Bits<GPIO_CRH_MODE12_Msk>(); }
        auto CNF12() noexcept { return reg_t::template Bits<GPIO_CRH_CNF12_Msk>(); }
        auto MODE13() noexcept { return reg_t::template Bits<GPIO_CRH_MODE13_Msk>(); }
        auto CNF13() noexcept { return reg_t::template Bits<GPIO_CRH_CNF13_Msk>(); }
        auto MODE14() noexcept { return reg_t::template Bits<GPIO_CRH_MODE14_Msk>(); }
        auto CNF14() noexcept { return reg_t::template Bits<GPIO_CRH_CNF14_Msk>(); }
        auto MODE15() noexcept { return reg_t::template Bits<GPIO_CRH_MODE15_Msk>(); }
        auto CNF15() noexcept { return reg_t::template Bits<GPIO_CRH_CNF15_Msk>(); }
    };

    template <uint8_t Port, uint8_t Pin>
    struct CRx : private CRL<Port, Pin>, private CRH<Port, Pin>
    {
        using CRL_t = CRL<Port, Pin>;
        using CRH_t = CRH<Port, Pin>;

        auto MODE() noexcept
        {
            // CRL
            if constexpr (Pin == 0) return CRL_t::MODE0();
            if constexpr (Pin == 1) return CRL_t::MODE1();
            if constexpr (Pin == 2) return CRL_t::MODE2();
            if constexpr (Pin == 3) return CRL_t::MODE3();
            if constexpr (Pin == 4) return CRL_t::MODE4();
            if constexpr (Pin == 5) return CRL_t::MODE5();
            if constexpr (Pin == 6) return CRL_t::MODE6();
            if constexpr (Pin == 7) return CRL_t::MODE7();
            // CRH
            if constexpr (Pin == 8) return CRH_t::MODE8();
            if constexpr (Pin == 9) return CRH_t::MODE9();
            if constexpr (Pin == 10) return CRH_t::MODE10();
            if constexpr (Pin == 11) return CRH_t::MODE11();
            if constexpr (Pin == 12) return CRH_t::MODE12();
            if constexpr (Pin == 13) return CRH_t::MODE13();
            if constexpr (Pin == 14) return CRH_t::MODE14();
            if constexpr (Pin == 15) return CRH_t::MODE15();
        }
        auto CNF() noexcept
        {
            // CRL
            if constexpr (Pin == 0) return CRL_t::CNF0();
            if constexpr (Pin == 1) return CRL_t::CNF1();
            if constexpr (Pin == 2) return CRL_t::CNF2();
            if constexpr (Pin == 3) return CRL_t::CNF3();
            if constexpr (Pin == 4) return CRL_t::CNF4();
            if constexpr (Pin == 5) return CRL_t::CNF5();
            if constexpr (Pin == 6) return CRL_t::CNF6();
            if constexpr (Pin == 7) return CRL_t::CNF7();
            // CRH
            if constexpr (Pin == 8) return CRH_t::CNF8();
            if constexpr (Pin == 9) return CRH_t::CNF9();
            if constexpr (Pin == 10) return CRH_t::CNF10();
            if constexpr (Pin == 11) return CRH_t::CNF10();
            if constexpr (Pin == 12) return CRH_t::CNF12();
            if constexpr (Pin == 13) return CRH_t::CNF13();
            if constexpr (Pin == 14) return CRH_t::CNF14();
            if constexpr (Pin == 15) return CRH_t::CNF15();
        }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress>
    struct IDR : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

        auto ID() noexcept
        {
            if constexpr (Pin == 0) return reg_t::template Bits<GPIO_IDR_IDR0_Msk>();
            if constexpr (Pin == 1) return reg_t::template Bits<GPIO_IDR_IDR1_Msk>();
            if constexpr (Pin == 2) return reg_t::template Bits<GPIO_IDR_IDR2_Msk>();
            if constexpr (Pin == 3) return reg_t::template Bits<GPIO_IDR_IDR3_Msk>();
            if constexpr (Pin == 4) return reg_t::template Bits<GPIO_IDR_IDR4_Msk>();
            if constexpr (Pin == 5) return reg_t::template Bits<GPIO_IDR_IDR5_Msk>();
            if constexpr (Pin == 6) return reg_t::template Bits<GPIO_IDR_IDR6_Msk>();
            if constexpr (Pin == 7) return reg_t::template Bits<GPIO_IDR_IDR7_Msk>();
            if constexpr (Pin == 8) return reg_t::template Bits<GPIO_IDR_IDR8_Msk>();
            if constexpr (Pin == 9) return reg_t::template Bits<GPIO_IDR_IDR9_Msk>();
            if constexpr (Pin == 10) return reg_t::template Bits<GPIO_IDR_IDR10_Msk>();
            if constexpr (Pin == 11) return reg_t::template Bits<GPIO_IDR_IDR11_Msk>();
            if constexpr (Pin == 12) return reg_t::template Bits<GPIO_IDR_IDR12_Msk>();
            if constexpr (Pin == 13) return reg_t::template Bits<GPIO_IDR_IDR13_Msk>();
            if constexpr (Pin == 14) return reg_t::template Bits<GPIO_IDR_IDR14_Msk>();
            if constexpr (Pin == 15) return reg_t::template Bits<GPIO_IDR_IDR15_Msk>();
        }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress>
    struct ODR : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

        auto OD() noexcept
        {
            if constexpr (Pin == 0) return reg_t::template Bits<GPIO_ODR_ODR0_Msk>();
            if constexpr (Pin == 1) return reg_t::template Bits<GPIO_ODR_ODR1_Msk>();
            if constexpr (Pin == 2) return reg_t::template Bits<GPIO_ODR_ODR2_Msk>();
            if constexpr (Pin == 3) return reg_t::template Bits<GPIO_ODR_ODR3_Msk>();
            if constexpr (Pin == 4) return reg_t::template Bits<GPIO_ODR_ODR4_Msk>();
            if constexpr (Pin == 5) return reg_t::template Bits<GPIO_ODR_ODR5_Msk>();
            if constexpr (Pin == 6) return reg_t::template Bits<GPIO_ODR_ODR6_Msk>();
            if constexpr (Pin == 7) return reg_t::template Bits<GPIO_ODR_ODR7_Msk>();
            if constexpr (Pin == 8) return reg_t::template Bits<GPIO_ODR_ODR8_Msk>();
            if constexpr (Pin == 9) return reg_t::template Bits<GPIO_ODR_ODR9_Msk>();
            if constexpr (Pin == 10) return reg_t::template Bits<GPIO_ODR_ODR10_Msk>();
            if constexpr (Pin == 11) return reg_t::template Bits<GPIO_ODR_ODR11_Msk>();
            if constexpr (Pin == 12) return reg_t::template Bits<GPIO_ODR_ODR12_Msk>();
            if constexpr (Pin == 13) return reg_t::template Bits<GPIO_ODR_ODR13_Msk>();
            if constexpr (Pin == 14) return reg_t::template Bits<GPIO_ODR_ODR14_Msk>();
            if constexpr (Pin == 15) return reg_t::template Bits<GPIO_ODR_ODR15_Msk>();
        }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress>
    struct BSRR : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

        void BS() noexcept
        {
            if constexpr (Pin == 0) reg_t::template Bits<GPIO_BSRR_BS0_Msk>() = true;
            if constexpr (Pin == 1) reg_t::template Bits<GPIO_BSRR_BS1_Msk>() = true;
            if constexpr (Pin == 2) reg_t::template Bits<GPIO_BSRR_BS2_Msk>() = true;
            if constexpr (Pin == 3) reg_t::template Bits<GPIO_BSRR_BS3_Msk>() = true;
            if constexpr (Pin == 4) reg_t::template Bits<GPIO_BSRR_BS4_Msk>() = true;
            if constexpr (Pin == 5) reg_t::template Bits<GPIO_BSRR_BS5_Msk>() = true;
            if constexpr (Pin == 6) reg_t::template Bits<GPIO_BSRR_BS6_Msk>() = true;
            if constexpr (Pin == 7) reg_t::template Bits<GPIO_BSRR_BS7_Msk>() = true;
            if constexpr (Pin == 8) reg_t::template Bits<GPIO_BSRR_BS8_Msk>() = true;
            if constexpr (Pin == 9) reg_t::template Bits<GPIO_BSRR_BS9_Msk>() = true;
            if constexpr (Pin == 10) reg_t::template Bits<GPIO_BSRR_BS10_Msk>() = true;
            if constexpr (Pin == 11) reg_t::template Bits<GPIO_BSRR_BS11_Msk>() = true;
            if constexpr (Pin == 12) reg_t::template Bits<GPIO_BSRR_BS12_Msk>() = true;
            if constexpr (Pin == 13) reg_t::template Bits<GPIO_BSRR_BS13_Msk>() = true;
            if constexpr (Pin == 14) reg_t::template Bits<GPIO_BSRR_BS14_Msk>() = true;
            if constexpr (Pin == 15) reg_t::template Bits<GPIO_BSRR_BS15_Msk>() = true;
        }
        void BR() noexcept
        {
            if constexpr (Pin == 0) reg_t::template Bits<GPIO_BSRR_BR0_Msk>() = true;
            if constexpr (Pin == 1) reg_t::template Bits<GPIO_BSRR_BR1_Msk>() = true;
            if constexpr (Pin == 2) reg_t::template Bits<GPIO_BSRR_BR2_Msk>() = true;
            if constexpr (Pin == 3) reg_t::template Bits<GPIO_BSRR_BR3_Msk>() = true;
            if constexpr (Pin == 4) reg_t::template Bits<GPIO_BSRR_BR4_Msk>() = true;
            if constexpr (Pin == 5) reg_t::template Bits<GPIO_BSRR_BR5_Msk>() = true;
            if constexpr (Pin == 6) reg_t::template Bits<GPIO_BSRR_BR6_Msk>() = true;
            if constexpr (Pin == 7) reg_t::template Bits<GPIO_BSRR_BR7_Msk>() = true;
            if constexpr (Pin == 8) reg_t::template Bits<GPIO_BSRR_BR8_Msk>() = true;
            if constexpr (Pin == 9) reg_t::template Bits<GPIO_BSRR_BR9_Msk>() = true;
            if constexpr (Pin == 10) reg_t::template Bits<GPIO_BSRR_BR10_Msk>() = true;
            if constexpr (Pin == 11) reg_t::template Bits<GPIO_BSRR_BR11_Msk>() = true;
            if constexpr (Pin == 12) reg_t::template Bits<GPIO_BSRR_BR12_Msk>() = true;
            if constexpr (Pin == 13) reg_t::template Bits<GPIO_BSRR_BR13_Msk>() = true;
            if constexpr (Pin == 14) reg_t::template Bits<GPIO_BSRR_BR14_Msk>() = true;
            if constexpr (Pin == 15) reg_t::template Bits<GPIO_BSRR_BR15_Msk>() = true;
        }
        BSRR& operator = (bool input) noexcept
        {
            (input) ? BS() : BR();
            return *this;
        }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress>
    struct BRR : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

        void BR() noexcept
        {
            if constexpr (Pin == 0) reg_t::template Bits<GPIO_BRR_BR0_Msk>() = true;
            if constexpr (Pin == 1) reg_t::template Bits<GPIO_BRR_BR1_Msk>() = true;
            if constexpr (Pin == 2) reg_t::template Bits<GPIO_BRR_BR2_Msk>() = true;
            if constexpr (Pin == 3) reg_t::template Bits<GPIO_BRR_BR3_Msk>() = true;
            if constexpr (Pin == 4) reg_t::template Bits<GPIO_BRR_BR4_Msk>() = true;
            if constexpr (Pin == 5) reg_t::template Bits<GPIO_BRR_BR5_Msk>() = true;
            if constexpr (Pin == 6) reg_t::template Bits<GPIO_BRR_BR6_Msk>() = true;
            if constexpr (Pin == 7) reg_t::template Bits<GPIO_BRR_BR7_Msk>() = true;
            if constexpr (Pin == 8) reg_t::template Bits<GPIO_BRR_BR8_Msk>() = true;
            if constexpr (Pin == 9) reg_t::template Bits<GPIO_BRR_BR9_Msk>() = true;
            if constexpr (Pin == 10) reg_t::template Bits<GPIO_BRR_BR10_Msk>() = true;
            if constexpr (Pin == 11) reg_t::template Bits<GPIO_BRR_BR11_Msk>() = true;
            if constexpr (Pin == 12) reg_t::template Bits<GPIO_BRR_BR12_Msk>() = true;
            if constexpr (Pin == 13) reg_t::template Bits<GPIO_BRR_BR13_Msk>() = true;
            if constexpr (Pin == 14) reg_t::template Bits<GPIO_BRR_BR14_Msk>() = true;
            if constexpr (Pin == 15) reg_t::template Bits<GPIO_BRR_BR15_Msk>() = true;
        }
    };

    template <uint8_t Port, uint8_t Pin, uint32_t BaseAddress>
    struct LCKR : public General::u32_reg_t<BaseAddress>
    {
        using reg_t = General::u32_reg_t<BaseAddress>;
        using reg_t::reg_t;

    private:
        auto LCKK() noexcept { return reg_t::template Bits<GPIO_LCKR_LCKK_Msk>(); }

    public:
        auto LCK() noexcept
        {
            if constexpr (Pin == 0) return reg_t::template Bits<GPIO_LCKR_LCK0_Msk>();
            if constexpr (Pin == 1) return reg_t::template Bits<GPIO_LCKR_LCK1_Msk>();
            if constexpr (Pin == 2) return reg_t::template Bits<GPIO_LCKR_LCK2_Msk>();
            if constexpr (Pin == 3) return reg_t::template Bits<GPIO_LCKR_LCK3_Msk>();
            if constexpr (Pin == 4) return reg_t::template Bits<GPIO_LCKR_LCK4_Msk>();
            if constexpr (Pin == 5) return reg_t::template Bits<GPIO_LCKR_LCK5_Msk>();
            if constexpr (Pin == 6) return reg_t::template Bits<GPIO_LCKR_LCK6_Msk>();
            if constexpr (Pin == 7) return reg_t::template Bits<GPIO_LCKR_LCK7_Msk>();
            if constexpr (Pin == 8) return reg_t::template Bits<GPIO_LCKR_LCK8_Msk>();
            if constexpr (Pin == 9) return reg_t::template Bits<GPIO_LCKR_LCK9_Msk>();
            if constexpr (Pin == 10) return reg_t::template Bits<GPIO_LCKR_LCK10_Msk>();
            if constexpr (Pin == 11) return reg_t::template Bits<GPIO_LCKR_LCK11_Msk>();
            if constexpr (Pin == 12) return reg_t::template Bits<GPIO_LCKR_LCK12_Msk>();
            if constexpr (Pin == 13) return reg_t::template Bits<GPIO_LCKR_LCK13_Msk>();
            if constexpr (Pin == 14) return reg_t::template Bits<GPIO_LCKR_LCK14_Msk>();
            if constexpr (Pin == 15) return reg_t::template Bits<GPIO_LCKR_LCK15_Msk>();
        }
        bool IsLocked() noexcept
        {
            return LCKK();
        }
        bool Lock() noexcept
        {
            if (IsLocked()) { return false; }
            
            // Lock key write sequence
            LCKK() = true;
            LCKK() = false;
            LCKK() = true;
            while(LCKK());
            return (LCKK()) ? true : false;
        }
    };

    template <uint8_t Port, uint8_t Pin>
    struct GPIOx
    {
        using CRx_t = CRx<Port, Pin>;
        using IDR_t = IDR<Port, Pin, GetPortBase(Port) + offsetof(GPIO_TypeDef, IDR)>;
        using ODR_t = ODR<Port, Pin, GetPortBase(Port) + offsetof(GPIO_TypeDef, ODR)>;
        using BSRR_t = BSRR<Port, Pin, GetPortBase(Port) + offsetof(GPIO_TypeDef, BSRR)>;
        using BRR_t = BRR<Port, Pin, GetPortBase(Port) + offsetof(GPIO_TypeDef, BRR)>;
        using LCKR_t = LCKR<Port, Pin, GetPortBase(Port) + offsetof(GPIO_TypeDef, LCKR)>;
    };
}