# C++

# Formatting

For _C++_ we use _clang-format_.

## Installation (XCode)
```
brew install clang-format
```

## Installation (CLion)
If you are using _Clion_, code formatting is automatically provided by the IDE, because we have a `.clang-format` file in the root of the directory. 
In order to enable this behaviour, you need to
```
Use the save actions plug-in to enable format on save.
The settings are:
  * 'Activate save action on save' should be enabled
  * Formatting actions: 'Re-format file' should be enabled
  * File path exclusions should have: CMakeLists.txt and lib/*
```

## Installation (VS2019)
_Visual studio 2019_ has built in clang-format support, but it is a very old version. To use a more modern version, you need to install the [clang tools](http://llvm.org/releases/3.7.0/LLVM-3.7.0-win64.exe) then add `%LLVM%\bin` to your path (`%LLVM%` is where you installed to)

## Automatic formatting
* Set the CMake option `ENABLE_CODE_FORMATTING` to add a target (`format-all`) which will reformat your codebase. 
* Set the CMake option `ENABLE_FORMAT_CODE_ON_BUILD` to add a target (`format`) which will be added as a dependency to all targets. When you hit build, this will reformat your code for you. This has some pros (code is always formatted), but the downside is that you will lose some undo / redo history on a file that  gets formatted. This is especially obvious in Xcode. We recommend that you use CLion.