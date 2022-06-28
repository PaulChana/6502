#pragma once

#include "Instruction.h"

namespace instructions
{
class LDXImmediate : public Instruction
{
public:
    LDXImmediate ();
    ~LDXImmediate () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDXZeroPage : public Instruction
{
public:
    LDXZeroPage ();
    ~LDXZeroPage () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDXZeroPageY : public Instruction
{
public:
    LDXZeroPageY ();
    ~LDXZeroPageY () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDXAbsolute : public Instruction
{
public:
    LDXAbsolute ();
    ~LDXAbsolute () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};

class LDXAbsoluteY : public Instruction
{
public:
    LDXAbsoluteY ();
    ~LDXAbsoluteY () override = default;
    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;
};
}
