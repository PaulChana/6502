#include "ProgramCounter.h"

#include <memory/Memory.h>

namespace cpu
{
void ProgramCounter::reset (const memory::Memory & memory)
{
    _program_counter = memory [memory::Memory::reset_vector_address [0]];
    _program_counter |= (memory [memory::Memory::reset_vector_address [1]] << 8);
}

bool ProgramCounter::operator== (uint16_t program_counter) const
{
    return _program_counter == program_counter;
}

}
