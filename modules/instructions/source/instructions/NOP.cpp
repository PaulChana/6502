#include "NOP.h"

namespace instructions
{
NOP::NOP ()
    : Instruction (0xEA)
{
}

uint8_t NOP::execute (memory::Memory &,
                      core::ProgramCounter & program_counter,
                      core::Flags &,
                      core::Registers &) const
{
    ++program_counter;
    return 2;
}
}