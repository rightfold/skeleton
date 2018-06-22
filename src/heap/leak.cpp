#include "src/heap/leak.hpp"
#include "src/value/value.hpp"

#include <cstddef>
#include <cstdlib>

using sk::value::Value;

namespace sk::heap
{
    Value Leak::allocate(
        Value* pointers,
        std::size_t pointerCount,
        std::size_t byteCount
    )
    {
        std::size_t size = Value::size(pointerCount, byteCount);
        void* memory = std::malloc(size);
        return Value(memory, pointers, pointerCount, byteCount);
    }
}
