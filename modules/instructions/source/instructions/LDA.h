#pragma once

#include "Instruction.h"

namespace instructions
{
class LDAImmediate : public Instruction
{
public:
    LDAImmediate ();
    ~LDAImmediate () override = default;
    void execute (memory::Memory & memory,
                  core::ProgramCounter & program_counter,
                  core::Flags & flags,
                  core::Registers & registers) const override;
};

class LDAZeroPage : public Instruction
{
public:
    LDAZeroPage ();
    ~LDAZeroPage () override = default;
    void execute (memory::Memory & memory,
                  core::ProgramCounter & program_counter,
                  core::Flags & flags,
                  core::Registers & registers) const override;
};

class LDAZeroPageX : public Instruction
{
public:
    LDAZeroPageX ();
    ~LDAZeroPageX () override = default;
    void execute (memory::Memory & memory,
                  core::ProgramCounter & program_counter,
                  core::Flags & flags,
                  core::Registers & registers) const override;
};
}