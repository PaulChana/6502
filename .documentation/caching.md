# Caching

To improve your build speeds on macOS, you can install [sccache](https://github.com/mozilla/sccache). This will mainly show benefits when you switch brances in git, or where you do a clean

## Installation
```brew install sccache```

## CMake 
Cmake needs to know that you want to enable sccache. You can either do this in `ccmake` by setting the `ENABLE_SCCACHE` option, or you can pass it on the command line to cmake (`-DENABLE_SCCACHE=ON`)