#pragma once

#include "src/core/program.hpp"
#include "src/utility/io.hpp"

namespace sk::bytecode
{
    sk::core::System decodeSystem(sk::utility::Reader& r);

    sk::core::Instruction decodeInstruction(sk::utility::Reader& r);

    sk::core::Subroutine decodeSubroutine(
        sk::utility::Reader& r,
        sk::core::Instruction const* instructions
    );
}
