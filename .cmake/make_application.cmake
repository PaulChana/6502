function (make_application TARGET)

  cmake_parse_arguments (
    ARGS
    ""
    ""
    "SOURCES;LIBRARIES;OUTNAME;BUNDLEID"
    ${ARGN})

  if (APPLE)
    set (PROJECT_RESOURCES project/macOS/application.xcassets
                           project/macOS/document.icns)
    set_source_files_properties (${PROJECT_RESOURCES}
                                 PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  elseif (MSVC)
    set (PROJECT_RESOURCES project/windows/application.ico
                           project/windows/resources.rc)
  endif ()

  source_group (Resources FILES ${PROJECT_RESOURCES} ${BUNDLE_RESOURCES})
  add_executable (${TARGET} ${ARGS_SOURCES} ${PROJECT_RESOURCES})
  target_sources (${TARGET} PRIVATE ${BUNDLE_RESOURCES})
  target_include_directories (${TARGET}
                              PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source)

  if (APPLE)

    target_sources (
      ${TARGET}
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/project/macOS/application.entitlements
    )

    set_target_properties (
      ${TARGET}
      PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST
        "${CMAKE_CURRENT_SOURCE_DIR}/project/macOS/Info.plist"
        XCODE_SCHEME_ENVIRONMENT "OS_ACTIVITY_MODE=disable"
        XCODE_ATTRIBUTE_CLANG_ENABLE_MODULES NO
        XCODE_ATTRIBUTE_COMPILER_INDEX_STORE_ENABLE NO
        XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "application"
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${ARGS_BUNDLEID}
        XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@loader_path/../Frameworks"
        XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME Yes
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS
        "${CMAKE_CURRENT_SOURCE_DIR}/project/macOS/application.entitlements"
        OUTPUT_NAME ${ARGS_OUTNAME}
        COMPILER_INDEX_STORE_ENABLE NO
        BUILD_RPATH "@loader_path/../Frameworks"
        RESOURCE "${BUNDLE_RESOURCES}")

  elseif (MSVC)

    set_target_properties (${TARGET} PROPERTIES WIN32_EXECUTABLE TRUE
                                                OUTPUT_NAME ${ARGS_OUTNAME})

    set_property (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  PROPERTY VS_STARTUP_PROJECT ${TARGET})
  endif ()

  target_link_libraries (${TARGET} PRIVATE ${ARGS_LIBRARIES})
  set_common_properties (${TARGET})

endfunction ()
