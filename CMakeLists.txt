#
# Project setup for nanosdr
#
# Copyright 2014 Alexandru Csete
# All rights reserved.
#
# This software is released under the Simplified BSD License.
#

cmake_minimum_required(VERSION 2.6)
project(nanosdr)

enable_testing()

## FIXME
include_directories(${CMAKE_SOURCE_DIR}/nanodsp/src)

# Add subdirectories
add_subdirectory(nanodsp)
add_subdirectory(nanorx)
