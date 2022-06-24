#include <catch2/catch_all.hpp>
#include <cpu/CPU.h>
#include <memory/Memory.h>

SCENARIO ("CPU has a program counter", "[cpu]")
{
    GIVEN ("A CPU")
    {
        memory::Memory memory;
        cpu::CPU cpu (memory);

        REQUIRE (cpu.program_counter () == 0x00);

        WHEN ("The cpu is reset")
        {
            memory [memory::Memory::reset_vector_address [0]] = 0x00;
            memory [memory::Memory::reset_vector_address [1]] = 0x10;
            cpu.reset ();

            THEN ("The program counter has been read from the reset vector")
            {
                REQUIRE (cpu.program_counter () == 0x1000);
            }
        }
    }
}