#include "LDA.h"

#include <cassert>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
void updateLDAFlags (core::Flags & flags, core::Registers & registers)
{
    flags [core::Flags::Flag::zero] = registers [core::Registers::Register::A] == 0;
    flags [core::Flags::Flag::negative] =
        (registers [core::Registers::Register::A] & 0b10000000) > 0;
}

LDAImmediate::LDAImmediate ()
    : Instruction (0xA9, "LDA", 2)
{
}

void LDAImmediate::execute (memory::Memory & memory,
                            core::ProgramCounter & program_counter,
                            core::Flags & flags,
                            core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] = memory [program_counter + 1];

    updateLDAFlags (flags, registers);

    program_counter += 2;
}

LDAZeroPage::LDAZeroPage ()
    : Instruction (0xA5, "LDA", 3)
{
}

void LDAZeroPage::execute (memory::Memory & memory,
                           core::ProgramCounter & program_counter,
                           core::Flags & flags,
                           core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] = memory [memory [program_counter + 1]];

    updateLDAFlags (flags, registers);

    program_counter += 2;
}

LDAZeroPageX::LDAZeroPageX ()
    : Instruction (0xB5, "LDA", 4)
{
}

void LDAZeroPageX::execute (memory::Memory & memory,
                            core::ProgramCounter & program_counter,
                            core::Flags & flags,
                            core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] =
        memory [memory [program_counter + 1] + registers [core::Registers::Register::X]];

    updateLDAFlags (flags, registers);

    program_counter += 2;
}

}
