#pragma once

#include "macros.h"

#include <etl/binary.h>

namespace Common 
{
    template <typename T, uint32_t ADDR, T BITMSK>
    class Bitfield
    {
    public:
        ALWAYS_INLINE void Clear() noexcept
        {
            (*s_addr) &= s_nMask;
        }
        ALWAYS_INLINE void Set(T input) noexcept
        {
            (*s_addr) = (*s_addr & s_nMask) | apply_mask(input);
        }
        ALWAYS_INLINE void Toggle(T input) noexcept
        {
            (*s_addr) ^= apply_mask(input);
        }
        ALWAYS_INLINE T Get() const noexcept
        {
            return (((*s_addr) & s_mask) >> s_pos);
        }
        ALWAYS_INLINE Bitfield& operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE operator T() const noexcept
        {
            return Get();
        }
        ALWAYS_INLINE Bitfield& operator |= (T input) noexcept
        {
            (*s_addr) |= apply_mask(input);
            return *this;
        }
        ALWAYS_INLINE Bitfield& operator &= (T input) noexcept
        {
            (*s_addr) &= (apply_mask(input) | s_nMask);
            return *this;
        }
    private:
        using ptr_t = T volatile * const;

        static constexpr T s_mask = BITMSK;
        static constexpr T s_nMask = (~s_mask);
        static constexpr T s_pos = etl::count_trailing_zeros(BITMSK);

        inline static ptr_t s_addr = reinterpret_cast<ptr_t>(ADDR);

    private:
        ALWAYS_INLINE static auto apply_mask(T input) noexcept
        {
            return ((input << s_pos) & s_mask);
        }
    };

    template <typename T, uint32_t ADDR>
    struct RawRegister
    {
        using ptr_t = T volatile * const;

        constexpr RawRegister() = default;

        inline static ptr_t s_addr = reinterpret_cast<ptr_t>(ADDR);

        ALWAYS_INLINE void Set(T input) noexcept
        {
            (*s_addr) = input;
        }
        ALWAYS_INLINE T Get() const noexcept
        {
            return *s_addr;
        }
        ALWAYS_INLINE RawRegister& Access() noexcept
        {
            return *this;
        }
        template <T MSK>
        ALWAYS_INLINE Bitfield<T, ADDR, MSK> Bits() const noexcept
        {
            return {};
        }
        ALWAYS_INLINE RawRegister& operator = (const T& input) noexcept
        {
            (*s_addr) = input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator %= (const T& input) noexcept
        {
            (*s_addr) %= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator ^= (const T& input) noexcept
        {
            (*s_addr) ^= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator *= (const T& input) noexcept
        {
            (*s_addr) *= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator /= (const T& input) noexcept
        {
            (*s_addr) /= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator += (const T& input) noexcept
        {
            (*s_addr) += input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator -= (const T& input) noexcept
        {
            (*s_addr) -= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator |= (const T& input) noexcept
        {
            (*s_addr) |= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator &= (const T& input) noexcept
        {
            (*s_addr) &= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator <<= (const T& input) noexcept
        {
            (*s_addr) <<= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator >>= (const T& input) noexcept
        {
            (*s_addr) >>= input;
            return *this;
        }
        ALWAYS_INLINE RawRegister& operator--() noexcept
        {
            --(*s_addr);
            return *this;
        }
        ALWAYS_INLINE T operator--(int) noexcept
        {
            auto retval = (*s_addr);
            --(*s_addr);
            return retval;
        }
        ALWAYS_INLINE RawRegister& operator++() noexcept
        {
            ++(*s_addr);
            return *this;
        }
        ALWAYS_INLINE T operator++(int) noexcept
        {
            auto retval = (*s_addr);
            ++(*s_addr);
            return retval;
        }
        ALWAYS_INLINE T operator ~ () const noexcept
        {
            return ~(*s_addr);
        }
        ALWAYS_INLINE T operator - () const noexcept
        {
            return -(*s_addr);
        }
        ALWAYS_INLINE T operator + () const noexcept
        {
            return +(*s_addr);
        }
        ALWAYS_INLINE T operator ^ (const T& input) const noexcept
        {
            return (*s_addr) ^ input;
        }
        ALWAYS_INLINE T operator % (const T& input) const noexcept
        {
            return (*s_addr) % input;
        }
        ALWAYS_INLINE T operator & (const T& input) const noexcept
        {
            return (*s_addr) & input;
        }
        ALWAYS_INLINE T operator | (const T& input) const noexcept
        {
            return (*s_addr) | input;
        }
        ALWAYS_INLINE T operator + (const T& input) const noexcept
        {
            return (*s_addr) + input;
        }
        ALWAYS_INLINE T operator - (const T& input) const noexcept
        {
            return (*s_addr) - input;
        }
        ALWAYS_INLINE T operator * (const T& input) const noexcept
        {
            return (*s_addr) * input;
        }
        ALWAYS_INLINE T operator / (const T& input) const noexcept
        {
            return (*s_addr) / input;
        }
        ALWAYS_INLINE T operator << (const T& input) const noexcept
        {
            return (*s_addr) << input;
        }
        ALWAYS_INLINE T operator >> (const T& input) const noexcept
        {
            return (*s_addr) >> input;
        }
        ALWAYS_INLINE bool operator ! () const noexcept
        {
            return !(*s_addr);
        }
        ALWAYS_INLINE bool operator && (const T& input) const noexcept
        {
            return (*s_addr) && input;
        }
        ALWAYS_INLINE bool operator || (const T& input) const noexcept
        {
            return (*s_addr) || input;
        }
        ALWAYS_INLINE bool operator == (const T& input) const noexcept
        {
            return (*s_addr) == input;
        }
        ALWAYS_INLINE bool operator != (const T& input) const noexcept
        {
            return (*s_addr) != input;
        }
        ALWAYS_INLINE bool operator < (const T& input) const noexcept
        {
            return (*s_addr) < input;
        }
        ALWAYS_INLINE bool operator <= (const T& input) const noexcept
        {
            return (*s_addr) <= input;
        }
        ALWAYS_INLINE bool operator > (const T& input) const noexcept
        {
            return (*s_addr) > input;
        }
        ALWAYS_INLINE bool operator >= (const T& input) const noexcept
        {
            return (*s_addr) >= input;
        }
    };
}

template <uint32_t RegAddress>
using u32_reg_t = Common::RawRegister<uint32_t, RegAddress>;

template <uint32_t RegAddress>
using u16_reg_t = Common::RawRegister<uint16_t, RegAddress>;