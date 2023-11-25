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
        Peripheral tPeriph,
        typename TxPin,
        typename RxPin,
        unsigned tPeriphClock,
        unsigned tBaudRate = 9600u,
        DataDirection tDirection = DataDirection::TX_RX,
        DataWidth tWidth = DataWidth::_8bits,
        Parity tParity = Parity::None,
        StopBits tStopBits = StopBits::_1bit,
        FlowControl tFlow = FlowControl::None
    >
    class Configuration : TxPin, RxPin
    {
    public:
        using kernal_t = CLK::Kernal<GetClockID<tPeriph>()>;
        using tx_pin_t = TxPin;
        using rx_pin_t = RxPin;

        using regs_t = Registers<Common::Tools::EnumValue(tPeriph)>;

        using SR = typename regs_t::SR;
        using DR = typename regs_t::DR;
        using BRR = typename regs_t::BRR;
        using CR1 = typename regs_t::CR1;
        using CR2 = typename regs_t::CR2;
        using CR3 = typename regs_t::CR3;
        using GTPR = typename regs_t::GTPR;

        static constexpr auto Peripheral = tPeriph;

        Configuration() noexcept :
            TxPin{ IO::Alternate::PushPull },
            RxPin{ IO::Input::PuPd, IO::PullResistor::PullUp }
        {
            
        }
        template <typename... tArgs>
        static void Configure(tArgs... args) noexcept
        {
            ( Set(args), ... );
        }
        static void Enable() noexcept
        {
            if (!CR1{}.UE().Read()) { CR1{}.UE() = true; }
        }
        static void Disable() noexcept
        {
            if (CR1{}.UE().Read()) { CR1{}.UE() = false; }
        }
        
    
    private:
        static void Set(DataDirection const input) noexcept
        {
            uint32_t tmp{ Common::Tools::EnumValue(input) };
            CR1{}.TE() = (tmp & 0b01);
            CR1{}.RE() = ((tmp >> 1u) & 0b01);
        }
        static void Set(DataWidth const input) noexcept
        {
            CR1{}.M() = Common::Tools::EnumValue(input);
        }
        static void Set(Parity const input) noexcept
        {
            uint32_t tmp{ Common::Tools::EnumValue(input) };
            CR1{}.PCE() = (tmp & 0b01);
            CR1{}.PS() = (tmp >> 1u) & 0b01;
        }
        static void Set(StopBits const & input) noexcept
        {
            CR2{}.STOP() = Common::Tools::EnumValue(input);
        }
        static void Set(FlowControl const & input) noexcept
        {
            uint32_t tmp{ Common::Tools::EnumValue(input) };
            CR3{}.CTSE() = (tmp & 0b01);
            CR3{}.RTSE() = ((tmp >> 1u) & 0b01);
        }
        static void Set(uint32_t baud_rate) noexcept
        {
            uint32_t div_x100 = ((tPeriphClock * 25u) / (4u * baud_rate));
            uint32_t div_mant = (div_x100 / 100u);
            uint32_t div_frac = ((((div_x100 - (div_mant * 100u)) * 16u) + 50u) / 100u);

            BRR{}.DIV_Mantissa() = (uint16_t)(div_mant & 0xFFF);
            BRR{}.DIV_Fraction() = (uint16_t)(div_frac & 0xF);
        }

    private:
        kernal_t const m_kernal{};
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
        static void AutoTransmit() noexcept
        {
            if (!CR1{}.TCIE())
            {
                CR1{}.TCIE() = true;
                if (auto data{ m_txBuffer.Pop() }; data.has_value())
                {
                    DR{} = data.value();
                }
            }
        }
        ALWAYS_INLINE
        static void BlockingTransmit(char const input) noexcept
        {
            while (!SR{}.TC());
            DR{} = input;
        }
        ALWAYS_INLINE
        static void SendBuffer(buffer_type & input) noexcept
        {
            while (input.Size())
            {
                m_txBuffer.Push(input.Pop().value());
            }
            AutoTransmit();
        }
        ALWAYS_INLINE
        static void BlockingSendBuffer(buffer_type & input) noexcept
        {
            while (input.Size())
            {
                BlockingTransmit(input.Pop().value());
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

    template <typename tConfig, typename tCallback>
    class Module : private tConfig
    {
    public:
        template <typename CB>
        Module(CB && callback) noexcept :
            m_callback{ std::forward<CB>(callback) }
        {
            tConfig::Configure(tConfig::tBaudRate, tConfig::tDirection, tConfig::tWidth, tConfig::tParity, tConfig::tStopBits, tConfig::tFlow);
            CR1{}.RXNEIE() = true;
            tConfig::Enable();
        }
        Module(tConfig, tCallback && callback) noexcept :
            Module{ std::forward<tCallback>(callback) }
        {}
        ~Module(){}

        static void Interrupt() noexcept
        {
            if (SR{}.RXNE())
            {
                char const c = DR{}.Read();
                if (!data_t::IsTerminator(c))
                {
                    data_t::m_rxBuffer.Push(c);
                    if constexpr (1)
                    {
                        data_t::BlockingTransmit(c);
                    }
                }
                else {
                    //data_t::BlockingSendBuffer(data_t::m_txBuffer);
                    callback_t::Run(true);
                    //data_t::StartTransmitting();
                    data_t::m_rxBuffer.Clear();
                    data_t::m_txBuffer.Clear();
                }
            }
            else if (SR{}.TC())
            {
                //while (SR{}.RXNE());
                if (auto data{ data_t::m_txBuffer.Pop() }; data.has_value())
                {
                    DR{} = data.value();
                }
                else {
                    CR1{}.TCIE() = false;
                }
            }
        }

    private:
        using tConfig::Peripheral;

        using SR = typename tConfig::SR;
        using DR = typename tConfig::DR;
        using BRR = typename tConfig::BRR;
        using CR1 = typename tConfig::CR1;
        using CR2 = typename tConfig::CR2;
        using CR3 = typename tConfig::CR3;
        using GTPR = typename tConfig::GTPR;

        using interrupt_t = ISR::Interrupt<Module, GetInterruptSource<Peripheral>()>;
        using callback_t = Common::StaticLambda<tCallback>;
        using data_t = DataHandler<Peripheral>;

    private:
        //kernal_t const m_kernal;
        interrupt_t const m_interrupt;
        callback_t const m_callback;
    };

    template <typename CFG, typename CB>
    Module(CFG, CB) -> Module<CFG, CB>;
}