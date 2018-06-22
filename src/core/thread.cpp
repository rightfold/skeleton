#include "src/core/program.hpp"
#include "src/core/thread.hpp"
#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <cstddef>
#include <memory>
#include <utility>

using sk::heap::Heap;
using sk::value::Value;

namespace sk::core
{
    StackFrame::StackFrame(Subroutine const& subroutine)
        : instructionPointer(subroutine.instructions)
        , variableCount(subroutine.variableCount)
    {
    }

    Thread::Thread(StackFrame stackFrame, std::unique_ptr<Heap> heap)
        : heap_(std::move(heap))
    {
        pushCallStack(stackFrame);
    }

    bool Thread::emptyCallStack() const
    {
        return callStack.empty();
    }

    void Thread::pushCallStack(StackFrame stackFrame)
    {
        variables.resize(variables.size() + stackFrame.variableCount);
        callStack.push_back(stackFrame);
    }

    void Thread::popCallStack()
    {
        StackFrame stackFrame = callStack.back();
        variables.resize(variables.size() - stackFrame.variableCount);
        callStack.pop_back();
    }

    Value* Thread::allVariables()
    {
        return variables.data();
    }

    std::size_t Thread::allVariableCount() const
    {
        return variables.size();
    }

    Instruction const*& Thread::topInstructionPointer()
    {
        StackFrame& stackFrame = callStack.back();
        return stackFrame.instructionPointer;
    }

    Value* Thread::topVariables()
    {
        StackFrame stackFrame = callStack.back();
        std::size_t offset = variables.size() - stackFrame.variableCount;
        return variables.data() + offset;
    }

    Heap& Thread::heap()
    {
        return *heap_;
    }
}
