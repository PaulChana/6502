#include <catch2/catch_all.hpp>
#include <memory/Memory.h>

SCENARIO ("Memory behaves properly", "[memory]")
{
    GIVEN ("A memory block")
    {
        memory::Memory memory;
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

SCENARIO ("Memory watchers trigger", "[memory]")
{
    GIVEN ("Memory and watcher")
    {
        memory::Memory memory;
        memory.initialise ();
        memory::Memory::Watcher watcher (memory);
        REQUIRE (! watcher.has_changed ());

        WHEN ("The memory changes, the watcher updates")
        {
            memory [0] = 0xFF;
            REQUIRE (watcher.has_changed ());

            AND_WHEN ("It is changed back")
            {
                memory [0] = 0x00;
                REQUIRE (! watcher.has_changed ());
            }
        }
    }
}

SCENARIO ("Memory can be read", "[memory]")
{
    GIVEN ("An initialised memory block")
    {
        memory::Memory memory;
        memory.initialise ();

        WHEN ("We read in range")
        {
            for (uint32_t index = 0; index < memory::Memory::memory_size; ++index)
            {
                THEN ("we get back zero")
                {
                    REQUIRE (memory [index] == 0x00);
                }
            }
        }

        WHEN ("We read outside of the range")
        {
            THEN ("We expect an exception")
            {
                REQUIRE_THROWS_AS (memory [memory::Memory::memory_size], std::invalid_argument);
            }
        }
    }
}

SCENARIO ("Memory can be written", "[memory]")
{
    GIVEN ("An initialised memory block")
    {
        memory::Memory memory;
        memory.initialise ();

        WHEN ("We write in range")
        {
            for (uint32_t index = 0; index < memory::Memory::memory_size; ++index)
            {
                memory [index] = index % 0xFF;
                THEN ("we get back 0xFF")
                {
                    REQUIRE (memory [index] == index % 0xFF);
                }
            }
        }

        WHEN ("We read outside of the range")
        {
            THEN ("We expect an exception")
            {
                REQUIRE_THROWS_AS (memory [memory::Memory::memory_size] = 0xFF,
                                   std::invalid_argument);
            }
        }
    }
}
