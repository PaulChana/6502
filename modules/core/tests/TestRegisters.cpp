#include <catch2/catch_all.hpp>
#include <core/Registers.h>

SCENARIO ("Registers can be interacted with", "[core]")
{
    GIVEN ("Registers")
    {
        core::Registers registers;

        THEN ("All registers should be zeroed")
        {
            REQUIRE (registers [core::Registers::Register::A] == 0x00);
            REQUIRE (registers [core::Registers::Register::X] == 0x00);
            REQUIRE (registers [core::Registers::Register::Y] == 0x00);
        }
        AND_THEN ("Registers can be set")
        {
            registers [core::Registers::Register::A] = 0x01;
            registers [core::Registers::Register::X] = 0x10;
            registers [core::Registers::Register::Y] = 0x11;

            REQUIRE (registers [core::Registers::Register::A] == 0x01);
            REQUIRE (registers [core::Registers::Register::X] == 0x10);
            REQUIRE (registers [core::Registers::Register::Y] == 0x11);
        }
        AND_WHEN ("Registers are reset")
        {
            registers.reset ();

            REQUIRE (registers [core::Registers::Register::A] == 0x00);
            REQUIRE (registers [core::Registers::Register::X] == 0x00);
            REQUIRE (registers [core::Registers::Register::Y] == 0x00);
        }
    }
}