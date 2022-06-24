#include "ProgramCounter.h"

#include <memory/Memory.h>

namespace core
{
void ProgramCounter::reset (const memory::Memory & memory)
{
    _program_counter = memory [memory::Memory::reset_vector_address [0]];
    _program_counter |= (memory [memory::Memory::reset_vector_address [1]] << 8);
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
