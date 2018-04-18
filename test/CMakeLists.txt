cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}-test)

function(create_add_executable dir name)
    add_executable(${name} ${dir}/${name}.cpp)
    target_link_libraries(${name} ${ARGN} common glfw glad)
endfunction(create_add_executable)


add_executable(hello test_hello.cpp)
target_link_libraries(hello common)

create_add_executable(hello_window test-hello_window hello_window)
target_compile_definitions(hello_window PUBLIC LOG_LEVEL=${LOG_LEVEL})

create_add_executable(hello_triangle test-hello_triangle hello_triangle)
target_compile_definitions(hello_triangle PUBLIC LOG_LEVEL=${LOG_LEVEL})

create_add_executable(shaders test-shaders_green shaders)
target_compile_definitions(test-shaders_green PUBLIC LOG_LEVEL=${LOG_LEVEL})
create_add_executable(shaders test-shaders_multicolor shaders)
target_compile_definitions(test-shaders_multicolor PUBLIC LOG_LEVEL=${LOG_LEVEL})

create_add_executable(spring1d test-spring1d spring1d spring1dsim)
target_compile_definitions(spring1d PUBLIC LOG_LEVEL=${LOG_LEVEL})

create_add_executable(spring2d test-spring2d spring2d spring2dsim)
target_compile_definitions(spring2d PUBLIC LOG_LEVEL=${LOG_LEVEL})

create_add_executable(particleflow test-particleflow particleflow)
target_compile_definitions(particleflow PUBLIC LOG_LEVEL=${LOG_LEVEL})
