cmake_minimum_required(VERSION 3.9)
project(${CMAKE_PROJECT_NAME}-test)

add_executable(hello test_hello.cpp)
target_link_libraries(hello common)