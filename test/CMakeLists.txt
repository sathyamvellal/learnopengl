cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}-test)

function(create_add_executable name)
    add_executable(test-${name} ${name}/test-${name}.cpp)
    target_link_libraries(test-${name} ${name} ${ARGN} common glfw glad)
endfunction(create_add_executable)


add_executable(hello test_hello.cpp)
target_link_libraries(hello common)

create_add_executable(hello_window)
target_compile_definitions(hello_window PUBLIC LOG_LEVEL=${LOG_LEVEL})
create_add_executable(hello_triangle)
target_compile_definitions(hello_triangle PUBLIC LOG_LEVEL=${LOG_LEVEL})
create_add_executable(shaders)
target_compile_definitions(shaders PUBLIC LOG_LEVEL=${LOG_LEVEL})
create_add_executable(spring1d spring1dsim)
target_compile_definitions(spring1d PUBLIC LOG_LEVEL=${LOG_LEVEL})
create_add_executable(spring2d)
target_compile_definitions(spring2d PUBLIC LOG_LEVEL=${LOG_LEVEL})