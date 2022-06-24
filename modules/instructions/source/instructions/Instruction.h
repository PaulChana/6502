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
    Instruction (uint8_t opcode, std::string mnemonic)
        : _opcode (opcode)
        , _mnemonic (std::move (mnemonic))
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

    [[nodiscard]] virtual uint8_t execute (memory::Memory & memory,
                                           core::ProgramCounter & program_counter,
                                           core::Flags & flags,
                                           core::Registers & registers) const = 0;

private:
    const uint8_t _opcode;
    const std::string _mnemonic;
};
}