#pragma once

#include <array>
#include <cstdint>

namespace memory
{
class Memory
{
public:
    static constexpr uint32_t memory_size = 65'536;
    static constexpr size_t reset_vector_address [2] = {0xFFFC, 0xFFFD};

    using MemoryData = std::array<uint8_t, memory_size>;

    Memory () = default;
    ~Memory () = default;

    Memory (const Memory & other) = delete;
    Memory & operator= (const Memory & other) = delete;

    void initialise ();

    [[nodiscard]] uint8_t operator[] (size_t index) const;
    [[nodiscard]] uint8_t & operator[] (size_t index);

    [[nodiscard]] uint16_t read (size_t index) const;

    static bool crosses_page_boundary (size_t address1, size_t address2);

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