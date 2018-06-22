#pragma once

#include "src/core/program.hpp"
#include "src/core/thread.hpp"
#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <boost/optional.hpp>

#include <cstddef>
#include <cstdint>

namespace sk::core
{
    /**
     * Information about a call.
     */
    struct Call
    {
        /**
         * The subroutine to call, by its slot.
         */
        std::size_t calleeSlot;

        /**
         * A pointer to the array of arguments to the subroutine.
         */
        sk::value::Value* arguments;

        /**
         * The number of arguments to call the subroutine with.
         */
        std::size_t argumentCount;
    };

    /**
     * After interpreting an instruction, this describes what should happen to
     * the call stack.
     *
     * If shouldReturn is true and call is present, a tail call occurs.
     */
    struct CallStackDiff
    {
        /**
         * Whether to enter a breakpoint.
         */
        bool shouldBreak;

        /**
         * Whether to return.
         */
        bool shouldReturn;

        /**
         * The call, if calling.
         */
        boost::optional<Call> call;

        /**
         * Where to jump to, relative to the current instruction. Ignored if
         * returnValue is present.
         */
        std::int32_t jumpRelative;
    };

    ThreadStatus resumeThread(
        Subroutine const* subroutines,
        sk::value::Value const* constants,
        Thread& thread
    );

    /**
     * Interpret a single instruction.
     */
    CallStackDiff interpretInstruction(
        sk::heap::Heap& heap,
        sk::value::Value const* constants,
        sk::value::Value* variables,
        Instruction const& instruction
    );
}
