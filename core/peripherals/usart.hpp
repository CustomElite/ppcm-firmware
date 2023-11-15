#pragma once

#include "usart_registers.hpp"

#include "interrupt.hpp"

#include "types.hpp"
#include "run_once.hpp"
#include "static_lambda.hpp"
#include "containers/fifo.hpp"

#include <cstdint>

namespace Peripherals::USART 
{
    //using namespace Settings;

    enum class Module : uint8_t
    {
        USART_1 = 1u,
        USART_2,
        USART_3
    };

    template <Module M>
    static constexpr auto GetClockModule() noexcept
    {
        if constexpr (M == Module::USART_1) { return CLK::Module::APB2_USART1; }
        if constexpr (M == Module::USART_2) { return CLK::Module::APB1_USART2; }
        if constexpr (M == Module::USART_3) { return CLK::Module::APB1_USART3; }
    }
    template <Module M>
    static constexpr auto GetInterruptSource() noexcept
    {
        if constexpr (M == Module::USART_1) { return Peripherals::ISR::InterruptSource::eUSART1; }
        if constexpr (M == Module::USART_2) { return Peripherals::ISR::InterruptSource::eUSART2; }
        if constexpr (M == Module::USART_3) { return Peripherals::ISR::InterruptSource::eUSART3; }
    }

    template <Module M>
    struct PowerKernal
    {
        using clk_t = CLK::Control<GetClockModule<M>()>;

        static void Construct() noexcept
        {
            clk_t::Power();
        }
        static void Destruct() noexcept
        {
            if (!clk_t::Reset()) { clk_t::Power(CLK::State::Off); }
        }
    };

    template <typename Properties>
    struct DataHandler
    {
    private:
        static constexpr auto Module = Properties::Module;
        static constexpr auto BufferSize = Properties::BufferSize;

        using REGS = MemoryMap::Registers<Common::Tools::EnumValue(Module)>;
        using SR = typename REGS::SR_t;
        using DR = typename REGS::DR_t;
        using BRR = typename REGS::BRR_t;
        using CR1 = typename REGS::CR1_t;
        using CR2 = typename REGS::CR2_t;
        using CR3 = typename REGS::CR3_t;
        using GTPR = typename REGS::GTPR_t;

        using buffer_t = Common::Containers::FIFO<char, BufferSize>;

    public:
        inline static buffer_t m_rxBuffer{};
        inline static buffer_t m_txBuffer{};

        static void StartTransmitting() noexcept
        {
            if (!CR1{}.TCIE())
            {
                CR1{}.TCIE() = true;
                if (auto data{ m_txBuffer.Pop() }; data.has_value())
                {
                    DR() = data.value();
                }
            }
        }
        static void BlockingTransmit(char const input) noexcept
        {
            while (!SR{}.TC());
            DR() = input;
        }
        static void TX_Push(char const input) noexcept
        {
            if (m_txBuffer.Push(input))
            {
                StartTransmitting();
            }
        }
        template <size_t N>
        static void SendBuffer(std::array<char, N> const & input) noexcept
        {
            for (char c : input) {
                if (m_txBuffer.IsFull()) { break; }
                m_txBuffer.Push(c);
            }

            StartTransmitting();
        }
        static void BlockingSendBuffer(buffer_t & input) noexcept
        {
            while (input.Size())
            {
                BlockingTransmit(input.Pop().value_or(0));
            }
        }
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

    template <typename Properties, typename CB>
    class Interface : Properties
    {
    private:
        using Properties::BaudRate;
        using Properties::Module;
        using Properties::DataDirection;
        using Properties::DataWidth;
        using Properties::Parity;
        using Properties::StopBits;
        using Properties::FlowControl;
        using Properties::ACK;

        using REGS = MemoryMap::Registers<Common::Tools::EnumValue(Module)>;
        using SR = typename REGS::SR_t;
        using DR = typename REGS::DR_t;
        using BRR = typename REGS::BRR_t;
        using CR1 = typename REGS::CR1_t;
        using CR2 = typename REGS::CR2_t;
        using CR3 = typename REGS::CR3_t;
        using GTPR = typename REGS::GTPR_t;

        using kernal_t = Common::RunOnce<PowerKernal<Module>>;
        using interrupt_t = ISR::Interrupt<Interface, GetInterruptSource<Module>()>;
        using callback_t = Common::StaticLambda<CB>;
        using data_t = DataHandler<Properties>;

    private:
        kernal_t const m_kernal;
        interrupt_t const m_interrupt;
        callback_t const m_callback;

        //inline static data_handler_t m_data{};

    public:
        template <typename C>
        Interface(C && callback) noexcept :
            m_kernal{},
            m_interrupt{},
            m_callback{ std::forward<C>(callback) }
        {
            CR1{}.SetDataWidth(DataWidth);
            CR1{}.SetParity(Parity);
            CR2{}.SetStopBits(StopBits);
            CR3{}.SetFlowControl(FlowControl);

            if constexpr (Module == Module::USART_1)
            {
                BRR{}.SetBaudRate(::System::SystemBus_t::APB2_Clock(), BaudRate);
            }
            else {
                BRR{}.SetBaudRate(::System::SystemBus_t::APB1_Clock(), BaudRate);
            }

            CR1{}.SetDataDirection(DataDirection);

            CR1{}.RXNEIE() = true;
            CR1{}.UE() = true;
            
        }
        Interface(Properties, CB && callback) noexcept :
            Interface{ std::forward<CB>(callback) }
        {}
        ~Interface(){}

        static void Interrupt() noexcept
        {
            if (SR{}.RXNE())
            {
                char const c = DR{}.Read();
                if (!data_t::IsTerminator(c))
                {
                    data_t::m_rxBuffer.Push(c);
                    if constexpr (ACK)
                    {
                        data_t::TX_Push(c);
                    }
                }
                else {
                    callback_t::Run(true);
                    //data_t::BlockingSendBuffer(data_t::m_rxBuffer);
                    data_t::m_rxBuffer.Clear();
                }
            }
            else if (SR{}.TC())
            {
                if (auto data{ data_t::m_txBuffer.Pop() }; data.has_value())
                {
                    DR{} = data.value();
                }
                else {
                    CR1{}.TCIE() = false;
                }
            }
        }
    };

    template <typename P, typename C>
    Interface(P, C) -> Interface<P, C>;
}