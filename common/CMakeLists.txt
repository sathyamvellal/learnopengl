cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}-common)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(COMMON_SRC src)
set(UTILS_SRC src/utils)

add_library(common STATIC
        ${COMMON_SRC}/hello.cpp
        ${UTILS_SRC}/logger.cpp
        ${UTILS_SRC}/files.cpp
        ${UTILS_SRC}/shader.cpp)
