#include <catch2/catch_all.hpp>
#include <core/StackPointer.h>

SCENARIO ("StackPointer can be interacted with", "[core]")
{
    GIVEN ("StackPointer")
    {
        core::StackPointer stackPointer;

        THEN ("All registers should be zeroed")
        {
            REQUIRE (stackPointer == 0x00);
        }
        AND_WHEN ("Stack pointer is reset")
        {
            stackPointer.reset ();

            REQUIRE (stackPointer == 0xFF);
        }
    }
}