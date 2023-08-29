cmake_minimum_required(VERSION 3.10)
set(ENV{CMAKE_BUILD_TYPE} Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(GPUSeparableCompilationTest)

enable_language(CUDA)
enable_language(HIP)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(cuda)
add_subdirectory(hip)