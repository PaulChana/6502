#!/bin/bash

if ! command -v choco &> /dev/null
then
    curl -OsL https://github.com/Kitware/CMake/releases/download/v3.21.3/cmake-3.21.3-macos10.10-universal.tar.gz
    tar xf cmake-3.21.3-macos10.10-universal.tar.gz --strip-components=1
    rm cmake-3.21.3-macos10.10-universal.tar.gz
    chmod -R a+rwx "$PWD/CMake.app"
    export PATH="$PATH:$PWD/CMake.app/Contents/bin"
    sudo "$PWD/CMake.app/Contents/bin/cmake-gui" --install
else
    set -euxo pipefail
    choco install cmake --version=3.21.3 --installargs '"ADD_CMAKE_TO_PATH=User"'
    PATH_TO_CMAKE='/c/Program Files/CMake/bin'
    echo "export PATH='$PATH_TO_CMAKE:$PATH'" >> $BASH_ENV
fi

