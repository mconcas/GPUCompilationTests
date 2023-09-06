cmake_minimum_required(VERSION 3.21)
set(ENV{CMAKE_BUILD_TYPE} Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(GPUSeparableCompilationTest)
include(CheckLanguage)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
  add_subdirectory(cuda)
else()
  message(STATUS "No CUDA support, skipping")
endif()

check_language(HIP)
if(CMAKE_HIP_COMPILER)
  enable_language(HIP)
  add_subdirectory(hip)
else()
  message(STATUS "No HIP support, skipping")
endif()