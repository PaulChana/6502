option (MAKE_MOCKS "Should mock targets be made" ON)

function (make_mock TARGET)
  if (NOT MAKE_MOCKS)
    message (VERBOSE "Mocks have been DISABLED")
    return ()
  endif ()

  cmake_parse_arguments (
    ARGS
    ""
    ""
    "SOURCES;LIBRARIES"
    ${ARGN})

  string (CONCAT MOCK_TARGET "mock-" ${TARGET})

  add_library (${MOCK_TARGET} ${ARGS_SOURCES})
  set_common_properties (${MOCK_TARGET})
  target_link_libraries (${MOCK_TARGET} PUBLIC ${TARGET} ${ARGS_LIBRARIES})
  target_include_directories (${MOCK_TARGET} PUBLIC mocks)
  set_target_properties (${MOCK_TARGET} PROPERTIES FOLDER mocks)
endfunction ()
