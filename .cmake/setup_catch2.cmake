option (ENABLE_CATCH2 "If set will enable catch2 as a test framework" OFF)

function (setup_catch2)
  if (NOT ENABLE_CATCH2)
    return ()
  endif ()

  fetchcontent_declare (
    Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.0-preview3)

  fetchcontent_makeavailable (Catch2)
endfunction ()
