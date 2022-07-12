#include "ProgramCounter.h"

#include <memory/Memory.h>

namespace core
{
void ProgramCounter::reset (const memory::Memory & memory)
{
    _program_counter = memory [memory::Memory::reset_vector_address [0]];
    _program_counter |= (memory [memory::Memory::reset_vector_address [1]] << 8);
}

ProgramCounter & ProgramCounter::operator++ ()
{
    ++_program_counter;
    return *this;
}

ProgramCounter & ProgramCounter::operator-- ()
{
    --_program_counter;
    return *this;
}

ProgramCounter & ProgramCounter::operator++ (int)
{
    _program_counter++;
    return *this;
}

ProgramCounter & ProgramCounter::operator-- (int)
{
    _program_counter--;
    return *this;
}

void ProgramCounter::operator= (uint16_t position)
{
    _program_counter = position;
}

void ProgramCounter::operator+= (uint16_t offset)
{
    _program_counter += offset;
}

ProgramCounter::operator uint16_t () const
{
    return _program_counter;
}

}
