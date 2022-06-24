option (ENABLE_SCCACHE "If set (and sccache is installed), it will be used" OFF)

function (setup_compiler_cache)
  if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    return ()
  endif ()

  if (NOT ENABLE_SCCACHE)
    return ()
  endif ()

  if (MSVC)
    message (STATUS "SCCACHE is not current supported by visual studio")
    return ()
  endif ()

  find_program (SCCACHE_PROGRAM sccache)
  if (NOT SCCACHE_PROGRAM)
    message (
      STATUS
        "SCCACHE was not found. For faster builds, install SCCACHE. See readme for details"
    )
    return ()
  endif ()

  message (VERBOSE "Found sccache on ${sccache}")

  if (CMAKE_GENERATOR MATCHES "Ninja|Makefiles")

    message (VERBOSE "Enabled sccache for Makefiles")

    foreach (lang IN ITEMS C CXX OBJC OBJCXX)
      set (
        CMAKE_${lang}_COMPILER_LAUNCHER
        ${CMAKE_COMMAND}
        -E
        env
        ${ccacheEnv}
        ${SCCACHE_PROGRAM}
        PARENT_SCOPE)
    endforeach ()

  elseif (CMAKE_GENERATOR STREQUAL Xcode)

    message (VERBOSE "Enabled sccache for Xcode")

    foreach (lang IN ITEMS C CXX)
      set (launch${lang} ${CMAKE_BINARY_DIR}/launch-${lang})

      file (WRITE ${launch${lang}} "#!/bin/bash\n\n")

      foreach (keyVal IN LISTS ccacheEnv)
        file (APPEND ${launch${lang}} "export ${keyVal}\n")
      endforeach ()

      file (
        APPEND ${launch${lang}}
        "exec \"${SCCACHE_PROGRAM}\" \"${CMAKE_${lang}_COMPILER}\" \"$@\"\n")

      execute_process (COMMAND chmod a+rx ${launch${lang}})

    endforeach ()

    set (CMAKE_XCODE_ATTRIBUTE_CC ${launchC} PARENT_SCOPE)
    set (CMAKE_XCODE_ATTRIBUTE_CXX ${launchCXX} PARENT_SCOPE)
    set (CMAKE_XCODE_ATTRIBUTE_LD ${launchC} PARENT_SCOPE)
    set (CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS ${launchCXX} PARENT_SCOPE)
  endif ()
endfunction ()
