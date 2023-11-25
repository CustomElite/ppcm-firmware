#pragma once

#include "common/tools.hpp"
#include "common/register.hpp"

#include "stm32f1xx.h"

namespace MCU::USART
{
    inline namespace Settings
    {
        enum class DataDirection : uint8_t
        {
            TX = 0b01,
            RX = 0b10,
            TX_RX = 0b11
        };
        enum class DataWidth : uint8_t
        {
            _8bits = 0b0,
            _9bits = 0b1
        };
        enum class Parity : uint8_t
        {
            None = 0b00,
            Even = 0b01,
            Odd = 0b11
        };
        enum class StopBits : uint8_t
        {
            _1bit = 0b00,
            _0_5bit = 0b01,
            _2bits = 0b10,
            _1_5bits = 0b11
        };
        enum class FlowControl : uint8_t
        {
            None = 0b0,
            CTS = 0b01,
            RTS = 0b10,
            CTS_RTS = 0b11
        };
    }

    namespace Flags 
    {

    
    }

    namespace MemoryMap
    {
        namespace { using namespace Common::Tools; }

        // Status register
        template <uint32_t tAddress>
        struct SR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            
            auto CTS() { return reg_t::template GetBitfield<USART_SR_CTS>(); } // CTS flag
            auto LBD() { return reg_t::template GetBitfield<USART_SR_LBD>(); } // LIN break detection flag
            auto TXE() { return reg_t::template GetBitfield<USART_SR_TXE>(); } // Transmit data register empty
            auto TC() { return reg_t::template GetBitfield<USART_SR_TC>(); } // Transmission complete
            auto RXNE() { return reg_t::template GetBitfield<USART_SR_RXNE>(); } // Receive data register not empty
            auto IDLE() { return reg_t::template GetBitfield<USART_SR_IDLE>(); } // IDLE line detected
            auto ORE() { return reg_t::template GetBitfield<USART_SR_ORE>(); } // Overrun error
            auto NE() { return reg_t::template GetBitfield<USART_SR_NE>(); } // Noise error
            auto FE() { return reg_t::template GetBitfield<USART_SR_FE>(); } // Framing error
            auto PE() { return reg_t::template GetBitfield<USART_SR_PE>(); } // Parity error
        };

        // Data register
        template <uint32_t tAddress>
        struct DR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;
            
            auto & operator = (uint16_t const rhs) noexcept
            {
                reg_t::template GetBitfield<USART_DR_DR>() = rhs;
                return *this;
            }
            constexpr auto GetAddress() const noexcept
            {
                return tAddress;
            }
        };

        // Baud rate register
        template <uint32_t tAddress>
        struct BRR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;
   
            auto DIV_Mantissa() { return reg_t::template GetBitfield<USART_BRR_DIV_Mantissa>(); } // Mantissa of USARTDIV
            auto DIV_Fraction() { return reg_t::template GetBitfield<USART_BRR_DIV_Fraction>(); } // Fraction of USARTDIV

            
        };

        // Control register 1
        template <uint32_t tAddress>
        struct CR1 : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto UE() { return reg_t::template GetBitfield<USART_CR1_UE>(); } // USART enable    
            auto M() { return reg_t::template GetBitfield<USART_CR1_M>(); } // Word length
            auto WAKE() { return reg_t::template GetBitfield<USART_CR1_WAKE>(); } // Wakeup method
            auto PCE() { return reg_t::template GetBitfield<USART_CR1_PCE>(); } // Parity control enable
            auto PS() { return reg_t::template GetBitfield<USART_CR1_PS>(); } // Parity selection 
            auto PEIE() { return reg_t::template GetBitfield<USART_CR1_PEIE>(); } // PE interrupt enable          
            auto TXEIE() { return reg_t::template GetBitfield<USART_CR1_TXEIE>(); } // TXE interrupt enable        
            auto TCIE() { return reg_t::template GetBitfield<USART_CR1_TCIE>(); } // Transmission complete interrupt enable           
            auto RXNEIE() { return reg_t::template GetBitfield<USART_CR1_RXNEIE>(); } // RXNE interrupt enable          
            auto TE() { return reg_t::template GetBitfield<USART_CR1_TE>(); } // Transmitter enable            
            auto RE() { return reg_t::template GetBitfield<USART_CR1_RE>(); } // Receiver enable         
            auto RWU() { return reg_t::template GetBitfield<USART_CR1_RWU>(); } // Receiver wakeup           
            auto SBK() { return reg_t::template GetBitfield<USART_CR1_SBK>(); } // Send break
            
            DataDirection GetDataDirection() const noexcept
            {
                return DataDirection{ (RE().Read() << 1u) | TE().Read() };
            }
            DataWidth GetDataWidth() const noexcept
            {
                return DataWidth{ M().Read() };
            }
            Parity GetParity() const noexcept
            {
                return Parity{ (PS().Read() << 1u) | PCE().Read() };
            }
        };

        // Control register 2
        template <uint32_t tAddress>
        struct CR2 : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto LINEN() { return reg_t::template GetBitfield<USART_CR2_LINEN>(); } // LIN mode enable
            auto STOP() { return reg_t::template GetBitfield<USART_CR2_STOP>(); } // STOP bits
            auto CLKEN() { return reg_t::template GetBitfield<USART_CR2_CLKEN>(); } // Clock enable
            auto CPOL() { return reg_t::template GetBitfield<USART_CR2_CPOL>(); } // Clock polarity
            auto CPHA() { return reg_t::template GetBitfield<USART_CR2_CPHA>(); } // Clock phase
            auto LBCL() { return reg_t::template GetBitfield<USART_CR2_LBCL>(); } // Last bit clock pulse
            auto LBDIE() { return reg_t::template GetBitfield<USART_CR2_LBDIE>(); } // LIN break detection interrupt enable
            auto LBDL() { return reg_t::template GetBitfield<USART_CR2_LBDL>(); } // LIN break detection length
            auto ADD() { return reg_t::template GetBitfield<USART_CR2_ADD>(); } // Address of USART node
        };

        // Control register 3
        template <uint32_t tAddress>
        struct CR3 : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto CTSIE() { return reg_t::template GetBitfield<USART_CR3_CTSIE>(); } // CTS interrupt enable
            auto CTSE() { return reg_t::template GetBitfield<USART_CR3_CTSE>(); } // CTS enable
            auto RTSE() { return reg_t::template GetBitfield<USART_CR3_RTSE>(); } // RTS enable
            auto DMAT() { return reg_t::template GetBitfield<USART_CR3_DMAT>(); } // DMA enable transmitter
            auto DMAR() { return reg_t::template GetBitfield<USART_CR3_DMAR>(); } // DMA enable receiver
            auto SCEN() { return reg_t::template GetBitfield<USART_CR3_SCEN>(); } // Smartcard mode enable
            auto NACK() { return reg_t::template GetBitfield<USART_CR3_NACK>(); } // Smartcard NACK enable
            auto HDSEL() { return reg_t::template GetBitfield<USART_CR3_HDSEL>(); } // Half-duplex selection
            auto IRLP() { return reg_t::template GetBitfield<USART_CR3_IRLP>(); } // IrDA low power
            auto IREN() { return reg_t::template GetBitfield<USART_CR3_IREN>(); } // IrDA mode enable
            auto EIE() { return reg_t::template GetBitfield<USART_CR3_EIE>(); } // Error interrupt mode
        };

        // Guard time and prescaler register
        template <uint32_t tAddress>
        struct GTPR : public u32_reg_t<tAddress>
        {
            using reg_t = u32_reg_t<tAddress>;
            using reg_t::reg_t;

            auto GT() { return reg_t::template GetBitfield<USART_GTPR_GT>(); } // Guard time value
            auto PSC() { return reg_t::template GetBitfield<USART_GTPR_PSC>(); } // Prescaler value
        };
    }

    template <size_t tPeriph>
    struct Registers
    {
    private:
        static constexpr uint32_t BaseAddress() noexcept
        {
            if constexpr (tPeriph == 1u) { return USART1_BASE; }
            if constexpr (tPeriph == 2u) { return USART2_BASE; }
            if constexpr (tPeriph == 3u) { return USART3_BASE; }
        }
    
    public:
        using SR = MemoryMap::SR<BaseAddress() + offsetof(USART_TypeDef, SR)>;
        using DR = MemoryMap::DR<BaseAddress() + offsetof(USART_TypeDef, DR)>;
        using BRR = MemoryMap::BRR<BaseAddress() + offsetof(USART_TypeDef, BRR)>;
        using CR1 = MemoryMap::CR1<BaseAddress() + offsetof(USART_TypeDef, CR1)>;
        using CR2 = MemoryMap::CR2<BaseAddress() + offsetof(USART_TypeDef, CR2)>;
        using CR3 = MemoryMap::CR3<BaseAddress() + offsetof(USART_TypeDef, CR3)>;
        using GTPR = MemoryMap::GTPR<BaseAddress() + offsetof(USART_TypeDef, GTPR)>;
    };
}