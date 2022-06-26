#include "FlagController.h"

namespace core
{
void FlagController::update_flags_ld (Flags & flags,
                                      const Registers & registers,
                                      Registers::Register register_type)
{
    flags [core::Flags::Flag::zero] = registers [register_type] == 0;
    flags [core::Flags::Flag::negative] = (registers [register_type] & 0b10000000) > 0;
}
}