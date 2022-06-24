option (MAKE_TEST_EXE "Should test executable targets be made" ON)

function (make_test_executable TARGET)

  if (NOT MAKE_TEST_EXE)
    message (VERBOSE "Executable tests have been DISABLED")
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

  if (APPLE)
    string (CONCAT BUNDLE_ID "com.focusrite-novation-ampify." ${TARGET})

    set_target_properties (
      ${TEST_TARGET}
      PROPERTIES MACOSX_BUNDLE TRUE
                 MACOSX_BUNDLE_INFO_PLIST
                 "${CMAKE_CURRENT_SOURCE_DIR}/tests/Info.plist"
                 XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${BUNDLE_ID})
  elseif (MSVC)
    set_target_properties (${TEST_TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)
  endif ()

  target_link_libraries (${TEST_TARGET} PRIVATE ${TARGET} ${ARGS_LIBRARIES})
  set_common_properties (${TEST_TARGET})
endfunction ()
