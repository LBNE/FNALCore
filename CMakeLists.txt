# - FNALCore top level build
# Project setup
# Require 2.8.12 for INTERFACE_ support and target ALIAS
cmake_minimum_required(VERSION 2.8.12)

# - Policies - set all here as may influence project() call
# Always id Clang as Clang, defer use of AppleClang id
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 OLD)
endif()

# Always use rpath on Mac, as it's supported in out min version, and
# CMake 3 and higher prefer it
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

project(FNALCore)

#-----------------------------------------------------------------------
# API and ABI versioning
# NB - this only demonstrates that it *can* be done
# More info on this at:
# - http://public.kitware.com/Bug/view.php?id=4383
# - http://techbase.kde.org/Policies/Binary_Compatibility_Issues_With_C++
#
# The following numbers are *arbitrary* for now. Remember that
# VERSION and SOVERSION do not neccessarily evolve in sync
# - Hard code version plus Major/Minor/Patch for now
set(FNALCore_VERSION "0.1.0")
set(FNALCore_VERSION_MAJOR 0)
set(FNALCore_VERSION_MINOR 1)
set(FNALCore_VERSION_PATCH 0)

set(FNALCore_SOVERSION "0.1.0")

# - We can also use a postfix to distinguish the debug lib from
# others if different build modes are ABI incompatible (can be
# extended to other modes)
set(FNALCore_DEBUG_POSTFIX "d")

#-----------------------------------------------------------------------
# Standard and Custom CMake Modules
#
list(INSERT CMAKE_MODULE_PATH 0
  ${CMAKE_CURRENT_LIST_DIR}/cmake
  ${CMAKE_CURRENT_LIST_DIR}/cmake/CheckCXX11Features/Modules
  )

# - Standard Support
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

# - Local Customs
# - Cetbuildtools bypass/simplifications
include(CetDummy)

# - Build product locations
# The variables CMAKE_{RUNTIME,LIBRARY,ARCHIVE}_OUTPUT_DIRECTORY can
# be used to specify where executables, dynamic and static libraries
# are output. They initialize the {RUNTIME,LIBRARY,ARCHIVE}_OUTPUT_DIRECTORY
# properties of targets added via add_{executable,target}, so can
# targets can override if need be.
#
# - Assume for now that GNUInstallDirs provides relative (to
#   CMAKE_INSTALL_PREFIX) paths, and reflect this layout in the
#   output directories. This should be o.k. even on DLL platforms
#   as CMake should output these to the RUNTIME directory.
#
set(BASE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/BuildProducts")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_LIBDIR}")

# Translate to cetbuildtool-speak for tests...
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

# - C++11 Check/Configuration
# To be added: list of C++11 features which *must* be present.
include(CheckCXX11Features)
include(CheckCXXStandardLibrary)

# Use of emplace methods in modules now requires that (at least)
# map support this. As cpp0x does not provide a workaround, fail
# if CXX11 checks are not present
if(NOT HAS_CXX11_VECTOR_EMPLACE)
  message(FATAL_ERROR "${CMAKE_CXX_COMPILER} does not support std::vector emplace member functions")
endif()

if(NOT HAS_CXX11_MAP_EMPLACE)
  message(FATAL_ERROR "${CMAKE_CXX_COMPILER} does not support std::map emplace member functions")
endif()

# In CMake 2.8.12 and higher, these can be propagated to clients via the
# target_compile_options command
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_COMPILER_FLAGS}")

#-----------------------------------------------------------------------
# Required Third Party
#
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_BOOST_CMAKE ON)
set(FNALCore_BOOST_COMPONENTS
  filesystem
  system
  regex
  thread
  program_options
  )
find_package(Boost 1.55.0 REQUIRED ${FNALCore_BOOST_COMPONENTS})

find_package(SQLite3 3.8.5 REQUIRED)

#-----------------------------------------------------------------------
# Testing
option(FNALCore_ENABLE_TESTING "Enable Unit Testing of FNALCore" OFF)
if(FNALCore_ENABLE_TESTING)
  enable_testing()
  set(BOOST_NO_SYSTEM_PATHS ON)
  find_package(Boost ${BOOST_VERSION} REQUIRED unit_test_framework)
  include(CetTest)
  cet_test_env("PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}:$ENV{PATH}")
  if(APPLE)
    cet_test_env("DYLD_LIBRARY_PATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}:$ENV{DYLD_LIBRARY_PATH}")
  elseif(UNIX)
    cet_test_env("LD_LIBRARY_PATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}:$ENV{LD_LIBRARY_PATH}")
  endif()
endif()

#-----------------------------------------------------------------------
# Build
add_subdirectory(FNALCore)

#-----------------------------------------------------------------------
# Documentation
option(FNALCore_BUILD_DOCS "Build documentation for FNALCore" ON)
if(FNALCore_BUILD_DOCS)
  add_subdirectory(doc)
endif()

#-----------------------------------------------------------------------
# Install support files
#
configure_package_config_file(
  cmake/FNALCoreConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/FNALCoreConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FNALCore-${FNALCore_VERSION}
  PATH_VARS
    CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_LIBDIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/FNALCoreConfigVersion.cmake
  VERSION ${FNALCore_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/FNALCoreConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/FNALCoreConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/FNALCore-${FNALCore_VERSION}
  )

#-----------------------------------------------------------------------
# Package
#
include(FNALCoreCPack)

