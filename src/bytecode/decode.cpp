#include "src/bytecode/decode.hpp"
#include "src/core/program.hpp"
#include "src/utility/io.hpp"

#include <cstdint>

using sk::core::Instruction;
using sk::core::Opcode;
using sk::core::Subroutine;
using sk::core::System;
using sk::utility::Reader;

namespace sk::bytecode
{
    System decodeSystem(Reader& r)
    {
        System system;

        std::uint64_t instructionCount = readUint64LE(r);
        std::uint64_t subroutineCount  = readUint64LE(r);

        system.instructions.reset(new Instruction[instructionCount]);
        system.subroutines.reset(new Subroutine[subroutineCount]);

        for (decltype(instructionCount) i = 0; i < instructionCount; ++i)
        {
            auto instruction = decodeInstruction(r);
            system.instructions[i] = instruction;
        }

        for (decltype(subroutineCount) i = 0; i < subroutineCount; ++i)
        {
            auto subroutine = decodeSubroutine(r, system.instructions.get());
            system.subroutines[i] = subroutine;
        }

        return system;
    }

    Instruction decodeInstruction(Reader& r)
    {
        Instruction instruction;
        instruction.opcode   = static_cast<Opcode>(readUint16LE(r));
        instruction.operand1 = readUint16LE(r);
        instruction.operand2 = readUint32LE(r);
        instruction.operand3 = readUint64LE(r);
        return instruction;
    }

    Subroutine decodeSubroutine(Reader& r, Instruction const* instructions)
    {
        Subroutine subroutine;
        subroutine.instructions  = instructions + readUint32LE(r);
        subroutine.variableCount = readUint32LE(r);
        return subroutine;
    }
}
