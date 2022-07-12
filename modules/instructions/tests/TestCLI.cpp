#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/CL.h>
#include <memory/Memory.h>

SCENARIO ("Can execute CLI", "[instructions/cli]")
{
    GIVEN ("An instruction, memory and flags")
    {
        instructions::CLI cli;
        REQUIRE (cli.opcode () == 0x58);

        memory::Memory memory;
        memory [0x00] = 0x58;

        core::Registers registers;
        core::Flags flags;
        core::ProgramCounter program_counter;
        program_counter = 0;

        flags [core::Flags::Flag::interrupt_disable] = true;

        WHEN ("It is executed")
        {
            core::Flags::Watcher flag_watcher (flags);

            auto cycles = cli.execute (memory, program_counter, flags, registers);
            REQUIRE (cycles == 2);

            THEN ("There should be a change in the flags")
            {
                REQUIRE (flag_watcher.has_changed ());
                REQUIRE (flags [core::Flags::Flag::interrupt_disable] == false);
            }
            THEN ("Program counter should be incremented by 1")
            {
                REQUIRE (program_counter == 1);
            }
        }
    }
}