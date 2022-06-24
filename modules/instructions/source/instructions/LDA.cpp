#include "LDA.h"

#include <cassert>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
uint8_t LDAImmediate::opcode () const
{
    return 0xA9;
}

std::string LDAImmediate::mnemonic () const
{
    return "LDA";
}

uint8_t LDAImmediate::cycles () const
{
    return 2;
}

void LDAImmediate::execute (memory::Memory & memory,
                            core::ProgramCounter & program_counter,
                            core::Flags & flags,
                            core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] = memory [program_counter + 1];

    flags [core::Flags::Flag::zero] = registers [core::Registers::Register::A] == 0;
    flags [core::Flags::Flag::negative] =
        (registers [core::Registers::Register::A] & 0b10000000) > 0;

    program_counter += cycles ();
}

}
