option (ENABLE_CODE_FORMATTING
        "Create a target that will reformat your code using clang-format" OFF)

option (
  ENABLE_FORMAT_CODE_ON_BUILD
  "If set (and clang-format is installed), code will be autoformatted as part of the build"
  OFF)

function (setup_code_formatter)
  if (NOT ENABLE_FORMAT_CODE_ON_BUILD AND NOT ENABLE_CODE_FORMATTING)
    return ()
  endif ()

  find_program (CLANGFORMAT "clang-format")
  if (NOT CLANGFORMAT)
    message (
      STATUS
        "Couldn't find clang format. If you would like auto formatting, install clang format (see readme.md)"
    )
    set (ENABLE_FORMAT_CODE_ON_BUILD OFF CACHE BOOL "" FORCE)
    set (ENABLE_CODE_FORMATTING OFF CACHE BOOL "" FORCE)
    return ()
  endif ()

  if (ENABLE_FORMAT_CODE_ON_BUILD)
    add_custom_target (
      format
      COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/.scripts/format-on-build.js"
              "format" "--root" "${CMAKE_CURRENT_SOURCE_DIR}")
    set_target_properties (format PROPERTIES FOLDER utilities)
  endif ()

  if (ENABLE_CODE_FORMATTING)
    add_custom_target (format-all COMMAND npm run format)
    set_target_properties (format-all PROPERTIES FOLDER utilities)
  endif ()
endfunction ()
