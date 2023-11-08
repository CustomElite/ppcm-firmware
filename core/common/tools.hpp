#pragma once

#include <type_traits>

namespace Common::Tools
{
    template <typename T, typename U = std::underlying_type_t<T>>
    constexpr auto EnumValue(T val) noexcept -> U
    {
        return static_cast<U>(val);
    }

    template <typename T, typename... Args>
    constexpr auto IsOneOf(const T& input, const Args&... test_vals) noexcept
    {
        return ( ... || (input == static_cast<T>(test_vals)));
    }

    template <typename T, typename... Args>
    constexpr auto IsAllOf(const T& input, const Args&... test_vals) noexcept
    {
        return ( ... && (input == static_cast<T>(test_vals)));
    }
}