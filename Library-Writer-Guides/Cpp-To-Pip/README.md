# How do I take my C++ code to a pip-install-able Python project?

This is one walkthrough of the process to go from a C++ project you have started writing, to an easy-to-use python library that can be installed with `pip install <libraryname>` and easily used by the rest of the community.

For our example, we have a very small, lightweight piece of C++ code, and in the following we will describe how to create Python bindings, how to create Python packaging, and how to register and publish it on PyPi.

We start, in the subdirectory [phase1](phase1/) with a single C++ file implementing something possibly of interest (this [union-find-merge-tree.cpp](phase1/union-find-merge-tree.cpp) has a sloppy implementation of union find for finding death times for persistent H0 and birth simplices for persistent H1.

To go from this to something distributable, there are several phases we need to get through:

1. Make a library and automate build. We may need to refactor so that any functionality you want to expose is actually contained in functions or variables that can be exposed. We also need to make sure that the code can be compiled with as little user interaction as possible.
2. Make a python glue-layer. Somehow we need to be able to call the functions and read the variables from python - this usually requires picking what parts of the library should be visible from python.
3. Make a distributable python package. With a packaging and build system, we need to make sure that the entire library can be distributed and installed easily for someone else to use from python.
4. Set up continuous builds of binary wheels for common platforms. A nice touch is to automatically compile the C++ parts for a range of commonly used platforms and make those available. GitHub has excellent support for this kind of regular recompilation.
5. Test the python package against [test.pypi.org](test.pypi.org). Make sure we have figured out any and all bugs or issues with our distributable package.
6. Publish the package on PyPI. After this step, all users _should_ be able to do `pip install <libraryname>` and get access to the code you wrote, hopefully with minimal issues along the way.

For many of these steps, there are many different ways you could accomplish the step. We will be showing one specific tool in each step - but may include a couple of links to alternatives as we go.

## Make a library

In [phase2](phase2/) we can find a refactored version of the code. Most steps have been moved out into separate functions, and we now have a header file that specifies any data types we have created and gives function declarations for every function we created.

## Automate build

There are many options available for a C++ build system. Hopefully you picked one when you started - if not, now is a good time to fix that. Here, we will set it up with a minimalistic [CMake](https://cmake.org) build system.

To set up for CMake, we first need to create a file `CMakeLists.txt`. A minimal such could look like this:
```
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(UnionFind)
add_executable(demo union-find.cpp)
```

If you use any modern C++ feature, make sure you pick the right C++ language standard here, and pick a CMake modern enough that it understand the language standard specification. By version 3.20, everything up to and including C++23 is handled.

You also need to make the `set(CMAKE_CXX_STANDARD 23)` and `set(CMAKE_CXX_STANDARD_REQUIRED True)` rows happen before `add_executable(demo union-find.cpp)`.

With this `CMakeLists.txt` in place, you can create a build directory, go into it, run `cmake <path-to-CMakeLists.txt-file>` and then `cmake --build .` to compile your project.

With a working CMake in place, let's add some more pieces. We can keep track of project versioning, and update our project to include automatically created files. We do this by:

* Changing `CMakeLists.txt` - we are changing the project definition line, and adding lines to configure the file `union-find-config.h` and to expand the search area for include files. The resulting file looks like this:
```
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(UnionFind VERSION 0.1)
configure_file(union-find-config.h.in union-find-config.h)
add_executable(demo union-find.cpp)
target_include_directories(demo PUBLIC "${PROJECT_BINARY_DIR}")
```

* Add a file `union-find-config.h.in` that specifies how to create the dynamically generated `union-find-config.h`:
```
// Configured options and settings for the project
#define UnionFind_VERSION_MAJOR @UnionFind_VERSION_MAJOR@
#define UnionFind_VERSION_MINOR @UnionFind_VERSION_MINOR@
```

* Include `union-find-config.h` in our source code, and refer to its content in our code.

### Refactor for a CMake configured library

In order to make a library, we may want to separate our executable code from our library code. So next, we split `union-find.cpp` into one file with the implementation of everything specified in `union-find.hpp`, and a separate file with everything else. You can see the resulting split in [phase4/union-find.cpp](phase4/union-find.cpp) and [phase4/union-find-exec.cpp](phase4/union-find-exec.cpp).

We also allow ourselves to split library and executable into different subdirectories. The `add_executable` declaration, and a `add_library` declaration that lists all the source files that make up the library can be included in `CMakeLists.txt` files in the subdirectories, and the subdirectories included in the toplevel `CMakeLists.txt` with `add_subdirectory(src/lib)` -- one command for each subdirectory with an `CMakeLists.txt` file.

When writing this tutorial, the first refactor attempt showed that the implementation of the function `dist2` still referred to the demo data, and was not generic enough. So it had to be rewritten, which required us to change its call signature slightly. Changes thus propagate to both the header and source files.

The library subdirectory can include a line `target_include_directories(unionfind INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})` to make the include file locations discoverable without editing makefiles for any users of the library in the subdirectory.

With the subdirectory organization, any compiled files can then be found in the corresponding subdirectory hierarchy within the `build` directory that you use.

### Add structure to install library and headers, and package the project



## Python glue layer

## Distributable package

## Continuous builds

## Test.PyPI

## PyPI

