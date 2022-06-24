#pragma once

#include <cstdint>
namespace memory
{
class Memory;
}

namespace cpu
{
class ProgramCounter
{
public:
    ProgramCounter () = default;
    ~ProgramCounter () = default;
    ProgramCounter (const ProgramCounter & other) = delete;
    ProgramCounter & operator= (const ProgramCounter & other) = delete;

    [[nodiscard]] bool operator== (uint16_t program_counter) const;

    void reset (const memory::Memory & memory);

private:
    uint16_t _program_counter = 0x00;
};

}