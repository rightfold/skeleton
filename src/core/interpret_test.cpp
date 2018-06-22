#include "src/core/interpret.hpp"
#include "src/core/program.hpp"
#include "src/heap/arena.hpp"
#include "src/value/value.hpp"

#include "gtest/gtest.h"

#include <cstdint>

using sk::core::CallStackDiff;
using sk::core::Instruction;
using sk::core::Opcode;
using sk::core::OperandType;
using sk::heap::Arena;
using sk::value::Value;

TEST(InterpretInstructionTest, NoOp)
{
    Arena heap(4096, 256);

    Instruction instruction;
    instruction.opcode = Opcode::NoOp;

    CallStackDiff diff = sk::core::interpretInstruction(
        heap,
        /* constants */ nullptr,
        /* variables */ nullptr,
        instruction
    );

    EXPECT_FALSE(diff.shouldReturn);
    EXPECT_FALSE(diff.call);
    EXPECT_EQ(diff.jumpRelative, 1);
}

TEST(InterpretInstructionTest, Call)
{
    Arena heap(4096, 256);

    Instruction instruction;
    instruction.opcode = Opcode::Call;
    instruction.operand1 = 0xCA;
    instruction.operand2 = 0xFE;
    instruction.operand3 = 0xBABE;

    Value variables[512];

    CallStackDiff diff = sk::core::interpretInstruction(
        heap,
        /* constants */ nullptr,
        variables,
        instruction
    );

    EXPECT_FALSE(diff.shouldReturn);
    EXPECT_TRUE(diff.call);
    EXPECT_EQ(diff.call->calleeSlot,      0xBABEu);
    EXPECT_EQ(diff.call->arguments,       variables + 0xFE);
    EXPECT_EQ(diff.call->argumentCount,   0xCAu);
    EXPECT_EQ(diff.jumpRelative, 1);
}

TEST(InterpretInstructionTest, Return)
{
    Arena heap(4096, 256);

    Instruction instruction;
    instruction.opcode = Opcode::Return;

    CallStackDiff diff = sk::core::interpretInstruction(
        heap,
        /* constants */ nullptr,
        /* variables */ nullptr,
        instruction
    );

    EXPECT_TRUE(diff.shouldReturn);
    EXPECT_FALSE(diff.call);
}

TEST(InterpretInstructionTest, GoTo)
{
    Arena heap(4096, 256);

    Instruction instruction;
    instruction.opcode = Opcode::GoTo;
    instruction.operand2 = 10;

    CallStackDiff diff = sk::core::interpretInstruction(
        heap,
        /* constants */ nullptr,
        /* variables */ nullptr,
        instruction
    );

    EXPECT_FALSE(diff.shouldReturn);
    EXPECT_FALSE(diff.call);
    EXPECT_EQ(diff.jumpRelative, 10);
}

TEST(InterpretInstructionTest, If)
{
    Arena heap(4096, 256);
    Value trueValue  = heap.allocate(nullptr, 0, 1);
    Value falseValue = heap.allocate(nullptr, 0, 0);

    Instruction instruction;
    instruction.opcode = Opcode::If;
    instruction.operand1 =
        static_cast<std::uint16_t>(OperandType::VariableSlot);
    instruction.operand2 = 3;
    instruction.operand3 = 10;

    Value variables[512];

    {
        variables[3] = trueValue;

        CallStackDiff diff = sk::core::interpretInstruction(
            heap,
            /* constants */ nullptr,
            variables,
            instruction
        );

        EXPECT_FALSE(diff.shouldReturn);
        EXPECT_FALSE(diff.call);
        EXPECT_EQ(diff.jumpRelative, 10);
    }

    {
        variables[3] = falseValue;

        CallStackDiff diff = sk::core::interpretInstruction(
            heap,
            /* constants */ nullptr,
            variables,
            instruction
        );

        EXPECT_FALSE(diff.shouldReturn);
        EXPECT_FALSE(diff.call);
        EXPECT_EQ(diff.jumpRelative, 1);
    }
}

TEST(InterpretInstructionTest, Allocate)
{
    Arena heap(4096, 256);

    Instruction instruction;
    instruction.opcode = Opcode::Allocate;
    instruction.operand1 = 3;
    instruction.operand2 = 8;
    instruction.operand3 = (std::uint64_t(4) << 32) | std::uint64_t(7);

    Value variables[512];

    CallStackDiff diff = sk::core::interpretInstruction(
        heap,
        /* constants */ nullptr,
        variables,
        instruction
    );

    Value result = variables[3];
    EXPECT_EQ(result.pointerCount(), 4u);
    EXPECT_EQ(result.byteCount(),    7u);

    EXPECT_FALSE(diff.shouldReturn);
    EXPECT_FALSE(diff.call);
    EXPECT_EQ(diff.jumpRelative, 1);
}
