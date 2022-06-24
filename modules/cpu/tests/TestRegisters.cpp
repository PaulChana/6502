#include <catch2/catch_all.hpp>
#include <cpu/Registers.h>

SCENARIO ("Registers can be interacted with", "[cpu]")
{
    GIVEN ("Registers")
    {
        cpu::Registers registers;

        THEN ("All registers should be zeroed")
        {
            REQUIRE (registers [cpu::Registers::Register::A] == 0x00);
            REQUIRE (registers [cpu::Registers::Register::X] == 0x00);
            REQUIRE (registers [cpu::Registers::Register::Y] == 0x00);
        }
        AND_THEN ("Registers can be set")
        {
            registers [cpu::Registers::Register::A] = 0x01;
            registers [cpu::Registers::Register::X] = 0x10;
            registers [cpu::Registers::Register::Y] = 0x11;

            REQUIRE (registers [cpu::Registers::Register::A] == 0x01);
            REQUIRE (registers [cpu::Registers::Register::X] == 0x10);
            REQUIRE (registers [cpu::Registers::Register::Y] == 0x11);
        }
        AND_WHEN ("Registers are reset")
        {
            registers.reset ();

            REQUIRE (registers [cpu::Registers::Register::A] == 0x00);
            REQUIRE (registers [cpu::Registers::Register::X] == 0x00);
            REQUIRE (registers [cpu::Registers::Register::Y] == 0x00);
        }
    }
}