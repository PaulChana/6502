## Prerequisites

Studio uses a variety of build tools. Most things can be accessed via an npm script.

Note, if you use `nvim` to manage node, you will need to ensure that you have a system version of node installed. 
Do this by running

```
brew install node
```

Before running anything you will need to do 

```
npm install
```

If you get an error around the Ampify prettier config, please see [The Installation section of our JS help](./javascript)

## Building on command line

```
npm run generate
npm run build
```

## Building a debug build on command line

```
npm run generate
npm run build-debug
```

## Making a project for _XCode_

```
npm run generate
```

Then open the xcode project located in 
```cmake-build/AmpifyStudio.xcproj```

## Opening in CLion

No need to generate. Just open the root Ampify Studio project in CLion and it will find all the right CMake settings for you. See [here](./cmake.md) about auto formatting

## Opening in Visual Studio 2019

No need to generate. Just open the root Ampify Studio project in VS2019 and it will find all the right CMake settings for you. You can, if required still generate the project using
```
npm run generate
```

Then open the vs project located in ```cmake-build/AmpifyStudio.sln```

