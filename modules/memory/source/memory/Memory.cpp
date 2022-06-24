#include "Memory.h"

namespace mem
{
void Memory::initialise ()
{
    _memory.fill (0x00);
}

uint8_t Memory::operator[] (size_t index) const
{
    if (index >= _memory.size ())
        throw std::invalid_argument ("Index out of range");

    return _memory [index];
}

uint8_t & Memory::operator[] (size_t index)
{
    if (index >= _memory.size ())
        throw std::invalid_argument ("Index out of range");

    return _memory [index];
}

}