option (ENABLE_ASAN
        "Is the address sanitizer enabled. Applies to CLion and MSVC" OFF)
option (
  ENABLE_SANITIZE_ADDRESS
  "If set, targets will be built with the address sanitizer. Only applies to XCode"
  OFF)
option (
  ENABLE_SANITIZE_UNDEFINED_BEHAVIOUR
  "If set, targets will be built with the undefined behaviour sanitizer. Only applies to XCode"
  OFF)
option (
  ENABLE_SANITIZE_THREADS
  "If set, targets will be built with the thread sanitizer. Only applies to XCode"
  OFF)

function (setup_sanitizers)
  if (ENABLE_ASAN)
    message (STATUS "ASAN has been ENABLED")
    set (SANITIZE_ADDRESS ON)
    if (APPLE)
      set (CMAKE_XCODE_GENERATE_SCHEME ON)
      set (CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER ON)
      set (CMAKE_XCODE_SCHEME_ADDRESS_SANITIZER_USE_AFTER_RETURN ON)
      set (CMAKE_CXX_FLAGS_INIT "-fno-omit-frame-pointer -fsanitize=address")
      set (CMAKE_LINKER_FLAGS_INIT "-fno-omit-frame-pointer -fsanitize=address")
      add_compile_options (-fsanitize=address)
      add_link_options (-fsanitize=address)
    else ()
      set (CMAKE_CXX_FLAGS_INIT "/fsanitize=address")
      add_compile_options (/fsanitize=address)
      add_link_options (-incremental:no /wholearchive:clang_rt.asan-x86_64.lib
                        /wholearchive:clang_rt.asan_cxx-x86_64.lib)
    endif ()
  endif ()

  if (ENABLE_SANITIZE_ADDRESS)
    message (STATUS "XCode address sanitizer has been ENABLED")
    set_target_properties (${TARGET} PROPERTIES XCODE_SCHEME_ADDRESS_SANITIZER
                                                YES)
  endif ()

  if (ENABLE_SANITIZE_UNDEFINED_BEHAVIOUR)
    message (STATUS "XCode undefined behaviour sanitizer has been ENABLED")
    set_target_properties (
      ${TARGET} PROPERTIES XCODE_SCHEME_UNDEFINED_BEHAVIOUR_SANITIZER YES)
  endif ()

  if (ENABLE_SANITIZE_THREADS)
    message (STATUS "XCode thread sanitizer has been ENABLED")
    set_target_properties (${TARGET} PROPERTIES XCODE_SCHEME_THREAD_SANITIZER
                                                YES)
  endif ()
endfunction ()
