#pragma once

#include <array>
#include <iterator>
#include <type_traits>

namespace Common::Containers
{
    static constexpr size_t dynamic_extent = size_t(-1);

    template <typename T, size_t tExtent = dynamic_extent>
    class Span
    {
    public:
        using value_type = T;

        using pointer = T*;
        using const_pointer = T const*;

        using reference = T&;
        using const_reference = T const&;

        using iterator = T*;
        using const_iterator = T const*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using size_type = size_t;
        using difference_type = ptrdiff_t;

        static constexpr auto extent{ tExtent };

        constexpr Span() noexcept = default;
        constexpr Span(Span const&) noexcept = default;
        constexpr Span(Span&&) noexcept = default;

        template <typename tIterator, typename tSize>
        constexpr explicit Span(tIterator const begin, tSize const) noexcept
            : m_begin{ std::addressof(*begin) }
        {}
        template <typename tIterator>
        constexpr explicit Span(tIterator const begin, tIterator const) noexcept
            : m_begin{ std::addressof(*begin) }
        {}
        template <size_t N>
        constexpr Span(value_type(&begin)[N]) noexcept
            : m_begin{ begin }
        {}
        template <typename tContainer, typename = std::enable_if_t<std::is_same_v<value_type, typename tContainer::value_type>, void>>
            constexpr Span(tContainer & input)
            : m_begin{ std::data(input) }
        {}
        template <typename U, size_t N, typename = std::enable_if_t<((N == extent) || (extent == dynamic_extent)), void>>
        constexpr Span(Span<U, N> const& rhs) noexcept
            : m_begin{ std::data(rhs) }
        {}
        [[nodiscard]]
        constexpr Span& operator = (Span const& rhs) noexcept
        {
            m_begin = rhs.m_begin;
            return *this;
        }
        [[nodiscard]]
        constexpr reference at(size_t idx) noexcept
        {
            return *(m_begin + std::min(idx, extent - 1u));
        }
        [[nodiscard]]
        constexpr reference operator[](size_t idx) noexcept
        {
            return *(m_begin + idx);
        }
        [[nodiscard]]
        constexpr reference front() noexcept
        {
            return *m_begin;
        }
        [[nodiscard]]
        constexpr reference back() noexcept
        {
            return *(m_begin + (extent - 1u));
        }
        [[nodiscard]]
        constexpr pointer data() noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator begin() noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator end() noexcept
        {
            return m_begin + extent;
        }
        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept
        {
            return m_begin + extent;
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() noexcept
        {
            return { end() };
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept
        {
            return { begin() };
        }
        [[nodiscard]]
        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return { end() };
        }
        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept
        {
            return { begin() };
        }
        [[nodiscard]]
        constexpr size_type size() const noexcept
        {
            return extent;
        }
        [[nodiscard]]
        constexpr size_type size_bytes() const noexcept
        {
            return sizeof(value_type) * extent;
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return ((!m_begin) || (size() == 0)) ? true : false;
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<value_type, tCount> first() const noexcept
        {
            static_assert(tCount <= extent, "Count cannot be greater than the span itself");
            return Span<value_type, tCount>{ m_begin, (m_begin + tCount) };
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> first(size_t count) const noexcept
        {
            return Span<value_type, dynamic_extent>{ m_begin, (m_begin + std::min(count, extent)) };
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<value_type, tCount> last() const noexcept
        {
            static_assert(tCount <= extent, "Count cannot be greater than the span itself");
            return Span<value_type, tCount>{ ((m_begin + extent) - tCount), (m_begin + extent) };
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> last(size_t count) const noexcept
        {
            return Span<value_type, dynamic_extent>{ ((m_begin + extent) - std::min(count, extent)), (m_begin + extent) };
        }
        template <size_t tOffset, size_t tCount = dynamic_extent>
        [[nodiscard]]
        constexpr std::conditional_t<(tCount != dynamic_extent), Span<value_type, tCount>, Span<value_type, (extent - tOffset)>>
            subspan() const noexcept
        {
            if constexpr (tCount != dynamic_extent)
            {
                static_assert((tOffset + tCount) <= extent, "Offset + Count cannot be greater than the span itself");
                return Span<value_type, tCount>{ (m_begin + tOffset), (m_begin + tOffset) + tCount };
            }
            else {
                static_assert(tOffset <= extent, "Offset cannot be greater than the span itself");
                return Span<value_type, (extent - tOffset)>{ (m_begin + tOffset), (m_begin + extent) };
            }
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> subspan(size_t offset, size_t count = dynamic_extent) const noexcept
        {
            return (count != dynamic_extent) 
                ? Span<value_type, dynamic_extent>{ (m_begin + std::min(offset, extent)), (m_begin + std::min((offset + count), extent)) }
                : Span<value_type, dynamic_extent>{ (m_begin + std::min(offset, extent)), (m_begin + extent) };
        }

    private:
        pointer m_begin{ nullptr };

    };

    template <typename T>
    class Span<T, dynamic_extent>
    {
    public:
        using value_type = T;

        using pointer = T*;
        using const_pointer = T const*;

        using reference = T&;
        using const_reference = T const&;

        using iterator = T*;
        using const_iterator = T const*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        using size_type = size_t;
        using difference_type = ptrdiff_t;

        static constexpr size_type extent = dynamic_extent;

        constexpr Span() noexcept = default;
        constexpr Span(Span const&) noexcept = default;
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
        constexpr Span(value_type(&input)[N]) noexcept
            : m_begin{ input }
            , m_end{ input + N }
        {}
        template <typename tContainer, typename = std::enable_if_t<std::is_same_v<value_type, typename tContainer::value_type>, void>>
        constexpr Span(tContainer & input)
            : m_begin{ std::data(input) }
            , m_end{ std::data(input) + std::size(input) }
        {}
        template <typename U, size_t N>
        constexpr Span(Span<U, N> const& rhs) noexcept
            : m_begin{ std::data(rhs) }
            , m_end{ std::data(rhs) + N }
        {}

        constexpr Span& operator = (Span const& rhs) noexcept
        {
            m_begin = rhs.m_begin;
            m_end = rhs.m_end;
            return *this;
        }
        constexpr reference operator[](size_t idx) noexcept
        {
            return *(m_begin + idx);
        }
        [[nodiscard]]
        constexpr reference at(size_t idx) noexcept
        {
            return *(m_begin + std::min(idx, extent - 1u));
        }
        [[nodiscard]]
        constexpr reference front() noexcept
        {
            return *m_begin;
        }
        [[nodiscard]]
        constexpr reference back() noexcept
        {
            return *(m_end - 1u);
        }
        [[nodiscard]]
        constexpr pointer data() noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator begin() noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr iterator end() noexcept
        {
            return m_end;
        }
        [[nodiscard]]
        constexpr const_iterator cbegin() const noexcept
        {
            return m_begin;
        }
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept
        {
            return m_end;
        }
        [[nodiscard]]
        constexpr reverse_iterator rbegin() noexcept
        {
            return reverse_iterator{ m_end };
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept
        {
            return reverse_iterator{ m_begin };
        }
        [[nodiscard]]
        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return const_reverse_iterator{ m_end };
        }
        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept
        {
            return const_reverse_iterator{ m_begin };
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept
        {
            return (size() == 0);
        }
        [[nodiscard]]
        constexpr size_type size() const noexcept
        {
            return (m_end - m_begin);//std::distance(m_begin, m_end);
        }
        [[nodiscard]]
        constexpr size_type size_bytes() const noexcept
        {
            return sizeof(value_type) * size();
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> first() const noexcept
        {
            return Span<value_type, dynamic_extent>{ m_begin, (m_begin + std::min(tCount, size())) };
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> first(size_t count) const noexcept
        {
            return Span<value_type, dynamic_extent>{ m_begin, (m_begin + std::min(count, size())) };
        }
        template <size_t tCount>
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> last() const noexcept
        {
            return Span<value_type, dynamic_extent>{ (m_end - std::min(tCount, size())), m_end };
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> last(size_t count) const noexcept
        {
            return Span<value_type, dynamic_extent>{ (m_end - std::min(count, size())), m_end };
        }
        template <size_t tOffset, size_t tCount = dynamic_extent>
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> subspan() const noexcept
        {
            return (tCount != dynamic_extent)
                ? Span<value_type, dynamic_extent>{ (m_begin + std::min(tOffset, size())), m_begin + std::min((tOffset + tCount), size()) }
                : Span<value_type, dynamic_extent>{ (m_begin + std::min(tOffset, size())), m_end };
        }
        [[nodiscard]]
        constexpr Span<value_type, dynamic_extent> subspan(size_t offset, size_t count = dynamic_extent) const noexcept
        {
            return (count != dynamic_extent)
                ? Span<value_type, dynamic_extent>{ (m_begin + std::min(offset, size())), m_begin + std::min((offset + count), size()) }
                : Span<value_type, dynamic_extent>{ (m_begin + std::min(offset, size())), m_end };
        }

    private:
        pointer m_begin{ nullptr };
        pointer m_end{ nullptr };
    };

    template <typename T1, size_t N1, typename T2, size_t N2>
    [[nodiscard]]
    constexpr std::enable_if_t<std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>, bool>
        operator == (Span<T1, N1> const& lhs, Span<T2, N2> const& rhs) noexcept
    {
        return ((lhs.begin() == rhs.begin()) && (lhs.size() == rhs.size()));
    }

    template <typename T1, size_t N1, typename T2, size_t N2>
    [[nodiscard]]
    constexpr bool operator != (Span<T1, N1> const& lhs, Span<T2, N2> const& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename T1, size_t N1, typename T2, size_t N2>
    constexpr std::enable_if_t<std::is_same_v<std::remove_cv_t<T1>, std::remove_cv_t<T2>>, bool>
        equal(Span<T1, N1> const& lhs, Span<T2, N2> const& rhs) noexcept
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
    Span(std::array<T, N> const&) -> Span<T const, N>;
}