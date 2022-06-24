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
            const uint16_t current_counter = program_counter;
            memory [current_counter] = 0xA9;

            WHEN ("It is executed with value of 0x10")
            {
                flags [core::Flags::Flag::zero] = true;
                flags [core::Flags::Flag::negative] = true;
                memory [current_counter + 1] = 0x10;
                lda.execute (memory, program_counter, flags, registers);

                THEN ("A,Z,N should be set properly")
                {
                    REQUIRE (registers [core::Registers::Register::A] == 0x10);
                    REQUIRE_FALSE (flags [core::Flags::Flag::negative]);
                    REQUIRE_FALSE (flags [core::Flags::Flag::zero]);
                }
                THEN ("Program counter should be incremented by 2")
                {
                    REQUIRE (program_counter == current_counter + 2);
                }
            }
            AND_WHEN ("It is executed with negative value")
            {
                program_counter = current_counter;
                memory [current_counter + 1] = 0x84;
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
                    REQUIRE (program_counter == current_counter + 2);
                }
            }
            AND_WHEN ("It is executed with zero value")
            {
                program_counter = current_counter;
                memory [current_counter + 1] = 0x00;
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
                    REQUIRE (program_counter == current_counter + 2);
                }
            }
        }
    }
}