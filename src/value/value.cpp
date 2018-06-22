#include "src/value/value.hpp"

#include <algorithm>
#include <cstddef>

using sk::value::Value;

// A value consists of four data items: the pointer count, the byte count, the
// pointer array, and the byte array. There is no padding.
//
// The Value constructor initializes these data items, except for the byte
// array which is left uninitialized. The getters likewise respect this layout.
//
// Since C++ lacks flexible arrays and in particular consecutive flexible
// arrays, we cannot use a normal struct for expressing this layout.

namespace
{
    std::size_t constexpr sizeSize    = sizeof(std::size_t);
    std::size_t constexpr pointerSize = sizeof(void*);
}

namespace sk::value
{
    Value::Value()
        : memory(nullptr)
    {
    }

    Value::Value(
        void* memory,
        Value* pointers,
        std::size_t pointerCount,
        std::size_t byteCount
    )
    {
        this->memory = memory;

        *pointerCountMem() = pointerCount;
        *byteCountMem()    = byteCount;
        std::copy_n(pointers, pointerCount, pointerArrayMem());
    }

    Value::operator bool() const
    {
        return memory;
    }

    std::size_t  Value::pointerCount () const { return *pointerCountMem (); }
    std::size_t  Value::byteCount    () const { return *byteCountMem    (); }
    Value const* Value::pointerArray () const { return  pointerArrayMem (); }
    char*        Value::byteArray    () const { return  byteArrayMem    (); }

    std::size_t Value::size(std::size_t pointerCount, std::size_t byteCount)
    {
        return sizeSize + sizeSize + pointerCount * pointerSize + byteCount;
    }

#define SK_PTR(type, name, offset)                                          \
    type* Value::name() const                                               \
    {                                                                       \
        auto valueMem = static_cast<char*>(memory);                         \
        return reinterpret_cast<type*>(valueMem + (offset));                \
    }
    SK_PTR(std::size_t, pointerCountMem,  0)
    SK_PTR(std::size_t, byteCountMem,    sizeSize)
    SK_PTR(Value,       pointerArrayMem, sizeSize + sizeSize)
    SK_PTR(char,        byteArrayMem,    sizeSize + sizeSize +
                                         pointerCount() * pointerSize)
#undef SK_PTR

    bool operator==(Value a, Value b) noexcept
    {
        return a.memory == b.memory;
    }

    bool operator!=(Value a, Value b) noexcept
    {
        return !operator==(a, b);
    }
}
