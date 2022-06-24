#include "CPU.h"

namespace cpu
{
CPU::CPU (memory::Memory & memory)
    : _memory (memory)
{
}

void CPU::reset ()
{
    reset_program_counter ();
    reset_stack_pointer ();
    reset_registers ();
    reset_flags ();
}

void CPU::reset_flags ()
{
    _flags.reset ();
}

void CPU::reset_registers ()
{
    _a = _x = _y = 0x00;
}

void CPU::reset_program_counter ()
{
    _program_counter = _memory [memory::Memory::reset_vector_address [0]];
    _program_counter |= (_memory [memory::Memory::reset_vector_address [1]] << 8);
}

void CPU::reset_stack_pointer ()
{
    _stack_pointer = 0xFF;
}

uint16_t CPU::program_counter () const noexcept
{
    return _program_counter;
}

uint8_t CPU::stack_pointer () const noexcept
{
    return _stack_pointer;
}

uint8_t CPU::a () const noexcept
{
    return _a;
}

uint8_t CPU::x () const noexcept
{
    return _x;
}

uint8_t CPU::y () const noexcept
{
    return _y;
}

bool CPU::flag (CPU::Flag flag) const noexcept
{
    return _flags [size_t (flag)];
}

}