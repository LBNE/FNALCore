FNALCore
========
Merges the main low level FNAL interfaces into a single framework:

- cpp0x (C++11 support)
- cetlib (low level routines)
- fhicl-cpp (fhicl configuration language parser)
- messagefacility

Why? Because you need em'all anyway, they use each other and they are
small.

Installation
============
Requirements
------------
- CMake 2.8.11 or above
- C++11 compliant compiler (NB, whilst the configuration will
  perform most checks, it's not guaranteed that everything has been
  checked)
- Boost 1.42 or higher, with regex and thread libraries compiled
  against C++11. If you want to run the unit tests, the Boost test
  library is also needed

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

FNALCore will install a single library, API headers and CMake support
files under the hierarchy:

```
CMAKE_INSTALL_PREFIX/
+- include/
|   +- FNALCore/
|      +- cpp0x/
|      +- cetlib/
|      +- fhiclcpp/
|      +- messagefacility/
+- lib{64}/
   +- libFNALCore.so
   +- cmake/
      +- FNALCore-<VERSION>
```


Using FNALCore
==============
To use FNALCore in your own projects, it is recommended to use CMake (other
tool support to be added). Simply add

```cmake
find_package(FNALCore REQUIRED)
```

to your CMake script. If you have installed FNALCore to a non standard
location, you may need to set FNALCore_DIR or CMAKE_INSTALL_PREFIX.

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
to the required Boost will be automatically set.

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

