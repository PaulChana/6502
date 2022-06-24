function (make_library TARGET)
  cmake_parse_arguments (
    ARGS
    ""
    ""
    "SOURCES;LIBRARIES"
    ${ARGN})

  source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ARGS_SOURCES})
  add_library (${TARGET} STATIC ${ARGS_SOURCES})
  target_link_libraries (${TARGET} PUBLIC ${ARGS_LIBRARIES})
  target_include_directories (${TARGET}
                              PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/source")
  set_common_properties (${TARGET})
  set_target_properties (${TARGET} PROPERTIES FOLDER modules)
endfunction ()
