#pragma once

#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace sk::heap
{
    /**
     * An arena heap allocates memory but does not collect it until the entire
     * heap is destroyed.
     *
     * An arena heap allocates pages of memory at once. When a page is full, a
     * new page is created. When allocating more than a threshold of a page at
     * once, a new page is created specifically for that value.
     */
    class Arena : public Heap
    {
    public:
        /**
         * @param singletonThreshold When a value is this size or bigger,
         *        allocate a new page specifically for that value. Must be less
         *        than or equal to pageSize.
         */
        explicit Arena(std::size_t pageSize, std::size_t singletonThreshold);

        value::Value allocate(
            value::Value* pointers,
            std::size_t pointerCount,
            std::size_t byteCount
        ) override;

    private:
        void* findMemory(std::size_t size);

        /**
         * Normal pages all have the same size, which is pageSize.
         */
        std::vector<std::unique_ptr<char[]>> normalPages;
        std::size_t currentPage;
        std::size_t currentOffset;
        std::size_t pageSize;

        /**
         * Singleton pages are created for values larger than
         * singletonThreshold. They are the same size as the single value they
         * contain.
         */
        std::vector<std::unique_ptr<char[]>> singletonPages;
        std::size_t singletonThreshold;
    };
}
