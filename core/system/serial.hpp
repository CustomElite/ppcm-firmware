#pragma once

#include "types.hpp"

#include "mcu/usart.hpp"

namespace System
{
    template <typename SysCore, typename GoodFunc, typename BadFunc>
    auto Serial(GoodFunc && good, BadFunc && bad) noexcept
    {
        return MCU::USART::Module
        {
            SerialProperties{},
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

