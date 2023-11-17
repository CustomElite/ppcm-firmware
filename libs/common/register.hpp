#pragma once

#include "macros.h"

#include <cstdint>
#include <cstddef>

namespace Common 
{
    template <typename T, uint32_t ADDR, T BITMSK>
    class Bitset
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
        ALWAYS_INLINE T Read() const noexcept
        {
            return (((*s_addr) & s_mask) >> s_pos);
        }
        ALWAYS_INLINE Bitset & operator = (T input) noexcept
        {
            Set(input);
            return *this;
        }
        ALWAYS_INLINE operator T() const noexcept
        {
            return Read();
        }
        ALWAYS_INLINE Bitset & operator |= (T input) noexcept
        {
            (*s_addr) |= apply_mask(input);
            return *this;
        }
        ALWAYS_INLINE Bitset & operator &= (T input) noexcept
        {
            (*s_addr) &= (apply_mask(input) | s_nMask);
            return *this;
        }

    private:
        ALWAYS_INLINE static constexpr T get_position() noexcept
        {
            T start{ 0 };
            T mask{ BITMSK };

            while((mask & 1) == 0)
            {
                ++start;
                mask >>= 1;
            }

            return start;
        }
        ALWAYS_INLINE static auto apply_mask(T input) noexcept
        {
            return ((input << s_pos) & s_mask);
        }
    
        using ptr_t = T volatile * const;

        static constexpr T s_mask = BITMSK;
        static constexpr T s_nMask = (~s_mask);
        static constexpr T s_pos = get_position();

        inline static ptr_t s_addr = reinterpret_cast<ptr_t>(ADDR);
    };

    template <typename T, uint32_t ADDR>
    struct RawRegister
    {
        using ptr_t = T volatile * const;

        constexpr RawRegister() = default;

        inline static ptr_t s_addr = reinterpret_cast<ptr_t>(ADDR);

        ALWAYS_INLINE void Write(T input) noexcept
        {
            (*s_addr) = input;
        }
        ALWAYS_INLINE T Read() const noexcept
        {
            return *s_addr;
        }
        ALWAYS_INLINE RawRegister & Access() noexcept
        {
            return *this;
        }
        template <T MSK>
        ALWAYS_INLINE Bitset<T, ADDR, MSK> Get() const noexcept
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