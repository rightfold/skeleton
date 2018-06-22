#include "src/heap/arena.hpp"
#include "src/value/value.hpp"
#include "src/utility/align.hpp"
#include "src/utility/likely.hpp"

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

using sk::value::Value;

namespace
{
    std::unique_ptr<char[]> makePage(std::size_t pageSize)
    {
        return std::unique_ptr<char[]>(new char[pageSize]);
    }
}

namespace sk::heap
{
    Arena::Arena(std::size_t pageSize, std::size_t singletonThreshold)
        : currentPage(0)
        , currentOffset(0)
        , pageSize(pageSize)
        , singletonThreshold(singletonThreshold)
    {
        assert(pageSize >= singletonThreshold);
        normalPages.push_back(makePage(pageSize));
    }

    Value Arena::allocate(
        Value* pointers,
        std::size_t pointerCount,
        std::size_t byteCount
    )
    {
        std::size_t size = Value::size(pointerCount, byteCount);
        void* memory = findMemory(size);
        Value value(memory, pointers, pointerCount, byteCount);
        return value;
    }

    void* Arena::findMemory(std::size_t size)
    {
        size = sk::utility::alignUp(size, alignof(Value));

        if (SK_UNLIKELY(size >= singletonThreshold))
        {
            auto page = makePage(size);
            void* memory = page.get();
            singletonPages.push_back(std::move(page));
            return memory;
        }
        else if (SK_UNLIKELY(currentOffset + size >= pageSize))
        {
            auto page = makePage(pageSize);
            void* memory = page.get();
            normalPages.push_back(std::move(page));
            ++currentPage;
            currentOffset += size;
            return memory;
        }
        else
        {
            void* memory = normalPages[currentPage].get() + currentOffset;
            currentOffset += size;
            return memory;
        }
    }
}
