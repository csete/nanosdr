#
# Cmake file for nanodsp unit tests.
# Builds both static and shared libraries.
#
# Copyright 2014 Alexandru Csete
# All rights reserved.
#
# This software is released under the Simplified BSD License, see
# license.txt for details
#

# nanodsp headers from source location
include_directories(${CMAKE_SOURCE_DIR}/src)

# nanodsp library
link_directories(${PROJECT_BINARY_DIR}/src)

add_executable(test_translate test_translate.cpp)
target_link_libraries(test_translate nanodsp)

add_test(freq_xlate_test test_translate)

