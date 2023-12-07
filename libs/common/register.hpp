#pragma once

#include "macros.h"

#include <bit>
#include <cstdint>

namespace Common 
{
    template <typename T, uint32_t tAddress, T tBitmask>
    class Bitfield
    {
    public:
        using Type = Bitfield<T, tAddress, tBitmask>;

        using ValueType = T;
        using Pointer = T volatile * const;

        ALWAYS_INLINE 
        void Clear() noexcept
        {
            (*s_Address) &= s_NMask;
        }
        ALWAYS_INLINE 
        void Set() noexcept
        {
            (*s_Address) = (*s_Address & s_NMask) | s_Mask;
        }
        ALWAYS_INLINE 
        void Toggle() noexcept
        {
            (*s_Address) ^= s_Mask;
        }
        ALWAYS_INLINE 
        void Write(ValueType const input) noexcept
        {
            (*s_Address) = (*s_Address & s_NMask) | apply_mask(input);
        }
        ALWAYS_INLINE 
        ValueType Read() const noexcept
        {
            return (((*s_Address) & s_Mask) >> s_Position);
        }
        ALWAYS_INLINE
        operator ValueType() const noexcept
        {
            return Read();
        }
        ALWAYS_INLINE 
        Bitfield & operator = (ValueType const other) noexcept
        {
            Write(other);
            return *this;
        }
        ALWAYS_INLINE 
        Bitfield & operator |= (ValueType const other) noexcept
        {
            (*s_Address) |= apply_mask(other);
            return *this;
        }
        ALWAYS_INLINE 
        Bitfield & operator &= (ValueType const other) noexcept
        {
            (*s_Address) &= (apply_mask(other) | s_NMask);
            return *this;
        }

    private:
        static auto apply_mask(ValueType const input) noexcept
        {
            return ((input << s_Position) & s_Mask);
        }

        static constexpr ValueType s_Mask{ tBitmask };
        static constexpr ValueType s_NMask{ (~s_Mask) };
        static constexpr ValueType s_Position{ std::countr_zero(s_Mask) };

        inline static Pointer s_Address{ reinterpret_cast<Pointer>(tAddress) };
    };

    template <typename T, uint32_t tAddress>
    struct RawRegister
    {
        using Type = RawRegister<T, tAddress>;

        using ValueType = T;
        using Pointer = T volatile * const;

        constexpr RawRegister() = default;

        ALWAYS_INLINE 
        void Write(ValueType const input) noexcept
        {
            (*s_Address) = input;
        }
        ALWAYS_INLINE 
        ValueType Read() const noexcept
        {
            return *s_Address;
        }
        ALWAYS_INLINE 
        RawRegister & Access() noexcept
        {
            return *this;
        }
        template <ValueType tMask>
        ALWAYS_INLINE 
        Bitfield<T, tAddress, tMask> CreateBitfield() const noexcept
        {
            return {};
        }
        ALWAYS_INLINE 
        RawRegister & operator =(ValueType const input) noexcept
        {
            (*s_Address) = input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator %=(ValueType const input) noexcept
        {
            (*s_Address) %= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator ^=(ValueType const input) noexcept
        {
            (*s_Address) ^= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator *=(ValueType const input) noexcept
        {
            (*s_Address) *= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator /=(ValueType const input) noexcept
        {
            (*s_Address) /= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator +=(ValueType const input) noexcept
        {
            (*s_Address) += input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator -=(ValueType const input) noexcept
        {
            (*s_Address) -= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator |=(ValueType const input) noexcept
        {
            (*s_Address) |= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator &=(ValueType const input) noexcept
        {
            (*s_Address) &= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator <<=(ValueType const input) noexcept
        {
            (*s_Address) <<= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator >>=(ValueType const input) noexcept
        {
            (*s_Address) >>= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator--() noexcept
        {
            --(*s_Address);
            return *this;
        }
        ALWAYS_INLINE 
        ValueType operator--(int) noexcept
        {
            auto retval = (*s_Address);
            --(*s_Address);
            return retval;
        }
        ALWAYS_INLINE 
        RawRegister & operator++() noexcept
        {
            ++(*s_Address);
            return *this;
        }
        ALWAYS_INLINE 
        ValueType operator++(int) noexcept
        {
            auto retval = (*s_Address);
            ++(*s_Address);
            return retval;
        }
        ALWAYS_INLINE 
        ValueType operator ~ () const noexcept
        {
            return ~(*s_Address);
        }
        ALWAYS_INLINE 
        ValueType operator - () const noexcept
        {
            return -(*s_Address);
        }
        ALWAYS_INLINE 
        ValueType operator + () const noexcept
        {
            return +(*s_Address);
        }
        ALWAYS_INLINE 
        ValueType operator ^ (ValueType const input) const noexcept
        {
            return (*s_Address) ^ input;
        }
        ALWAYS_INLINE 
        ValueType operator % (ValueType const input) const noexcept
        {
            return (*s_Address) % input;
        }
        ALWAYS_INLINE 
        ValueType operator & (ValueType const input) const noexcept
        {
            return (*s_Address) & input;
        }
        ALWAYS_INLINE 
        ValueType operator | (ValueType const input) const noexcept
        {
            return (*s_Address) | input;
        }
        ALWAYS_INLINE 
        ValueType operator + (ValueType const input) const noexcept
        {
            return (*s_Address) + input;
        }
        ALWAYS_INLINE 
        ValueType operator - (ValueType const input) const noexcept
        {
            return (*s_Address) - input;
        }
        ALWAYS_INLINE 
        ValueType operator * (ValueType const input) const noexcept
        {
            return (*s_Address) * input;
        }
        ALWAYS_INLINE 
        ValueType operator / (ValueType const input) const noexcept
        {
            return (*s_Address) / input;
        }
        ALWAYS_INLINE 
        ValueType operator << (ValueType const input) const noexcept
        {
            return (*s_Address) << input;
        }
        ALWAYS_INLINE 
        ValueType operator >> (ValueType const input) const noexcept
        {
            return (*s_Address) >> input;
        }
        ALWAYS_INLINE 
        bool operator ! () const noexcept
        {
            return !(*s_Address);
        }
        ALWAYS_INLINE 
        bool operator && (ValueType const input) const noexcept
        {
            return (*s_Address) && input;
        }
        ALWAYS_INLINE 
        bool operator || (ValueType const input) const noexcept
        {
            return (*s_Address) || input;
        }
        ALWAYS_INLINE
        bool operator == (ValueType const input) const noexcept
        {
            return (*s_Address) == input;
        }
        ALWAYS_INLINE 
        bool operator != (ValueType const input) const noexcept
        {
            return (*s_Address) != input;
        }
        ALWAYS_INLINE 
        bool operator < (ValueType const input) const noexcept
        {
            return (*s_Address) < input;
        }
        ALWAYS_INLINE 
        bool operator <= (ValueType const input) const noexcept
        {
            return (*s_Address) <= input;
        }
        ALWAYS_INLINE 
        bool operator > (ValueType const input) const noexcept
        {
            return (*s_Address) > input;
        }
        ALWAYS_INLINE 
        bool operator >= (ValueType const input) const noexcept
        {
            return (*s_Address) >= input;
        }

    private:
        inline static Pointer s_Address{ reinterpret_cast<Pointer>(tAddress) };

    };
}

template <uint32_t RegAddress>
using u32_reg_t = Common::RawRegister<uint32_t, RegAddress>;

template <uint32_t RegAddress>
using u16_reg_t = Common::RawRegister<uint16_t, RegAddress>;