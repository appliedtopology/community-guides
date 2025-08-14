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

## Automate build

## Python glue layer

## Distributable package

## Continuous builds

## Test.PyPI

## PyPI

