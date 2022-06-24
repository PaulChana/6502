option (MAKE_TESTS "Enable tests" ON)

function (make_test TARGET)

  if (NOT MAKE_TESTS)
    message (VERBOSE "Tests have been DISABLED")
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
