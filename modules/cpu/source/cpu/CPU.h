#pragma once

#include <cstdint>
#include <memory/Memory.h>

namespace cpu
{
class CPU
{
public:
    CPU (memory::Memory & memory);
    ~CPU () = default;

    CPU (const CPU & other) = delete;
    CPU & operator= (const CPU & other) = delete;

    void reset ();

    [[nodiscard]] uint16_t program_counter () const noexcept;

private:
    void reset_program_counter ();

    memory::Memory & _memory;

    uint16_t _program_counter = 0x00;
};
}