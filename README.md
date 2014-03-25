CheckCXX11Features
=================
CMake modules to determine which C++11 features and which C++ Standard
Library (Vendor/Version) the compiler detected by CMake supports.

The baseline tests are taken from the `cmake-cxx11` repository:

git://anongit.kde.org/scratch/dakon/cmake-cxx11.git

which is also [viewable online](http://quickgit.kde.org/?p=scratch%2Fdakon%2Fcmake-cxx11.git)

Additional tests have been added to determine support for further aspects
of the standard. These are still a work in progress, so may not work
perfectly on every combination of compiler and standard library.

A preliminary check of the standard library being linked is also provided,
though this is still a work in progress, and does not work when
cross compiling.

How to Use
==========
Demonstration
-------------
Currently, the project supplies a CMake script to test and demonstrate
the functionality. To try this out, simply run `cmake` (2.8.3 or better), pointing it the directory in which this README resides.
Though an out-of-source build is not enforced, it is strongly recommended
that you use a separate directory for builds so that multiple
compilers/versions can be tested easily

The CMake step will try to compile and run test programs, each exercising
a feture of the C++11 standard (note that some features also have checks
for compilation and runtime failures). CMake will report the running and
result of each feature test. For each feature tested, an internal
cache variable is set to indicate the availability of support for that
feature under the current build configuration. A complete list of these
variables can be found in Modules/CheckCXX11Features.cmake.

At present, there is nothing to do beyond the CMake step as no programs
are built! However, an example header template, `example_header.hpp.in` is
provided that demonstrates the use of the cache variables to set
preprocessor directives indicating support of each feature.

In Your Own Projects
--------------------
Import the CMake scripts and support directories under the Modules
directory into a suitable location. Ensure your project's CMAKE_MODULE_PATH
points to this location, and then simple add the lines

```cmake
include(CheckCXX11Features)
include(CheckCXX11StandardLibrary)
```

to your project's CMakeLists.txt script. Inclusion of the scripts will
result in the tests being run. See the documentation in the modules
themselves for the variables that are set.

