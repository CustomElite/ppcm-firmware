#pragma once

#include "gpio.hpp"
#include "interrupt.hpp"
#include "mcu_config.hpp"
#include "rcc.hpp"
#include "pin_defs.hpp"
#include "usart.hpp"

#include <optional>
#include <etl/singleton.h>

namespace System
{
    class USART_Properties
    {
    public:
        static constexpr uint32_t BaudRate = 19200u;
        static constexpr auto Module = USART::Module::USART_1;
        static constexpr auto DataDirection = USART::Settings::DataDirection::TX_RX;
        static constexpr auto DataWidth = USART::Settings::DataWidth::_8bits;
        static constexpr auto Parity = USART::Settings::Parity::None;
        static constexpr auto StopBits = USART::Settings::StopBits::_1bit;
        static constexpr auto FlowControl = USART::Settings::FlowControl::None;
        static constexpr uint8_t BufferSize = 64u;
        static constexpr bool ACK = true;

        USART_Properties() noexcept :
            m_tx{ IO::Alternate::PushPull },
            m_rx{ IO::Input::PuPd, IO::PullResistor::PullUp }
        {}
    
    private:
        USART_TX const m_tx;
        USART_RX const m_rx;
    };

    template <typename SYS, typename GoodFunc, typename BadFunc>
    auto Serial(GoodFunc && good, BadFunc && bad) noexcept
    {
        return USART::Interface
        {
            USART_Properties{},
            [ g{ std::forward<GoodFunc>(good) }, b{ std::forward<BadFunc>(bad) } ](bool const q)
            {
                if (q)
                {
                    g();
                }
                else {
                    b();
                }
            }
        };
    }
}

