#pragma once

#include "Instruction.h"

namespace instructions
{
class NOP : public Instruction
{
public:
    NOP ();
    ~NOP () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};
}