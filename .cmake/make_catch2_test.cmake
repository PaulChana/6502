option (MAKE_CATCH2_TESTS "Enable catch2 tests" ON)

function (make_catch2_test TARGET)

  if (NOT MAKE_CATCH2_TESTS)
    message (VERBOSE "Catch2 tests have been DISABLED")
    return ()
  endif ()

  if (NOT ENABLE_CATCH2)
    message (
      FATAL_ERROR
        "Catch2 is not enabled, make sure you call cmake with -DENABLE_CATCH2=1"
    )
    return ()
  endif ()

  cmake_parse_arguments (
    ARGS
    ""
    ""
    "SOURCES;LIBRARIES"
    ${ARGN})

  string (CONCAT TEST_TARGET "test-" ${TARGET})
  add_executable (${TEST_TARGET} ${ARGS_SOURCES})

  source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ARGS_SOURCES})

  set_target_properties (${TEST_TARGET} PROPERTIES FOLDER tests)

  target_link_libraries (${TEST_TARGET} PRIVATE ${ARGS_LIBRARIES} ${TARGET}
                                                Catch2::Catch2WithMain)
  set_common_properties (${TEST_TARGET})
  add_test (NAME ${TEST_TARGET} COMMAND ${TEST_TARGET} --verbosity high)
  set_target_properties (${TEST_TARGET} PROPERTIES UNITY_BUILD OFF)
endfunction ()
