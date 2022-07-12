#pragma once

#include "Instruction.h"

namespace instructions
{
class CLC : public Instruction
{
public:
    CLC ();
    ~CLC () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};
}