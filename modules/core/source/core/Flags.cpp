#include "Flags.h"

namespace core
{
void Flags::reset ()
{
    _flags.reset ();
}

bool Flags::operator[] (Flag flag) const
{
    return _flags [size_t (flag)];
}

std::bitset<Flags::number_of_flags>::reference Flags::operator[] (Flag flag) noexcept
{
    return _flags [size_t (flag)];
}
}