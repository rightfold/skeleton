#include "src/bytecode/decode.hpp"
#include "src/core/interpret.hpp"
#include "src/core/program.hpp"
#include "src/core/thread.hpp"
#include "src/debug/value.hpp"
#include "src/heap/arena.hpp"
#include "src/utility/io.hpp"
#include "src/value/value.hpp"

#include <iostream>

using sk::core::StackFrame;
using sk::core::Subroutine;
using sk::core::System;
using sk::core::Thread;
using sk::core::ThreadStatus;
using sk::heap::Arena;
using sk::utility::FileReader;
using sk::value::Value;

int main()
{
    FileReader r("bazel-genfiles/example/bytecode/system.sksys");
    System system = sk::bytecode::decodeSystem(r);

    Subroutine subroutine = system.subroutines[0];
    StackFrame stackFrame(subroutine);
    Thread thread(stackFrame, std::make_unique<Arena>(4096, 256));

    for (;;)
    {
        ThreadStatus status = sk::core::resumeThread(
            system.subroutines.get(),
            /* constants */ nullptr,
            thread
        );

        if (status == ThreadStatus::Finished)
        {
            break;
        }

        std::cout << "=== BREAKPOINT ===\n";
        for (std::size_t i = 0; i < thread.allVariableCount(); ++i)
        {
            Value variable = thread.allVariables()[i];
            std::cout << i << ": ";
            sk::debug::dumpValue(variable);
            std::cout << "\n";
        }
    }

    return 0;
}
