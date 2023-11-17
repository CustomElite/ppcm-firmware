#pragma once

namespace Common::Math
{
    template <typename T>
    constexpr auto Minimum(T const &lhs, T const &rhs) noexcept -> T
    {
        return (lhs < rhs) ? lhs : rhs;
    }

    template <typename T>
    constexpr auto Maximum(T const &lhs, T const &rhs) noexcept -> T
    {
        return (lhs > rhs) ? lhs : rhs;
    }

    template <typename T>
    constexpr auto IsBetween(T const &val, T const &min, T const &max) noexcept -> bool
    {
        return ((val >= min) && (val <= max));
    }
}