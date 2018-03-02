cmake_minimum_required(VERSION 3.8)
project(learnopengl)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR  ${CMAKE_BUILD_DIR}/bin)
set(CMAKE_LIBRARY_DIR ${CMAKE_BUILD_DIR}/lib)
set(CMAKE_TESTS_BINARY_DIR ${CMAKE_BINARY_DIR}/test)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/common/include)

include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${COMMON_INCLUDE_DIR})

include_directories(/usr/local/Cellar/open-mpi/2.1.1/include)
link_directories(/usr/local/opt/libevent/lib)
link_directories(/usr/local/Cellar/open-mpi/2.1.1/lib)

set(LOG_LEVEL LOG_DEBUG)

# Third-party libraries
add_subdirectory(lib)

# Common code, packaged as a library
add_subdirectory(common)

# Sub-projects, packaged as libraries
add_subdirectory(src)

# Tests for Sub-projects, as execiutables
add_subdirectory(test)
