#pragma once

#include "Instruction.h"

namespace instructions
{
class LDAImmediate : public Instruction
{
public:
    [[nodiscard]] uint8_t opcode () const override;
    [[nodiscard]] std::string mnemonic () const override;
    [[nodiscard]] uint8_t cycles () const override;

    void execute (memory::Memory & memory,
                  core::ProgramCounter & program_counter,
                  core::Flags & flags,
                  core::Registers & registers) const override;
};
}
