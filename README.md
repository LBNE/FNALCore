FNALCore
========
A study of merging the FNAL libraries providing "foundation" functionality
for the [art](https://cdcvs.fnal.gov/redmine/projects/art) framework.
There are four of these libraries:

- [cpp0x](https://cdcvs.fnal.gov/redmine/projects/cpp0x) (provide C++11 features for partially compilant compilers)
- [cetlib](https://cdcvs.fnal.gov/redmine/projects/cetlib) (low level routines)
- [fhicl-cpp](https://cdcvs.fnal.gov/redmine/projects/fhicl-cpp) (fhicl configuration language parser and data structures)
- [messagefacility](https://cdcvs.fnal.gov/redmine/projects/messagefacility) (logging library)

which are currently supplied through separate repositories
and build into 3 (cpp0x is header only, but implies an ABI) binary
libraries. However, `fhicl-cpp` uses and exposes the `cetlib` interface,
and `messagefacility` uses and exposes the `fhicl-cpp` and `cetlib`
interfaces (`cpp0x` is ignored because it is a facade for the C++11
standard library). Though modularization and reuse is generally good,
clients of any of these libraries need to be aware of this coupling and
this can cause issues for clients and developers in maintaining API and
ABI compatibility. In particular, the dependency graph of the modules,
whilst acyclic, is vertical, increasing the coupling between them.

Motivated by other "foundation" libraries providing similar functionality
(core data structures, configuration language parsing, configurable
logging) in a single layer such as [QtCore](http://qt-project.org/doc/qt-5/qtcore-index.html), [Poco](http://pocoproject.org/) and [CoreFoundation/Cocoa](https://developer.apple.com/technologies/mac/cocoa.html),
this project merges the four FNAL libraries with the aim of simplifing
use for clients as well as maintenance by developers.
Such layers can have relatively diverse functionality because it
all falls under the purpose of "general utility".

- Source code is kept modular, with one directory per module.
- A single binary library is created vs three.
- In future, separate libraries can be built if required, but clients still
interact through the single layer scheme.

The advantages of these schemes for clients is that they only have a
single layer to install and then use. For developers, they can
still develop, say `fhicl-cpp`, in isolation yet get immediate feedback
at the build stage on whether their changes break clients
(e.g. `messagefacility`). The scheme also removes the need for a complex
dependency manager system integrated in the CMake buildtool, allowing
the full functionality of that tool to be used.

Installation
============
Requirements
------------
- CMake 2.8.12 or above
- C++0X/11 compliant compiler (NB, whilst the configuration will
  perform most checks, it's not guaranteed that everything has been
  checked)
  - The `cpp0x` module provides minimal implementations of some
    C++11 features, but is not complete.
  - Boost implementations are used in some cases.
  - Features that the compiler/standard library *must* provide include
    (not complete as yet):
    - `emplace` member functions of `std::` collections.
- Boost 1.42 or higher, with filesystem, system, regex and thread libraries
  compiled against C++11. If you want to run the unit tests, the Boost test
  library is also needed. NB: the C++11 compatibility of the found
  Boost is *not* checked, but an incompatible Boost should cause
  the unit tests to fail. It should be noted that as a robust
  ABI checks are tricky to implement, it is up to *you*, not the buildsystem,
  to point to the right Boost.
- SQLite3 3.7.15 or higher for fhiclcpp database support.
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

If you want to run unit tests, run cmake with the `FNALCore_ENABLE_TESTING`
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
         +- doxygen/
```

You can also build source and binary tarballs for redistribution by
running

```
$ make package_source
...
$ make package
```

Note that at present the binary tarballs do not provide any dependency
checking nor refinding of the Boost package required to use FNALCore.
This will be fixed in future updates.


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

Documentation
-------------
Though FNALCore modules are not fully marked up for Doxygen, you can still
view what is available by pointing your web browser to the file

```
CMAKE_INSTALL_PREFIX/
+- share/
   +- doc/
      +- FNALCore/
         +- doxygen/
            +- html/
               +- index.html
```

Licensing
=========
Original code from upstream uses the GPLv2'd polarssl lib, so FNALCore
is GPLv2.

Git Repository Layout
=====================
FNALCore originally copied files from each of the subprojects in by
hand. Whilst useful for the prototype stage, the full demonstrator
requires some connection back to the upstream FNAL repositories to

- Make updates easier
- Retain upstream commits so that patches to the C++ code can be
  submitted upstream.
- Retain upstream commits so that any future adoption of FNALCore
  holds prior history of files.

Git offers several options for this, the most common being submodules
and subtrees. The latter are used currently as they seem to offer the
"simplest" approach given the above. There is plenty of discussion
on the web on submodules vs subtrees, and a good starting point
can be found on the following page:

- http://blogs.atlassian.com/2013/05/alternatives-to-git-submodule-git-subtree/

The major change to the structure of FNALCore is that each library
is now stored via subtrees

```
+- FNALCore.git
   +- FNALCore/
      +- cpp0x/ -> subtree
         +- CMakeLists.txt
         +- cpp0x/
         +- test/
```

This is chosen to help isolate the individual subtrees and for that reason
only. It is not neccessarily the cleanest arrangement of code.
The subtrees themselves use the master branches of the
[LBNE mirrors](https://github.com/LBNE) of
[cpp0x](https://github.com/LBNE/fnal-cpp0x),
[cetlib](https://github.com/LBNE/fnal-cetlib),
[fhicl-cpp](https://github.com/LBNE/fnal-fhicl-cpp)
and
[messagefacility](https://github.com/LBNE/fnal-messagefacility)

There are still some gotchas with the subtree approach, so care is needed
in the following cases.

1. Local commits should not cross subtree boundaries. This is so
   that commits can easily be split out of a subtree and pushed back
   upstream if required.
  - Subtree prefixes can be found by `git log | grep git-subtree-dir`
2. `git log` will show the commits from all the subtrees
3. `git log <subtreeprefix>` will not show the commit logs of the subtree
  - This can be worked around by supplying the SHA1 of the commit
    in the subtree at the point it was added in, e.g.
    `git log <sha1> <subtreepath>`. These SHA1s are stored in the commit
    message for the subtree add.
  - Graphical viewers such as `gitk` will show the complete tree

Updating the Subtrees
---------------------
Whilst a `git pull` (or fetch/merge) will update everything, this does not
update the subtrees from the upstream repositories they were created from.
To update the subtrees from their upstream repos, we need to pull in changes
for each individually. This could be scripted in the long term, though
it's expected that adoption of FNALCore would result in retirement of
the separate repos.

The easiest way to set things up is to add remotes for each parent repo
as a shorthand.

```sh
$ git remote add cpp0x-upstream https://github.com/LBNE/fnal-cpp0x.git
...
$ git remote add cetlib-upstream https://github.com/LBNE/fnal-cetlib.git
...
$ git remote add fhiclcpp-upstream https://github.com/LBNE/fnal-fhicl-cpp.git
...
$ git remote add messagefacility-upstream https://github.com/LBNE/fnal-messagefacility.git
```

Each subtree is then updated by a fetch from the remote followed by a
`subtree pull` (NB, these commands must be performed in the top level directory, i.e. the location of the `.git` directory)

```sh
$ git fetch cpp0x-upstream
$ git subtree pull --prefix=FNALCore/cpp0x cpp0x-upstream master
```

The same syntax can be used with the other subtrees, just change the
remote name and prefix as needed. It's not completely clear whether the `fetch` is always needed for every pull (but it doesn't hurt).


Pushing Local Subtree Changes Upstream
--------------------------------------
We may make local modifications to files under the subtrees, for example
patches for Mac. To push these upstream, you need to have write permission
to the upstream repo. If you do, then all that needs to be done to push
all local commits back to the subtree master is:

```sh
$ git subtree push --prefix=FNALCore/cpp0x cpp0x-upstream master
```

and similarly for the other subtrees. It's this separation of the trees
that means you must keep commits "atomic" to the subtree. For example,
if you patch something in `FNALCore/cetlib` which also affects something
in `FNALCore/fhicl-cpp`, then perform two separate commits, one for each
tree.

