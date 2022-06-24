make_library (utils SOURCES source/utils/FileDownloader.cpp
              source/utils/FileDownloader.h)

make_catch2_test (utils SOURCES tests/TestFileDownloader.cpp)

make_mock (utils SOURCES mocks/utils/MockFileDownloader.cpp
           mocks/utils/MockFileDownloader.h)
