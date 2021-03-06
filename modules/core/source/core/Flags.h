#pragma once

#include <bitset>
#include <cstdint>

namespace core
{
class Flags
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
    static constexpr auto number_of_flags = 7;
    static_assert (size_t (Flag::negative) + 1 == number_of_flags, "Expected 7 flags");

    Flags () = default;
    ~Flags () = default;
    Flags (const Flags & other) = delete;
    Flags & operator= (const Flags & other) = delete;

    void reset ();

    [[nodiscard]] bool operator[] (Flag flag) const;
    [[nodiscard]] std::bitset<number_of_flags>::reference operator[] (Flag flag) noexcept;

    class Watcher
    {
    public:
        Watcher (Flags & flags);

        [[nodiscard]] bool has_changed () const;

    private:
        Flags & _flags;
        std::bitset<number_of_flags> _source_flags;
    };

private:
    std::bitset<number_of_flags> _flags = {false};
};
}
