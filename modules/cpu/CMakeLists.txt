make_library (
    cpu
    SOURCES
    source/cpu/CPU.cpp
    source/cpu/CPU.h
    source/cpu/Flags.cpp
    source/cpu/Flags.h
    source/cpu/Instruction.h
    source/cpu/ProgramCounter.cpp
    source/cpu/ProgramCounter.h
    source/cpu/Registers.cpp
    source/cpu/Registers.h
    source/cpu/StackPointer.cpp
    source/cpu/StackPointer.h
    LIBRARIES
    memory)
make_test (
    cpu
    SOURCES
    tests/TestCPU.cpp
    tests/TestFlags.cpp
    tests/TestRegisters.cpp)
