#include "src/core/interpret.hpp"
#include "src/core/program.hpp"
#include "src/heap/heap.hpp"
#include "src/value/value.hpp"

#include <boost/optional.hpp>

#include <cassert>
#include <cstddef>

using sk::core::OperandType;
using sk::heap::Heap;
using sk::value::Value;

namespace
{
    Value readOperand(
        Value const* constants,
        Value* variables,
        OperandType type,
        std::size_t slot
    )
    {
        switch (type)
        {
            case OperandType::ConstantSlot:
                return constants[slot];

            case OperandType::VariableSlot:
                return variables[slot];

            default:
                assert(false);
        }
    }
}

namespace sk::core
{
    ThreadStatus resumeThread(
        Subroutine const* subroutines,
        Value const* constants,
        Thread& thread
    )
    {
        for (;;)
        {
            Instruction const*& instructionPointer =
                thread.topInstructionPointer();
            Value* variables = thread.topVariables();

            CallStackDiff diff = interpretInstruction(
                thread.heap(),
                constants,
                variables,
                *instructionPointer
            );

            if (!diff.shouldReturn)
            {
                instructionPointer += diff.jumpRelative;
            }

            if (diff.shouldReturn)
            {
                Value returnValue = variables[0];
                thread.popCallStack();
                if (!diff.call)
                {
                    if (thread.emptyCallStack())
                    {
                        return ThreadStatus::Finished;
                    }
                    Value* variables = thread.topVariables();
                    variables[0] = returnValue;
                }
            }

            if (diff.call)
            {
                Subroutine subroutine = subroutines[diff.call->calleeSlot];
                StackFrame stackFrame(subroutine);
                thread.pushCallStack(stackFrame);
                Value* variables = thread.topVariables();
                std::copy_n(
                    diff.call->arguments,
                    diff.call->argumentCount,
                    variables + 1
                );
            }

            if (diff.shouldBreak)
            {
                return ThreadStatus::Broken;
            }
        }
    }

    CallStackDiff interpretInstruction(
        Heap& heap,
        Value const* constants,
        Value* variables,
        Instruction const& instruction
    )
    {
        CallStackDiff callStackDiff;
        callStackDiff.shouldBreak  = false;
        callStackDiff.shouldReturn = false;
        callStackDiff.call         = boost::none;
        callStackDiff.jumpRelative = 1;

        switch (instruction.opcode)
        {
            case Opcode::NoOp:
                {
                    break;
                }

            case Opcode::Break:
                {
                    callStackDiff.shouldBreak = true;
                    break;
                }

            case Opcode::TailCall:
                {
                    callStackDiff.shouldReturn = true;
                    /* fallthrough */
                }

            case Opcode::Call:
                {
                    std::size_t argumentCount     = instruction.operand1;
                    std::size_t firstArgumentSlot = instruction.operand2;
                    std::size_t calleeSlot        = instruction.operand3;

                    Call call;
                    call.calleeSlot      = calleeSlot;
                    call.arguments       = variables + firstArgumentSlot;
                    call.argumentCount   = argumentCount;

                    callStackDiff.call = call;

                    break;
                }

            case Opcode::Return:
                {
                    callStackDiff.shouldReturn = true;
                    break;
                }

            case Opcode::GoTo:
                {
                    std::size_t jumpTarget = instruction.operand2;
                    callStackDiff.jumpRelative = jumpTarget;
                    break;
                }

            case Opcode::If:
                {
                    OperandType conditionType =
                        static_cast<OperandType>(instruction.operand1);
                    std::size_t conditionSlot = instruction.operand2;
                    std::size_t jumpTarget    = instruction.operand3;

                    Value condition = readOperand(
                        constants,
                        variables,
                        conditionType,
                        conditionSlot
                    );

                    if (condition.byteCount() != 0)
                    {
                        callStackDiff.jumpRelative = jumpTarget;
                    }

                    break;
                }

            case Opcode::Allocate:
                {
                    std::size_t targetSlot = instruction.operand1;
                    std::size_t firstPointerSlot = instruction.operand2;
                    std::size_t pointerCount = instruction.operand3 >> 32;
                    std::size_t byteCount = instruction.operand3 & 0xFFFFFFFF;

                    Value result = heap.allocate(
                        variables + firstPointerSlot,
                        pointerCount,
                        byteCount
                    );

                    variables[targetSlot] = result;

                    break;
                }

            default:
                assert(false);
        }

        return callStackDiff;
    }
}
