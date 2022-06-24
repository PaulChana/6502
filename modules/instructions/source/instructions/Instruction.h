#pragma once

#include <cstdint>
#include <string>
#include <utility>

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
    Instruction (uint8_t opcode, std::string mnemonic, uint8_t cycles)
        : _opcode (opcode)
        , _mnemonic (std::move (mnemonic))
        , _cycles (cycles)
    {
    }
    virtual ~Instruction () = default;

    [[nodiscard]] uint8_t opcode () const
    {
        return _opcode;
    }

    [[nodiscard]] std::string mnemonic () const
    {
        return _mnemonic;
    }

    [[nodiscard]] uint8_t cycles () const
    {
        return _cycles;
    }

    virtual void execute (memory::Memory & memory,
                          core::ProgramCounter & program_counter,
                          core::Flags & flags,
                          core::Registers & registers) const = 0;

private:
    const uint8_t _opcode;
    const std::string _mnemonic;
    const uint8_t _cycles;
};
}