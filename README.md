CheckCXX11Features
=================
Test ability of CMake to detect support for C++11 features by the compiler
and/or standard library.

The baseline tests are taken from the `cmake-cxx11` repository:

git://anongit.kde.org/scratch/dakon/cmake-cxx11.git

which is also [viewable online](http://quickgit.kde.org/?p=scratch%2Fdakon%2Fcmake-cxx11.git)

Additional tests have been added to determine support for further aspects
of the standard. These are still a work in progress, so may not work
perfectly on every combination of compiler and standard library.

A preliminary check of the standard library being linked is also provided,
though this is still a work in progress.

How to Use
==========
Simply run `cmake` (2.8.3 or better), pointing it the directory in which
this README resides.
Though an out-of-source build is not enforced, it is strongly recommended that
you use a separate directory for builds so that multiple compilers/versions
can be tested.

The CMake step will try to compile and run test programs, each exercising
a feture of the C++11 standard (note that some features also have checks
for compilation and runtime failures). CMake will report the running and
result of each feature test. For each feature tested, an internal
cache variable is set to indicate the availability of support for that
feature under the current build configuration. A complete list of these
variables can be found in CMake/cmake-cxx11/Modules/CheckCXX11Features.cmake.

At present, there is nothing to do beyond the CMake step as no programs
are built! However, an example header template, `example_header.hpp.in` is
provided that demonstrates the use of the cache variables to set
preprocessor directives indicating support of each feature.


