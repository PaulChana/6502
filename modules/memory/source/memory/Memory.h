#pragma once

#include <array>
#include <cstdint>

namespace mem
{
class Memory
{
public:
    static constexpr auto memory_size = 1024 * 64;
    using MemoryData = std::array<uint8_t, memory_size>;

    Memory () = default;
    ~Memory () = default;

    void initialise ();

    [[nodiscard]] constexpr size_t size () const noexcept
    {
        return _memory.size ();
    }

    [[nodiscard]] constexpr MemoryData::iterator begin () noexcept
    {
        return _memory.begin ();
    }

    [[nodiscard]] constexpr MemoryData::iterator end () noexcept
    {
        return _memory.end ();
    }

    [[nodiscard]] constexpr MemoryData::const_iterator begin () const noexcept
    {
        return _memory.begin ();
    }

    [[nodiscard]] constexpr MemoryData::const_iterator end () const noexcept
    {
        return _memory.end ();
    }

private:
    MemoryData _memory;
};
}