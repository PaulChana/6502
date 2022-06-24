#include "Registers.h"
namespace cpu
{
void Registers::reset ()
{
    _registers.fill (0x00);
}

uint8_t Registers::operator[] (Registers::Register index) const
{
    return _registers [size_t (index)];
}

uint8_t & Registers::operator[] (Registers::Register index)
{
    return _registers [size_t (index)];
}
}
