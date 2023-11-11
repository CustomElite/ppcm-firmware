#pragma once

#include "stm32f103xb.h"
#include "tools.hpp"
#include "register.hpp"

#include "stm32f1xx.h"

namespace Peripheral::USART
{
    namespace Settings
    {
        enum class DataWidth : uint8_t
        {
            _8bits = 0,
            _9bits
        };
        enum class Parity : uint8_t
        {
            None = 0,
            Even,
            Odd
        };
        enum class StopBits : uint8_t
        {
            _1bit = 0,
            _0_5bit,
            _2bits,
            _1_5bits
        };
    }

    static constexpr uint32_t GetModuleBase(size_t module) noexcept
    {
        switch(module)
        {
            case 1: return USART1_BASE;
            case 2: return USART2_BASE;
            case 3: return USART3_BASE;
        }
    }
    namespace RegisterMap
    {
        // Status register
        template <size_t MODULE, uint32_t ADDR>
        struct SR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // CTS flag
            auto CTS() { return reg_t::template Bits<USART_SR_CTS>(); }

            // LIN break detection flag
            auto LBD() { return reg_t::template Bits<USART_SR_LBD>(); }

            // Transmit data register empty
            auto TXE() { return reg_t::template Bits<USART_SR_TXE>(); }

            // Transmission complete
            auto TC() { return reg_t::template Bits<USART_SR_TC>(); }

            // Receive data register not empty
            auto RXNE() { return reg_t::template Bits<USART_SR_RXNE>(); }

            // IDLE line detected
            auto IDLE() { return reg_t::template Bits<USART_SR_IDLE>(); }

            // Overrun error
            auto ORE() { return reg_t::template Bits<USART_SR_ORE>(); }

            // Noise error
            auto NE() { return reg_t::template Bits<USART_SR_NE>(); }

            // Framing error
            auto FE() { return reg_t::template Bits<USART_SR_FE>(); }

            // Parity error
            auto PE() { return reg_t::template Bits<USART_SR_PE>(); }
        };

        // Data register
        template <size_t MODULE, uint32_t ADDR>
        struct DR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Data register
            auto & operator = (uint32_t const &rhs)
            { 
                reg_t::template Bits<USART_DR_DR>() = rhs; 
                return *this;
            }
        };

        // Baud rate register
        template <size_t MODULE, uint32_t ADDR>
        struct BRR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Mantissa of USARTDIV
            auto DIV_Mantissa() { return reg_t::template Bits<USART_BRR_DIV_Mantissa>(); }

            // Fraction of USARTDIV
            auto DIV_Fraction() { return reg_t::template Bits<USART_BRR_DIV_Fraction>(); }

            void SetBaudRate(uint32_t pclk, uint32_t baud_rate) noexcept
            {
                auto div_x100 = ((pclk * 25u) / (4u * baud_rate));
                auto div_mant = (div_x100 / 100u);
                auto div_frac = ((((div_x100 - (div_mant * 100u)) * 16u) + 50u) / 100u);

                DIV_Mantissa() = (uint16_t)((div_mant << 4u) + (div_frac & 0xF0));
                DIV_Fraction() = (uint16_t)(div_frac & 0x0F);
            }
        };

        // Control register 1
        template <size_t MODULE, uint32_t ADDR>
        struct CR1 : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // USART enable
            auto UE() { return reg_t::template Bits<USART_CR1_UE>(); }

            // Word length
            auto M() { return reg_t::template Bits<USART_CR1_M>(); }

            // Wakeup method
            auto WAKE() { return reg_t::template Bits<USART_CR1_WAKE>(); }

            // Parity control enable
            auto PCE() { return reg_t::template Bits<USART_CR1_PCE>(); }

            // Parity selection
            auto PS() { return reg_t::template Bits<USART_CR1_PS>(); }

            // PE interrupt enable
            auto PEIE() { return reg_t::template Bits<USART_CR1_PEIE>(); }

            // TXE interrupt enable
            auto TXEIE() { return reg_t::template Bits<USART_CR1_TXEIE>(); }

            // Transmission complete interrupt enable
            auto TCIE() { return reg_t::template Bits<USART_CR1_TCIE>(); }

            // RXNE interrupt enable
            auto RXNEIE() { return reg_t::template Bits<USART_CR1_RXNEIE>(); }

            // Transmitter enable
            auto TE() { return reg_t::template Bits<USART_CR1_TE>(); }

            // Receiver enable
            auto RE() { return reg_t::template Bits<USART_CR1_RE>(); }

            // Receiver wakeup
            auto RWU() { return reg_t::template Bits<USART_CR1_RWU>(); }

            // Send break
            auto SBK() { return reg_t::template Bits<USART_CR1_SBK>(); }
        };

        // Control register 2
        template <size_t MODULE, uint32_t ADDR>
        struct CR2 : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // LIN mode enable
            auto LINEN() { return reg_t::template Bits<USART_CR2_LINEN>(); }

            // STOP bits
            auto STOP() { return reg_t::template Bits<USART_CR2_STOP>(); }

            // Clock enable
            auto CLKEN() { return reg_t::template Bits<USART_CR2_CLKEN>(); }

            // Clock polarity
            auto CPOL() { return reg_t::template Bits<USART_CR2_CPOL>(); }

            // Clock phase
            auto CPHA() { return reg_t::template Bits<USART_CR2_CPHA>(); }

            // Last bit clock pulse
            auto LBCL() { return reg_t::template Bits<USART_CR2_LBCL>(); }

            // LIN break detection interrupt enable
            auto LBDIE() { return reg_t::template Bits<USART_CR2_LBDIE>(); }

            // LIN break detection length
            auto LBDL() { return reg_t::template Bits<USART_CR2_LBDL>(); }

            // Address of USART node
            auto ADD() { return reg_t::template Bits<USART_CR2_ADD>(); }
        };

        // Control register 3
        template <size_t MODULE, uint32_t ADDR>
        struct CR3 : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // CTS interrupt enable
            auto CTSIE() { return reg_t::template Bits<USART_CR3_CTSIE>(); }

            // CTS enable
            auto CTSE() { return reg_t::template Bits<USART_CR3_CTSE>(); }

            // RTS enable
            auto RTSE() { return reg_t::template Bits<USART_CR3_RTSE>(); }

            // DMA enable transmitter
            auto DMAT() { return reg_t::template Bits<USART_CR3_DMAT>(); }

            // DMA enable receiver
            auto DMAR() { return reg_t::template Bits<USART_CR3_DMAR>(); }

            // Smartcard mode enable
            auto SCEN() { return reg_t::template Bits<USART_CR3_SCEN>(); }

            // Smartcard NACK enable
            auto NACK() { return reg_t::template Bits<USART_CR3_NACK>(); }

            // Half-duplex selection
            auto HDSEL() { return reg_t::template Bits<USART_CR3_HDSEL>(); }

            // IrDA low power
            auto IRLP() { return reg_t::template Bits<USART_CR3_IRLP>(); }

            // IrDA mode enable
            auto IREN() { return reg_t::template Bits<USART_CR3_IREN>(); }

            // Error interrupt mode
            auto EIE() { return reg_t::template Bits<USART_CR3_EIE>(); }
        };

        // Guard time and prescaler register
        template <size_t MODULE, uint32_t ADDR>
        struct GTPR : public u32_reg_t<ADDR>
        {
            using reg_t = u32_reg_t<ADDR>;
            using reg_t::reg_t;

            // Guard time value
            auto GT() { return reg_t::template Bits<USART_GTPR_GT>(); }

            // Prescaler value
            auto PSC() { return reg_t::template Bits<USART_GTPR_PSC>(); }
        };

        template <size_t MODULE>
        struct Registers
        {
            using SR_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, SR)>;
            using DR_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, DR)>;
            using BRR_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, BRR)>;
            using CR1_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, CR1)>;
            using CR2_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, CR2)>;
            using CR3_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, CR3)>;
            using GTPR_t = SR<MODULE, GetModuleBase(MODULE) + offsetof(USART_TypeDef, GTPR)>;
        };
    }
}