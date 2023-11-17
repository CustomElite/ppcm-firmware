#pragma once

#include <array>
#include <cstddef>
#include <optional>

namespace Common::Containers 
{
    template <typename T, std::size_t N, bool Blind = false>
    class FIFO
    {
    public: 
        using value_type = T;

        static constexpr std::size_t Capacity = N;

        constexpr FIFO() noexcept = default;

        template <typename... Args>
        constexpr std::size_t Push(Args && ... args) noexcept
        {
            return (SinglePush(std::forward<Args>(args)) + ... );
        }

        [[nodiscard]]
        constexpr std::optional<T> Pop() noexcept
        {
            if (IsEmpty()) { return {}; }

            T retval = Front();
            IncrementTail();
            return retval;
        }

        constexpr void Clear() noexcept
        {
            m_head = m_tail = 0;
        }

        [[nodiscard]]
        constexpr value_type & Front() noexcept
        {
            return m_data[Index(m_tail)];
        }
        [[nodiscard]]
        constexpr value_type const & Front() const noexcept
        {
            return m_data[Index(m_tail)];
        }

        [[nodiscard]]
        constexpr value_type & Back() noexcept
        {
            return m_data[Index(m_head)];
        }
        [[nodiscard]]
        constexpr value_type const & Back() const noexcept
        {
            return m_data[Index(m_head)];
        }

        [[nodiscard]]
        constexpr std::size_t Size() const noexcept
        {
            return (m_head - m_tail);
        }
        [[nodiscard]]
        constexpr std::size_t Available() const noexcept
        {
            return (N - Size());
        }
        [[nodiscard]]
        constexpr bool IsEmpty() const noexcept
        {
            return (Size() == 0);
        }
        [[nodiscard]]
        constexpr bool IsFull() const noexcept
        {
            return (Size() == N);
        }

        [[nodiscard]]
        value_type & operator[](std::size_t index) noexcept
        {
            return m_data[Index(index + m_tail)];
        }
        [[nodiscard]]
        value_type const & operator[](std::size_t index) const noexcept
        {
            return m_data[Index(index + m_tail)];
        }

    protected:
        std::size_t m_head{ 0 };
        std::size_t m_tail{ 0 };
        std::array<T, N> m_data;

        constexpr void Wrap() noexcept
        {
            while ((m_head >= N) && (m_tail >= N))
            {
                m_head -= N;
                m_tail -= N;
            }
        }
        constexpr void IncrementHead() noexcept
        {
            ++m_head;
            Wrap();
        }
        constexpr void IncrementTail() noexcept
        {
            ++m_tail;
            Wrap();
        }
        [[nodiscard]]
        constexpr std::size_t Index(std::size_t input) noexcept
        {
            return (input % N);
        }
        constexpr std::size_t SinglePush(T const & input) noexcept
        {
            if (IsFull())
            {
                if constexpr (Blind == false) { return 0; }

                IncrementTail();
            }

            Back() = input;
            IncrementHead();
            return 1u;
        }
    };
}