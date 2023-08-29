cmake_minimum_required(VERSION 3.10)
set(ENV{CMAKE_BUILD_TYPE} Debug)
project(GPUSeparableCompilationTest)

enable_language(CUDA)
enable_language(HIP)
add_subdirectory(cuda)
add_subdirectory(hip)