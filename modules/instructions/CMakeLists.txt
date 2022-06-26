make_library (
  instructions
  SOURCES
  source/instructions/Instruction.h
  source/instructions/LDA.cpp
  source/instructions/LDA.h
  source/instructions/LDX.cpp
  source/instructions/LDX.h
  LIBRARIES
  memory
  core)
make_test (instructions SOURCES tests/TestLDA.cpp tests/TestLDX.cpp)
