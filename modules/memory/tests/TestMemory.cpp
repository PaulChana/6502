#include <catch2/catch_all.hpp>
#include <memory/Memory.h>

SCENARIO ("Memory behaves properly", "[memory]")
{
    GIVEN ("A memory block")
    {
        mem::Memory memory;
        REQUIRE (memory.size () > 0);

        WHEN ("The memory is initialised")
        {
            memory.initialise ();

            THEN ("The memory should all be zero")
            {
                for (const auto & byte : memory)
                    REQUIRE (byte == 0x00);
            }
        }
    }
}
