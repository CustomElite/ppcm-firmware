#pragma once

#include <array>
#include <cstddef>
#include <optional>

namespace Common::Containers 
{
    template <typename T, size_t N>
    class RingBuffer
    {
    public:
        using ValueType = T;
        using Pointer = T*;
        using Reference = T&;
        using ConstReference = T const &;
        using SizeType = size_t;

        constexpr RingBuffer() noexcept = default;

        [[nodiscard]]
        Reference operator[](SizeType offset) noexcept
        {
            return m_Buffer[wrap(m_Read + offset)];
        }

        template <typename... tArgs>
        constexpr SizeType Push(tArgs && ... args) noexcept
        {
            return (push_impl(std::forward<tArgs>(args)) + ... );
        }
        constexpr std::optional<ValueType> Pop() noexcept
        {
            if (Empty()) { return {}; }

            ValueType retval = Front();
            increment_read();
            return retval;
        }
        constexpr void Clear() noexcept
        {
            m_Write = m_Read = 0;
        }
        [[nodiscard]]
        constexpr Reference Front() noexcept
        {
            return m_Buffer[m_Read];
        }
        [[nodiscard]]
        constexpr Reference Back() noexcept
        {
            return m_Buffer[(m_Write == 0) ? MaxSize : m_Write - 1u];
        }
        [[nodiscard]]
        constexpr size_t Capacity() const noexcept
        {
            return MaxSize;
        }
        [[nodiscard]]
        constexpr SizeType Size() const noexcept
        {
            return (m_Write >= m_Read) ? m_Write - m_Read : BufferSize - (m_Read - m_Write);
        }
        [[nodiscard]]
        constexpr size_t Available() const noexcept
        {
            return MaxSize - Size();
        }
        [[nodiscard]]
        constexpr bool Empty() const noexcept
        {
            return m_Read == m_Write;
        }
        [[nodiscard]]
        constexpr bool Full() const noexcept
        {
            return Size() == MaxSize;
        }
        [[nodiscard]]
        constexpr operator bool() const noexcept
        {
            return !Empty();
        }

    private:
        static constexpr SizeType BufferSize = N + 1;
        static constexpr SizeType MaxSize = N;

        constexpr void increment_write() noexcept
        {
            m_Write = wrap(m_Write + 1u);
        }
        constexpr void increment_read() noexcept
        {
            m_Read = wrap(m_Read + 1u);
        }
        [[nodiscard]]
        constexpr SizeType wrap(SizeType input) const noexcept
        {
            return (input % BufferSize);
        }
        constexpr SizeType push_impl(ConstReference input) noexcept
        {
            m_Buffer[m_Write] = input;
            increment_write();

            if (m_Write == m_Read) { increment_read(); }

            return 1u;
        }

    private:
        SizeType m_Write{ 0 };
        SizeType m_Read{ 0 };
        std::array<T, BufferSize> m_Buffer{};
    };
}