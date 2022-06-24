#include "CPU.h"

#include <memory/Memory.h>

namespace cpu
{
CPU::CPU (memory::Memory & memory)
    : _memory (memory)
{
}

void CPU::reset ()
{
    _flags.reset ();
    _registers.reset ();
    _program_counter.reset (_memory);
    _stack_pointer.reset ();
}

core::ProgramCounter & CPU::program_counter () noexcept
{
    return _program_counter;
}

const core::ProgramCounter & CPU::program_counter () const noexcept
{
    return _program_counter;
}

core::Registers & CPU::registers () noexcept
{
    return _registers;
}

const core::Registers & CPU::registers () const noexcept
{
    return _registers;
}

core::Flags & CPU::flags () noexcept
{
    return _flags;
}

const core::Flags & CPU::flags () const noexcept
{
    return _flags;
}

core::StackPointer & CPU::stack_pointer () noexcept
{
    return _stack_pointer;
}

const core::StackPointer & CPU::stack_pointer () const noexcept
{
    return _stack_pointer;
}

}