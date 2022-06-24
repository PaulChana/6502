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

ProgramCounter & CPU::program_counter () noexcept
{
    return _program_counter;
}

const ProgramCounter & CPU::program_counter () const noexcept
{
    return _program_counter;
}

Registers & CPU::registers () noexcept
{
    return _registers;
}

const Registers & CPU::registers () const noexcept
{
    return _registers;
}

Flags & CPU::flags () noexcept
{
    return _flags;
}

const Flags & CPU::flags () const noexcept
{
    return _flags;
}

StackPointer & CPU::stack_pointer () noexcept
{
    return _stack_pointer;
}

const StackPointer & CPU::stack_pointer () const noexcept
{
    return _stack_pointer;
}

}