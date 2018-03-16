cmake_minimum_required(VERSION 3.9)
project(${CMAKE_PROJECT_NAME}-src)

set(BUILD_SHADER_DIR ${CMAKE_BUILD_DIR}/shaders)

function(create_add_library name)
    add_library(${name} STATIC ${name}/${name}.cpp)
endfunction(create_add_library)

function(copy_shaders name)
    message(copying files ...)
    file(COPY ${name}/vertex.glsl DESTINATION ${BUILD_SHADER_DIR}/${name})
    file(COPY ${name}/fragment.glsl DESTINATION ${BUILD_SHADER_DIR}/${name})
endfunction(copy_shaders)

create_add_library(hello_window)

create_add_library(hello_triangle)
copy_shaders(hello_triangle)

create_add_library(shaders)
copy_shaders(shaders)
