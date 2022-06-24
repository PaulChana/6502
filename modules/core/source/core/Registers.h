#pragma once

#include <array>
#include <cstdint>

namespace core
{
class Registers
{
public:
    enum class Register
    {
        A,
        X,
        Y
    };

    Registers () = default;
    ~Registers () = default;
    Registers (const Registers & other) = delete;
    Registers & operator= (const Registers & other) = delete;

    void reset ();

    [[nodiscard]] uint8_t operator[] (Register index) const;
    [[nodiscard]] uint8_t & operator[] (Register index);

private:
    static constexpr auto num_registers = 3;
    static_assert (size_t (Register::Y) + 1 == num_registers, "Expected 3 registers");
    std::array<uint8_t, num_registers> _registers = {0x00, 0x00, 0x00};
};
}
