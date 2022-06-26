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
    : Instruction (0xA9, "LDA")
{
}

uint8_t LDAImmediate::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] = memory [program_counter + 1];

    updateLDAFlags (flags, registers);

    program_counter += 2;
    return 2;
}

LDAZeroPage::LDAZeroPage ()
    : Instruction (0xA5, "LDA")
{
}

uint8_t LDAZeroPage::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] = memory [memory [program_counter + 1]];

    updateLDAFlags (flags, registers);

    program_counter += 2;
    return 3;
}

LDAZeroPageX::LDAZeroPageX ()
    : Instruction (0xB5, "LDA")
{
}

uint8_t LDAZeroPageX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] =
        memory [memory [program_counter + 1] + registers [core::Registers::Register::X]];

    updateLDAFlags (flags, registers);

    program_counter += 2;
    return 4;
}

LDAAbsolute::LDAAbsolute ()
    : Instruction (0xAD, "LDA")
{
}

uint8_t LDAAbsolute::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    auto address = memory.read (program_counter + 1);

    registers [core::Registers::Register::A] = memory [address];

    updateLDAFlags (flags, registers);

    program_counter += 3;
    return 4;
}

LDAAbsoluteX::LDAAbsoluteX ()
    : Instruction (0xBD, "LDA")
{
}

uint8_t LDAAbsoluteX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    auto address = memory.read (program_counter + 1);
    auto rootAddress = address;
    address += registers [core::Registers::Register::X];

    registers [core::Registers::Register::A] = memory [address];

    updateLDAFlags (flags, registers);

    program_counter += 3;

    if (((rootAddress ^ address) >> 8) > 0)
        return 5;

    return 4;
}

LDAAbsoluteY::LDAAbsoluteY ()
    : Instruction (0xB9, "LDA")
{
}

uint8_t LDAAbsoluteY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    auto address = memory.read (program_counter + 1);
    auto rootAddress = address;
    address += registers [core::Registers::Register::Y];

    registers [core::Registers::Register::A] = memory [address];

    updateLDAFlags (flags, registers);

    program_counter += 3;

    if (((rootAddress ^ address) >> 8) > 0)
        return 5;

    return 4;
}

}
