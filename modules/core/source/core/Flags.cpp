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

Flags::Watcher::Watcher (Flags & flags)
    : _flags (flags)
    , _source_flags (flags._flags)
{
}

bool Flags::Watcher::has_changed () const
{
    return _source_flags != _flags._flags;
}
}