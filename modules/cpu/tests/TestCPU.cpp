#include <catch2/catch_all.hpp>
#include <cpu/CPU.h>
#include <memory/Memory.h>

SCENARIO ("CPU can be reset", "[cpu]")
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
                REQUIRE (cpu.registers () [core::Registers::Register::A] == 0x00);
                REQUIRE (cpu.registers () [core::Registers::Register::X] == 0x00);
                REQUIRE (cpu.registers () [core::Registers::Register::Y] == 0x00);
            }
            AND_THEN ("The flags are all reset")
            {
                REQUIRE (! cpu.flags () [core::Flags::Flag::carry]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::zero]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::interrupt_disable]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::decimal_mode]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::brk]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::overflow]);
                REQUIRE (! cpu.flags () [core::Flags::Flag::negative]);
            }
        }
    }
}