# C++ Example project

[![Platform](https://img.shields.io/static/v1?label=Platform&message=macOS%20%7C%20windows&color=pink&style=flat)](./.documentation/building.md)

[![Language](https://img.shields.io/static/v1?label=Language&message=C%2B%2B&color=orange&style=flat)](./.documentation/building.md)
[![Code Style](https://img.shields.io/static/v1?label=Code%20Style&message=Clang%20Format&color=pink&style=flat)](https://clang.llvm.org/docs/ClangFormat.html)

[![Language](https://img.shields.io/static/v1?label=Language&message=TypeScript&color=orange&style=flat)](./.documentation/building.md)
[![Code Style](https://img.shields.io/static/v1?label=Code%20Style&message=Prettier&color=pink&style=flat)](https://prettier.io)

[![Language](https://img.shields.io/static/v1?label=Language&message=CMake&color=orange&style=flat)](https://www.cmake.org)
[![Code Style](https://img.shields.io/static/v1?label=Code%20Style&message=CMake%20Format&color=pink&style=flat)](https://github.com/cheshirekow/cmake_format)

## Prerequisites

- [Cmake](https://www.cmake.org). Must be 3.20 or higher. Normally just get the latest version
- [Node](https://nodejs.org/en/). Should be 14.x, with npm 6.14.x

## Project layout and format

This is an example C++ project. The aim of this repository is to give you a basic skeleton for any project you might want to build that uses C++. It includes all the key parts to build a basic project across both macos and windows. 

### Directory structure

.circleci 
  - This is the directory that holds the config for circle. If you want to make changes to the default behaviour of circle you would make it in this directory. By default the config in here will pull your repo, setup cmake and node, and then build and test your application.
.cmake
  - This is where all the cmake files are defined. This repository includes a lot of utility cmake files, that will let you very simply get started with using cmake. <br/>
  We break our project layouts up in to a few types of cmake targets:
    - static libraries are considered the lowest levels. You can declare these using `make_library`, and then specify the source files you want. Look at `CMakeLists.txt` in the root for an example. We encourage you to make liberal use of these libraries, to break your code down in to modular sections. 
    - tests are next up. Each static library can have an associated test. These tests can be either `make_test` which will run an arbitrary executable from, `make_catch2_test` which will link in catch2 or `make_test_executable` which will run a windowed test. Note that the name of each test will be automatically constructed for consistency, and is the form `test-${NAME}`. By convention, we pass the same name to both `make_test` and `make_library`, then you will have `libX.lib` and `test-libX.lib`. Note that `libX` is automatically added to the dependency list, and is not required to be defined.
    - mocks are also available. A mock is a static library that provides a simple way for users of your static lib to get a mocked version of your code for their tests. Use `make_mock` to make one of these. 
  - It is definately worth reading through the cmake files, to understand all the functionality that is available. Especially pay attention to the settings in `global_options.cmake`
.documentation
  - Documentation for the project is defined in here, in MD format. Mostly these files are linked to from this readme.
.scripts
  - This directory contains all the build scripts for the project. Most of this will be called from the npm package scripts. Run `npm run help` to get information on most of these scripts. 
.utilities
  - Utility build function are in this location. Currently, just the time-trace functions are here to let you time your builds and understand what times the time. See [this](https://github.com/aras-p/ClangBuildAnalyzer) repo for more info
modules
  - The modules directory contains source code that will build up to be the main chunk of your application. Consider these to be all of your low level source code that will combine to be your final application. Normally the modules will be broken down to contain 3 directories - source (your library code), tests (your tests) and mocks (your mocks). 
project
  - Contains all the source code for your main application, as well as any resources for the application - for example icon files, plists, rc files etc

## Additional files
In the directory root you will find a bunch of files:
* .clang-format
  * The main C++ formatting style is set here
* .cmake-format
  * Formatting for the cmake files are defined here
* CMakeLists.txt
  * Core cmake list for the project
* package(-lock).json
  * Node package file to define dependencies and setup
* .babelrc, .eslintrc.json, tsconfig.json 
  * These files are for setting up our js configuration

## TL;DR quick start

1. Install node
1. Install cmake
1. Run `npm install` once to install all dependancies. 
1. `npm run generate`
1. `npm run build`

## Building

You can build on the command line, or using an IDE (We support _XCode_, _CLion_ and _VS2019_ currently). See [here](./.documentation/building.md) for how to build


## CI

Our ci is [CircleCI](https://app.circleci.com/pipelines/github/Focusrite-Novation). The config for circle is [here](./.circleci/config.yml)

## Code formatting

We use a variety of code formatting tools. Please make sure you have these installed on your system to keep the codebase styling consistent.

- [C++](./.documentation/cplusplus.md)
- [Javascript](./.documentation/javascript.md)
- [Cmake](./.documentation/cmake.md)

## Code caching

We have code caching available to speed up builds. [Learn more](./.documentation/caching.md)

## Scripts

We have a variety of scripts available in our package.json. [Learn more](./.documentation/scripts.md)
