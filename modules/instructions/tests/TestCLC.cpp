#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/CLC.h>
#include <memory/Memory.h>

SCENARIO ("Can execute CLC", "[instructions/clc]")
{
    GIVEN ("An instruction, memory and flags")
    {
        instructions::CLC clc;
        REQUIRE (clc.opcode () == 0x18);

        memory::Memory memory;
        memory [0x00] = 0x18;

        core::Registers registers;
        core::Flags flags;
        core::ProgramCounter program_counter;
        program_counter = 0;

        flags [core::Flags::Flag::carry] = true;

        WHEN ("It is executed")
        {
            core::Flags::Watcher flag_watcher (flags);

            auto cycles = clc.execute (memory, program_counter, flags, registers);
            REQUIRE (cycles == 2);

            THEN ("There should be a change in the flags")
            {
                REQUIRE (flag_watcher.has_changed ());
            }
            THEN ("Program counter should be incremented by 1")
            {
                REQUIRE (program_counter == 1);
            }
        }
    }
}