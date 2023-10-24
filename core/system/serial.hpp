#pragma once

#include <etl/private/delegate_cpp11.h>
#include <optional>
#include <stddef.h>

#include <etl/singleton.h>
#include <etl/memory_model.h>
#include <etl/queue_spsc_atomic.h>
#include <stdint.h>

#include "interrupt.hpp"

#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"

namespace System
{
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
            m_isr{ delegate_t::create<Serial, &Serial::Interrupt>(*this) },
            m_rxBuffer{}
        {
            if (m_usart == USART1)
                configure(baud_rate);
        }

        void WriteC(char input) const noexcept
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
        void Interrupt() noexcept
        {
            if (LL_USART_IsActiveFlag_RXNE(m_usart))
                m_rxBuffer.push(LL_USART_ReceiveData8(m_usart));
        }

    private:
        using buffer_t = etl::queue_spsc_atomic<char, 64u, etl::memory_model::MEMORY_MODEL_SMALL>;
        using interrupt_t = System::Interrupt<Serial, InterruptSource::eUSART1, 2u>;
        using delegate_t = interrupt_t::delegate_t;

    private:
        USART_TypeDef* m_usart;
        interrupt_t m_isr;
        buffer_t m_rxBuffer;

    private:
        void configure(size_t baud_rate) const noexcept
        {
            /* Peripheral clock enable */
            LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA | LL_APB2_GRP1_PERIPH_USART1);

            /* USART1 GPIO Configuration */
            LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
            LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
            LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
            LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_UP);

            LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_FLOATING);
            LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);

            /* UART Configuration */
            LL_USART_SetTransferDirection(USART1, LL_USART_DIRECTION_TX_RX);
            LL_USART_ConfigCharacter(USART1, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
            LL_USART_SetBaudRate(USART1, __LL_RCC_CALC_PCLK2_FREQ(SystemCoreClock, LL_RCC_GetAPB2Prescaler()), baud_rate);
            LL_USART_ConfigAsyncMode(USART1);
            
            LL_USART_EnableIT_RXNE(USART1);

            LL_USART_Enable(USART1);
        }
        inline void transmit_byte(const uint8_t data) const noexcept
        {
            while (!LL_USART_IsActiveFlag_TXE(m_usart));
            LL_USART_TransmitData8(m_usart, data);
        }
    };
}

