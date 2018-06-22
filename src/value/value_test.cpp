#include "src/heap/arena.hpp"
#include "src/value/value.hpp"

#include "gtest/gtest.h"

#include <array>

using sk::heap::Arena;
using sk::value::Value;

TEST(ValueTest, EmptyValue)
{
    Arena heap(4096, 256);
    Value value = heap.allocate(nullptr, 0, 0);

    EXPECT_EQ(value.pointerCount(), 0u);
    EXPECT_EQ(value.byteCount(),    0u);
}

TEST(ValueTest, PairValue)
{
    Arena heap(4096, 256);

    Value firstValue  = heap.allocate(nullptr, 0, 0);
    Value secondValue = heap.allocate(nullptr, 0, 0);

    std::array<Value, 2> pairElements = {{firstValue, secondValue}};
    Value pairValue = heap.allocate(pairElements.data(), 2, 0);

    EXPECT_EQ(pairValue.pointerCount(), 2u);
    EXPECT_EQ(pairValue.byteCount(),    0u);
}
