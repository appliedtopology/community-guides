# How do I take my C++ code to a pip-install-able Python project?

This is one walkthrough of the process to go from a C++ project you have started writing, to an easy-to-use python library that can be installed with `pip install <libraryname>` and easily used by the rest of the community.

For our example, we have a very small, lightweight piece of C++ code, and in the following we will describe how to create Python bindings, how to create Python packaging, and how to register and publish it on PyPi.
