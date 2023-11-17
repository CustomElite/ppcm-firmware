#pragma once

#include "pin_defs.hpp"

#include "mcu/gpio.hpp"
#include "mcu/interrupt.hpp"
#include "mcu/usart.hpp"

#include <optional>

namespace System
{
    struct USART_Properties
    {
        static constexpr uint32_t BaudRate = 19200u;
        static constexpr auto Module = USART::Peripheral::USART_1;
        static constexpr auto DataDirection = USART::Settings::DataDirection::TX_RX;
        static constexpr auto DataWidth = USART::Settings::DataWidth::_8bits;
        static constexpr auto Parity = USART::Settings::Parity::None;
        static constexpr auto StopBits = USART::Settings::StopBits::_1bit;
        static constexpr auto FlowControl = USART::Settings::FlowControl::None;
        static constexpr uint8_t BufferSize = 64u;
        static constexpr bool ACK = true;

        using TX_Pin = USART_TX;
        using RX_Pin = USART_RX;
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

