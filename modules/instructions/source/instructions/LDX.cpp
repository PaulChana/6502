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
}