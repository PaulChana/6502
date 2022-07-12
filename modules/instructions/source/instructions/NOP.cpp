#include "NOP.h"

namespace instructions
{
NOP::NOP ()
    : Instruction (0xEA)
{
}

uint8_t NOP::execute (memory::Memory & memory,
                      core::ProgramCounter & program_counter,
                      core::Flags &,
                      core::Registers &) const
{
    assert (memory [program_counter] == opcode ());
    ++program_counter;
    return 2;
}
}