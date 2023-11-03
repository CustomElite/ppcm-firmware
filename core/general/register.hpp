#pragma once

#include "macros.h"

#include <etl/binary.h>

namespace General 
{
    template <typename T, size_t RegAddress, T BitMask>
    class Bitfield
    {
    public:
        ALWAYS_INLINE void Clear() noexcept
        {
            (*Addr) &= nMask;
        }
        ALWAYS_INLINE void Set(T input) noexcept
        {
            (*Addr) = (*Addr & nMask) | apply_mask(input);
        }
        ALWAYS_INLINE void Toggle(T input) noexcept
        {
            (*Addr) ^= apply_mask(input);
        }
        ALWAYS_INLINE T Get() const noexcept
        {
            return (((*Addr) & Mask) >> Pos);
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
            (*Addr) |= apply_mask(input);
            return *this;
        }
        ALWAYS_INLINE Bitfield& operator &= (T input) noexcept
        {
            (*Addr) &= (apply_mask(input) | nMask);
            return *this;
        }
    private:
        using ptr_t = volatile T* const;

        static constexpr T Mask = BitMask;
        static constexpr T nMask = (~Mask);
        static constexpr T Pos = etl::count_trailing_zeros(BitMask);

        inline static ptr_t Addr = reinterpret_cast<ptr_t>(RegAddress);

    private:
        ALWAYS_INLINE static auto apply_mask(T input) noexcept
        {
            return ((input << Pos) & Mask);
        }
    };

    template <typename T, size_t Address>
    struct Register
    {
        using ptr_t = volatile T* const;
        using base_t = T;

        constexpr Register() = default;

        inline static ptr_t Addr = reinterpret_cast<ptr_t>(Address);

        ALWAYS_INLINE void Set(T input) noexcept
        {
            (*Addr) = input;
        }
        ALWAYS_INLINE T Get() const noexcept
        {
            return *Addr;
        }
        ALWAYS_INLINE Register& Access() noexcept
        {
            return *this;
        }
        template <T Mask>
        ALWAYS_INLINE Bitfield<T, Address, Mask> Bits() const noexcept
        {
            return {};
        }
        ALWAYS_INLINE Register& operator = (const T& input) noexcept
        {
            (*Addr) = input;
            return *this;
        }
        ALWAYS_INLINE Register& operator %= (const T& input) noexcept
        {
            (*Addr) %= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator ^= (const T& input) noexcept
        {
            (*Addr) ^= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator *= (const T& input) noexcept
        {
            (*Addr) *= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator /= (const T& input) noexcept
        {
            (*Addr) /= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator += (const T& input) noexcept
        {
            (*Addr) += input;
            return *this;
        }
        ALWAYS_INLINE Register& operator -= (const T& input) noexcept
        {
            (*Addr) -= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator |= (const T& input) noexcept
        {
            (*Addr) |= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator &= (const T& input) noexcept
        {
            (*Addr) &= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator <<= (const T& input) noexcept
        {
            (*Addr) <<= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator >>= (const T& input) noexcept
        {
            (*Addr) >>= input;
            return *this;
        }
        ALWAYS_INLINE Register& operator--() noexcept
        {
            --(*Addr);
            return *this;
        }
        ALWAYS_INLINE T operator--(int) noexcept
        {
            auto retval = (*Addr);
            --(*Addr);
            return retval;
        }
        ALWAYS_INLINE Register& operator++() noexcept
        {
            ++(*Addr);
            return *this;
        }
        ALWAYS_INLINE T operator++(int) noexcept
        {
            auto retval = (*Addr);
            ++(*Addr);
            return retval;
        }
        ALWAYS_INLINE T operator ~ () const noexcept
        {
            return ~(*Addr);
        }
        ALWAYS_INLINE T operator - () const noexcept
        {
            return -(*Addr);
        }
        ALWAYS_INLINE T operator + () const noexcept
        {
            return +(*Addr);
        }
        ALWAYS_INLINE T operator ^ (const T& input) const noexcept
        {
            return (*Addr) ^ input;
        }
        ALWAYS_INLINE T operator % (const T& input) const noexcept
        {
            return (*Addr) % input;
        }
        ALWAYS_INLINE T operator & (const T& input) const noexcept
        {
            return (*Addr) & input;
        }
        ALWAYS_INLINE T operator | (const T& input) const noexcept
        {
            return (*Addr) | input;
        }
        ALWAYS_INLINE T operator + (const T& input) const noexcept
        {
            return (*Addr) + input;
        }
        ALWAYS_INLINE T operator - (const T& input) const noexcept
        {
            return (*Addr) - input;
        }
        ALWAYS_INLINE T operator * (const T& input) const noexcept
        {
            return (*Addr) * input;
        }
        ALWAYS_INLINE T operator / (const T& input) const noexcept
        {
            return (*Addr) / input;
        }
        ALWAYS_INLINE T operator << (const T& input) const noexcept
        {
            return (*Addr) << input;
        }
        ALWAYS_INLINE T operator >> (const T& input) const noexcept
        {
            return (*Addr) >> input;
        }
        ALWAYS_INLINE bool operator ! () const noexcept
        {
            return !(*Addr);
        }
        ALWAYS_INLINE bool operator && (const T& input) const noexcept
        {
            return (*Addr) && input;
        }
        ALWAYS_INLINE bool operator || (const T& input) const noexcept
        {
            return (*Addr) || input;
        }
        ALWAYS_INLINE bool operator == (const T& input) const noexcept
        {
            return (*Addr) == input;
        }
        ALWAYS_INLINE bool operator != (const T& input) const noexcept
        {
            return (*Addr) != input;
        }
        ALWAYS_INLINE bool operator < (const T& input) const noexcept
        {
            return (*Addr) < input;
        }
        ALWAYS_INLINE bool operator <= (const T& input) const noexcept
        {
            return (*Addr) <= input;
        }
        ALWAYS_INLINE bool operator > (const T& input) const noexcept
        {
            return (*Addr) > input;
        }
        ALWAYS_INLINE bool operator >= (const T& input) const noexcept
        {
            return (*Addr) >= input;
        }
    };

    template <size_t RegAddress>
    using u32_reg_t = General::Register<uint32_t, RegAddress>;

    template <size_t RegAddress>
    using u16_reg_t = General::Register<uint16_t, RegAddress>;
}