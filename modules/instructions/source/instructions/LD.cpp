#include "LD.h"

#include <core/FlagController.h>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <memory/Memory.h>

namespace instructions
{
uint8_t LD::immediate (memory::Memory & memory,
                       core::ProgramCounter & program_counter,
                       core::Flags & flags,
                       core::Registers & registers,
                       core::Registers::Register target)
{
    registers [target] = memory [program_counter + 1];
    core::FlagController::update_flags_ld (flags, registers, target);
    program_counter += 2;
    return 2;
}

uint8_t LD::zero_page (memory::Memory & memory,
                       core::ProgramCounter & program_counter,
                       core::Flags & flags,
                       core::Registers & registers,
                       core::Registers::Register target)
{
    registers [target] = memory [memory [program_counter + 1]];
    core::FlagController::update_flags_ld (flags, registers, target);
    program_counter += 2;
    return 3;
}

uint8_t LD::zero_page_shift (memory::Memory & memory,
                             core::ProgramCounter & program_counter,
                             core::Flags & flags,
                             core::Registers & registers,
                             core::Registers::Register target,
                             core::Registers::Register shift)
{
    registers [target] = memory [memory [program_counter + 1] + registers [shift]];
    core::FlagController::update_flags_ld (flags, registers, target);
    program_counter += 2;
    return 4;
}

uint8_t LD::absolute (memory::Memory & memory,
                      core::ProgramCounter & program_counter,
                      core::Flags & flags,
                      core::Registers & registers,
                      core::Registers::Register target)
{
    auto address = memory.read (program_counter + 1);
    registers [target] = memory [address];
    core::FlagController::update_flags_ld (flags, registers, target);
    program_counter += 3;
    return 4;
}

uint8_t LD::absolute_shift (memory::Memory & memory,
                            core::ProgramCounter & program_counter,
                            core::Flags & flags,
                            core::Registers & registers,
                            core::Registers::Register target,
                            core::Registers::Register shift)
{
    auto address = memory.read (program_counter + 1);
    auto rootAddress = address;
    address += registers [shift];
    registers [target] = memory [address];
    core::FlagController::update_flags_ld (flags, registers, target);
    program_counter += 3;
    return memory::Memory::crosses_page_boundary (rootAddress, address) ? 5 : 4;
}
}