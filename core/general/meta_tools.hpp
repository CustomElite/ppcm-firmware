#pragma once

#include <type_traits>

namespace General 
{
    template <typename T, typename U = std::underlying_type_t<T>>
    constexpr auto EnumValue(T val) noexcept -> U
    {
        return static_cast<U>(val);
    }
}