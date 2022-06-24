#pragma once
#include <cstdint>

namespace cpu
{
class StackPointer
{
public:
    StackPointer () = default;
    ~StackPointer () = default;
    StackPointer (const StackPointer & other) = delete;
    StackPointer & operator= (const StackPointer & other) = delete;

    [[nodiscard]] bool operator== (uint8_t value) const;

    void reset ();

private:
    uint8_t _address = 0x00;
};
}
