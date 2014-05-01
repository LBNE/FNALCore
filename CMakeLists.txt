# - FNALCore top level build
# Project setup
# Require 2.8.11 to get the nice interface export features
cmake_minimum_required(VERSION 2.8.11)
project(FNALCore)
set(FNALCore_VERSION "1.0.0")


#-----------------------------------------------------------------------
# Standard and Custom CMake Modules
#
list(INSERT CMAKE_MODULE_PATH 0
  ${CMAKE_CURRENT_LIST_DIR}/cmake/CheckCXX11Features/Modules
  )

# - Standard Support
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

# - C++11 Checks
include(CheckCXX11Features)
include(CheckCXXStandardLibrary)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_COMPILER_FLAGS})

#-----------------------------------------------------------------------
# Required Third Party
#
find_package(Boost 1.42.0 REQUIRED regex)

#-----------------------------------------------------------------------
# Testing
option(FNALCore_ENABLE_TESTING "Enable Unit Testing of FNALCore" OFF)
if(FNALCore_ENABLE_TESTING)
  enable_testing()
endif()

#-----------------------------------------------------------------------
# cpp0x

#-----------------------------------------------------------------------
# cetlib

#-----------------------------------------------------------------------
# fhicl-cpp

#-----------------------------------------------------------------------
# messagefacility


#-----------------------------------------------------------------------
# Install support files

#-----------------------------------------------------------------------
# Package
#

