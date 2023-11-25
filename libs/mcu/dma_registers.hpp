#pragma once

#include "common/tools.hpp"
#include "common/register.hpp"

#include "stm32f1xx.h"

namespace Peripherals::DMA
{
    inline namespace Settings
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

    namespace MemoryMap
    {
        // Interrupt status register
        template <std::size_t CH, uint32_t ADDR>
        struct ISR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto TEIF() // Transfer error flag
            {
                if constexpr(CH == 7u) { return TEIF7(); }
                if constexpr(CH == 6u) { return TEIF6(); }
                if constexpr(CH == 5u) { return TEIF5(); }
                if constexpr(CH == 4u) { return TEIF4(); }
                if constexpr(CH == 3u) { return TEIF3(); }
                if constexpr(CH == 2u) { return TEIF2(); }
                if constexpr(CH == 1u) { return TEIF1(); }
            }
            auto HTIF() // Half transfer flag
            {
                if constexpr(CH == 7u) { return HTIF7(); }
                if constexpr(CH == 6u) { return HTIF6(); }
                if constexpr(CH == 5u) { return HTIF5(); }
                if constexpr(CH == 4u) { return HTIF4(); }
                if constexpr(CH == 3u) { return HTIF3(); }
                if constexpr(CH == 2u) { return HTIF2(); }
                if constexpr(CH == 1u) { return HTIF1(); }
            }
            auto TCIF() // Transfer complete flag
            {
                if constexpr(CH == 7u) { return TCIF7(); }
                if constexpr(CH == 6u) { return TCIF6(); }
                if constexpr(CH == 5u) { return TCIF5(); }
                if constexpr(CH == 4u) { return TCIF4(); }
                if constexpr(CH == 3u) { return TCIF3(); }
                if constexpr(CH == 2u) { return TCIF2(); }
                if constexpr(CH == 1u) { return TCIF1(); }
            }
            auto GIF() // Global interrupt flag
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
            auto TEIF7() { return reg_t::template GetBitfield<DMA_ISR_TEIF7>(); }
            auto HTIF7() { return reg_t::template GetBitfield<DMA_ISR_HTIF7>(); }
            auto TCIF7() { return reg_t::template GetBitfield<DMA_ISR_TCIF7>(); }
            auto GIF7()  { return reg_t::template GetBitfield<DMA_ISR_GIF7>(); }
            auto TEIF6() { return reg_t::template GetBitfield<DMA_ISR_TEIF6>(); }
            auto HTIF6() { return reg_t::template GetBitfield<DMA_ISR_HTIF6>(); }
            auto TCIF6() { return reg_t::template GetBitfield<DMA_ISR_TCIF6>(); }
            auto GIF6()  { return reg_t::template GetBitfield<DMA_ISR_GIF6>(); }
            auto TEIF5() { return reg_t::template GetBitfield<DMA_ISR_TEIF5>(); }
            auto HTIF5() { return reg_t::template GetBitfield<DMA_ISR_HTIF5>(); }
            auto TCIF5() { return reg_t::template GetBitfield<DMA_ISR_TCIF5>(); }
            auto GIF5()  { return reg_t::template GetBitfield<DMA_ISR_GIF5>(); }
            auto TEIF4() { return reg_t::template GetBitfield<DMA_ISR_TEIF4>(); }
            auto HTIF4() { return reg_t::template GetBitfield<DMA_ISR_HTIF4>(); }
            auto TCIF4() { return reg_t::template GetBitfield<DMA_ISR_TCIF4>(); }
            auto GIF4()  { return reg_t::template GetBitfield<DMA_ISR_GIF4>(); }
            auto TEIF3() { return reg_t::template GetBitfield<DMA_ISR_TEIF3>(); }
            auto HTIF3() { return reg_t::template GetBitfield<DMA_ISR_HTIF3>(); }
            auto TCIF3() { return reg_t::template GetBitfield<DMA_ISR_TCIF3>(); }
            auto GIF3()  { return reg_t::template GetBitfield<DMA_ISR_GIF3>(); }
            auto TEIF2() { return reg_t::template GetBitfield<DMA_ISR_TEIF2>(); }
            auto HTIF2() { return reg_t::template GetBitfield<DMA_ISR_HTIF2>(); }
            auto TCIF2() { return reg_t::template GetBitfield<DMA_ISR_TCIF2>(); }
            auto GIF2()  { return reg_t::template GetBitfield<DMA_ISR_GIF2>(); }
            auto TEIF1() { return reg_t::template GetBitfield<DMA_ISR_TEIF1>(); }
            auto HTIF1() { return reg_t::template GetBitfield<DMA_ISR_HTIF1>(); }
            auto TCIF1() { return reg_t::template GetBitfield<DMA_ISR_TCIF1>(); }
            auto GIF1()  { return reg_t::template GetBitfield<DMA_ISR_GIF1>(); }
        };

        // Interrupt flag clear register
        template <std::size_t CH, uint32_t ADDR>
        struct IFCR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto CTEIF() // Transfer error clear
            {
                if constexpr(CH == 7u) { return CTEIF7(); }
                if constexpr(CH == 6u) { return CTEIF6(); }
                if constexpr(CH == 5u) { return CTEIF5(); }
                if constexpr(CH == 4u) { return CTEIF4(); }
                if constexpr(CH == 3u) { return CTEIF3(); }
                if constexpr(CH == 2u) { return CTEIF2(); }
                if constexpr(CH == 1u) { return CTEIF1(); }
            }

            auto CHTIF() // Half transfer clear
            {
                if constexpr(CH == 7u) { return CHTIF7(); }
                if constexpr(CH == 6u) { return CHTIF6(); }
                if constexpr(CH == 5u) { return CHTIF5(); }
                if constexpr(CH == 4u) { return CHTIF4(); }
                if constexpr(CH == 3u) { return CHTIF3(); }
                if constexpr(CH == 2u) { return CHTIF2(); }
                if constexpr(CH == 1u) { return CHTIF1(); }
            }

            auto CTCIF() // Transfer complete clear
            {
                if constexpr(CH == 7u) { return CTCIF7(); }
                if constexpr(CH == 6u) { return CTCIF6(); }
                if constexpr(CH == 5u) { return CTCIF5(); }
                if constexpr(CH == 4u) { return CTCIF4(); }
                if constexpr(CH == 3u) { return CTCIF3(); }
                if constexpr(CH == 2u) { return CTCIF2(); }
                if constexpr(CH == 1u) { return CTCIF1(); }
            }

            auto CGIF() // Global interrupt clear
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
            auto CTEIF7() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF7>(); }
            auto CHTIF7() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF7>(); }
            auto CTCIF7() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF7>(); }
            auto CGIF7()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF7>(); }
            auto CTEIF6() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF6>(); }
            auto CHTIF6() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF6>(); }
            auto CTCIF6() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF6>(); }
            auto CGIF6()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF6>(); }
            auto CTEIF5() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF5>(); }
            auto CHTIF5() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF5>(); }
            auto CTCIF5() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF5>(); }
            auto CGIF5()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF5>(); }
            auto CTEIF4() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF4>(); }
            auto CHTIF4() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF4>(); }
            auto CTCIF4() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF4>(); }
            auto CGIF4()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF4>(); }
            auto CTEIF3() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF3>(); }
            auto CHTIF3() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF3>(); }
            auto CTCIF3() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF3>(); }
            auto CGIF3()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF3>(); }
            auto CTEIF2() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF2>(); }
            auto CHTIF2() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF2>(); }
            auto CTCIF2() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF2>(); }
            auto CGIF2()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF2>(); }
            auto CTEIF1() { return reg_t::template GetBitfield<DMA_IFCR_CTEIF1>(); }
            auto CHTIF1() { return reg_t::template GetBitfield<DMA_IFCR_CHTIF1>(); }
            auto CTCIF1() { return reg_t::template GetBitfield<DMA_IFCR_CTCIF1>(); }
            auto CGIF1()  { return reg_t::template GetBitfield<DMA_IFCR_CGIF1>(); }
        };

        // Configuration register
        template <std::size_t CH, uint32_t ADDR>
        struct CCR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;
            
            auto MEM2MEM() { return reg_t::template GetBitfield<DMA_CCR_MEM2MEM>(); } // Memory to memory mode
            auto PL() { return reg_t::template GetBitfield<DMA_CCR_PL>(); } // Priority level
            auto MSIZE() { return reg_t::template GetBitfield<DMA_CCR_MSIZE>(); } // Memory size
            auto PSIZE() { return reg_t::template GetBitfield<DMA_CCR_PSIZE>(); } // Peripheral size
            auto MINC() { return reg_t::template GetBitfield<DMA_CCR_MINC>(); } // Memory increment mode
            auto PINC() { return reg_t::template GetBitfield<DMA_CCR_PINC>(); } // Peripheral increment mode
            auto CIRC() { return reg_t::template GetBitfield<DMA_CCR_CIRC>(); } // Circular mode
            auto DIR() { return reg_t::template GetBitfield<DMA_CCR_DIR>(); } // Data transfer direction
            auto TEIE() { return reg_t::template GetBitfield<DMA_CCR_TEIE>(); } // Tranfer error interrupt enable
            auto HTIE() { return reg_t::template GetBitfield<DMA_CCR_HTIE>(); } // Half transfer interrupt enable
            auto TCIE() { return reg_t::template GetBitfield<DMA_CCR_TCIE>(); } // Transfer complete interrupt enable
            auto EN() { return reg_t::template GetBitfield<DMA_CCR_EN>(); } // Channel enable
        };

        // Number of data register
        template <std::size_t CH, uint32_t ADDR>
        struct CNDTR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            static constexpr uint32_t Maximum = DMA_CNDTR_NDT + 1u;

            auto NDT() { return reg_t::template GetBitfield<DMA_CNDTR_NDT>(); } // Number of data to transfer
        };

        // Peripheral address register
        template <std::size_t CH, uint32_t ADDR>
        struct CPAR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto PeriphAddress() { return reg_t::template GetBitfield<DMA_CPAR_PA>(); } // Peripheral address
        };

        // Memory address register
        template <std::size_t CH, uint32_t ADDR>
        struct CMAR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            auto MemAddress() { return reg_t::template GetBitfield<DMA_CMAR_MA>(); } // Memory address
        };

        template <std::size_t CH>
        struct Registers
        {
        private:
            static constexpr uint32_t GetChannelBase() noexcept
            {
                if constexpr (CH == 1u) { return DMA1_Channel1_BASE; }
                if constexpr (CH == 2u) { return DMA1_Channel2_BASE; }
                if constexpr (CH == 3u) { return DMA1_Channel3_BASE; }
                if constexpr (CH == 4u) { return DMA1_Channel4_BASE; }
                if constexpr (CH == 5u) { return DMA1_Channel5_BASE; }
                if constexpr (CH == 6u) { return DMA1_Channel6_BASE; }
                if constexpr (CH == 7u) { return DMA1_Channel7_BASE; }
            }
            
        public:
            using ISR_t = ISR<CH, DMA1_BASE + offsetof(DMA_TypeDef, ISR)>;
            using IFCR_t = IFCR<CH, DMA1_BASE + offsetof(DMA_TypeDef, IFCR)>;
            using CCR_t = CCR<CH, GetChannelBase() + offsetof(DMA_Channel_TypeDef, CCR)>;
            using CNDTR_t = CNDTR<CH, GetChannelBase() + offsetof(DMA_Channel_TypeDef, CNDTR)>;
            using CPAR_t = CPAR<CH, GetChannelBase() + offsetof(DMA_Channel_TypeDef, CPAR)>;
            using CMAR_t = CMAR<CH, GetChannelBase() + offsetof(DMA_Channel_TypeDef, CMAR)>;
        };
    }
}