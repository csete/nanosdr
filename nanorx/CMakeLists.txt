project(nanorx CXX)
cmake_minimum_required(VERSION 2.6)

include_directories(
    ${CMAKE_SOURCE_DIR}/nanodsp/src
    ${CMAKE_SOURCE_DIR}/nanorx
)

link_directories(
    # This is where libnanodsp.a and libnanodsp.so are located
    ${CMAKE_BINARY_DIR}/nanodsp/src
)

FILE(GLOB SRCS *.cpp)
add_executable(nanorx ${SRCS})
add_dependencies(nanorx nanodsp)  ## FIXME: parallel build fails

target_link_libraries(nanorx nanodsp)
