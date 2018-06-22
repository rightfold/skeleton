#pragma once

#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <cstddef>

namespace sk::heap
{
    /**
     * The leak heap allocates memory but never collects garbage. Everything
     * allocated will be leaked.
     */
    class Leak : public Heap
    {
    public:
        value::Value allocate(
            value::Value* pointers,
            std::size_t pointerCount,
            std::size_t byteCount
        ) override;
    };
}
