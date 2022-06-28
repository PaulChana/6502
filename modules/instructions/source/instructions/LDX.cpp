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
    : Instruction (0xA2, "LDX")
{
}

uint8_t LDXImmediate::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::X] = memory [program_counter + 1];

    core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::X);

    program_counter += 2;
    return 2;
}

LDXZeroPage::LDXZeroPage ()
    : Instruction (0xA6, "LDX")
{
}

uint8_t LDXZeroPage::execute (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::X] = memory [memory [program_counter + 1]];

    core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::X);

    program_counter += 2;
    return 3;
}

LDXZeroPageY::LDXZeroPageY ()
    : Instruction (0xB6, "LDX")
{
}

uint8_t LDXZeroPageY::execute (memory::Memory & memory,
                               core::ProgramCounter & program_counter,
                               core::Flags & flags,
                               core::Registers & registers) const
{
    assert (memory [program_counter] == opcode ());

    registers [core::Registers::Register::X] =
        memory [memory [program_counter + 1] + registers [core::Registers::Register::Y]];

    core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::X);

    program_counter += 2;
    return 4;
}
}