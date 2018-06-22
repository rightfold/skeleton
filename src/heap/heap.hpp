#pragma once

#include "src/value/value.hpp"

#include <cstddef>

namespace sk::heap
{
    /**
     * A heap allocates memory for values and optionally collects garbage.
     */
    class Heap
    {
    public:
        virtual ~Heap();

        /**
         * Create a new value given a pointer count and a byte count on the
         * heap.
         */
        virtual value::Value allocate(
            value::Value* pointers,
            std::size_t pointerCount,
            std::size_t byteCount
        ) = 0;
    };
}
