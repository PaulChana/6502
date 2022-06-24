make_library (
  cpu
  SOURCES
  source/cpu/CPU.cpp
  source/cpu/CPU.h
  LIBRARIES
  core
  memory)
make_test (cpu SOURCES tests/TestCPU.cpp)
