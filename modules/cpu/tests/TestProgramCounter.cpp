#include <catch2/catch_all.hpp>
#include <cpu/ProgramCounter.h>
#include <memory/Memory.h>

SCENARIO ("ProgramCounter can be interacted with", "[cpu]")
{
    GIVEN ("ProgramCounter")
    {
        cpu::ProgramCounter counter;
        REQUIRE (counter == 0x00);

        AND_GIVEN ("Memory")
        {
            memory::Memory memory;
            memory [memory::Memory::reset_vector_address [0]] = 0x00;
            memory [memory::Memory::reset_vector_address [1]] = 0x10;

            WHEN ("Program counter is reset")
            {
                counter.reset (memory);
                THEN ("Program counter should read from the reset vector")
                {
                    REQUIRE (counter == 0x1000);
                }
            }
        }
    }
}