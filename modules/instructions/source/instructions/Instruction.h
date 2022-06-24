#pragma once

#include <cstdint>
#include <string>

namespace memory
{
class Memory;
}
namespace core
{
class Flags;
class Registers;
class ProgramCounter;
}

namespace instructions
{
class Instruction
{
public:
    virtual ~Instruction () = default;

    [[nodiscard]] virtual uint8_t opcode () const = 0;
    [[nodiscard]] virtual std::string mnemonic () const = 0;
    [[nodiscard]] virtual uint8_t cycles () const = 0;

    virtual void execute (memory::Memory & memory,
                          core::ProgramCounter & program_counter,
                          core::Flags & flags,
                          core::Registers & registers) const = 0;
};
}