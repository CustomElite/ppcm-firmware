#pragma once

#include "gpio.hpp"
#include "interrupt.hpp"
#include "mcu_config.hpp"
#include "rcc.hpp"
#include "static_lambda.hpp"

#include <optional>
#include <etl/singleton.h>
#include <etl/memory_model.h>
#include <etl/queue_spsc_atomic.h>
#include <etl/private/delegate_cpp11.h>

namespace System
{
    using namespace Peripherals;
    using namespace Common::Tools;
    
    class Serial
    {
    public:
        static Serial& Get() noexcept
        {
            return etl::singleton<Serial>::instance();
        }

    public:
        Serial(USART_TypeDef* instance, size_t baud_rate = 9600u) noexcept
            : m_usart{ instance },
            m_tx{IO::Alternate::PushPull},
            m_rx{IO::Input::PuPd, IO::PullResistor::PullUp},
            m_rxBuffer{},
            //m_isr{ delegate_t::template create<Serial, &Serial::interrupt_handler>(*this) }
            m_isr{ 
                [](){
                    if (LL_USART_IsActiveFlag_RXNE(Get().m_usart))
                    Get().m_rxBuffer.push(LL_USART_ReceiveData8(Get().m_usart));
                } 
            }
        {
            if (m_usart == USART1)
                Configure(baud_rate);
        }

        void Write(char input) const noexcept
        {
            transmit_byte(input);
        }
        std::optional<char> Read() noexcept
        {
            char c = 0;
            if (m_rxBuffer.pop(c))
                return {c};
            else
                return {};
        }
        size_t Size() const noexcept
        {
            return m_rxBuffer.size();
        }
        bool Empty() const noexcept
        {
            return m_rxBuffer.empty();
        }

    private:
        using buffer_t = etl::queue_spsc_atomic<char, 64u, etl::memory_model::MEMORY_MODEL_SMALL>;
        using interrupt_t = ISR::Interrupt<Serial, ISR::InterruptSource::eUSART1, 5u>;
        //using callback_t = Common::StaticLambda<typename T>

        using TX_Pin = IO::Module<IO::Port::A, 9>;
        using RX_Pin = IO::Module<IO::Port::A, 10>;

    private:
        USART_TypeDef * const m_usart;
        TX_Pin m_tx;
        RX_Pin m_rx;

        buffer_t m_rxBuffer;

        const interrupt_t m_isr;

    private:
        void Configure(size_t baud_rate) const noexcept
        {
            /* Peripheral clock enable */
            CLK::ClockControl<CLK::PeriphClock::APB2_USART1>::Power();

            /* UART Configuration */
            LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);
            LL_USART_ConfigCharacter(USART1, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
            LL_USART_SetBaudRate(USART1, __LL_RCC_CALC_PCLK2_FREQ(SystemCoreClock, LL_RCC_GetAPB2Prescaler()), baud_rate);
            LL_USART_ConfigAsyncMode(USART1);
            
            LL_USART_EnableIT_RXNE(USART1);

            LL_USART_Enable(USART1);
        }
        void interrupt_handler() noexcept
        {
            if (LL_USART_IsActiveFlag_RXNE(m_usart))
                m_rxBuffer.push(LL_USART_ReceiveData8(m_usart));
        }
        inline void transmit_byte(const uint8_t data) const noexcept
        {
            while (!LL_USART_IsActiveFlag_TXE(m_usart));
            LL_USART_TransmitData8(m_usart, data);
        }
    };
}

