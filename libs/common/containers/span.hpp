#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <type_traits>

namespace Common::Containers 
{
    constexpr size_t dynamic_extent = std::integral_constant<size_t, size_t(-1)>::value;
    
    template <typename T, size_t Extent = dynamic_extent>
    class Span
    {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;
        using size_type = size_t;

        using pointer = T*;
        using const_pointer = T const *;

        using reference = T&;
        using const_reference = T const &;

        using iterator = T*;
        using reverse_iterator = std::reverse_iterator<iterator>;

        constexpr Span() noexcept = default;
        constexpr Span(Span const &) noexcept = default;
        constexpr Span(Span &&) noexcept = default;

        template <typename tIterator>
        constexpr explicit Span(tIterator const begin, tIterator const) noexcept
            : m_begin{ std::addressof(*begin) }
        {}
        template <typename tIterator, typename tSize>
        constexpr explicit Span(tIterator const begin, tSize const) noexcept
            : m_begin{ std::addressof(*begin) }
        {}
        template <size_t N>
        constexpr Span(element_type(&begin)[N]) noexcept
            : m_begin{ begin }
        {}
        template <typename tContainer, typename = std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<tContainer>>
                                                                && !std::is_array_v<std::remove_reference_t<tContainer>>
                                                                &&  std::is_same_v<value_type, typename std::remove_cv_t<std::remove_reference_t<tContainer>>::value_type>, void>>
        constexpr Span(tContainer && input)
            : m_begin{ input.data() }
        {}
        template <typename U, size_t N>
        constexpr Span(Span<U, N> const & rhs, std::enable_if_t<(Extent == dynamic_extent) || (N == dynamic_extent) || (N == Extent), void>) noexcept
            : m_begin{ rhs.data() }
        {}

        [[nodiscard]]
        constexpr reference front() const noexcept
        {
            return *m_begin;
        }
        [[nodiscard]]
        constexpr reference back() const noexcept
        {
            return *((m_begin + Extent) - 1u);
        }
        [[nodiscard]]
        constexpr pointer data() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator begin() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator end() const noexcept
        {
            return (m_begin + Extent);
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator{ (m_begin + Extent) };
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() const noexcept
        {
            return reverse_iterator{ m_begin };
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return (!m_begin) ? true : false;
        }
        [[nodiscard]]
        constexpr size_type size() const noexcept
        {
            return Extent;
        }
        [[nodiscard]]
        constexpr size_type size_bytes() const noexcept
        {
            return sizeof(element_type) * Extent;
        }
        [[nodiscard]]
        constexpr Span& operator = (Span const & rhs) noexcept
        {
            m_begin = rhs.m_begin;
            return *this;
        }
        [[nodiscard]]
        constexpr reference operator[](size_t const index) const noexcept
        {
            return m_begin[index];
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<element_type, tCount> first() const noexcept
        {
            return Span<element_type, tCount>{ m_begin, (m_begin + tCount) };
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> first(size_t const count) const noexcept
        {
            return Span<element_type, dynamic_extent>{ m_begin, (m_begin + count) };
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<element_type, tCount> last() const noexcept
        {
            return Span<element_type, tCount>{ ((m_begin + Extent) - tCount), (m_begin + Extent) };
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> last(size_t const count) const noexcept
        {
            return Span<element_type, dynamic_extent>{ ((m_begin + Extent) - count), (m_begin + Extent) };
        }
        template <size_t tOffset, size_t tCount = dynamic_extent>
        [[nodiscard]]
        constexpr Span<element_type, tCount != dynamic_extent ? tCount : (Extent - tOffset)> subspan() const noexcept
        {
            return (tCount != dynamic_extent) ? Span<element_type, tCount>((m_begin + tOffset), (m_begin + tOffset) + tCount)
                                              : Span<element_type, (Extent - tOffset)>((m_begin + tOffset), (m_begin + Extent));
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> subspan(size_t const offset, size_t const count = dynamic_extent) const noexcept
        {
            return (count != dynamic_extent) ? Span<element_type, dynamic_extent>((m_begin + offset), (m_begin + offset) + count)
                                             : Span<element_type, dynamic_extent>((m_begin + offset), (m_begin + Extent));
        }

    private:
        pointer m_begin{ nullptr };

    };

    template <typename T>
    class Span<T, dynamic_extent>
    {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;
        using size_type = size_t;
        
        using pointer = T*;
        using const_pointer = T const *;

        using reference = T&;
        using const_reference = T const &;

        using iterator = T*;
        using reverse_iterator = std::reverse_iterator<iterator>;

        static constexpr size_type Extent = dynamic_extent;

        constexpr Span() noexcept = default;
        constexpr Span(Span const &) noexcept = default;
        constexpr Span(Span&&) noexcept = default;

        template <typename tIterator, typename tSize>
        constexpr Span(tIterator const begin, tSize const size) noexcept
            : m_begin{ std::addressof(*begin) }
            , m_end{ std::addressof(*begin) + size }
        {}
        template <typename tIterator>
        constexpr Span(tIterator const begin, tIterator const end) noexcept
            : m_begin{ std::addressof(*begin) }
            , m_end{ std::addressof(*begin) + std::distance(begin, end) }
        {}
        template <size_t N>
        constexpr Span(element_type(&input)[N]) noexcept
            : m_begin{ input }
            , m_end{ input + N }
        {}
        template <typename tContainer, typename = std::enable_if_t<!std::is_pointer_v<std::remove_reference_t<tContainer>>
                                                                && !std::is_array_v<std::remove_reference_t<tContainer>>
                                                                &&  std::is_same_v<value_type, typename std::remove_cv_t<std::remove_reference_t<tContainer>>::value_type>, void>>
        constexpr Span(tContainer&& input)
            : m_begin{ input.data() }
            , m_end{ input.data() + input.size() }
        {}
        template <typename U, size_t N>
        constexpr Span(Span<U, N> const & rhs) noexcept
            : m_begin{ rhs.data() }
            , m_end{ rhs.data() + rhs.size() }
        {}

        constexpr Span& operator = (Span const & rhs) noexcept
        {
            m_begin = rhs.m_begin;
            m_end = rhs.m_end;
            return *this;
        }
        constexpr reference operator[](size_t const index) noexcept
        {
            return m_begin[index];
        }

        [[nodiscard]]
        constexpr reference front() const noexcept
        {
            return *m_begin;
        }
        [[nodiscard]]
        constexpr reference back() const noexcept
        {
            return *(m_end - 1u);
        }
        [[nodiscard]]
        constexpr pointer data() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator begin() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator end() const noexcept
        {
            return m_end;
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() const noexcept
        {
            return reverse_iterator{ m_end };
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() const noexcept
        {
            return reverse_iterator{ m_begin };
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return (m_begin == m_end);
        }
        [[nodiscard]]
        constexpr size_type size() const noexcept
        {
            return (m_end - m_begin);
        }
        [[nodiscard]]
        constexpr size_type size_bytes() const noexcept
        {
            return sizeof(element_type) * size();
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<element_type, tCount> first() const noexcept
        {
            return Span<element_type, tCount>{ m_begin, (m_begin + tCount) };
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> first(size_t const count) const noexcept
        {
            return Span<element_type, dynamic_extent>{ m_begin, (m_begin + count) };
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<element_type, tCount> last() const noexcept
        {
            return Span<element_type, tCount>{ (m_end - tCount), m_end };
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> last(size_t const count) const noexcept
        {
            return Span<element_type, dynamic_extent>{ (m_end - count), m_end };
        }
        template <size_t tOffset, size_t tCount = dynamic_extent>
        [[nodiscard]]
        constexpr Span<element_type, tCount> subspan() const noexcept
        {
            return (tCount != dynamic_extent) ? Span<element_type, tCount>{ (m_begin + tOffset), ((m_begin + tOffset) + tCount) }
                                              : Span<element_type, dynamic_extent>{ (m_begin + tOffset), m_end };
        }
        [[nodiscard]]
        constexpr Span<element_type, dynamic_extent> subspan(size_t const offset, size_t const count = dynamic_extent) const noexcept
        {
            return (count != dynamic_extent) ? Span<element_type, dynamic_extent>{ (m_begin + offset), ((m_begin + offset) + count) }
                                             : Span<element_type, dynamic_extent>{ (m_begin + offset), m_end };
        }

    private:
        pointer m_begin{ nullptr };
        pointer m_end{ nullptr };
    };

    template <typename T1, size_t N1, typename T2, size_t N2>
    [[nodiscard]]
    constexpr std::enable_if_t<std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>, bool>
    operator == (Span<T1, N1> const & lhs, Span<T2, N2> const & rhs) noexcept
    {
        return ((lhs.begin() == rhs.begin()) && (lhs.size() == rhs.size()));
    }

    template <typename T1, size_t N1, typename T2, size_t N2>
    [[nodiscard]]
    constexpr bool operator != (Span<T1, N1> const & lhs, Span<T2, N2> const & rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T1, size_t N1, typename T2, size_t N2>
    constexpr std::enable_if_t<std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>, bool>
    equal(Span<T1, N1> const & lhs, Span<T2, N2> const & rhs) noexcept
    {
        return ((lhs.empty() && rhs.empty())
            || ((lhs.begin() == rhs.begin()) && (lhs.size() == rhs.size()))
            || std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <typename tIterator>
    Span(tIterator const, tIterator const) -> Span<std::remove_pointer_t<tIterator>, dynamic_extent>;
    template <typename tIterator, typename tSize>
    Span(tIterator const, tSize const) -> Span<std::remove_pointer_t<tIterator>, dynamic_extent>;
    template <typename T, size_t N>
    Span(T(&)[N]) -> Span<T, N>;
    template <typename T, size_t N>
    Span(std::array<T, N>&) -> Span<T, N>;
    template <typename T, size_t N>
    Span(std::array<T, N> const &) -> Span<T const, N>;
}