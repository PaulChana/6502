#pragma once

#include <cstdint>
namespace memory
{
class Memory;
}

namespace core
{
class ProgramCounter
{
public:
    ProgramCounter () = default;
    ~ProgramCounter () = default;
    ProgramCounter (const ProgramCounter & other) = delete;
    ProgramCounter & operator= (const ProgramCounter & other) = delete;

    ProgramCounter & operator++ ();
    ProgramCounter & operator-- ();
    ProgramCounter & operator++ (int);
    ProgramCounter & operator-- (int);

    void operator+= (uint16_t offset);
    void operator= (uint16_t position);
    [[nodiscard]] operator uint16_t () const;

    void reset (const memory::Memory & memory);

private:
    uint16_t _program_counter = 0x00;
};

}