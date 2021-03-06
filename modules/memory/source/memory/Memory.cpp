#include "Memory.h"

namespace memory
{
void Memory::initialise ()
{
    _memory.fill (0x00);
}

uint16_t Memory::read (size_t index) const
{
    uint16_t address = _memory [index];
    address |= (_memory [index + 1] << 8);
    return address;
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

bool Memory::crosses_page_boundary (size_t address1, size_t address2)
{
    return ((address1 ^ address2) >> 8) > 0;
}

Memory::Watcher::Watcher (Memory & memory)
    : _memory (memory)
    , _source_memory (memory._memory)
{
}

bool Memory::Watcher::has_changed () const
{
    return _source_memory != _memory._memory;
}

}