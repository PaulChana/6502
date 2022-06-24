function (set_common_properties TARGET)

  set_target_properties (
    ${TARGET}
    PROPERTIES CXX_STANDARD 17
               CXX_EXTENSIONS OFF
               UNITY_BUILD ON
               UNITY_BUILD_MODE BATCH
               UNITY_BUILD_BATCH_SIZE 25)

  exclude_objc_from_unity (${TARGET})

  if (ENABLE_FORMAT_CODE_ON_BUILD)
    add_dependencies (${TARGET} format)
  endif ()

  if (APPLE)

    set_xcode_properties (${TARGET})

    target_compile_definitions (
      ${TARGET} PUBLIC $<IF:$<CONFIG:Debug>,_DEBUG=1,_NDEBUG=1>
                       $<IF:$<CONFIG:Debug>,DEBUG=1,NDEBUG=1>)

    target_link_options (${TARGET} PRIVATE -ObjC)

    target_compile_options (
      ${TARGET}
      PRIVATE -Wall
              -Wextra
              -Wshadow
              -Werror
              -Wreorder
              -Wstring-conversion
              -Wimplicit-int-float-conversion
              -Wnon-virtual-dtor
              -Wunused-private-field
              $<IF:$<CONFIG:Debug>,-DDEBUG,-DNDEBUG>
              $<$<CONFIG:Release>:-DRELEASE>)

  elseif (MSVC)

    target_compile_options (
      ${TARGET}
      PRIVATE $<IF:$<CONFIG:Debug>,/Od,/Ox>
              $<$<CONFIG:Release>:/O2>
              /W4
              /WX
              /MP)

    target_link_options (${TARGET} PRIVATE $<$<CONFIG:Release>:/MAP>
                         $<$<CONFIG:Release>:/DEBUG:FULL>)

  endif ()

endfunction ()
