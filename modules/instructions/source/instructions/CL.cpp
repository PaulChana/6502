#include "CL.h"

#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <memory/Memory.h>

namespace instructions
{
CL::CL (uint8_t opcode, core::Flags::Flag flag)
    : Instruction (opcode)
    , _flag (flag)
{
}

uint8_t CL::execute (memory::Memory & memory,
                      core::ProgramCounter & program_counter,
                      core::Flags & flags,
                      core::Registers &) const
{
    assert (memory [program_counter] == opcode ());
    ++program_counter;
    flags [_flag] = false;
    return 2;
}
}