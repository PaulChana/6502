#pragma once

#include <cstdint>
#include <string>

namespace memory
{
class Memory;
}

namespace cpu
{
class Flags;
class Registers;
class Instruction
{
public:
    virtual ~Instruction () = default;

    [[nodiscard]] virtual uint8_t opcode () const = 0;
    [[nodiscard]] virtual std::string mnemonic () const = 0;
    [[nodiscard]] virtual uint8_t cycles () const = 0;

    void
    execute (memory::Memory & memory, cpu::Flags & flags, cpu::Registers & registers) const = 0;
};
}