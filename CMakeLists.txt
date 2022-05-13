cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)

set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest)
include_directories(${GTEST_ROOT})
add_subdirectory(${GTEST_ROOT})
link_directories(${GTEST_ROOT})

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${SRC_ROOT})
add_subdirectory(${SRC_ROOT})
