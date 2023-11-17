#pragma once

#include "common/tools.hpp"

#include <cstdint>

namespace System 
{
    constexpr float operator ""_v(long double volts) noexcept { return static_cast<float>(volts); }
    constexpr float operator ""_mv(long double millivolts) noexcept { return static_cast<float>(millivolts / 1000.0f); }
    constexpr float operator ""_a(long double amp) noexcept { return static_cast<float>(amp); }
    constexpr float operator ""_ma(long double milliamps) noexcept { return static_cast<float>(milliamps / 1000.0f); }

    constexpr uint32_t operator ""_sec(long double seconds) noexcept { return static_cast<uint32_t>(seconds * 1000u); }
    constexpr uint32_t operator ""_sec(unsigned long long seconds) noexcept { return static_cast<uint32_t>(seconds * 1000u); }
    constexpr uint32_t operator ""_msec(long double milliseconds) noexcept { return static_cast<uint32_t>(milliseconds); }
    constexpr uint32_t operator ""_msec(unsigned long long milliseconds) noexcept { return static_cast<uint32_t>(milliseconds); }
    constexpr uint32_t operator ""_usec(long double microseconds) noexcept { return static_cast<uint32_t>(microseconds / 1000u); }
    constexpr uint32_t operator ""_usec(unsigned long long microseconds) noexcept { return static_cast<uint32_t>(microseconds / 1000u); }

    constexpr uint32_t operator ""_u32(unsigned long long rhs) noexcept { return static_cast<uint32_t>(rhs); }

    constexpr uint32_t const LSI_Clock = 40'000u;
    constexpr uint32_t const LSE_Clock = 32'768u;
    constexpr uint32_t const RTC_Clock = LSE_Clock;
    constexpr uint32_t const HSI_Clock = 8'000'000u;
    constexpr uint32_t const HSE_Clock = 8'000'000u;

    constexpr float const VDD_Voltage = 3.3_v;
}