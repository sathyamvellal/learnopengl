cmake_minimum_required(VERSION 3.8)
project(${CMAKE_PROJECT_NAME}-lib)

# GLFW
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

# GLAD
add_subdirectory(glad)