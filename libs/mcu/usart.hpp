#pragma once

#include "macros.h"

#include "mcu/rcc.hpp"
#include "rcc.hpp"
#include "gpio.hpp"
#include "interrupt.hpp"
#include "stm32f103xb.h"
#include "usart_registers.hpp"

#include "common/run_once.hpp"
#include "common/static_lambda.hpp"
#include "common/containers/fifo.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

namespace MCU::USART 
{
    enum class Peripheral : uint8_t
    {
        USART_1 = 1u,
        USART_2,
        USART_3
    };

    namespace {
        template <Peripheral tPeriph>
        constexpr auto GetClockID() noexcept
        {
            if constexpr (tPeriph == Peripheral::USART_1) { return CLK::ClockID::APB2_USART1; }
            if constexpr (tPeriph == Peripheral::USART_2) { return CLK::ClockID::APB1_USART2; }
            if constexpr (tPeriph == Peripheral::USART_3) { return CLK::ClockID::APB1_USART3; }
        }
        template <Peripheral tPeriph>
        constexpr auto GetInterruptSource() noexcept
        {
            if constexpr (tPeriph == Peripheral::USART_1) { return ISR::InterruptSource::eUSART1; }
            if constexpr (tPeriph == Peripheral::USART_2) { return ISR::InterruptSource::eUSART2; }
            if constexpr (tPeriph == Peripheral::USART_3) { return ISR::InterruptSource::eUSART3; }
        }
    }

    template 
    <
        Peripheral tPeriph
        , typename tTxPin
        , typename tRxPin
        , unsigned tPeriphClock
        , unsigned tBaudRate = 9600u
        , DataDirection tDirection = DataDirection::TX_RX
        , DataWidth tWidth = DataWidth::_8bits
        , Parity tParity = Parity::None
        , StopBits tStopBits = StopBits::_1bit
        , FlowControl tFlow = FlowControl::None
    >
    struct Properties
    {
        using tx_pin_t = tTxPin;
        using rx_pin_t = tRxPin;

        static constexpr auto s_Peripheral = tPeriph;
        static constexpr auto s_PeriphClockFreq = tPeriphClock;
        static constexpr auto s_BaudRate = tBaudRate;
        static constexpr auto s_DataDirection = tDirection;
        static constexpr auto s_DataWidth = tWidth;
        static constexpr auto s_Parity = tParity;
        static constexpr auto s_StopBits = tStopBits;
        static constexpr auto s_FlowControl = tFlow;
    };

    template <Peripheral tPeriph, size_t BufferSize = 64u>
    struct DataHandler
    {
        using buffer_type = Common::Containers::FIFO<char, BufferSize>;

        using regs_t = Registers<Common::Tools::EnumValue(tPeriph)>;
        using SR = typename regs_t::SR;
        using DR = typename regs_t::DR;
        using CR1 = typename regs_t::CR1;

        inline static buffer_type m_rxBuffer{};
        inline static buffer_type m_txBuffer{};

        ALWAYS_INLINE
        static void TransmitInternal() noexcept
        {
            if (!CR1{}.TCIE())
            {
                CR1{}.TCIE() = true;
            }

            if (auto data{ m_txBuffer.Pop() }; data.has_value())
            {
                DR{} = data.value();
            }
            else {
                CR1{}.TCIE() = false;
            }
        }
        ALWAYS_INLINE
        static void BlockingTransmit(char const input) noexcept
        {
            while (!SR{}.TC());
            DR{} = input;
        }
        ALWAYS_INLINE
        static void PushTx(char const input) noexcept
        {
            if (!m_txBuffer.IsFull())
            {
                m_txBuffer.Push(input);
            }
        }
        ALWAYS_INLINE
        static bool IsTerminator(char const input) noexcept
        {
            switch (input)
            {
                case '\r':
                case '\n':
                case ';': return true;
                default: return false;
            }
        }
    };

    template <typename tProperties, typename tCallable>
    class Module : private tProperties
    {
    public:
        template <typename C>
        Module(C && callback) noexcept
            : m_tx{ IO::Alternate::PushPull }
            , m_rx{ IO::Input::PuPd, IO::PullResistor::PullUp }
            , m_callback{ std::forward<C>(callback) }
        {
            regs_t{}.SetBaudRate(s_PeriphClockFreq, s_BaudRate);
            
            regs_t{}.Configure(s_DataDirection, s_DataWidth, s_Parity, s_StopBits, s_FlowControl);

            CR1{}.RXNEIE() = true;

            Enable();
        }
        Module(tProperties, tCallable && callback) noexcept :
            Module{ std::forward<tCallable>(callback) }
        {}
        ~Module(){}
        ALWAYS_INLINE
        static void Enable() noexcept
        {
            if (!CR1{}.UE().Read())
            {
                CR1{}.UE() = true;
            }
        }
        ALWAYS_INLINE
        static void Disable() noexcept
        {
            if (CR1{}.UE().Read())
            {
                CR1{}.UE() = false;
            }
        }

        static void Interrupt() noexcept
        {
            if (SR{}.RXNE())
            {
                char const c = DR{}.Read();
                if (!data_t{}.IsTerminator(c))
                {
                    data_t{}.PushTx(c);
                    if constexpr (0)
                    {
                        data_t::BlockingTransmit(c);
                    }
                }
                else {
                    //data_t::BlockingSendBuffer(data_t::m_txBuffer);
                    callback_t::Run(true);
                    data_t{}.TransmitInternal();
                    data_t::m_rxBuffer.Clear();
                }
            }
            else if (SR{}.TC())
            {
                data_t{}.TransmitInternal();
            }
        }

    private:
        using tProperties::s_Peripheral
            , tProperties::s_PeriphClockFreq
            , tProperties::s_BaudRate
            , tProperties::s_DataDirection
            , tProperties::s_DataWidth
            , tProperties::s_Parity
            , tProperties::s_StopBits
            , tProperties::s_FlowControl;
        
        using typename tProperties::tx_pin_t;
        using typename tProperties::rx_pin_t;

        using data_t = DataHandler<s_Peripheral>;

        using regs_t = Registers<Common::Tools::EnumValue(s_Peripheral)>;
        using SR = typename regs_t::SR;
        using DR = typename regs_t::DR;
        using BRR =typename regs_t::BRR;
        using CR1 = typename regs_t::CR1;
        using CR2 = typename regs_t::CR2;
        using CR3 = typename regs_t::CR3;
        using GTPR = typename regs_t::GTPR;
        
        using kernal_t = CLK::Kernal<GetClockID<s_Peripheral>()>;
        using isr_t = ISR::Interrupt<Module, GetInterruptSource<s_Peripheral>()>;
        using callback_t = Common::StaticLambda<tCallable>;

    private:
        kernal_t const m_clk{};
        isr_t const m_isr{};

        tx_pin_t const m_tx;
        rx_pin_t const m_rx;
        callback_t const m_callback;
    };

    template <typename CFG, typename CB>
    Module(CFG, CB) -> Module<CFG, CB>;
}