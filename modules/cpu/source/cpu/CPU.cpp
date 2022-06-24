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
}

void CPU::reset_program_counter ()
{
    _program_counter = _memory [memory::Memory::reset_vector_address [0]];
    _program_counter |= (_memory [memory::Memory::reset_vector_address [1]] << 8);
}

uint16_t CPU::program_counter () const noexcept
{
    return _program_counter;
}

}