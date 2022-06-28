#include "LDY.h"

#include <cassert>
#include <core/FlagController.h>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
LDYImmediate::LDYImmediate ()
    : Instruction (0xA0)
{
}

uint8_t LDYImmediate::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::immediate (memory, program_counter, flags, registers, core::Registers::Register::Y);
}

LDYZeroPage::LDYZeroPage ()
    : Instruction (0xA4)
{
}

uint8_t LDYZeroPage::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page (memory, program_counter, flags, registers, core::Registers::Register::Y);
}

LDYZeroPageX::LDYZeroPageX ()
    : Instruction (0xB4)
{
}

uint8_t LDYZeroPageX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page_shift (memory,
                                program_counter,
                                flags,
                                registers,
                                core::Registers::Register::Y,
                                core::Registers::Register::X);
}

LDYAbsolute::LDYAbsolute ()
    : Instruction (0xAC)
{
}

uint8_t LDYAbsolute::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute (memory, program_counter, flags, registers, core::Registers::Register::Y);
}

LDYAbsoluteX::LDYAbsoluteX ()
    : Instruction (0xBC)
{
}

uint8_t LDYAbsoluteX::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute_shift (memory,
                               program_counter,
                               flags,
                               registers,
                               core::Registers::Register::Y,
                               core::Registers::Register::X);
}
}