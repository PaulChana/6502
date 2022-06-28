#include "LDA.h"

#include "LD.h"

#include <cassert>
#include <core/FlagController.h>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
LDAImmediate::LDAImmediate ()
    : Instruction (0xA9)
{
}

uint8_t LDAImmediate::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::immediate (memory, program_counter, flags, registers, core::Registers::Register::A);
}

LDAZeroPage::LDAZeroPage ()
    : Instruction (0xA5)
{
}

uint8_t LDAZeroPage::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page (memory, program_counter, flags, registers, core::Registers::Register::A);
}

LDAZeroPageX::LDAZeroPageX ()
    : Instruction (0xB5)
{
}

uint8_t LDAZeroPageX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page_shift (memory,
                                program_counter,
                                flags,
                                registers,
                                core::Registers::Register::A,
                                core::Registers::Register::X);
}

LDAAbsolute::LDAAbsolute ()
    : Instruction (0xAD)
{
}

uint8_t LDAAbsolute::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute (memory, program_counter, flags, registers, core::Registers::Register::A);
}

LDAAbsoluteX::LDAAbsoluteX ()
    : Instruction (0xBD)
{
}

uint8_t LDAAbsoluteX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute_shift (memory,
                               program_counter,
                               flags,
                               registers,
                               core::Registers::Register::A,
                               core::Registers::Register::X);
}

LDAAbsoluteY::LDAAbsoluteY ()
    : Instruction (0xB9)
{
}

uint8_t LDAAbsoluteY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute_shift (memory,
                               program_counter,
                               flags,
                               registers,
                               core::Registers::Register::A,
                               core::Registers::Register::Y);
}

LDAIndirectX::LDAIndirectX ()
    : Instruction (0xA1)
{
}

uint8_t LDAIndirectX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::A] =
        memory [memory.read (program_counter + 1) + registers [core::Registers::Register::X]];

    core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::A);

    program_counter += 2;

    return 6;
}

LDAIndirectY::LDAIndirectY ()
    : Instruction (0xB1)
{
}

uint8_t LDAIndirectY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    auto address = memory.read (program_counter + 1);
    auto rootAddress = address;
    address += registers [core::Registers::Register::Y];

    registers [core::Registers::Register::A] = memory [address];

    core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::A);

    program_counter += 2;

    return memory::Memory::crosses_page_boundary (rootAddress, address) ? 6 : 5;
}

}
