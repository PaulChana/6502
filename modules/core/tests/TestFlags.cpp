#include <catch2/catch_all.hpp>
#include <core/Flags.h>

SCENARIO ("Flags can be interacted with", "[core]")
{
    GIVEN ("Flags")
    {
        core::Flags flags;

        THEN ("All flags should start as off")
        {
            REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
            REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
            REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
            REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
            REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
            REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
            REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
        }
        AND_THEN ("Flags can be set / get through operators")
        {
            flags [core::Flags::Flag::carry] = true;
            flags [core::Flags::Flag::zero] = true;
            flags [core::Flags::Flag::interrupt_disable] = true;
            flags [core::Flags::Flag::decimal_mode] = true;
            flags [core::Flags::Flag::brk] = true;
            flags [core::Flags::Flag::overflow] = true;
            flags [core::Flags::Flag::negative] = true;

            REQUIRE (flags [core::Flags::Flag::carry]);
            REQUIRE (flags [core::Flags::Flag::zero]);
            REQUIRE (flags [core::Flags::Flag::interrupt_disable]);
            REQUIRE (flags [core::Flags::Flag::decimal_mode]);
            REQUIRE (flags [core::Flags::Flag::brk]);
            REQUIRE (flags [core::Flags::Flag::overflow]);
            REQUIRE (flags [core::Flags::Flag::negative]);
        }
        AND_WHEN ("Flags are reset")
        {
            flags.reset ();

            REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
            REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
            REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
            REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
            REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
            REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
            REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
        }
    }
}