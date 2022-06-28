#pragma once

#include <core/Registers.h>

namespace memory
{
class Memory;
}
namespace core
{
class Flags;
class ProgramCounter;
}

namespace instructions
{
class LD
{
public:
    static uint8_t immediate (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers,
                              core::Registers::Register target);

    static uint8_t zero_page (memory::Memory & memory,
                              core::ProgramCounter & program_counter,
                              core::Flags & flags,
                              core::Registers & registers,
                              core::Registers::Register target);

    static uint8_t zero_page_shift (memory::Memory & memory,
                                    core::ProgramCounter & program_counter,
                                    core::Flags & flags,
                                    core::Registers & registers,
                                    core::Registers::Register target,
                                    core::Registers::Register shift);

    static uint8_t absolute (memory::Memory & memory,
                             core::ProgramCounter & program_counter,
                             core::Flags & flags,
                             core::Registers & registers,
                             core::Registers::Register target);

    static uint8_t absolute_shift (memory::Memory & memory,
                                   core::ProgramCounter & program_counter,
                                   core::Flags & flags,
                                   core::Registers & registers,
                                   core::Registers::Register target,
                                   core::Registers::Register shift);
};
}
