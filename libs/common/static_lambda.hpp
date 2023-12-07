#pragma once

#include <utility>
#include <type_traits>
#include <array>
#include <cstdint>

namespace Common
{
    template <typename T, typename tKey = void>
    class StaticLambda
    {
    public:
        using buffer_t = uint8_t[sizeof(std::decay_t<T>)];

        StaticLambda() = default;

        StaticLambda(T && function) noexcept
        {
            Construct(std::forward<T>(function));
        }
        StaticLambda & operator = (T && function) const noexcept
        {
            Construct(std::forward<T>(function));
            return *this;
        }
        template <typename... tArgs>
        decltype(auto) operator()(tArgs && ... args) const noexcept
        {
            return Run(std::forward<tArgs>(args)...);
        }

    private:
        inline static buffer_t s_data;
        inline static T * volatile s_dataPtr{nullptr};

        static T & GetFunction() noexcept
        {
            return *s_dataPtr;
        }
        static void Destruct() noexcept
        {
            if (s_dataPtr)
            {
                ((T*)s_data) -> ~T();
                s_dataPtr = nullptr;
            }
        }
        static void Construct(T && function) noexcept
        {
            Destruct();
            ::new(s_data) T{ std::move(function) };
            s_dataPtr = (T*)&s_data[0];
        }

    public:
        template <typename... tArgs>
        static auto Run(tArgs && ... args) noexcept -> decltype(GetFunction()(std::forward<tArgs>(args)...))
        {
            if (s_dataPtr)
            {
                return GetFunction()(std::forward<tArgs>(args)...);
            }
            else 
            {
                if constexpr(std::is_void_v<decltype(GetFunction()(std::forward<tArgs>(args)...))>)
                {
                    return;
                }
                else {
                    return {};
                }
            }
        }
    };

    template <typename T>
    StaticLambda(T &&) -> StaticLambda<std::decay_t<T>>;
}