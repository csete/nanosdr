# Cmake file for nanodsp tests.
# Builds both static and shared libraries.
#
# Copyright 2014 Alexandru Csete
# All rights reserved.
#
# This software is released under the Simplified BSD License, see
# license.txt for details
#

include_directories("${PROJECT_SOURCE_DIR}")
FILE(GLOB SRCS *.cpp)

# Build static library
add_library(nanodsp-static STATIC ${SRCS})
set_target_properties(nanodsp-static PROPERTIES OUTPUT_NAME "nanodsp")
install(TARGETS nanodsp-static DESTINATION lib${LIB_SUFFIX})

# Build shared library
add_library(nanodsp-shared SHARED ${SRCS})
set_target_properties(nanodsp-shared PROPERTIES OUTPUT_NAME "nanodsp")
#set_target_properties(nanodsp-shared PROPERTIES VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.0 SOVERSION 0)
install(TARGETS nanodsp-shared DESTINATION lib${LIB_SUFFIX})

# Install headers
set(NANODSP_PUBLIC_HEADERS
    datatypes.h
    translate.h
)

install(FILES ${NANODSP_PUBLIC_HEADERS}
    DESTINATION include/nanodsp
)
