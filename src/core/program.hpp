#pragma once

#include <array>
#include <cstdint>
#include <memory>

namespace sk::core
{
    // Be careful that constant, argument, and subroutine slots should be at
    // least 32 bits wide. Do not put them in operand one.

    /**
     * An opcode tells the interpreter what to do.
     */
    enum class Opcode : std::uint16_t
    {
        /**
         * A no-op instruction does nothing.
         *
         * Operands:
         *
         *  -# Ignored.
         *  -# Ignored.
         *  -# Ignored.
         */
        NoOp = 0x00,

        /**
         * Enter a breakpoint.
         *
         * Operands:
         *
         *  -# Ignored.
         *  -# Ignored.
         *  -# Ignored.
         */
        Break = 0x01,

        /**
         * Like Call, but do not create a new stack frame. Operands are the
         * same as for call.
         */
        TailCall = 0x10,

        /**
         * A call instruction calls a subroutine. The return value is stored in
         * the variable at slot zero.
         *
         * Operands:
         *
         *  -# The number of arguments.
         *  -# The variable slot of the first argument. Ignored if the number
         *     of arguments is zero.
         *  -# The callee subroutine slot.
         */
        Call = 0x11,

        /**
         * A return instruction pops the stack frame off the call stack. The
         * caller finds the return value in variable slot zero of the callee.
         *
         * Operands:
         *
         *  -# Ignored.
         *  -# Ignored.
         *  -# Ignored.
         */
        Return = 0x12,

        /**
         * A go to instruction does an unconditional jump.
         *
         * Operands:
         *
         *  -# Ignored.
         *  -# The relative offset of the instruction to jump to.
         *  -# Ignored.
         */
        GoTo = 0x20,

        /**
         * An if instruction does a conditional jump. The condition is a value
         * which is considered true if its byte count is nonzero and false if
         * its byte count is zero.
         *
         * Operands:
         *
         *  -# The condition operand type.
         *  -# The condition constant or variable slot.
         *  -# The relative offset of the instruction to jump to if the
         *     condition is true.
         */
        If = 0x21,

        /**
         * An allocate instruction creates a new value.
         *
         * Operands:
         *
         *  -# The variable slot at which to store the new value.
         *  -# The variable slot of the first pointer value. Ignored if the
         *     pointer count is zero.
         *  -# The pointer count as a 32-bit integer and the byte count as a
         *     32-bit integer, packed into a 64-bit integer in that order.
         */
        Allocate = 0x30,
    };

    /**
     * What the operand encodes.
     */
    enum class OperandType : std::uint16_t
    {
        /**
         * The operand is the slot of a constant.
         */
        ConstantSlot,

        /**
         * The operand is the slot of a variable.
         */
        VariableSlot,
    };

    /**
     * An instruction pairs an opcode with operands.
     */
    struct Instruction
    {
        Opcode opcode;
        std::uint16_t operand1;
        std::uint32_t operand2;
        std::uint64_t operand3;
    };

    /**
     * A subroutine is an array of instructions and metadata.
     */
    struct Subroutine
    {
        Instruction const* instructions;
        std::size_t variableCount;
    };

    /**
     * A system contains all information necessary to run a program.
     */
    struct System
    {
        std::unique_ptr<Instruction[]> instructions;
        std::unique_ptr<Subroutine[]> subroutines;
    };
}
