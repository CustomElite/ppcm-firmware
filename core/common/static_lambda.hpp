#pragma once

#include <etl/power.h>
#include <utility>
#include <type_traits>
#include <array>
#include <cstdint>

namespace Common
{
    template <typename T, typename KEY = void>
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
        template <typename... ARGS>
        decltype(auto) operator()(ARGS && ... args) const noexcept
        {
            return Run(std::forward<ARGS>(args)...);
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
        template <typename... ARGS>
        static auto Run(ARGS && ... args) noexcept -> decltype(GetFunction()(std::forward<ARGS>(args)...))
        {
            if (s_dataPtr)
            {
                return GetFunction()(std::forward<ARGS>(args)...);
            }
            else {
                if constexpr(std::is_void_v<decltype(GetFunction()(std::forward<ARGS>(args)...))>)
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