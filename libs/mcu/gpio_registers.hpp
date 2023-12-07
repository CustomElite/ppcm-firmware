#pragma once

#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "common/tools.hpp"
#include "common/register.hpp"

#include <type_traits>

namespace MCU::IO
{
    namespace
    {
        template <unsigned tPort, uint32_t tAddress>
        struct CRL : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

        protected:
            template <unsigned tPin>
            auto MODEx()
            {
                if constexpr (tPin == 7) { return reg_t::template CreateBitfield<GPIO_CRL_MODE7>(); }
                if constexpr (tPin == 6) { return reg_t::template CreateBitfield<GPIO_CRL_MODE6>(); }
                if constexpr (tPin == 5) { return reg_t::template CreateBitfield<GPIO_CRL_MODE5>(); }
                if constexpr (tPin == 4) { return reg_t::template CreateBitfield<GPIO_CRL_MODE4>(); }
                if constexpr (tPin == 3) { return reg_t::template CreateBitfield<GPIO_CRL_MODE3>(); }
                if constexpr (tPin == 2) { return reg_t::template CreateBitfield<GPIO_CRL_MODE2>(); }
                if constexpr (tPin == 1) { return reg_t::template CreateBitfield<GPIO_CRL_MODE1>(); }
                if constexpr (tPin == 0) { return reg_t::template CreateBitfield<GPIO_CRL_MODE0>(); }
            }
            template <unsigned tPin>
            auto CNFx()
            {
                if constexpr (tPin == 7) { return reg_t::template CreateBitfield<GPIO_CRL_CNF7>(); }
                if constexpr (tPin == 6) { return reg_t::template CreateBitfield<GPIO_CRL_CNF6>(); }
                if constexpr (tPin == 5) { return reg_t::template CreateBitfield<GPIO_CRL_CNF5>(); }
                if constexpr (tPin == 4) { return reg_t::template CreateBitfield<GPIO_CRL_CNF4>(); }
                if constexpr (tPin == 3) { return reg_t::template CreateBitfield<GPIO_CRL_CNF3>(); }
                if constexpr (tPin == 2) { return reg_t::template CreateBitfield<GPIO_CRL_CNF2>(); }
                if constexpr (tPin == 1) { return reg_t::template CreateBitfield<GPIO_CRL_CNF1>(); }
                if constexpr (tPin == 0) { return reg_t::template CreateBitfield<GPIO_CRL_CNF0>(); }
            }
        };

        template <unsigned tPort, uint32_t tAddress>
        struct CRH : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

        protected:
            template <unsigned tPin>
            auto MODEx()
            {
                if constexpr (tPin == 15) { return reg_t::template CreateBitfield<GPIO_CRH_MODE15>(); }
                if constexpr (tPin == 14) { return reg_t::template CreateBitfield<GPIO_CRH_MODE14>(); }
                if constexpr (tPin == 13) { return reg_t::template CreateBitfield<GPIO_CRH_MODE13>(); }
                if constexpr (tPin == 12) { return reg_t::template CreateBitfield<GPIO_CRH_MODE12>(); }
                if constexpr (tPin == 11) { return reg_t::template CreateBitfield<GPIO_CRH_MODE11>(); }
                if constexpr (tPin == 10) { return reg_t::template CreateBitfield<GPIO_CRH_MODE10>(); }
                if constexpr (tPin == 9) { return reg_t::template CreateBitfield<GPIO_CRH_MODE9>(); }
                if constexpr (tPin == 8) { return reg_t::template CreateBitfield<GPIO_CRH_MODE8>(); }
            }

            template <unsigned tPin>
            auto CNFx()
            {
                if constexpr (tPin == 15) { return reg_t::template CreateBitfield<GPIO_CRH_CNF15>(); }
                if constexpr (tPin == 14) { return reg_t::template CreateBitfield<GPIO_CRH_CNF14>(); }
                if constexpr (tPin == 13) { return reg_t::template CreateBitfield<GPIO_CRH_CNF13>(); }
                if constexpr (tPin == 12) { return reg_t::template CreateBitfield<GPIO_CRH_CNF12>(); }
                if constexpr (tPin == 11) { return reg_t::template CreateBitfield<GPIO_CRH_CNF11>(); }
                if constexpr (tPin == 10) { return reg_t::template CreateBitfield<GPIO_CRH_CNF10>(); }
                if constexpr (tPin == 9) { return reg_t::template CreateBitfield<GPIO_CRH_CNF9>(); }
                if constexpr (tPin == 8) { return reg_t::template CreateBitfield<GPIO_CRH_CNF8>(); }
            }
        };

        template <unsigned tPort, unsigned tPin, typename CR_REG>
        struct CRx_t : public CR_REG
        {
            auto MODE() { return CR_REG::template MODEx<tPin>(); }
            auto CNF() { return CR_REG::template CNFx<tPin>(); }
        };

        template <unsigned tPort, unsigned tPin, uint32_t tAddress>
        struct IDR_t : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto ID()
            {
                if constexpr (tPin == 15) { return reg_t::template CreateBitfield<GPIO_IDR_IDR15>().Read(); }
                if constexpr (tPin == 14) { return reg_t::template CreateBitfield<GPIO_IDR_IDR14>().Read(); }
                if constexpr (tPin == 13) { return reg_t::template CreateBitfield<GPIO_IDR_IDR13>().Read(); }
                if constexpr (tPin == 12) { return reg_t::template CreateBitfield<GPIO_IDR_IDR12>().Read(); }
                if constexpr (tPin == 11) { return reg_t::template CreateBitfield<GPIO_IDR_IDR11>().Read(); }
                if constexpr (tPin == 10) { return reg_t::template CreateBitfield<GPIO_IDR_IDR10>().Read(); }
                if constexpr (tPin == 9) { return reg_t::template CreateBitfield<GPIO_IDR_IDR9>().Read(); }
                if constexpr (tPin == 8) { return reg_t::template CreateBitfield<GPIO_IDR_IDR8>().Read(); }
                if constexpr (tPin == 7) { return reg_t::template CreateBitfield<GPIO_IDR_IDR7>().Read(); }
                if constexpr (tPin == 6) { return reg_t::template CreateBitfield<GPIO_IDR_IDR6>().Read(); }
                if constexpr (tPin == 5) { return reg_t::template CreateBitfield<GPIO_IDR_IDR5>().Read(); }
                if constexpr (tPin == 4) { return reg_t::template CreateBitfield<GPIO_IDR_IDR4>().Read(); }
                if constexpr (tPin == 3) { return reg_t::template CreateBitfield<GPIO_IDR_IDR3>().Read(); }
                if constexpr (tPin == 2) { return reg_t::template CreateBitfield<GPIO_IDR_IDR2>().Read(); }
                if constexpr (tPin == 1) { return reg_t::template CreateBitfield<GPIO_IDR_IDR1>().Read(); }
                if constexpr (tPin == 0) { return reg_t::template CreateBitfield<GPIO_IDR_IDR0>().Read(); }
            }
        };

        template <unsigned tPort, unsigned tPin, uint32_t tAddress>
        struct ODR_t : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto OD()
            {
                if constexpr (tPin == 15) { return reg_t::template CreateBitfield<GPIO_ODR_ODR15>(); }
                if constexpr (tPin == 14) { return reg_t::template CreateBitfield<GPIO_ODR_ODR14>(); }
                if constexpr (tPin == 13) { return reg_t::template CreateBitfield<GPIO_ODR_ODR13>(); }
                if constexpr (tPin == 12) { return reg_t::template CreateBitfield<GPIO_ODR_ODR12>(); }
                if constexpr (tPin == 11) { return reg_t::template CreateBitfield<GPIO_ODR_ODR11>(); }
                if constexpr (tPin == 10) { return reg_t::template CreateBitfield<GPIO_ODR_ODR10>(); }
                if constexpr (tPin == 9) { return reg_t::template CreateBitfield<GPIO_ODR_ODR9>(); }
                if constexpr (tPin == 8) { return reg_t::template CreateBitfield<GPIO_ODR_ODR8>(); }
                if constexpr (tPin == 7) { return reg_t::template CreateBitfield<GPIO_ODR_ODR7>(); }
                if constexpr (tPin == 6) { return reg_t::template CreateBitfield<GPIO_ODR_ODR6>(); }
                if constexpr (tPin == 5) { return reg_t::template CreateBitfield<GPIO_ODR_ODR5>(); }
                if constexpr (tPin == 4) { return reg_t::template CreateBitfield<GPIO_ODR_ODR4>(); }
                if constexpr (tPin == 3) { return reg_t::template CreateBitfield<GPIO_ODR_ODR3>(); }
                if constexpr (tPin == 2) { return reg_t::template CreateBitfield<GPIO_ODR_ODR2>(); }
                if constexpr (tPin == 1) { return reg_t::template CreateBitfield<GPIO_ODR_ODR1>(); }
                if constexpr (tPin == 0) { return reg_t::template CreateBitfield<GPIO_ODR_ODR0>(); }
            }

            ODR_t & operator = (bool const rhs) noexcept
            {
                OD() = rhs;
            }
        };

        template <unsigned tPort, unsigned tPin, uint32_t tAddress>
        struct BSRR_t : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            void Set()
            {
                if constexpr (tPin == 15) { reg_t::template CreateBitfield<GPIO_BSRR_BS15>() = true; }
                if constexpr (tPin == 14) { reg_t::template CreateBitfield<GPIO_BSRR_BS14>() = true; }
                if constexpr (tPin == 13) { reg_t::template CreateBitfield<GPIO_BSRR_BS13>() = true; }
                if constexpr (tPin == 12) { reg_t::template CreateBitfield<GPIO_BSRR_BS12>() = true; }
                if constexpr (tPin == 11) { reg_t::template CreateBitfield<GPIO_BSRR_BS11>() = true; }
                if constexpr (tPin == 10) { reg_t::template CreateBitfield<GPIO_BSRR_BS10>() = true; }
                if constexpr (tPin == 9) { reg_t::template CreateBitfield<GPIO_BSRR_BS9>() = true; }
                if constexpr (tPin == 8) { reg_t::template CreateBitfield<GPIO_BSRR_BS8>() = true; }
                if constexpr (tPin == 7) { reg_t::template CreateBitfield<GPIO_BSRR_BS7>() = true; }
                if constexpr (tPin == 6) { reg_t::template CreateBitfield<GPIO_BSRR_BS6>() = true; }
                if constexpr (tPin == 5) { reg_t::template CreateBitfield<GPIO_BSRR_BS5>() = true; }
                if constexpr (tPin == 4) { reg_t::template CreateBitfield<GPIO_BSRR_BS4>() = true; }
                if constexpr (tPin == 3) { reg_t::template CreateBitfield<GPIO_BSRR_BS3>() = true; }
                if constexpr (tPin == 2) { reg_t::template CreateBitfield<GPIO_BSRR_BS2>() = true; }
                if constexpr (tPin == 1) { reg_t::template CreateBitfield<GPIO_BSRR_BS1>() = true; }
                if constexpr (tPin == 0) { reg_t::template CreateBitfield<GPIO_BSRR_BS0>() = true; }
            }
            void Reset()
            {
                if constexpr (tPin == 15) { reg_t::template CreateBitfield<GPIO_BSRR_BR15>() = true; }
                if constexpr (tPin == 14) { reg_t::template CreateBitfield<GPIO_BSRR_BR14>() = true; }
                if constexpr (tPin == 13) { reg_t::template CreateBitfield<GPIO_BSRR_BR13>() = true; }
                if constexpr (tPin == 12) { reg_t::template CreateBitfield<GPIO_BSRR_BR12>() = true; }
                if constexpr (tPin == 11) { reg_t::template CreateBitfield<GPIO_BSRR_BR11>() = true; }
                if constexpr (tPin == 10) { reg_t::template CreateBitfield<GPIO_BSRR_BR10>() = true; }
                if constexpr (tPin == 9) { reg_t::template CreateBitfield<GPIO_BSRR_BR9>() = true; }
                if constexpr (tPin == 8) { reg_t::template CreateBitfield<GPIO_BSRR_BR8>() = true; }
                if constexpr (tPin == 7) { reg_t::template CreateBitfield<GPIO_BSRR_BR7>() = true; }
                if constexpr (tPin == 6) { reg_t::template CreateBitfield<GPIO_BSRR_BR6>() = true; }
                if constexpr (tPin == 5) { reg_t::template CreateBitfield<GPIO_BSRR_BR5>() = true; }
                if constexpr (tPin == 4) { reg_t::template CreateBitfield<GPIO_BSRR_BR4>() = true; }
                if constexpr (tPin == 3) { reg_t::template CreateBitfield<GPIO_BSRR_BR3>() = true; }
                if constexpr (tPin == 2) { reg_t::template CreateBitfield<GPIO_BSRR_BR2>() = true; }
                if constexpr (tPin == 1) { reg_t::template CreateBitfield<GPIO_BSRR_BR1>() = true; }
                if constexpr (tPin == 0) { reg_t::template CreateBitfield<GPIO_BSRR_BR0>() = true; }
            }
            BSRR_t & operator = (bool const input) noexcept
            {
                (input) ? Set() : Reset();
                return *this;
            }
        };

        template <unsigned tPort, unsigned tPin, uint32_t tAddress>
        struct BRR_t : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            void Reset()
            {
                if constexpr (tPin == 15) { reg_t::template CreateBitfield<GPIO_BRR_BR15>() = true; }
                if constexpr (tPin == 14) { reg_t::template CreateBitfield<GPIO_BRR_BR14>() = true; }
                if constexpr (tPin == 13) { reg_t::template CreateBitfield<GPIO_BRR_BR13>() = true; }
                if constexpr (tPin == 12) { reg_t::template CreateBitfield<GPIO_BRR_BR12>() = true; }
                if constexpr (tPin == 11) { reg_t::template CreateBitfield<GPIO_BRR_BR11>() = true; }
                if constexpr (tPin == 10) { reg_t::template CreateBitfield<GPIO_BRR_BR10>() = true; }
                if constexpr (tPin == 9) { reg_t::template CreateBitfield<GPIO_BRR_BR9>() = true; }
                if constexpr (tPin == 8) { reg_t::template CreateBitfield<GPIO_BRR_BR8>() = true; }
                if constexpr (tPin == 7) { reg_t::template CreateBitfield<GPIO_BRR_BR7>() = true; }
                if constexpr (tPin == 6) { reg_t::template CreateBitfield<GPIO_BRR_BR6>() = true; }
                if constexpr (tPin == 5) { reg_t::template CreateBitfield<GPIO_BRR_BR5>() = true; }
                if constexpr (tPin == 4) { reg_t::template CreateBitfield<GPIO_BRR_BR4>() = true; }
                if constexpr (tPin == 3) { reg_t::template CreateBitfield<GPIO_BRR_BR3>() = true; }
                if constexpr (tPin == 2) { reg_t::template CreateBitfield<GPIO_BRR_BR2>() = true; }
                if constexpr (tPin == 1) { reg_t::template CreateBitfield<GPIO_BRR_BR1>() = true; }
                if constexpr (tPin == 0) { reg_t::template CreateBitfield<GPIO_BRR_BR0>() = true; }
            }
        };

        template <unsigned tPort, unsigned tPin, uint32_t tAddress>
        struct LCKR_t : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto LCK()
            {
                if constexpr (tPin == 15) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK15>(); }
                if constexpr (tPin == 14) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK14>(); }
                if constexpr (tPin == 13) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK13>(); }
                if constexpr (tPin == 12) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK12>(); }
                if constexpr (tPin == 11) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK11>(); }
                if constexpr (tPin == 10) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK10>(); }
                if constexpr (tPin == 9) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK9>(); }
                if constexpr (tPin == 8) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK8>(); }
                if constexpr (tPin == 7) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK7>(); }
                if constexpr (tPin == 6) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK6>(); }
                if constexpr (tPin == 5) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK5>(); }
                if constexpr (tPin == 4) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK4>(); }
                if constexpr (tPin == 3) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK3>(); }
                if constexpr (tPin == 2) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK2>(); }
                if constexpr (tPin == 1) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK1>(); }
                if constexpr (tPin == 0) { return reg_t::template CreateBitfield<GPIO_LCKR_LCK0>(); }
            }
            auto LCKK() { return reg_t::template CreateBitfield<GPIO_LCKR_LCKK>(); }
        };
    }

    inline namespace Settings
    {
        enum class State : bool
        {
            Low = false,
            High = true
        };
        enum class Input : uint8_t
        {
            Analog = 0b00,
            Floating = 0b01,
            PuPd = 0b10
        };
        enum class Output : uint8_t
        {
            PushPull = 0b00,
            OpenDrain = 0b01
        };
        enum class Alternate : uint8_t
        {
            PushPull = 0b10,
            OpenDrain = 0b11
        };
        enum class OutputSpeed : uint8_t
        {
            _10MHz = 0b01,
            _2MHz = 0b10,
            _50MHz = 0b11
        };
        enum class PullResistor : uint8_t
        {
            PullDown = 0,
            PullUp
        };
    }

    template <unsigned tPort, unsigned tPin>
    struct IPeripheral
    {
    private:
        static constexpr uint32_t BaseAddress() noexcept
        {
            if constexpr (tPort == 0u) { return GPIOA_BASE; }
            if constexpr (tPort == 1u) { return GPIOB_BASE; }
            if constexpr (tPort == 2u) { return GPIOC_BASE; }
            if constexpr (tPort == 3u) { return GPIOD_BASE; }
            if constexpr (tPort == 4u) { return GPIOE_BASE; }
        }

    public:
        //using CRx_t = CRx<tPort, tPin, std::conditional_t<(tPin < 8U), CRL_t, CRH_t>>;
        //using IDR_t = IDR<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, IDR)>;
        //using ODR_t = ODR<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, ODR)>;
        //using BSRR_t = BSRR<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BSRR)>;
        //using BRR_t = BRR<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BRR)>;
        //using LCKR_t = LCKR<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, LCKR)>;

        struct Registers
        {
        private:
            using CRL_t = CRL<tPort, BaseAddress() + offsetof(GPIO_TypeDef, CRL)>;
            using CRH_t = CRH<tPort, BaseAddress() + offsetof(GPIO_TypeDef, CRH)>;

        public:
            //using CRx_t = CRx_t<tPort, tPin, std::conditional_t<(tPin < 8U), CRL_t, CRH_t>>;
            //using IDR_t = IDR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, IDR)>;
            //using ODR_t = ODR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, ODR)>;
            //using BSRR_t = BSRR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BSRR)>;
            //using BRR_t = BRR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BRR)>;
            //using LCKR_t = LCKR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, LCKR)>;

            static CRx_t<tPort, tPin, std::conditional_t<(tPin < 8U), CRL_t, CRH_t>> CRx() noexcept { return {}; }
            static IDR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, IDR)> IDR() noexcept { return {}; }
            static ODR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, ODR)> ODR() noexcept { return {}; }
            static BSRR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BSRR)> BSRR() noexcept { return {}; }
            static BRR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, BRR)> BRR() noexcept { return {}; }
            static LCKR_t<tPort, tPin, BaseAddress() + offsetof(GPIO_TypeDef, LCKR)> LCKR() noexcept { return {}; }
        };

        ALWAYS_INLINE 
        static void Set(Input const input) noexcept
        {
            Registers::CRx().MODE() = false;
            Registers::CRx().CNF() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(Output const input) noexcept
        {
            Registers::CRx().MODE() = true;
            Registers::CRx().CNF() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(Alternate const input) noexcept
        {
            Registers::CRx().MODE() = true;
            Registers::CRx().CNF() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(OutputSpeed const input) noexcept
        {
            Registers::CRx().MODE() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(PullResistor const input) noexcept
        {
            Registers::ODR().OD() = Common::Tools::EnumValue(input);
        }
        ALWAYS_INLINE 
        static void Set(bool input) noexcept
        {
            Registers::BSRR() = input;
        }
        ALWAYS_INLINE 
        static void Set(State input) noexcept
        {
            Registers::BSRR() = Common::Tools::EnumValue(input);
        }
        static bool IsLocked() noexcept
        {
            return Registers::LCKR().LCKK();
        }
        static bool Lock() noexcept
        {
            if (IsLocked()) { return false; }

            // Lock key write sequence
            Registers::LCKR().LCKK() = 1u;
            Registers::LCKR().LCKK() = 0u;
            Registers::LCKR().LCKK() = 1u;

            while (Registers::LCKR().LCKK());

            return (Registers::LCKR().LCKK()) ? true : false;
        }
    };
}