#include "CLC.h"

#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <memory/Memory.h>

namespace instructions
{
CLC::CLC ()
    : Instruction (0x18)
{
}

uint8_t CLC::execute (memory::Memory & memory,
                      core::ProgramCounter & program_counter,
                      core::Flags & flags,
                      core::Registers &) const
{
    assert (memory [program_counter] == opcode ());
    ++program_counter;
    flags [core::Flags::Flag::carry] = false;
    return 2;
}
}