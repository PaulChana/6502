#include <catch2/catch_all.hpp>
#include <core/FlagController.h>
#include <core/Flags.h>
#include <core/Registers.h>

SCENARIO ("Flag watchers trigger", "[core]")
{
    GIVEN ("Flags and watcher")
    {
        core::Flags flags;
        core::Flags::Watcher watcher (flags);
        REQUIRE (! watcher.has_changed ());

        WHEN ("The flag state changes, the watcher updates")
        {
            flags [core::Flags::Flag::zero] = true;
            REQUIRE (watcher.has_changed ());

            AND_WHEN ("It is changed back")
            {
                flags [core::Flags::Flag::zero] = false;
                REQUIRE (! watcher.has_changed ());
            }
        }
    }
}

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

SCENARIO ("Flags can be updated from registers", "[core]")
{
    GIVEN ("Flags, registers and a controller")
    {
        core::Flags flags;
        core::Registers registers;
        WHEN ("Flags are updated from zero A register")
        {
            flags [core::Flags::Flag::zero] = false;

            registers [core::Registers::Register::A] = 0x00;
            registers [core::Registers::Register::X] = 0x01;
            registers [core::Registers::Register::Y] = 0x01;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::A);

            THEN ("Zero flag should be set")
            {
                REQUIRE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
            }
        }
        AND_WHEN ("Flags are updated from zero X register")
        {
            flags [core::Flags::Flag::zero] = false;

            registers [core::Registers::Register::A] = 0x01;
            registers [core::Registers::Register::X] = 0x00;
            registers [core::Registers::Register::Y] = 0x01;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::X);

            THEN ("Zero flag should be set")
            {
                REQUIRE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
            }
        }
        AND_WHEN ("Flags are updated from zero Y register")
        {
            flags [core::Flags::Flag::zero] = false;

            registers [core::Registers::Register::A] = 0x01;
            registers [core::Registers::Register::X] = 0x01;
            registers [core::Registers::Register::Y] = 0x00;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::Y);

            THEN ("Zero flag should be set")
            {
                REQUIRE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
            }
        }
        AND_WHEN ("Flags are updated from negative A register")
        {
            flags [core::Flags::Flag::negative] = false;

            registers [core::Registers::Register::A] = 0x80;
            registers [core::Registers::Register::X] = 0x00;
            registers [core::Registers::Register::Y] = 0x00;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::A);

            THEN ("Negative flag should be set")
            {
                REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE (flags [core::Flags::Flag::negative]);
            }
        }
        AND_WHEN ("Flags are updated from negative X register")
        {
            flags [core::Flags::Flag::negative] = false;

            registers [core::Registers::Register::A] = 0x00;
            registers [core::Registers::Register::X] = 0x80;
            registers [core::Registers::Register::Y] = 0x00;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::X);

            THEN ("Negative flag should be set")
            {
                REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE (flags [core::Flags::Flag::negative]);
            }
        }

        AND_WHEN ("Flags are updated from negative Y register")
        {
            flags [core::Flags::Flag::negative] = false;

            registers [core::Registers::Register::A] = 0x00;
            registers [core::Registers::Register::X] = 0x00;
            registers [core::Registers::Register::Y] = 0x80;

            core::FlagController::update_flags_ld (flags, registers, core::Registers::Register::Y);

            THEN ("Negative flag should be set")
            {
                REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                REQUIRE_FALSE (flags [core::Flags::Flag::carry]);
                REQUIRE_FALSE (flags [core::Flags::Flag::interrupt_disable]);
                REQUIRE_FALSE (flags [core::Flags::Flag::decimal_mode]);
                REQUIRE_FALSE (flags [core::Flags::Flag::brk]);
                REQUIRE_FALSE (flags [core::Flags::Flag::overflow]);
                REQUIRE (flags [core::Flags::Flag::negative]);
            }
        }
    }
}