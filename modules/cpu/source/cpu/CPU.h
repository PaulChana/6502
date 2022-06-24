#pragma once

#include <bitset>
#include <cstdint>
#include <memory/Memory.h>

namespace cpu
{
class CPU
{
public:
    enum class Flag
    {
        carry = 0,
        zero,
        interrupt_disable,
        decimal_mode,
        brk,
        overflow,
        negative,
    };

    CPU (memory::Memory & memory);
    ~CPU () = default;

    CPU (const CPU & other) = delete;
    CPU & operator= (const CPU & other) = delete;

    void reset ();

    [[nodiscard]] uint16_t program_counter () const noexcept;
    [[nodiscard]] uint8_t stack_pointer () const noexcept;

    [[nodiscard]] uint8_t a () const noexcept;
    [[nodiscard]] uint8_t x () const noexcept;
    [[nodiscard]] uint8_t y () const noexcept;

    [[nodiscard]] bool flag (Flag flag) const noexcept;

private:
    static constexpr auto number_of_flags = 7;
    static_assert (size_t (Flag::negative) + 1 == number_of_flags, "Expected 7 flags");

    void reset_program_counter ();
    void reset_stack_pointer ();
    void reset_registers ();
    void reset_flags ();

    memory::Memory & _memory;

    uint16_t _program_counter = 0x00;
    uint8_t _stack_pointer = 0x00;
    uint8_t _a = 0x00;
    uint8_t _x = 0x00;
    uint8_t _y = 0x00;
    std::bitset<number_of_flags> _flags;
};
}