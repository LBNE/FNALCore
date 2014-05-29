FNALCore
========
A study of merging the FNAL libraries providing "foundation" functionality
for the [art](https://cdcvs.fnal.gov/redmine/projects/art) framework.
There are four of these libraries:

- cpp0x (provide C++11 features for partially compilant compilers)
- cetlib (low level routines)
- fhicl-cpp (fhicl configuration language parser and data structures)
- messagefacility (logging library)

which are currently supplied through separate repositories
and build into 3 (cpp0x is header only, but locked to GCC) binary
libraries. However, `fhicl-cpp` uses and exposes the `cetlib` interface,
and `messagefacility` uses and exposes the `fhicl-cpp` and `cetlib`
interfaces (`cpp0x` is ignored because it is a facade for the C++11
standard library). Though modularization and reuse is generally good,
clients of any of these libraries need to be aware of this coupling and
this can cause issues for clients and developers in maintaining API and
ABI compatibility.

Motivated by other "foundation" libraries providing similar functionality
(core data structures, configuration language parsing, configurable
logging) such as [QtCore](http://qt-project.org/doc/qt-5/qtcore-index.html), [Poco](http://pocoproject.org/) and [CoreFoundation/Cocoa](https://developer.apple.com/technologies/mac/cocoa.html), this project merges
the four FNAL libraries with the aim of simplifing use for clients as
well as maintenance by developers.

- Source code is kept modular, with one directory per module.
- A single binary library is created vs three.
- In future, separate libraries can be built if required.

The advantages of these schemes for clients is that they only have a
single package to install and then use. For developers, they can
still develop, say `fhicl-cpp`, in isolation yet get immediate feedback
at the build stage on whether their changes break clients
(e.g. `messagefacility`). The scheme also removes the need for a complex
dependency manager system integrated in the CMake buildtool, allowing
the full functionality to be used.

Installation
============
Requirements
------------
- CMake 2.8.11 or above
- C++0X/11 compliant compiler (NB, whilst the configuration will
  perform most checks, it's not guaranteed that everything has been
  checked)
- Boost 1.42 or higher, with regex and thread libraries compiled
  against C++11. If you want to run the unit tests, the Boost test
  library is also needed. NB: the C++11 compatibility of the found
  Boost is *not* checked, but an incompatible Boost should cause
  the unit tests to fail. It should be noted that as a robust
  ABI check is not yet possible, it is up to *you*, not the buildsystem,
  to point to the right Boost.
- Doxygen 1.8 or higher for documentation.

How to Install
--------------
The build of FNALCore provides a standard CMake system, so if you
have all the requirements installed and available directly, then
you can simply do

```
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
$ make install
```

Selection of compiler, installation prefix and path to Boost can be
adjusted using the usual CMake variables (TODO: expand this)

If you want to run unit tests, run cmake with the FNALCore_ENABLE_TESTING
variable set, e.g.

```
$ cmake -DFNALCore_ENABLE_TESTING=ON ..
$ make -j4
$ make test
```

All unit tests use the CTest system, so can be run individually using
that interface.

FNALCore will install a single library, API headers, CMake support
files and documentation under the hierarchy:

```
CMAKE_INSTALL_PREFIX/
+- include/
|   +- FNALCore/
|      +- cpp0x/
|      +- cetlib/
|      +- fhiclcpp/
|      +- messagefacility/
+- lib{64}/
|  +- libFNALCore.so
|  +- cmake/
|     +- FNALCore-<VERSION>
+- share/
   +- doc/
      +- FNALCore/
```


Using FNALCore
==============
To use FNALCore in your own projects, it is recommended to use CMake (other
tool support to be added). Simply add

```cmake
find_package(FNALCore REQUIRED)
```

to your CMake script. If you have installed FNALCore to a non standard
location, you may need to set FNALCore_DIR or CMAKE_PREFIX_PATH.

To use the headers and link to the library, you can add

```cmake
include_directories(${FNALCore_INCLUDE_DIRS})

add_executable(foo foo.cc)
target_link_libraries(foo FNALCore::FNALCore)
```

as needed to your CMake scripts.

At present, FNALCore does not automatically check that your build
configuration is binary compatible (compiler version, C++ standard and
library vendor). However, once FNALCore is found the CMake variables
`FNALCore_CXX_COMPILER_ID`, `FNALCore_CXX_COMPILER_VERSION`,
`FNALCore_CXX_STDLIB_ID` and `FNALCore_STDLIB_VERSION` are available
for manual checks.

FNALCore exposes Boost headers in its public API, and the include path
to the required Boost will be automatically set. At present, this results
in a non-relocatable path being encoded in the FNALCore support files.
This can be resolved when FindBoost supports imported targets, or
a wrapper can be written.

Header Paths and Adapting Existing Code
---------------------------------------
Provided you have the `<CMAKE_INSTALL_PREFIX>/include/FNALCore` directory
as an include path to your compiler (and `find_package` will do this
for you in CMake), then you can use the FNALCore headers just as in their
separate packages:

```cpp
#include "cpp0x/array"
#include "cetlib/nybbler.h"
```

Any existing code you have written using separately compiled cpp0x,
cetlib etc is API compatible with FNALCore. The only change that is
required is to use `find_package(FNALCore)` and to link any binary against
the FNALCore library instead of the separate cpp0x, cetlib etc libraries.

Licensing
=========
Original code from upstream uses the GPLv2'd polarssl lib, so FNALCore
is GPLv2.

