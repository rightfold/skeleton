#include "src/debug/value.hpp"

#include <iostream>

using sk::value::Value;

namespace sk::debug
{
    void dumpValue(Value value)
    {
        if (value)
        {
            std::cout << "{\"pointers\": [";
            auto pointerCount = value.pointerCount();
            for (decltype(pointerCount) i = 0; i < pointerCount; ++i)
            {
                dumpValue(value.pointerArray()[i]);
                if (i != pointerCount - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << "], \"bytes\": " << value.byteCount() << "}";
        }
        else
        {
            std::cout << "null";
        }
    }
}
