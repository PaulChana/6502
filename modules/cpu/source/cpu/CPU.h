#pragma once

#include "Flags.h"
#include "ProgramCounter.h"
#include "Registers.h"
#include "StackPointer.h"

#include <cstdint>

namespace memory
{
class Memory;
}

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

    [[nodiscard]] ProgramCounter & program_counter () noexcept;
    [[nodiscard]] const ProgramCounter & program_counter () const noexcept;

    [[nodiscard]] StackPointer & stack_pointer () noexcept;
    [[nodiscard]] const StackPointer & stack_pointer () const noexcept;

    [[nodiscard]] Flags & flags () noexcept;
    [[nodiscard]] const Flags & flags () const noexcept;

    [[nodiscard]] Registers & registers () noexcept;
    [[nodiscard]] const Registers & registers () const noexcept;

private:
    memory::Memory & _memory;

    ProgramCounter _program_counter;
    StackPointer _stack_pointer;
    Registers _registers;
    Flags _flags;
};
}