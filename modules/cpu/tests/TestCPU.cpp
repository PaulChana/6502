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
        REQUIRE (cpu.stack_pointer () == 0x00);

        WHEN ("The cpu is reset")
        {
            memory [memory::Memory::reset_vector_address [0]] = 0x00;
            memory [memory::Memory::reset_vector_address [1]] = 0x10;
            cpu.reset ();

            THEN ("The program counter has been read from the reset vector")
            {
                REQUIRE (cpu.program_counter () == 0x1000);
            }
            AND_THEN ("The stack pointer is reset to start of the stack")
            {
                REQUIRE (cpu.stack_pointer () == 0xFF);
            }
            AND_THEN ("The registers are zero")
            {
                REQUIRE (cpu.a () == 0x00);
                REQUIRE (cpu.x () == 0x00);
                REQUIRE (cpu.y () == 0x00);
            }
            AND_THEN ("The flags are all reset")
            {
                REQUIRE (! cpu.flag (cpu::CPU::Flag::carry));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::zero));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::interrupt_disable));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::decimal_mode));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::brk));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::overflow));
                REQUIRE (! cpu.flag (cpu::CPU::Flag::negative));
            }
        }
    }
}