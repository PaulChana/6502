#pragma once

#include "Instruction.h"

#include <core/Flags.h>

namespace instructions
{
class CL : public Instruction
{
public:
    CL (uint8_t opcode, core::Flags::Flag flag);
    ~CL () override = default;

    [[nodiscard]] uint8_t execute (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers) const override;

private:
    const core::Flags::Flag _flag;
};

class CLC : public CL
{
public:
    CLC ()
        : CL (0x18, core::Flags::Flag::carry)
    {
    }
    ~CLC () override = default;
};

class CLD : public CL
{
public:
    CLD ()
        : CL (0xD8, core::Flags::Flag::decimal_mode)
    {
    }
    ~CLD () override = default;
};

class CLI : public CL
{
public:
    CLI ()
        : CL (0x58, core::Flags::Flag::interrupt_disable)
    {
    }
    ~CLI () override = default;
};

class CLV : public CL
{
public:
    CLV ()
        : CL (0xB8, core::Flags::Flag::overflow)
    {
    }
    ~CLV () override = default;
};
}