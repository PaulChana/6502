#pragma once

#include "Flags.h"
#include "Registers.h"

namespace core
{
class FlagController
{
public:
    static void
    update_flags_ld (Flags & flags, const Registers & registers, Registers::Register register_type);
};
}
