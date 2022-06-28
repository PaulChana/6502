#include "LDX.h"

#include <cassert>
#include <core/FlagController.h>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
LDXImmediate::LDXImmediate ()
    : Instruction (0xA2)
{
}

uint8_t LDXImmediate::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::immediate (memory, program_counter, flags, registers, core::Registers::Register::X);
}

LDXZeroPage::LDXZeroPage ()
    : Instruction (0xA6)
{
}

uint8_t LDXZeroPage::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page (memory, program_counter, flags, registers, core::Registers::Register::X);
}

LDXZeroPageY::LDXZeroPageY ()
    : Instruction (0xB6)
{
}

uint8_t LDXZeroPageY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::zero_page_shift (memory,
                                program_counter,
                                flags,
                                registers,
                                core::Registers::Register::X,
                                core::Registers::Register::Y);
}

LDXAbsolute::LDXAbsolute ()
    : Instruction (0xAE)
{
}

uint8_t LDXAbsolute::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute (memory, program_counter, flags, registers, core::Registers::Register::X);
}

LDXAbsoluteY::LDXAbsoluteY ()
    : Instruction (0xBE)
{
}

uint8_t LDXAbsoluteY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());
    return LD::absolute_shift (memory,
                               program_counter,
                               flags,
                               registers,
                               core::Registers::Register::X,
                               core::Registers::Register::Y);
}
}