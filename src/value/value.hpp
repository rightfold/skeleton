#pragma once

#include <cstddef>

namespace sk::value
{
    /**
     * A value consists of an array of pointers and an array of bytes. Pointers
     * point to other values on the same heap. Bytes can be arbitrary data.
     */
    class Value
    {
    public:
        /**
         * Create a null value. This should never be seen by a program, but is
         * used for uninitialized variables.
         */
        Value();

        /**
         * Create a value given memory. The memory will be initialized
         * according to the other parameters.
         */
        Value(
            void* memory,
            Value* pointers,
            std::size_t pointerCount,
            std::size_t byteCount
        );

        /**
         * Check if the value is not null.
         */
        explicit operator bool() const;

        /**
         * These functions access the data inside the value.
         */
        std::size_t  pointerCount () const;
        std::size_t  byteCount    () const;
        Value const* pointerArray () const;
        char*        byteArray    () const;

        /**
         * Given a pointer count and a byte count, compute how much memory is
         * needed for the value.
         */
        static std::size_t size(
            std::size_t pointerCount,
            std::size_t byteCount
        );

    private:
        /**
         * These functions return pointers to non-const, and are used in both
         * the constructor and the accessors.
         */
        std::size_t* pointerCountMem () const;
        std::size_t* byteCountMem    () const;
        Value*       pointerArrayMem () const;
        char*        byteArrayMem    () const;

        void* memory;

        friend bool operator==(Value, Value) noexcept;
    };

    /**
     * Check that two values are at the same address or are both the null
     * value.
     */
    bool operator==(Value a, Value b) noexcept;

    /**
     * Check that two values are not at the same address or are not both the
     * null value.
     */
    bool operator!=(Value a, Value b) noexcept;
}
