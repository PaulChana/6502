option (MAKE_TEST "Should test targets be made" ON)

function (make_test TARGET)

  if (NOT MAKE_TEST)
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

  string (
    CONCAT LOG_DIR
           "--log="
           ${PROJECT_SOURCE_DIR}
           "/logs/unit-tests/"
           ${TEST_TARGET}
           ".log")

  add_test (NAME ${TEST_TARGET} COMMAND ${TEST_TARGET} ${LOG_DIR})
  set_tests_properties (${TEST_TARGET} PROPERTIES TIMEOUT 300)
  set_target_properties (${TEST_TARGET} PROPERTIES FOLDER tests)

  if (MSVC)
    set_target_properties (${TEST_TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)
    set_property (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  PROPERTY VS_STARTUP_PROJECT ${TEST_TARGET})
  endif ()

  target_link_libraries (${TEST_TARGET} PRIVATE ${TARGET} ${ARGS_LIBRARIES})
  set_common_properties (${TEST_TARGET})

endfunction ()
