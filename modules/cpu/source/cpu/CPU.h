#pragma once

#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <core/StackPointer.h>
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

    [[nodiscard]] core::ProgramCounter & program_counter () noexcept;
    [[nodiscard]] const core::ProgramCounter & program_counter () const noexcept;

    [[nodiscard]] core::StackPointer & stack_pointer () noexcept;
    [[nodiscard]] const core::StackPointer & stack_pointer () const noexcept;

    [[nodiscard]] core::Flags & flags () noexcept;
    [[nodiscard]] const core::Flags & flags () const noexcept;

    [[nodiscard]] core::Registers & registers () noexcept;
    [[nodiscard]] const core::Registers & registers () const noexcept;

private:
    memory::Memory & _memory;

    core::ProgramCounter _program_counter;
    core::StackPointer _stack_pointer;
    core::Registers _registers;
    core::Flags _flags;
};
}