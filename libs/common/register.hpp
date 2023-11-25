#pragma once

#include "macros.h"

#include <cstdint>
#include <cstddef>

namespace Common 
{
    template <typename T, uint32_t ADDR, T BITMASK>
    class Bitfield
    {
    public:
        using type = T;
        using pointer = T volatile * const;

        ALWAYS_INLINE 
        void Clear() noexcept
        {
            (*Address) &= nBitmask;
        }
        ALWAYS_INLINE 
        void Set(type const input) noexcept
        {
            (*Address) = (*Address & nBitmask) | apply_mask(input);
        }
        ALWAYS_INLINE 
        void Toggle(type const input) noexcept
        {
            (*Address) ^= apply_mask(input);
        }
        ALWAYS_INLINE 
        type Read() const noexcept
        {
            return (((*Address) & Bitmask) >> BitPosition);
        }
        ALWAYS_INLINE 
        Bitfield & operator = (type const rhs) noexcept
        {
            Set(rhs);
            return *this;
        }
        ALWAYS_INLINE 
        operator type() const noexcept
        {
            return Read();
        }
        ALWAYS_INLINE 
        Bitfield & operator |= (type rhs) noexcept
        {
            (*Address) |= apply_mask(rhs);
            return *this;
        }
        ALWAYS_INLINE 
        Bitfield & operator &= (type rhs) noexcept
        {
            (*Address) &= (apply_mask(rhs) | nBitmask);
            return *this;
        }

    private:
        static constexpr auto get_position() noexcept
        {
            type start{ 0 };
            type mask{ BITMASK };

            while((mask & 1) == 0)
            {
                ++start;
                mask >>= 1;
            }

            return start;
        }
        static auto apply_mask(type input) noexcept
        {
            return ((input << BitPosition) & Bitmask);
        }

        static constexpr type Bitmask = BITMASK;
        static constexpr type nBitmask = (~Bitmask);
        static constexpr type BitPosition = get_position();

        inline static pointer Address = reinterpret_cast<pointer>(ADDR);
    };

    template <typename T, uint32_t ADDR>
    struct RawRegister
    {
        using type = T;
        using pointer = T volatile * const;

        constexpr RawRegister() = default;

        inline static pointer s_addr = reinterpret_cast<pointer>(ADDR);

        ALWAYS_INLINE 
        void Write(type input) noexcept
        {
            (*s_addr) = input;
        }
        ALWAYS_INLINE 
        type Read() const noexcept
        {
            return *s_addr;
        }
        ALWAYS_INLINE 
        RawRegister & Access() noexcept
        {
            return *this;
        }
        template <type MASK>
        ALWAYS_INLINE 
        Bitfield<T, ADDR, MASK> GetBitfield() const noexcept
        {
            return {};
        }
        ALWAYS_INLINE 
        RawRegister & operator = (type const & input) noexcept
        {
            (*s_addr) = input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator %= (type const & input) noexcept
        {
            (*s_addr) %= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator ^= (type const & input) noexcept
        {
            (*s_addr) ^= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator *= (type const & input) noexcept
        {
            (*s_addr) *= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator /= (type const & input) noexcept
        {
            (*s_addr) /= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator += (type const & input) noexcept
        {
            (*s_addr) += input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator -= (type const & input) noexcept
        {
            (*s_addr) -= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator |= (type const & input) noexcept
        {
            (*s_addr) |= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator &= (type const & input) noexcept
        {
            (*s_addr) &= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator <<= (type const & input) noexcept
        {
            (*s_addr) <<= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator >>= (type const & input) noexcept
        {
            (*s_addr) >>= input;
            return *this;
        }
        ALWAYS_INLINE 
        RawRegister & operator--() noexcept
        {
            --(*s_addr);
            return *this;
        }
        ALWAYS_INLINE 
        type operator--(int) noexcept
        {
            auto retval = (*s_addr);
            --(*s_addr);
            return retval;
        }
        ALWAYS_INLINE 
        RawRegister & operator++() noexcept
        {
            ++(*s_addr);
            return *this;
        }
        ALWAYS_INLINE 
        type operator++(int) noexcept
        {
            auto retval = (*s_addr);
            ++(*s_addr);
            return retval;
        }
        ALWAYS_INLINE 
        type operator ~ () const noexcept
        {
            return ~(*s_addr);
        }
        ALWAYS_INLINE 
        type operator - () const noexcept
        {
            return -(*s_addr);
        }
        ALWAYS_INLINE 
        type operator + () const noexcept
        {
            return +(*s_addr);
        }
        ALWAYS_INLINE 
        type operator ^ (type const & input) const noexcept
        {
            return (*s_addr) ^ input;
        }
        ALWAYS_INLINE 
        type operator % (type const & input) const noexcept
        {
            return (*s_addr) % input;
        }
        ALWAYS_INLINE 
        type operator & (type const & input) const noexcept
        {
            return (*s_addr) & input;
        }
        ALWAYS_INLINE 
        type operator | (type const & input) const noexcept
        {
            return (*s_addr) | input;
        }
        ALWAYS_INLINE 
        type operator + (type const & input) const noexcept
        {
            return (*s_addr) + input;
        }
        ALWAYS_INLINE 
        type operator - (type const & input) const noexcept
        {
            return (*s_addr) - input;
        }
        ALWAYS_INLINE 
        type operator * (type const & input) const noexcept
        {
            return (*s_addr) * input;
        }
        ALWAYS_INLINE 
        type operator / (type const & input) const noexcept
        {
            return (*s_addr) / input;
        }
        ALWAYS_INLINE 
        type operator << (type const & input) const noexcept
        {
            return (*s_addr) << input;
        }
        ALWAYS_INLINE 
        type operator >> (type const & input) const noexcept
        {
            return (*s_addr) >> input;
        }
        ALWAYS_INLINE 
        bool operator ! () const noexcept
        {
            return !(*s_addr);
        }
        ALWAYS_INLINE 
        bool operator && (type const & input) const noexcept
        {
            return (*s_addr) && input;
        }
        ALWAYS_INLINE 
        bool operator || (type const & input) const noexcept
        {
            return (*s_addr) || input;
        }
        ALWAYS_INLINE 
        bool operator == (type const & input) const noexcept
        {
            return (*s_addr) == input;
        }
        ALWAYS_INLINE 
        bool operator != (type const & input) const noexcept
        {
            return (*s_addr) != input;
        }
        ALWAYS_INLINE 
        bool operator < (type const & input) const noexcept
        {
            return (*s_addr) < input;
        }
        ALWAYS_INLINE 
        bool operator <= (type const & input) const noexcept
        {
            return (*s_addr) <= input;
        }
        ALWAYS_INLINE 
        bool operator > (type const & input) const noexcept
        {
            return (*s_addr) > input;
        }
        ALWAYS_INLINE 
        bool operator >= (type const & input) const noexcept
        {
            return (*s_addr) >= input;
        }
    };
}

template <uint32_t RegAddress>
using u32_reg_t = Common::RawRegister<uint32_t, RegAddress>;

template <uint32_t RegAddress>
using u16_reg_t = Common::RawRegister<uint16_t, RegAddress>;