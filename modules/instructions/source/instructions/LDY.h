#pragma once

#include "Instruction.h"

namespace instructions
{
class LDYImmediate : public Instruction
{
public:
    LDYImmediate ();
    ~LDYImmediate () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDYZeroPage : public Instruction
{
public:
    LDYZeroPage ();
    ~LDYZeroPage () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDYZeroPageX : public Instruction
{
public:
    LDYZeroPageX ();
    ~LDYZeroPageX () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDYAbsolute : public Instruction
{
public:
    LDYAbsolute ();
    ~LDYAbsolute () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDYAbsoluteX : public Instruction
{
public:
    LDYAbsoluteX ();
    ~LDYAbsoluteX () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};
}
