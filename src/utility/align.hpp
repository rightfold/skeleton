#pragma once

#include <cassert>
#include <type_traits>

namespace sk::utility
{
    /**
     * Round an unsigned number up to a power of two.
     */
    template<typename T>
    T alignUp(T n, T a);

    template<typename T>
    T alignUp(T n, T a)
    {
        static_assert(std::is_unsigned<T>());
        assert((a & (a - 1)) == 0);
        return (n + a - 1) & ~(a - 1);
    }
}
