#pragma once

#include "common/tools.hpp"
#include "common/register.hpp"

#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include <type_traits>

namespace MCU::SPI
{
    namespace { using namespace Common::Tools; }

    inline namespace Settings
    {
        enum class Mode : bool
        {
            Slave = false,
            Master = true
        };

        enum class DataWidth : bool
        {
            _8bit = false,
            _16bit = true
        };

        enum class BitOrder : bool
        {
            MSB_First = false,
            LSB_First = true
        };
        
        enum class ClockPolarity : bool
        {
            Low = false,
            High = true
        };

        enum class ClockPhase : bool
        {
            LeadingEdge = false,
            TrailingEdge = true
        };

        enum class DataDirection : uint8_t
        {
            FullDuplex = 0b000,
            Simplex_RX = 0b001,
            HalfDuplex_RX = 0b100,
            HalfDuplex_TX = 0b110
        };

        enum class ClockPrescaler : uint8_t
        {
            Div2 = 0b000,
            Div4 = 0b001,
            Div8 = 0b010,
            Div16 = 0b011,
            Div32 = 0b100,
            Div64 = 0b101,
            Div128 = 0b110,
            Div256 = 0b111
        };
    }

    namespace MemoryMap
    {
        // Control register 1
        template <uint32_t tAddress>
        struct CR1 : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;

            auto BIDIMODE() { return reg_t::template GetBitfield<SPI_CR1_BIDIMODE>(); }// Bidirectional data mode enable
            auto BIDIOE() { return reg_t::template GetBitfield<SPI_CR1_BIDIOE>(); } // Output enable in bidirectional mode
            auto CRCEN() { return reg_t::template GetBitfield<SPI_CR1_CRCNEXT>(); } // Hardware CRC calculation enable
            auto CRCNEXT() { return reg_t::template GetBitfield<SPI_CR1_BIDIOE>(); } // CRC transfer next
            auto DFF() { return reg_t::template GetBitfield<SPI_CR1_DFF>(); } // Data frame format
            auto RXONLY() { return reg_t::template GetBitfield<SPI_CR1_RXONLY>(); } // Receive only
            auto SSM() { return reg_t::template GetBitfield<SPI_CR1_SSM>(); } // Software slave management    
            auto SSI() { return reg_t::template GetBitfield<SPI_CR1_SSI>(); } // Internal slave select
            auto LSBFIRST() { return reg_t::template GetBitfield<SPI_CR1_LSBFIRST>(); } // Frame format
            auto SPE() { return reg_t::template GetBitfield<SPI_CR1_SPE>(); } // SPI enable
            auto BR() { return reg_t::template GetBitfield<SPI_CR1_BR>(); } // Baud rate control
            auto MSTR() { return reg_t::template GetBitfield<SPI_CR1_MSTR>(); } // Master selection
            auto CPOL() { return reg_t::template GetBitfield<SPI_CR1_CPOL>(); } // Clock polarity
            auto CPHA() { return reg_t::template GetBitfield<SPI_CR1_CPHA>(); } // Clock phase

            auto GetDataDirection() const noexcept
            {
                uint8_t retval{0};
                retval |= (BIDIMODE().Read() << 2u);
                retval |= (BIDIOE().Read() << 1u);
                retval |= (RXONLY().Read());

                return DataDirection{ retval };
            }
            auto GetDataWidth() const noexcept
            {
                return DataWidth{ DFF().Read() };
            }
            auto GetBitOrder() const noexcept
            {
                return BitOrder{ LSBFIRST().Read() };
            }
            auto GetClockPrescaler() const noexcept
            {
                return ClockPrescaler{ BR().Read() };
            }
            auto GetMode() const noexcept
            {
                return Mode{ MSTR().Read() };
            }
            auto GetClockPhase() const noexcept
            {
                return ClockPhase{ CPHA().Read() };
            }
            auto GetClockPolarity() const noexcept
            {
                return ClockPolarity{ CPOL().Read() };
            }
        };

        // Control register 2
        template <uint32_t tAddress>
        struct CR2 : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;

            auto TXEIE() { return reg_t::template GetBitfield<SPI_CR2_TXEIE>(); } // Tx buffer empty interrupt enable 
            auto RXNEIE() { return reg_t::template GetBitfield<SPI_CR2_RXNEIE>(); } // RX buffer not empty interrupt enable       
            auto ERRIE() { return reg_t::template GetBitfield<SPI_CR2_ERRIE>(); } // Error interrupt enable           
            auto SSOE() { return reg_t::template GetBitfield<SPI_CR2_SSOE>(); } // SS output enable         
            auto TXDMAEN() { return reg_t::template GetBitfield<SPI_CR2_TXDMAEN>(); } // Tx buffer DMA enable      
            auto RXDMAEN() { return reg_t::template GetBitfield<SPI_CR2_RXDMAEN>(); } // Rx buffer DMA enable
        };

        // Status register
        template <uint32_t tAddress>
        struct SR : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;

            auto BSY() { return reg_t::template GetBitfield<SPI_SR_BSY>(); } // Busy flag            
            auto OVR() { return reg_t::template GetBitfield<SPI_SR_OVR>(); } // Overrun flag            
            auto MODF() { return reg_t::template GetBitfield<SPI_SR_MODF>(); } // Mode fault           
            auto CRCERR() { return reg_t::template GetBitfield<SPI_SR_CRCERR>(); } // CRC error flag            
            auto UDR() { return reg_t::template GetBitfield<SPI_SR_UDR>(); } // Underrun flag           
            auto CHSIDE() { return reg_t::template GetBitfield<SPI_SR_CHSIDE>(); } // Channel side            
            auto TXE() { return reg_t::template GetBitfield<SPI_SR_TXE>(); } // Transmit buffer empty
            auto RXNE() { return reg_t::template GetBitfield<SPI_SR_RXNE>(); } // Receive buffer not empty
        };

        // Data register
        template <uint32_t tAddress>
        struct DR : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;
            using reg_t::operator=;

            constexpr auto GetAddress() const noexcept
            {
                return tAddress;
            }
        };

        // CRC polynomial register
        template <uint32_t tAddress>
        struct CRCPR : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;
            using reg_t::operator=;
        };

        // Rx CRC register
        template <uint32_t tAddress>
        struct RXCRCR : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;
            using reg_t::operator=;
        };

        // Tx CRC register
        template <uint32_t tAddress>
        struct TXCRCR : public u16_reg_t<tAddress>
        {
            using reg_t = u16_reg_t<tAddress>;
            using reg_t::reg_t;
            using reg_t::operator=;
        };
    }

    template <size_t tPeriph>
    struct Registers
    {
    private:
        static constexpr uint32_t GetBaseAddress() noexcept
        {
            if constexpr (tPeriph == 1u) { return SPI1_BASE; }
            if constexpr (tPeriph == 2u) { return SPI2_BASE; }
        }

        void Set(DataDirection const input) noexcept
        {
            CR1().BIDIMODE() = ((EnumValue(input) >> 2u) & 1u);
            CR1().BIDIOE() = ((EnumValue(input) >> 1u) & 1u);
            CR1().RXONLY() = ((EnumValue(input) >> 0u) & 1u);
        }
        void Set(DataWidth const input) noexcept
        {
            CR1().DFF() = EnumValue(input);
        }
        void Set(BitOrder const input) noexcept
        {
            CR1().LSBFIRST() = EnumValue(input);
        }
        void Set(ClockPrescaler const input) noexcept
        {
            CR1().BR() = EnumValue(input);
        }
        void Set(Mode const input) noexcept
        {
            CR1().MSTR() = EnumValue(input);
        }
        void Set(ClockPhase const input) noexcept
        {
            CR1().CPHA() = EnumValue(input);
        }
        void Set(ClockPolarity const input) noexcept
        {
            CR1().CPOL() = EnumValue(input);
        }

    public:
        using CR1_t = MemoryMap::CR1<GetBaseAddress() + offsetof(SPI_TypeDef, CR1)>;
        using CR2_t = MemoryMap::CR2<GetBaseAddress() + offsetof(SPI_TypeDef, CR2)>;
        using SR_t = MemoryMap::SR<GetBaseAddress() + offsetof(SPI_TypeDef, SR)>;
        using DR_t = MemoryMap::DR<GetBaseAddress() + offsetof(SPI_TypeDef, DR)>;
        using CRCPR_t = MemoryMap::CRCPR<GetBaseAddress() + offsetof(SPI_TypeDef, CRCPR)>;
        using RXCRCR_t = MemoryMap::RXCRCR<GetBaseAddress() + offsetof(SPI_TypeDef, RXCRCR)>;
        using TXCRCR_t = MemoryMap::TXCRCR<GetBaseAddress() + offsetof(SPI_TypeDef, TXCRCR)>;

        CR1_t CR1() { return {}; }
        CR2_t CR2() { return {}; }
        SR_t SR() { return {}; }
        DR_t DR() { return {}; }
        CRCPR_t CRCPR() { return {}; }
        RXCRCR_t RXCRCR() { return {}; }
        TXCRCR_t TXCRCR() { return {}; }

        void EnablePeriph() noexcept
        {
            if (!CR1().SPE().Read()) { CR1().SPE() = true; }
        }
        void DisablePeriph() noexcept
        {
            if (CR1().SPE().Read()) { CR1().SPE() = false; }
        }
        template <typename... tArgs>
        void Configure(tArgs... args) noexcept
        {
            ( Set(args), ... );
        }
    };
}