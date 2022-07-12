make_library (
  instructions
  SOURCES
  source/instructions/Instruction.h
  source/instructions/CLC.cpp
  source/instructions/CLC.h
  source/instructions/LD.cpp
  source/instructions/LD.h
  source/instructions/LDA.cpp
  source/instructions/LDA.h
  source/instructions/LDX.cpp
  source/instructions/LDX.h
  source/instructions/LDY.cpp
  source/instructions/LDY.h
  source/instructions/NOP.cpp
  source/instructions/NOP.h
  LIBRARIES
  memory
  core)

make_test (
  instructions
  SOURCES
  tests/TestCLC.cpp
  tests/TestLDA.cpp
  tests/TestLDX.cpp
  tests/TestLDY.cpp
  tests/TestNOP.cpp)
