#
# Cmake file for nanodsp library.
# Builds both static and shared libraries.
#
# Copyright 2014 Alexandru Csete
# All rights reserved.
#
# This software is released under the Simplified BSD License, see
# license.txt for details
#
# TODO:
#   Support platforms other than linux
#

cmake_minimum_required(VERSION 2.6)
project(nanodsp CXX)
enable_testing()

# select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")


# Compiler specific setup
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -Wextra -fno-exceptions)
endif()

if (NOT WIN32)
    # http://gcc.gnu.org/wiki/Visibility
    #add_definitions(-fvisibility=hidden)
endif()

#include_directories(${PROJECT_BINARY_DIR})
#link_directories(${PROJECT_BINARY_DIR})


add_subdirectory(src)
add_subdirectory(tests)
