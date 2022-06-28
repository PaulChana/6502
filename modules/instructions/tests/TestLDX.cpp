#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/LDX.h>
#include <memory/Memory.h>

SCENARIO ("Can execute LDX immediate", "[instructions/ldx]")
{
    GIVEN ("An LDX immediate")
    {
        instructions::LDXImmediate ldx;
        REQUIRE (ldx.opcode () == 0xA2);
        REQUIRE (ldx.mnemonic () == "LDX");

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            WHEN ("It is executed with value of 0x10")
            {
                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                memory [0x00] = 0xA2;
                memory [0x01] = 0x10;
                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x10);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                program_counter = 0;
                memory [0x00] = 0xA2;
                memory [0x01] = 0x84;
                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = false;
                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x84);
                    REQUIRE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                program_counter = 0;
                memory [0x00] = 0xA2;
                memory [0x01] = 0x00;
                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x00);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
        }
    }
}

SCENARIO ("Can execute LDX Zero page", "[instructions/ldx]")
{
    GIVEN ("An LDX zero page")
    {
        instructions::LDXZeroPage ldx;
        REQUIRE (ldx.opcode () == 0xA6);
        REQUIRE (ldx.mnemonic () == "LDX");

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xA6;
                memory [0x01] = 0x10;
                memory [0x10] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x0F);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                memory [0x00] = 0xA6;
                memory [0x01] = 0x10;
                memory [0x10] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x84);
                    REQUIRE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                memory [0x00] = 0xA6;
                memory [0x01] = 0x10;
                memory [0x10] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x00);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
        }
    }
}

SCENARIO ("Can execute LDX Zero page,Y", "[instructions/ldx]")
{
    GIVEN ("An LDX zero page,Y")
    {
        instructions::LDXZeroPageY ldx;
        REQUIRE (ldx.opcode () == 0xB6);
        REQUIRE (ldx.mnemonic () == "LDX");

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            registers [core::Registers::Register::Y] = 0x10;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xB6;
                memory [0x01] = 0x10;
                memory [0x20] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x0F);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                memory [0x00] = 0xB6;
                memory [0x01] = 0x10;
                memory [0x20] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x84);
                    REQUIRE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                memory [0x00] = 0xB6;
                memory [0x01] = 0x10;
                memory [0x20] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldx.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::X] == 0x00);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == 2);
                }
            }
        }
    }
}