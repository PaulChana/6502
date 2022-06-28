#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/LDY.h>
#include <memory/Memory.h>

SCENARIO ("Can execute LDY immediate", "[instructions/ldy]")
{
    GIVEN ("An LDY immediate")
    {
        instructions::LDYImmediate ldy;
        REQUIRE (ldy.opcode () == 0xA0);

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
                memory [0x00] = 0xA0;
                memory [0x01] = 0x10;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x10);
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
                memory [0x00] = 0xA0;
                memory [0x01] = 0x84;
                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = false;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x84);
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
                memory [0x00] = 0xA0;
                memory [0x01] = 0x00;
                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 2);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x00);
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

SCENARIO ("Can execute LDY Zero page", "[instructions/ldy]")
{
    GIVEN ("An LDY zero page")
    {
        instructions::LDYZeroPage ldy;
        REQUIRE (ldy.opcode () == 0xA4);

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xA4;
                memory [0x01] = 0x10;
                memory [0x10] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x0F);
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
                memory [0x00] = 0xA4;
                memory [0x01] = 0x10;
                memory [0x10] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x84);
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
                memory [0x00] = 0xA4;
                memory [0x01] = 0x10;
                memory [0x10] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 3);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x00);
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

SCENARIO ("Can execute LDY Zero page,X", "[instructions/ldy]")
{
    GIVEN ("An LDY zero page,X")
    {
        instructions::LDYZeroPageX ldy;
        REQUIRE (ldy.opcode () == 0xB4);

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            registers [core::Registers::Register::X] = 0x10;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xB4;
                memory [0x01] = 0x10;
                memory [0x20] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x0F);
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
                memory [0x00] = 0xB4;
                memory [0x01] = 0x10;
                memory [0x20] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x84);
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
                memory [0x00] = 0xB4;
                memory [0x01] = 0x10;
                memory [0x20] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x00);
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

SCENARIO ("Can execute LDY Absolute", "[instructions/ldy]")
{
    GIVEN ("An LDY Absolute")
    {
        instructions::LDYAbsolute ldy;
        REQUIRE (ldy.opcode () == 0xAC);

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xAC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x80] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x0F);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                memory [0x00] = 0xAC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x80] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x84);
                    REQUIRE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                memory [0x00] = 0xAC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x80] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x00);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
        }
    }
}

SCENARIO ("Can execute LDY Absolute,X", "[instructions/ldy]")
{
    GIVEN ("An LDY Absolute X")
    {
        instructions::LDYAbsoluteX ldy;
        REQUIRE (ldy.opcode () == 0xBC);

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            registers [core::Registers::Register::X] = 0x01;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xBC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x81] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x0F);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                memory [0x00] = 0xBC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x81] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x84);
                    REQUIRE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                memory [0x00] = 0xBC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x81] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                REQUIRE (cycles == 4);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x00);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
            AND_WHEN ("It goes over a page boundary")
            {
                registers [core::Registers::Register::X] = 0x80;

                memory [0x00] = 0xBC;
                memory [0x01] = 0x80;
                memory [0x02] = 0x00;
                memory [0x100] = 0x05;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                auto cycles = ldy.execute (memory, program_counter, flags, registers);
                THEN ("It should take more cycles")
                {
                    REQUIRE (cycles == 5);
                }
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::Y] == 0x05);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 3")
                {
                    REQUIRE (program_counter == 3);
                }
            }
        }
    }
}