#pragma once

#include <array>
#include <cstddef>
#include <iterator>
#include <optional>
#include <type_traits>

namespace Common::Containers 
{
    template <typename T, size_t N, bool Circular = false>
    class FIFO
    {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;

        using pointer = T*;
        using const_pointer = T const *;

        using reference = T&;
        using const_reference = T const &;

        constexpr FIFO() noexcept = default;
        constexpr FIFO(element_type const initial_value) noexcept
            : m_data{ initial_value }
        {}

        template <typename... tArgs>
        constexpr size_t push(tArgs && ... args) noexcept
        {
            return (push_impl(std::forward<tArgs>(args)) + ... );
        }
        [[nodiscard]]
        constexpr std::optional<value_type> pop() noexcept
        {
            if (empty()) { return {}; }

            value_type retval = front();
            increment_tail();
            return retval;
        }
        constexpr void clear() noexcept
        {
            m_head = m_tail = 0;
        }
        [[nodiscard]]
        constexpr reference front() noexcept
        {
            return m_data[index(m_tail)];
        }
        [[nodiscard]]
        constexpr const_reference front() const noexcept
        {
            return m_data[index(m_tail)];
        }
        [[nodiscard]]
        constexpr reference back() noexcept
        {
            return m_data[index(m_head)];
        }
        [[nodiscard]]
        constexpr const_reference back() const noexcept
        {
            return m_data[index(m_head)];
        }
        [[nodiscard]]
        constexpr pointer data() noexcept
        {
            return m_data.data();
        }
        [[nodiscard]]
        constexpr size_t size() const noexcept
        {
            return N;
        }
        [[nodiscard]]
        constexpr size_t available() const noexcept
        {
            return (m_head - m_tail);
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return (available() == 0);
        }
        [[nodiscard]]
        constexpr bool full() const noexcept
        {
            return (available() == N);
        }
        [[nodiscard]]
        constexpr operator bool() noexcept
        {
            return !empty();
        }
        [[nodiscard]]
        reference operator[](size_t const idx) noexcept
        {
            return m_data[index(idx + m_tail)];
        }

    protected:
        size_t m_head{ 0 };
        size_t m_tail{ 0 };
        std::array<T, N> m_data{};

        constexpr void wrap() noexcept
        {
            while ((m_head >= N) && (m_tail >= N))
            {
                m_head -= N;
                m_tail -= N;
            }
        }
        constexpr void increment_head() noexcept
        {
            ++m_head;
            wrap();
        }
        constexpr void increment_tail() noexcept
        {
            ++m_tail;
            wrap();
        }
        [[nodiscard]]
        constexpr size_t index(size_t const input) noexcept
        {
            return (input % N);
        }
        constexpr size_t push_impl(T const & input) noexcept
        {
            if (full())
            {
                if constexpr (Circular == false) { return 0; }

                increment_tail();
            }

            back() = input;
            increment_head();
            return 1u;
        }
    };
}