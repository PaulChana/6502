#include "StackPointer.h"

namespace core
{
void StackPointer::reset ()
{
    _address = 0xFF;
}

bool StackPointer::operator== (uint8_t address) const
{
    return _address == address;
}

}