cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}-src)

set(BUILD_SHADER_DIR ${CMAKE_BUILD_DIR}/shaders)

function(create_add_library dir name)
    add_library(${name} STATIC ${dir}/${name}.cpp)
endfunction(create_add_library)

function(copy_shaders name)
    message(copying files ...)
    file(COPY ${name}/vertex.glsl DESTINATION ${BUILD_SHADER_DIR}/${name})
    file(COPY ${name}/fragment.glsl DESTINATION ${BUILD_SHADER_DIR}/${name})
endfunction(copy_shaders)

create_add_library(hello_window hello_window)

create_add_library(hello_triangle hello_triangle)
copy_shaders(hello_triangle)

create_add_library(shaders shaders)
copy_shaders(shaders)

create_add_library(spring1d spring1d)
create_add_library(spring1d spring1dsim)
copy_shaders(spring1d)

create_add_library(spring2d spring2d)
create_add_library(spring2d spring2dsim)

create_add_library(particleflow particleflow)
copy_shaders(particleflow)

create_add_library(blobbies blobbies)
copy_shaders(blobbies)

create_add_library(sandbox001 sandbox001)
copy_shaders(sandbox001)