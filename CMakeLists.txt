cmake_minimum_required(VERSION 3.10)
project(GPUSeparableCompilationTest)

enable_language(CUDA)
add_subdirectory(cuda)
add_subdirectory(hip)