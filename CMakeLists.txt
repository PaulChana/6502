cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

include (.cmake/global_options.cmake)
include (.cmake/global_includes.cmake)

include (.cmake/xcode_properties.cmake)
include (.cmake/common_properties.cmake)
include (.cmake/make_library.cmake)
include (.cmake/make_mock.cmake)
include (.cmake/make_test.cmake)
include (.cmake/utility_functions.cmake)

include (.cmake/setup_catch2.cmake)
include (.cmake/setup_code_formatter.cmake)
include (.cmake/setup_compiler_cache.cmake)
include (.cmake/setup_sanitizers.cmake)
include (.cmake/setup_time_trace.cmake)

project ("6502")

enable_testing ()

setup_catch2 ()
setup_code_formatter ()
setup_compiler_cache ()
setup_sanitizers ()
setup_time_trace ()

add_subdirectory (modules/memory)
add_subdirectory (modules/cpu)
