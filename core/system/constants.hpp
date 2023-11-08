#pragma once

#include "tools.hpp"

#include <cstdint>

namespace System 
{
    constexpr float operator ""_v(long double v) noexcept { return static_cast<float>(v); }
    constexpr float operator ""_mv(long double mv) noexcept { return (static_cast<float>(mv) / 1000.0f); }
    constexpr float operator ""_a(long double a) noexcept { return static_cast<float>(a); }
    constexpr float operator ""_ma(long double ma) noexcept { return (static_cast<float>(ma) / 1000.0f); }

    constexpr uint32_t operator ""_u32(unsigned long long rhs) noexcept { return static_cast<uint32_t>(rhs); }

    constexpr uint32_t const LSI_Clock = 40'000u;
    constexpr uint32_t const LSE_Clock = 32'768u;
    constexpr uint32_t const RTC_Clock = LSE_Clock;
    constexpr uint32_t const HSI_Clock = 8'000'000u;
    constexpr uint32_t const HSE_Clock = 8'000'000u;

    constexpr float const VDD_Voltage = 3.3_v;
}