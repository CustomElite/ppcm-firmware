#pragma once

#include <type_traits>

namespace Common::Tools
{
    template <typename T, class = void>
    struct EnumType
    {
        using type = T;
    };
    template <typename T>
    struct EnumType<T, std::enable_if_t<std::is_enum_v<T>>>
    {
        using type = std::underlying_type_t<T>;
    };

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