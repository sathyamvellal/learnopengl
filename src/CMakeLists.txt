cmake_minimum_required(VERSION 3.9)
project(${CMAKE_PROJECT_NAME}-src)

function(create_add_library name)
    add_library(${name} STATIC ${name}/${name}.cpp)
endfunction(create_add_library)

create_add_library(hello_window)