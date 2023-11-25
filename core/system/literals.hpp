#pragma once

#include <cstdint>

namespace System 
{
    inline namespace Literals 
    {
        constexpr float operator ""_v(long double volts) noexcept { return static_cast<float>(volts); }
        constexpr float operator ""_mv(long double millivolts) noexcept { return static_cast<float>(millivolts / 1'000.0f); }
        constexpr float operator ""_a(long double amp) noexcept { return static_cast<float>(amp); }
        constexpr float operator ""_ma(long double milliamps) noexcept { return static_cast<float>(milliamps / 1'000.0f); }

        constexpr uint32_t operator ""_sec(long double seconds) noexcept { return static_cast<uint32_t>(seconds * 1'000u); }
        constexpr uint32_t operator ""_sec(unsigned long long seconds) noexcept { return static_cast<uint32_t>(seconds * 1'000u); }
        constexpr uint32_t operator ""_ms(long double milliseconds) noexcept { return static_cast<uint32_t>(milliseconds); }
        constexpr uint32_t operator ""_ms(unsigned long long milliseconds) noexcept { return static_cast<uint32_t>(milliseconds); }

        constexpr uint32_t operator ""_Hz(unsigned long long hertz) noexcept { return static_cast<uint32_t>(hertz); }
        constexpr uint32_t operator ""_KHz(unsigned long long kilohertz) noexcept { return static_cast<uint32_t>(kilohertz * 1'000u); }
        constexpr uint32_t operator ""_KHz(long double kilohertz) noexcept { return static_cast<uint32_t>(kilohertz * 1'000u); }
        constexpr uint32_t operator ""_MHz(unsigned long long megahertz) noexcept { return static_cast<uint32_t>(megahertz * 1'000'000u); }
        constexpr uint32_t operator ""_MHz(long double megahertz) noexcept { return static_cast<uint32_t>(megahertz * 1'000'000u); }

        constexpr uint32_t operator ""_u32(unsigned long long rhs) noexcept { return static_cast<uint32_t>(rhs); }
    }
}



