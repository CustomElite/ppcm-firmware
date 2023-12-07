#pragma once

#include "macros.h"

#include "mcu/rcc.hpp"
#include "rcc.hpp"
#include "gpio.hpp"
#include "interrupt.hpp"
#include "usart_registers.hpp"

#include "common/static_lambda.hpp"
#include "common/containers/ring_buffer.hpp"

#include <cstddef>
#include <cstdint>

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
        constexpr auto ClockID() noexcept
        {
            if constexpr (tPeriph == Peripheral::USART_1) { return CLK::ClockID::APB2_USART1; }
            if constexpr (tPeriph == Peripheral::USART_2) { return CLK::ClockID::APB1_USART2; }
            if constexpr (tPeriph == Peripheral::USART_3) { return CLK::ClockID::APB1_USART3; }
        }
        template <Peripheral tPeriph>
        constexpr auto InterruptSource() noexcept
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
        , size_t tPeriphClock
        , size_t tBaudRate = 9600u
        , DataDirection tDirection = DataDirection::TxRx
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

        constexpr Properties() noexcept = default;

    private:
        tx_pin_t const m_tx{ IO::Alternate::PushPull };
        rx_pin_t const m_rx{ IO::PullResistor::PullUp, IO::Input::PuPd };
    };

    template <Peripheral tPeriph, size_t BufferSize = 64u>
    struct DataHandler
    {
        using buffer_t = Common::Containers::RingBuffer<char, BufferSize>;

        using HW = HardwareKernal<Common::Tools::EnumValue(tPeriph)>;

        inline static buffer_t s_rxBuffer{};
        inline static Common::Containers::RingBuffer<char, 8> s_txBuffer{};

        ALWAYS_INLINE
        static void TransmitInternal() noexcept
        {
            
            if (!HW::Registers::CR1().TCIE())
            {
                HW::Registers::CR1().TCIE() = true;
            }

            if (auto data{ s_txBuffer.Pop() }; data.has_value())
            {
                HW::Registers::DR() = data.value();
            }
            else {
                HW::Registers::CR1().TCIE() = false;
            }
        }
        ALWAYS_INLINE
        static void BlockingTransmit(char const input) noexcept
        {
            while (!HW::Registers::SR().TC());
            HW::Registers::DR() = input;
        }
        ALWAYS_INLINE
        static void PushTx(char const input) noexcept
        {
            s_txBuffer.Push(input);
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

    template <typename tProperties, typename tCallback>
    class Module : private tProperties, Common::StaticLambda<tCallback>
    {
    public:
        template <typename C>
        Module(C && callback) noexcept
            : Properties{}
            , Callback{ std::forward<C>(callback) }
        {
            HW::SetBaudRate(s_PeriphClockFreq, s_BaudRate);
            
            HW::Configure(s_DataDirection, s_DataWidth, s_Parity, s_StopBits, s_FlowControl);

            HW::Registers::CR1().RXNEIE() = true;

            HW::Enable();
        }
        Module(tProperties, tCallback && callback) noexcept
            : Module{ std::forward<tCallback>(callback) }
        {}
        ~Module()
        {
            HW::Disable();
        }
        
        static void Interrupt() noexcept
        {
            if (HW::Registers::SR().RXNE())
            {
                char const c = HW::Registers::DR().Read();
                if (!Data::IsTerminator(c))
                {
                    Data::PushTx(c);
                    if constexpr (0)
                    {
                        Data::BlockingTransmit(c);
                    }
                }
                else {
                    //data_t::BlockingSendBuffer(data_t::m_txBuffer);
                    Callback::Run(true);
                    Data::TransmitInternal();
                    Data::s_rxBuffer.Clear();
                }
            }
            else if (HW::Registers::SR().TC())
            {
                Data::TransmitInternal();
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
        
        using Data = DataHandler<s_Peripheral>;
        using Properties = tProperties;
        using Callback = Common::StaticLambda<tCallback>;
        using HW = HardwareKernal<Common::Tools::EnumValue(s_Peripheral)>;
        
        using clk_t = CLK::Kernal<ClockID<s_Peripheral>()>;
        using isr_t = ISR::Kernal<Module, InterruptSource<s_Peripheral>()>;
        

    private:
        clk_t const m_clk{};
        isr_t const m_isr{};
    };

    template <typename CFG, typename CB>
    Module(CFG, CB) -> Module<CFG, CB>;
}