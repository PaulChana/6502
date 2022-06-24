make_library (
  core
  SOURCES
  source/core/Flags.cpp
  source/core/Flags.h
  source/core/ProgramCounter.cpp
  source/core/ProgramCounter.h
  source/core/Registers.cpp
  source/core/Registers.h
  source/core/StackPointer.cpp
  source/core/StackPointer.h
  LIBRARIES
  memory)
make_test (
  core
  SOURCES
  tests/TestFlags.cpp
  tests/TestProgramCounter.cpp
  tests/TestRegisters.cpp
  tests/TestStackPointer.cpp)
