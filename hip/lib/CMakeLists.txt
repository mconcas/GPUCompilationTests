set(HIPIFY_EXECUTABLE "/opt/rocm/bin/hipify-perl")
file(GLOB CUDA_SOURCES_FULL_PATH "../../cuda/lib/*.cu")

foreach(file ${CUDA_SOURCES_FULL_PATH})
  message(STATUS "Processing ${file}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${file})
  get_filename_component(CUDA_SOURCE ${file} NAME)
  string(REPLACE ".cu" "" CUDA_SOURCE_NAME ${CUDA_SOURCE})
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${CUDA_SOURCE_NAME}.hip.cxx
    COMMAND ${HIPIFY_EXECUTABLE} --quiet-warnings ${CMAKE_CURRENT_SOURCE_DIR}/../../cuda/lib/${CUDA_SOURCE} > ${CMAKE_CURRENT_SOURCE_DIR}/${CUDA_SOURCE_NAME}.hip.cxx
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../cuda/lib/${CUDA_SOURCE}
  )
endforeach()

set(CMAKE_CXX_COMPILER /opt/rocm/bin/hipcc)
set(CMAKE_CXX_LINKER /opt/rocm/bin/hipcc)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fgpu-rdc")

add_library(hiplib cudalib.hip.cxx)

#  | sed '1{/\#include \"hip\\/hip_runtime.h\"/d}'