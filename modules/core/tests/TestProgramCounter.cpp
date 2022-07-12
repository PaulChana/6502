#include <catch2/catch_all.hpp>
#include <core/ProgramCounter.h>
#include <memory/Memory.h>

SCENARIO ("ProgramCounter can be interacted with", "[core]")
{
    GIVEN ("ProgramCounter")
    {
        core::ProgramCounter counter;
        REQUIRE (counter == 0x00);

        AND_GIVEN ("Memory")
        {
            memory::Memory memory;
            memory [memory::Memory::reset_vector_address [0]] = 0x00;
            memory [memory::Memory::reset_vector_address [1]] = 0x10;

            WHEN ("Program counter is reset")
            {
                counter.reset (memory);
                THEN ("Program counter should read from the reset vector")
                {
                    REQUIRE (counter == 0x1000);
                }
                AND_THEN ("We can cast back to an address")
                {
                    uint16_t counter_value = counter;
                    REQUIRE (counter_value == 0x1000);
                }
                AND_THEN ("We can offset the counter")
                {
                    counter += 0x05;
                    REQUIRE (counter == 0x1005);
                }
                AND_THEN ("We can increment the counter")
                {
                    counter++;
                    REQUIRE (counter == 0x1001);
                }
                AND_THEN ("We can increment the counter")
                {
                    ++counter;
                    REQUIRE (counter == 0x1001);
                }
                AND_THEN ("We can decrement the counter")
                {
                    counter--;
                    REQUIRE (counter == 0xFFF);
                }
                AND_THEN ("We can decrement the counter")
                {
                    --counter;
                    REQUIRE (counter == 0xFFF);
                }
                AND_WHEN ("We set the counter")
                {
                    counter = 0x0100;
                    REQUIRE (counter == 0x100);
                }
            }
        }
    }
}