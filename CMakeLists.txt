cmake_minimum_required (VERSION 3.20 FATAL_ERROR)

# =======================================================
# Global options (such as min os versions, DLL link options will be specified in
# these global includes
# =======================================================
include (.cmake/global_options.cmake)
include (.cmake/global_includes.cmake)

# =======================================================
# These includes are all the core parts of the cmake architecture They let you
# easily make static libs, executables, tests as well as utilities that will let
# you alter projects. Note that mocks and all test variants can be disabled
# using the options defined in the top of each file. They default to being on -
# so you need to actively disable them to avoid generation. The one exception
# here is make_application, which assumes it is the main application and cannot
# be disabled
# =======================================================
include (.cmake/xcode_properties.cmake)
include (.cmake/common_properties.cmake)
include (.cmake/make_application.cmake)
include (.cmake/make_library.cmake)
include (.cmake/make_mock.cmake)
include (.cmake/make_catch2_test.cmake)
include (.cmake/make_test_exe.cmake)
include (.cmake/make_test.cmake)
include (.cmake/utility_functions.cmake)

# =======================================================
# Utility options all get pulled in here. These are build time utilities such as
# code formatting, caches, santisers etc that will let you inspect or otherwise
# work faster. Each of these files will include options at the top to let you
# customise their behaviour. By default they will all be off
# =======================================================
include (.cmake/setup_catch2.cmake)
include (.cmake/setup_code_formatter.cmake)
include (.cmake/setup_compiler_cache.cmake)
include (.cmake/setup_sanitizers.cmake)
include (.cmake/setup_time_trace.cmake)

project ("SuperProject")

enable_testing ()

# =======================================================
# Call all the setup routines. In the default state these will do nothing unless
# you enable the options as defined in the include files
# =======================================================
setup_catch2 ()
setup_code_formatter ()
setup_compiler_cache ()
setup_sanitizers ()
setup_time_trace ()

# =======================================================
# Defining some basic modules that we might want to use later. Each of these is
# a self contained unit with its own tests, mocks etc
# =======================================================
add_subdirectory (modules/utils)

# =======================================================
# Here we will define our main application
# =======================================================
make_application (
  SuperProject
  SOURCES
  project/source/main.cpp
  LIBRARIES
  utils
  OUTNAME
  "Super project"
  BUNDLEID
  "com.focusrite.bar")
