#pragma once

#include <cstddef>

namespace Common
{
    template <typename T>
    struct RunOnce
    {
    public:
        RunOnce() noexcept
        {
            if (Construct()) { T::Construct(); }
        }
        ~RunOnce() noexcept
        {
            if (Destruct()) { T::Destruct(); }
        }

    private:
        inline static size_t s_count = 0;

        static bool Construct() noexcept
        {
            bool const retval = (s_count++ == 0);
            return retval;
        }
        static bool Destruct() noexcept
        {
            return (--s_count == 0);
        }
    };
}