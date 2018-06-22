#pragma once

#include "src/core/program.hpp"
#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace sk::core
{
    /**
     * A stack frame.
     */
    struct StackFrame
    {
        explicit StackFrame(Subroutine const& subroutine);

        /**
         * The instruction pointer, the instruction to execute next.
         */
        Instruction const* instructionPointer;

        /**
         * Number of variables used for this stack frame. Popping the stack
         * frame will also pop this many variables off the variable stack.
         */
        std::size_t variableCount;
    };

    /**
     * Thread status.
     */
    enum class ThreadStatus
    {
        Finished,
        Broken,
    };

    /**
     * A green thread.
     */
    class Thread
    {
    public:
        Thread(StackFrame stackFrame, std::unique_ptr<sk::heap::Heap> heap);

        bool emptyCallStack() const;
        void pushCallStack(StackFrame stackFrame);
        void popCallStack();

        /**
         * Pointer to all variables in the thread.
         */
        sk::value::Value* allVariables();

        /**
         * Number of variables in the thread.
         */
        std::size_t allVariableCount() const;

        /**
         * Reference to the instruction pointer of the top stack frame.
         */
        Instruction const*& topInstructionPointer();

        /**
         * Pointer to the begin of the variables in the top stack frame.
         */
        sk::value::Value* topVariables();

        sk::heap::Heap& heap();

    private:
        std::vector<sk::value::Value> variables;
        std::vector<StackFrame> callStack;
        std::unique_ptr<sk::heap::Heap> heap_;
    };
}
