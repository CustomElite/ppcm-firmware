#pragma once

#include "mcu_config.hpp"

#include "common/tools.hpp"
#include "common/register.hpp"

#include <type_traits>

namespace MCU::IO
{
    using namespace Common;

    namespace Settings
    {
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

    constexpr static uint32_t GetPortBase(size_t port) noexcept
    {
        switch (port)
        {
            case 0: return GPIOA_BASE;
            case 1: return GPIOB_BASE;
            case 2: return GPIOC_BASE;
            case 3: return GPIOD_BASE;
            case 4: return GPIOE_BASE;
        };
    }

    namespace MemoryMap
    {
        using namespace Settings;

        template <uint8_t PORT, uint32_t ADDR = GetPortBase(PORT) + offsetof(GPIO_TypeDef, CRL)>
        struct CRL : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        protected:
            template <uint8_t PIN>
            auto MODEx()
            {
                if constexpr (PIN == 7) { return reg_t::template Get<GPIO_CRL_MODE7>(); }
                if constexpr (PIN == 6) { return reg_t::template Get<GPIO_CRL_MODE6>(); }
                if constexpr (PIN == 5) { return reg_t::template Get<GPIO_CRL_MODE5>(); }
                if constexpr (PIN == 4) { return reg_t::template Get<GPIO_CRL_MODE4>(); }
                if constexpr (PIN == 3) { return reg_t::template Get<GPIO_CRL_MODE3>(); }
                if constexpr (PIN == 2) { return reg_t::template Get<GPIO_CRL_MODE2>(); }
                if constexpr (PIN == 1) { return reg_t::template Get<GPIO_CRL_MODE1>(); }
                if constexpr (PIN == 0) { return reg_t::template Get<GPIO_CRL_MODE0>(); }
            }
            template <uint8_t PIN>
            auto CNFx()
            {
                if constexpr (PIN == 7) { return reg_t::template Get<GPIO_CRL_CNF7>(); }
                if constexpr (PIN == 6) { return reg_t::template Get<GPIO_CRL_CNF6>(); }
                if constexpr (PIN == 5) { return reg_t::template Get<GPIO_CRL_CNF5>(); }
                if constexpr (PIN == 4) { return reg_t::template Get<GPIO_CRL_CNF4>(); }
                if constexpr (PIN == 3) { return reg_t::template Get<GPIO_CRL_CNF3>(); }
                if constexpr (PIN == 2) { return reg_t::template Get<GPIO_CRL_CNF2>(); }
                if constexpr (PIN == 1) { return reg_t::template Get<GPIO_CRL_CNF1>(); }
                if constexpr (PIN == 0) { return reg_t::template Get<GPIO_CRL_CNF0>(); }
            }
        };

        template <uint8_t PORT, uint32_t ADDR>
        struct CRH : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        protected:
            template <uint8_t PIN>
            auto MODEx()
            {
                if constexpr (PIN == 15) { return reg_t::template Get<GPIO_CRH_MODE15>(); }
                if constexpr (PIN == 14) { return reg_t::template Get<GPIO_CRH_MODE14>(); }
                if constexpr (PIN == 13) { return reg_t::template Get<GPIO_CRH_MODE13>(); }
                if constexpr (PIN == 12) { return reg_t::template Get<GPIO_CRH_MODE12>(); }
                if constexpr (PIN == 11) { return reg_t::template Get<GPIO_CRH_MODE11>(); }
                if constexpr (PIN == 10) { return reg_t::template Get<GPIO_CRH_MODE10>(); }
                if constexpr (PIN == 9) { return reg_t::template Get<GPIO_CRH_MODE9>(); }
                if constexpr (PIN == 8) { return reg_t::template Get<GPIO_CRH_MODE8>(); }
            }

            template <uint8_t PIN>
            auto CNFx()
            {
                if constexpr (PIN == 15) { return reg_t::template Get<GPIO_CRH_CNF15>(); }
                if constexpr (PIN == 14) { return reg_t::template Get<GPIO_CRH_CNF14>(); }
                if constexpr (PIN == 13) { return reg_t::template Get<GPIO_CRH_CNF13>(); }
                if constexpr (PIN == 12) { return reg_t::template Get<GPIO_CRH_CNF12>(); }
                if constexpr (PIN == 11) { return reg_t::template Get<GPIO_CRH_CNF11>(); }
                if constexpr (PIN == 10) { return reg_t::template Get<GPIO_CRH_CNF10>(); }
                if constexpr (PIN == 9) { return reg_t::template Get<GPIO_CRH_CNF9>(); }
                if constexpr (PIN == 8) { return reg_t::template Get<GPIO_CRH_CNF8>(); }
            }
        };

        template <uint8_t PORT, uint8_t PIN, typename CR_REG>
        struct CRx : private CR_REG
        {
            auto MODE()
            {
                return CR_REG::template MODEx<PIN>();
            }
            auto CNF()
            {
                return CR_REG::template CNFx<PIN>();
            }

            void ConfigureMode(Input input) noexcept
            {
                MODE() = false;
                CNF() = Tools::EnumValue(input);
            }
            void ConfigureMode(Output input) noexcept
            {
                MODE() = true;
                CNF() = Tools::EnumValue(input);
            }
            void ConfigureMode(Alternate input) noexcept
            {
                MODE() = true;
                CNF() = Tools::EnumValue(input);
            }
        };

        template <uint8_t PORT, uint8_t PIN, uint32_t ADDR>
        struct IDR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto ID()
            {
                if constexpr (PIN == 15) { return reg_t::template Get<GPIO_IDR_IDR15>().Read(); }
                if constexpr (PIN == 14) { return reg_t::template Get<GPIO_IDR_IDR14>().Read(); }
                if constexpr (PIN == 13) { return reg_t::template Get<GPIO_IDR_IDR13>().Read(); }
                if constexpr (PIN == 12) { return reg_t::template Get<GPIO_IDR_IDR12>().Read(); }
                if constexpr (PIN == 11) { return reg_t::template Get<GPIO_IDR_IDR11>().Read(); }
                if constexpr (PIN == 10) { return reg_t::template Get<GPIO_IDR_IDR10>().Read(); }
                if constexpr (PIN == 9) { return reg_t::template Get<GPIO_IDR_IDR9>().Read(); }
                if constexpr (PIN == 8) { return reg_t::template Get<GPIO_IDR_IDR8>().Read(); }
                if constexpr (PIN == 7) { return reg_t::template Get<GPIO_IDR_IDR7>().Read(); }
                if constexpr (PIN == 6) { return reg_t::template Get<GPIO_IDR_IDR6>().Read(); }
                if constexpr (PIN == 5) { return reg_t::template Get<GPIO_IDR_IDR5>().Read(); }
                if constexpr (PIN == 4) { return reg_t::template Get<GPIO_IDR_IDR4>().Read(); }
                if constexpr (PIN == 3) { return reg_t::template Get<GPIO_IDR_IDR3>().Read(); }
                if constexpr (PIN == 2) { return reg_t::template Get<GPIO_IDR_IDR2>().Read(); }
                if constexpr (PIN == 1) { return reg_t::template Get<GPIO_IDR_IDR1>().Read(); }
                if constexpr (PIN == 0) { return reg_t::template Get<GPIO_IDR_IDR0>().Read(); }
            }
        };

        template <uint8_t PORT, uint8_t PIN, uint32_t ADDR>
        struct ODR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto OD()
            {
                if constexpr (PIN == 15) { return reg_t::template Get<GPIO_ODR_ODR15>(); }
                if constexpr (PIN == 14) { return reg_t::template Get<GPIO_ODR_ODR14>(); }
                if constexpr (PIN == 13) { return reg_t::template Get<GPIO_ODR_ODR13>(); }
                if constexpr (PIN == 12) { return reg_t::template Get<GPIO_ODR_ODR12>(); }
                if constexpr (PIN == 11) { return reg_t::template Get<GPIO_ODR_ODR11>(); }
                if constexpr (PIN == 10) { return reg_t::template Get<GPIO_ODR_ODR10>(); }
                if constexpr (PIN == 9) { return reg_t::template Get<GPIO_ODR_ODR9>(); }
                if constexpr (PIN == 8) { return reg_t::template Get<GPIO_ODR_ODR8>(); }
                if constexpr (PIN == 7) { return reg_t::template Get<GPIO_ODR_ODR7>(); }
                if constexpr (PIN == 6) { return reg_t::template Get<GPIO_ODR_ODR6>(); }
                if constexpr (PIN == 5) { return reg_t::template Get<GPIO_ODR_ODR5>(); }
                if constexpr (PIN == 4) { return reg_t::template Get<GPIO_ODR_ODR4>(); }
                if constexpr (PIN == 3) { return reg_t::template Get<GPIO_ODR_ODR3>(); }
                if constexpr (PIN == 2) { return reg_t::template Get<GPIO_ODR_ODR2>(); }
                if constexpr (PIN == 1) { return reg_t::template Get<GPIO_ODR_ODR1>(); }
                if constexpr (PIN == 0) { return reg_t::template Get<GPIO_ODR_ODR0>(); }
            }

            ODR & operator = (bool const rhs) noexcept
            {
                OD() = rhs;
            }

            void SetPullResistor(PullResistor const & input) noexcept
            {
                OD() = Tools::EnumValue(input);
            }
        };

        template <uint8_t PORT, uint8_t PIN, uint32_t ADDR>
        struct BSRR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            void Set() noexcept
            {
                if constexpr (PIN == 15) { reg_t::template Get<GPIO_BSRR_BS15>() = true; }
                if constexpr (PIN == 14) { reg_t::template Get<GPIO_BSRR_BS14>() = true; }
                if constexpr (PIN == 13) { reg_t::template Get<GPIO_BSRR_BS13>() = true; }
                if constexpr (PIN == 12) { reg_t::template Get<GPIO_BSRR_BS12>() = true; }
                if constexpr (PIN == 11) { reg_t::template Get<GPIO_BSRR_BS11>() = true; }
                if constexpr (PIN == 10) { reg_t::template Get<GPIO_BSRR_BS10>() = true; }
                if constexpr (PIN == 9) { reg_t::template Get<GPIO_BSRR_BS9>() = true; }
                if constexpr (PIN == 8) { reg_t::template Get<GPIO_BSRR_BS8>() = true; }
                if constexpr (PIN == 7) { reg_t::template Get<GPIO_BSRR_BS7>() = true; }
                if constexpr (PIN == 6) { reg_t::template Get<GPIO_BSRR_BS6>() = true; }
                if constexpr (PIN == 5) { reg_t::template Get<GPIO_BSRR_BS5>() = true; }
                if constexpr (PIN == 4) { reg_t::template Get<GPIO_BSRR_BS4>() = true; }
                if constexpr (PIN == 3) { reg_t::template Get<GPIO_BSRR_BS3>() = true; }
                if constexpr (PIN == 2) { reg_t::template Get<GPIO_BSRR_BS2>() = true; }
                if constexpr (PIN == 1) { reg_t::template Get<GPIO_BSRR_BS1>() = true; }
                if constexpr (PIN == 0) { reg_t::template Get<GPIO_BSRR_BS0>() = true; }
            }
            void Reset() noexcept
            {
                if constexpr (PIN == 15) { reg_t::template Get<GPIO_BSRR_BR15>() = true; }
                if constexpr (PIN == 14) { reg_t::template Get<GPIO_BSRR_BR14>() = true; }
                if constexpr (PIN == 13) { reg_t::template Get<GPIO_BSRR_BR13>() = true; }
                if constexpr (PIN == 12) { reg_t::template Get<GPIO_BSRR_BR12>() = true; }
                if constexpr (PIN == 11) { reg_t::template Get<GPIO_BSRR_BR11>() = true; }
                if constexpr (PIN == 10) { reg_t::template Get<GPIO_BSRR_BR10>() = true; }
                if constexpr (PIN == 9) { reg_t::template Get<GPIO_BSRR_BR9>() = true; }
                if constexpr (PIN == 8) { reg_t::template Get<GPIO_BSRR_BR8>() = true; }
                if constexpr (PIN == 7) { reg_t::template Get<GPIO_BSRR_BR7>() = true; }
                if constexpr (PIN == 6) { reg_t::template Get<GPIO_BSRR_BR6>() = true; }
                if constexpr (PIN == 5) { reg_t::template Get<GPIO_BSRR_BR5>() = true; }
                if constexpr (PIN == 4) { reg_t::template Get<GPIO_BSRR_BR4>() = true; }
                if constexpr (PIN == 3) { reg_t::template Get<GPIO_BSRR_BR3>() = true; }
                if constexpr (PIN == 2) { reg_t::template Get<GPIO_BSRR_BR2>() = true; }
                if constexpr (PIN == 1) { reg_t::template Get<GPIO_BSRR_BR1>() = true; }
                if constexpr (PIN == 0) { reg_t::template Get<GPIO_BSRR_BR0>() = true; }
            }
            BSRR& operator = (bool const input) noexcept
            {
                (input) ? Set() : Reset();
                return *this;
            }
        };

        template <uint8_t PORT, uint8_t PIN, uint32_t ADDR>
        struct BRR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            void Reset() noexcept
            {
                if constexpr (PIN == 15) { reg_t::template Get<GPIO_BRR_BR15>() = true; }
                if constexpr (PIN == 14) { reg_t::template Get<GPIO_BRR_BR14>() = true; }
                if constexpr (PIN == 13) { reg_t::template Get<GPIO_BRR_BR13>() = true; }
                if constexpr (PIN == 12) { reg_t::template Get<GPIO_BRR_BR12>() = true; }
                if constexpr (PIN == 11) { reg_t::template Get<GPIO_BRR_BR11>() = true; }
                if constexpr (PIN == 10) { reg_t::template Get<GPIO_BRR_BR10>() = true; }
                if constexpr (PIN == 9) { reg_t::template Get<GPIO_BRR_BR9>() = true; }
                if constexpr (PIN == 8) { reg_t::template Get<GPIO_BRR_BR8>() = true; }
                if constexpr (PIN == 7) { reg_t::template Get<GPIO_BRR_BR7>() = true; }
                if constexpr (PIN == 6) { reg_t::template Get<GPIO_BRR_BR6>() = true; }
                if constexpr (PIN == 5) { reg_t::template Get<GPIO_BRR_BR5>() = true; }
                if constexpr (PIN == 4) { reg_t::template Get<GPIO_BRR_BR4>() = true; }
                if constexpr (PIN == 3) { reg_t::template Get<GPIO_BRR_BR3>() = true; }
                if constexpr (PIN == 2) { reg_t::template Get<GPIO_BRR_BR2>() = true; }
                if constexpr (PIN == 1) { reg_t::template Get<GPIO_BRR_BR1>() = true; }
                if constexpr (PIN == 0) { reg_t::template Get<GPIO_BRR_BR0>() = true; }
            }
        };

        template <uint8_t PORT, uint8_t PIN, uint32_t ADDR>
        struct LCKR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

        private:
            auto LCKK() noexcept { return reg_t::template Get<GPIO_LCKR_LCKK>(); }

        public:
            auto LCK() noexcept
            {
                if constexpr (PIN == 15) { return reg_t::template Get<GPIO_LCKR_LCK15>(); }
                if constexpr (PIN == 14) { return reg_t::template Get<GPIO_LCKR_LCK14>(); }
                if constexpr (PIN == 13) { return reg_t::template Get<GPIO_LCKR_LCK13>(); }
                if constexpr (PIN == 12) { return reg_t::template Get<GPIO_LCKR_LCK12>(); }
                if constexpr (PIN == 11) { return reg_t::template Get<GPIO_LCKR_LCK11>(); }
                if constexpr (PIN == 10) { return reg_t::template Get<GPIO_LCKR_LCK10>(); }
                if constexpr (PIN == 9) { return reg_t::template Get<GPIO_LCKR_LCK9>(); }
                if constexpr (PIN == 8) { return reg_t::template Get<GPIO_LCKR_LCK8>(); }
                if constexpr (PIN == 7) { return reg_t::template Get<GPIO_LCKR_LCK7>(); }
                if constexpr (PIN == 6) { return reg_t::template Get<GPIO_LCKR_LCK6>(); }
                if constexpr (PIN == 5) { return reg_t::template Get<GPIO_LCKR_LCK5>(); }
                if constexpr (PIN == 4) { return reg_t::template Get<GPIO_LCKR_LCK4>(); }
                if constexpr (PIN == 3) { return reg_t::template Get<GPIO_LCKR_LCK3>(); }
                if constexpr (PIN == 2) { return reg_t::template Get<GPIO_LCKR_LCK2>(); }
                if constexpr (PIN == 1) { return reg_t::template Get<GPIO_LCKR_LCK1>(); }
                if constexpr (PIN == 0) { return reg_t::template Get<GPIO_LCKR_LCK0>(); }
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

        template <uint8_t PORT, uint8_t PIN>
        struct Registers
        {
        private:
            using CRL_t = CRL<PORT, GetPortBase(PORT) + offsetof(GPIO_TypeDef, CRL)>;
            using CRH_t = CRH<PORT, GetPortBase(PORT) + offsetof(GPIO_TypeDef, CRH)>;
        
        public:
            using CRx_t = CRx< PORT, PIN, std::conditional_t< (PIN < 8U), CRL_t, CRH_t > >;
            using IDR_t = IDR<PORT, PIN, GetPortBase(PORT) + offsetof(GPIO_TypeDef, IDR)>;
            using ODR_t = ODR<PORT, PIN, GetPortBase(PORT) + offsetof(GPIO_TypeDef, ODR)>;
            using BSRR_t = BSRR<PORT, PIN, GetPortBase(PORT) + offsetof(GPIO_TypeDef, BSRR)>;
            using BRR_t = BRR<PORT, PIN, GetPortBase(PORT) + offsetof(GPIO_TypeDef, BRR)>;
            using LCKR_t = LCKR<PORT, PIN, GetPortBase(PORT) + offsetof(GPIO_TypeDef, LCKR)>;
        };
    }
}