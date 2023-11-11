#pragma once

#include "tools.hpp"
#include "register.hpp"

#include "stm32f1xx.h"

namespace Peripheral::DMA
{
    namespace Settings
    {
        enum class Priority : uint8_t
        {
            Low = 0,
            Medium,
            High,
            VeryHigh
        };
        enum class MemorySize : uint8_t
        {
            _8bit = 0,
            _16bit,
            _32bit
        };
        enum class Direction : uint8_t
        {
            ReadPeripheral = 0,
            ReadMemory,
            MemoryToMemory
        };
    }

    static constexpr uint32_t GetChannelBase(uint8_t channel) noexcept
    {
        switch(channel)
        {
            case 1: return DMA1_Channel1_BASE;
            case 2: return DMA1_Channel2_BASE;
            case 3: return DMA1_Channel3_BASE;
            case 4: return DMA1_Channel4_BASE;
            case 5: return DMA1_Channel5_BASE;
            case 6: return DMA1_Channel6_BASE;
            case 7: return DMA1_Channel7_BASE;
        };
    }

    namespace RegisterMap
    {
        using namespace Settings;

        // Interrupt status register
        template <size_t CH, uint32_t ADDR>
        struct ISR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Transfer error flag
            auto TEIF()
            {
                if constexpr(CH == 7u) { return TEIF7(); }
                if constexpr(CH == 6u) { return TEIF6(); }
                if constexpr(CH == 5u) { return TEIF5(); }
                if constexpr(CH == 4u) { return TEIF4(); }
                if constexpr(CH == 3u) { return TEIF3(); }
                if constexpr(CH == 2u) { return TEIF2(); }
                if constexpr(CH == 1u) { return TEIF1(); }
            }

            // Half transfer flag
            auto HTIF()
            {
                if constexpr(CH == 7u) { return HTIF7(); }
                if constexpr(CH == 6u) { return HTIF6(); }
                if constexpr(CH == 5u) { return HTIF5(); }
                if constexpr(CH == 4u) { return HTIF4(); }
                if constexpr(CH == 3u) { return HTIF3(); }
                if constexpr(CH == 2u) { return HTIF2(); }
                if constexpr(CH == 1u) { return HTIF1(); }
            }

            // Transfer complete flag
            auto TCIF()
            {
                if constexpr(CH == 7u) { return TCIF7(); }
                if constexpr(CH == 6u) { return TCIF6(); }
                if constexpr(CH == 5u) { return TCIF5(); }
                if constexpr(CH == 4u) { return TCIF4(); }
                if constexpr(CH == 3u) { return TCIF3(); }
                if constexpr(CH == 2u) { return TCIF2(); }
                if constexpr(CH == 1u) { return TCIF1(); }
            }

            // Global interrupt flag
            auto GIF()
            {
                if constexpr(CH == 7u) { return GIF7(); }
                if constexpr(CH == 6u) { return GIF6(); }
                if constexpr(CH == 5u) { return GIF5(); }
                if constexpr(CH == 4u) { return GIF4(); }
                if constexpr(CH == 3u) { return GIF3(); }
                if constexpr(CH == 2u) { return GIF2(); }
                if constexpr(CH == 1u) { return GIF1(); }
            }

        private:
            auto TEIF7() { return reg_t::template Bits<DMA_ISR_TEIF7>(); }
            auto HTIF7() { return reg_t::template Bits<DMA_ISR_HTIF7>(); }
            auto TCIF7() { return reg_t::template Bits<DMA_ISR_TCIF7>(); }
            auto GIF7()  { return reg_t::template Bits<DMA_ISR_GIF7>(); }
            auto TEIF6() { return reg_t::template Bits<DMA_ISR_TEIF6>(); }
            auto HTIF6() { return reg_t::template Bits<DMA_ISR_HTIF6>(); }
            auto TCIF6() { return reg_t::template Bits<DMA_ISR_TCIF6>(); }
            auto GIF6()  { return reg_t::template Bits<DMA_ISR_GIF6>(); }
            auto TEIF5() { return reg_t::template Bits<DMA_ISR_TEIF5>(); }
            auto HTIF5() { return reg_t::template Bits<DMA_ISR_HTIF5>(); }
            auto TCIF5() { return reg_t::template Bits<DMA_ISR_TCIF5>(); }
            auto GIF5()  { return reg_t::template Bits<DMA_ISR_GIF5>(); }
            auto TEIF4() { return reg_t::template Bits<DMA_ISR_TEIF4>(); }
            auto HTIF4() { return reg_t::template Bits<DMA_ISR_HTIF4>(); }
            auto TCIF4() { return reg_t::template Bits<DMA_ISR_TCIF4>(); }
            auto GIF4()  { return reg_t::template Bits<DMA_ISR_GIF4>(); }
            auto TEIF3() { return reg_t::template Bits<DMA_ISR_TEIF3>(); }
            auto HTIF3() { return reg_t::template Bits<DMA_ISR_HTIF3>(); }
            auto TCIF3() { return reg_t::template Bits<DMA_ISR_TCIF3>(); }
            auto GIF3()  { return reg_t::template Bits<DMA_ISR_GIF3>(); }
            auto TEIF2() { return reg_t::template Bits<DMA_ISR_TEIF2>(); }
            auto HTIF2() { return reg_t::template Bits<DMA_ISR_HTIF2>(); }
            auto TCIF2() { return reg_t::template Bits<DMA_ISR_TCIF2>(); }
            auto GIF2()  { return reg_t::template Bits<DMA_ISR_GIF2>(); }
            auto TEIF1() { return reg_t::template Bits<DMA_ISR_TEIF1>(); }
            auto HTIF1() { return reg_t::template Bits<DMA_ISR_HTIF1>(); }
            auto TCIF1() { return reg_t::template Bits<DMA_ISR_TCIF1>(); }
            auto GIF1()  { return reg_t::template Bits<DMA_ISR_GIF1>(); }
        };

        // Interrupt flag clear register
        template <size_t CH, uint32_t ADDR>
        struct IFCR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Transfer error clear
            auto CTEIF()
            {
                if constexpr(CH == 7u) { return CTEIF7(); }
                if constexpr(CH == 6u) { return CTEIF6(); }
                if constexpr(CH == 5u) { return CTEIF5(); }
                if constexpr(CH == 4u) { return CTEIF4(); }
                if constexpr(CH == 3u) { return CTEIF3(); }
                if constexpr(CH == 2u) { return CTEIF2(); }
                if constexpr(CH == 1u) { return CTEIF1(); }
            }

            // Half transfer clear
            auto CHTIF()
            {
                if constexpr(CH == 7u) { return CHTIF7(); }
                if constexpr(CH == 6u) { return CHTIF6(); }
                if constexpr(CH == 5u) { return CHTIF5(); }
                if constexpr(CH == 4u) { return CHTIF4(); }
                if constexpr(CH == 3u) { return CHTIF3(); }
                if constexpr(CH == 2u) { return CHTIF2(); }
                if constexpr(CH == 1u) { return CHTIF1(); }
            }

            // Transfer complete clear
            auto CTCIF()
            {
                if constexpr(CH == 7u) { return CTCIF7(); }
                if constexpr(CH == 6u) { return CTCIF6(); }
                if constexpr(CH == 5u) { return CTCIF5(); }
                if constexpr(CH == 4u) { return CTCIF4(); }
                if constexpr(CH == 3u) { return CTCIF3(); }
                if constexpr(CH == 2u) { return CTCIF2(); }
                if constexpr(CH == 1u) { return CTCIF1(); }
            }

            // Global interrupt clear
            auto CGIF()
            {
                if constexpr(CH == 7u) { return CGIF7(); }
                if constexpr(CH == 6u) { return CGIF6(); }
                if constexpr(CH == 5u) { return CGIF5(); }
                if constexpr(CH == 4u) { return CGIF4(); }
                if constexpr(CH == 3u) { return CGIF3(); }
                if constexpr(CH == 2u) { return CGIF2(); }
                if constexpr(CH == 1u) { return CGIF1(); }
            }

        private:
            auto CTEIF7() { return reg_t::template Bits<DMA_IFCR_CTEIF7>(); }
            auto CHTIF7() { return reg_t::template Bits<DMA_IFCR_CHTIF7>(); }
            auto CTCIF7() { return reg_t::template Bits<DMA_IFCR_CTCIF7>(); }
            auto CGIF7()  { return reg_t::template Bits<DMA_IFCR_CGIF7>(); }
            auto CTEIF6() { return reg_t::template Bits<DMA_IFCR_CTEIF6>(); }
            auto CHTIF6() { return reg_t::template Bits<DMA_IFCR_CHTIF6>(); }
            auto CTCIF6() { return reg_t::template Bits<DMA_IFCR_CTCIF6>(); }
            auto CGIF6()  { return reg_t::template Bits<DMA_IFCR_CGIF6>(); }
            auto CTEIF5() { return reg_t::template Bits<DMA_IFCR_CTEIF5>(); }
            auto CHTIF5() { return reg_t::template Bits<DMA_IFCR_CHTIF5>(); }
            auto CTCIF5() { return reg_t::template Bits<DMA_IFCR_CTCIF5>(); }
            auto CGIF5()  { return reg_t::template Bits<DMA_IFCR_CGIF5>(); }
            auto CTEIF4() { return reg_t::template Bits<DMA_IFCR_CTEIF4>(); }
            auto CHTIF4() { return reg_t::template Bits<DMA_IFCR_CHTIF4>(); }
            auto CTCIF4() { return reg_t::template Bits<DMA_IFCR_CTCIF4>(); }
            auto CGIF4()  { return reg_t::template Bits<DMA_IFCR_CGIF4>(); }
            auto CTEIF3() { return reg_t::template Bits<DMA_IFCR_CTEIF3>(); }
            auto CHTIF3() { return reg_t::template Bits<DMA_IFCR_CHTIF3>(); }
            auto CTCIF3() { return reg_t::template Bits<DMA_IFCR_CTCIF3>(); }
            auto CGIF3()  { return reg_t::template Bits<DMA_IFCR_CGIF3>(); }
            auto CTEIF2() { return reg_t::template Bits<DMA_IFCR_CTEIF2>(); }
            auto CHTIF2() { return reg_t::template Bits<DMA_IFCR_CHTIF2>(); }
            auto CTCIF2() { return reg_t::template Bits<DMA_IFCR_CTCIF2>(); }
            auto CGIF2()  { return reg_t::template Bits<DMA_IFCR_CGIF2>(); }
            auto CTEIF1() { return reg_t::template Bits<DMA_IFCR_CTEIF1>(); }
            auto CHTIF1() { return reg_t::template Bits<DMA_IFCR_CHTIF1>(); }
            auto CTCIF1() { return reg_t::template Bits<DMA_IFCR_CTCIF1>(); }
            auto CGIF1()  { return reg_t::template Bits<DMA_IFCR_CGIF1>(); }
        };

        // Configuration register
        template <size_t CH, uint32_t ADDR>
        struct CCR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Memory to memory mode
            auto MEM2MEM() { return reg_t::template Bits<DMA_CCR_MEM2MEM>(); }

            // Priority level
            auto PL() { return reg_t::template Bits<DMA_CCR_PL>(); }

            // Memory size
            auto MSIZE() { return reg_t::template Bits<DMA_CCR_MSIZE>(); }

            // Peripheral size
            auto PSIZE() { return reg_t::template Bits<DMA_CCR_PSIZE>(); }

            // Memory increment mode
            auto MINC() { return reg_t::template Bits<DMA_CCR_MINC>(); }

            // Peripheral increment mode
            auto PINC() { return reg_t::template Bits<DMA_CCR_PINC>(); }

            // Circular mode
            auto CIRC() { return reg_t::template Bits<DMA_CCR_CIRC>(); }

            // Data transfer direction
            auto DIR() { return reg_t::template Bits<DMA_CCR_DIR>(); }

            // Tranfer error interrupt enable
            auto TEIE() { return reg_t::template Bits<DMA_CCR_TEIE>(); }

            // Half transfer interrupt enable
            auto HTIE() { return reg_t::template Bits<DMA_CCR_HTIE>(); }

            // Transfer complete interrupt enable
            auto TCIE() { return reg_t::template Bits<DMA_CCR_TCIE>(); }

            // Channel enable
            auto EN() { return reg_t::template Bits<DMA_CCR_EN>(); }
        };

        // Number of data register
        template <size_t CH, uint32_t ADDR>
        struct CNDTR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            static constexpr uint32_t Maximum = DMA_CNDTR_NDT + 1u;

            // Number of data to transfer
            auto NDT() { return reg_t::template Bits<DMA_CNDTR_NDT>(); }
        };

        // Peripheral address register
        template <size_t CH, uint32_t ADDR>
        struct CPAR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Peripheral address
            auto PA() { return reg_t::template Bits<DMA_CPAR_PA>(); }
        };

        // Memory address register
        template <size_t CH, uint32_t ADDR>
        struct CMAR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Memory address
            auto MA() { return reg_t::template Bits<DMA_CMAR_MA>(); }
        };

        template <size_t CH>
        struct Registers
        {
            using ISR_t = ISR<CH, DMA1_BASE + offsetof(DMA_TypeDef, ISR)>;
            using IFCR_t = IFCR<CH, DMA1_BASE + offsetof(DMA_TypeDef, IFCR)>;
            using CCR_t = CCR<CH, GetChannelBase(CH) + offsetof(DMA_Channel_TypeDef, CCR)>;
            using CNDTR_t = CNDTR<CH, GetChannelBase(CH) + offsetof(DMA_Channel_TypeDef, CNDTR)>;
            using CPAR_t = CPAR<CH, GetChannelBase(CH) + offsetof(DMA_Channel_TypeDef, CPAR)>;
            using CMAR_t = CMAR<CH, GetChannelBase(CH) + offsetof(DMA_Channel_TypeDef, CMAR)>;
        };
    }
}