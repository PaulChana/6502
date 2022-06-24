#include <catch2/catch_all.hpp>
#include <cpu/Flags.h>

SCENARIO ("Flags can be interacted with", "[cpu]")
{
    GIVEN ("Flags")
    {
        cpu::Flags flags;

        THEN ("All flags should start as off")
        {
            REQUIRE (! flags [cpu::Flags::Flag::carry]);
            REQUIRE (! flags [cpu::Flags::Flag::zero]);
            REQUIRE (! flags [cpu::Flags::Flag::interrupt_disable]);
            REQUIRE (! flags [cpu::Flags::Flag::decimal_mode]);
            REQUIRE (! flags [cpu::Flags::Flag::brk]);
            REQUIRE (! flags [cpu::Flags::Flag::overflow]);
            REQUIRE (! flags [cpu::Flags::Flag::negative]);
        }
        AND_THEN ("Flags can be set / get through operators")
        {
            flags [cpu::Flags::Flag::carry] = true;
            flags [cpu::Flags::Flag::zero] = true;
            flags [cpu::Flags::Flag::interrupt_disable] = true;
            flags [cpu::Flags::Flag::decimal_mode] = true;
            flags [cpu::Flags::Flag::brk] = true;
            flags [cpu::Flags::Flag::overflow] = true;
            flags [cpu::Flags::Flag::negative] = true;

            REQUIRE (flags [cpu::Flags::Flag::carry]);
            REQUIRE (flags [cpu::Flags::Flag::zero]);
            REQUIRE (flags [cpu::Flags::Flag::interrupt_disable]);
            REQUIRE (flags [cpu::Flags::Flag::decimal_mode]);
            REQUIRE (flags [cpu::Flags::Flag::brk]);
            REQUIRE (flags [cpu::Flags::Flag::overflow]);
            REQUIRE (flags [cpu::Flags::Flag::negative]);
        }
        AND_WHEN ("Flags are reset")
        {
            flags.reset ();

            REQUIRE (! flags [cpu::Flags::Flag::carry]);
            REQUIRE (! flags [cpu::Flags::Flag::zero]);
            REQUIRE (! flags [cpu::Flags::Flag::interrupt_disable]);
            REQUIRE (! flags [cpu::Flags::Flag::decimal_mode]);
            REQUIRE (! flags [cpu::Flags::Flag::brk]);
            REQUIRE (! flags [cpu::Flags::Flag::overflow]);
            REQUIRE (! flags [cpu::Flags::Flag::negative]);
        }
    }
}