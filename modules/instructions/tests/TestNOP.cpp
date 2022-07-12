#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/NOP.h>
#include <memory/Memory.h>

SCENARIO ("Can execute NOP", "[instructions/nop]")
{
    GIVEN ("An instruction, memory and flags")
    {
        instructions::NOP nop;
        REQUIRE (nop.opcode () == 0xEA);

        memory::Memory memory;
        memory [0x00] = 0xEA;

        core::Registers registers;
        core::Flags flags;
        core::ProgramCounter program_counter;
        program_counter = 0;

        WHEN ("It is executed")
        {
            core::Flags::Watcher flag_watcher (flags);
            memory::Memory::Watcher memory_watcher (memory);

            auto cycles = nop.execute (memory, program_counter, flags, registers);
            REQUIRE (cycles == 2);

            THEN ("There should be no change in the memory or flags")
            {
                REQUIRE (! flag_watcher.has_changed ());
                REQUIRE (! memory_watcher.has_changed ());
            }
            THEN ("Program counter should be incremented by 1")
            {
                REQUIRE (program_counter == 1);
            }
        }
    }
}