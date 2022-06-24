#include <catch2/catch_all.hpp>
#include <core/Flags.h>
#include <core/ProgramCounter.h>
#include <core/Registers.h>
#include <instructions/LDA.h>
#include <memory/Memory.h>

SCENARIO ("Can execute LDA immediate", "[instructions/lda]")
{
    GIVEN ("An LDA immediate")
    {
        instructions::LDAImmediate lda;
        REQUIRE (lda.opcode () == 0xA9);
        REQUIRE (lda.mnemonic () == "LDA");
        REQUIRE (lda.cycles () == 2);

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
                memory [0x00] = 0xA9;
                memory [0x01] = 0x10;
                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x10);
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
                memory [0x00] = 0xA9;
                memory [0x01] = 0x84;
                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = false;
                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x84);
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
                memory [0x00] = 0xA9;
                memory [0x01] = 0x00;
                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;
                lda.execute (memory, program_counter, flags, registers);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x00);
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

SCENARIO ("Can execute LDA Zero page", "[instructions/lda]")
{
    GIVEN ("An LDA zero page")
    {
        instructions::LDAZeroPage lda;
        REQUIRE (lda.opcode () == 0xA5);
        REQUIRE (lda.mnemonic () == "LDA");
        REQUIRE (lda.cycles () == 3);

        AND_GIVEN ("Memory and flags")
        {
            memory::Memory memory;
            core::Registers registers;
            core::Flags flags;
            core::ProgramCounter program_counter;
            program_counter = 0;

            WHEN ("It is executed with value of 0x10")
            {
                memory [0x00] = 0xA5;
                memory [0x01] = 0x10;
                memory [0x10] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x0F);
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
                memory [0x00] = 0xA5;
                memory [0x01] = 0x10;
                memory [0x10] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x84);
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
                memory [0x00] = 0xA5;
                memory [0x01] = 0x10;
                memory [0x10] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                lda.execute (memory, program_counter, flags, registers);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x00);
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

SCENARIO ("Can execute LDA Zero page,X", "[instructions/lda]")
{
    GIVEN ("An LDA zero page,X")
    {
        instructions::LDAZeroPageX lda;
        REQUIRE (lda.opcode () == 0xB5);
        REQUIRE (lda.mnemonic () == "LDA");
        REQUIRE (lda.cycles () == 4);

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
                memory [0x00] = 0xB5;
                memory [0x01] = 0x10;
                memory [0x20] = 0x0F;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;

                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x0F);
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
                memory [0x00] = 0xB5;
                memory [0x01] = 0x10;
                memory [0x20] = 0x84;

                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x84);
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
                memory [0x00] = 0xB5;
                memory [0x01] = 0x10;
                memory [0x20] = 0x00;

                flags [core::Flags::Flag::zero] = false;
                flags [core::Flags::Flag::negative] = true;

                lda.execute (memory, program_counter, flags, registers);
                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x00);
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