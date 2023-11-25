#pragma once

#include <array>
#include <cstddef>
#include <optional>

namespace Common::Containers 
{
    template <typename T, size_t N, bool Blind = false>
    class FIFO
    {
    public: 
        using value_type = T;

        static constexpr size_t Capacity = N;
        static constexpr bool IsBlind = Blind;

        constexpr FIFO() noexcept = default;

        template <typename... Args>
        constexpr size_t Push(Args && ... args) noexcept
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
        constexpr size_t Size() const noexcept
        {
            return (m_head - m_tail);
        }
        [[nodiscard]]
        constexpr size_t Available() const noexcept
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
        value_type & operator[](size_t index) noexcept
        {
            return m_data[Index(index + m_tail)];
        }
        [[nodiscard]]
        value_type const & operator[](size_t index) const noexcept
        {
            return m_data[Index(index + m_tail)];
        }

    protected:
        size_t m_head{ 0 };
        size_t m_tail{ 0 };
        std::array<T, N> m_data{ 0 };

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
        constexpr size_t Index(size_t input) noexcept
        {
            return (input % N);
        }
        constexpr size_t SinglePush(T const & input) noexcept
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