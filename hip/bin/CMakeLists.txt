set(HIPIFY_EXECUTABLE "/opt/rocm/bin/hipify-perl")
file(GLOB CUDA_SOURCES_FULL_PATH "../../cuda/bin/*.cu")

foreach(file ${CUDA_SOURCES_FULL_PATH})
  message(STATUS "Processing ${file}")
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${file})
  get_filename_component(CUDA_SOURCE ${file} NAME)
  string(REPLACE ".cu" "" CUDA_SOURCE_NAME ${CUDA_SOURCE})
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${CUDA_SOURCE_NAME}.hip
    COMMAND ${HIPIFY_EXECUTABLE} --quiet-warnings ${CMAKE_CURRENT_SOURCE_DIR}/../../cuda/bin/${CUDA_SOURCE} > ${CMAKE_CURRENT_SOURCE_DIR}/${CUDA_SOURCE_NAME}.hip
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../cuda/bin/${CUDA_SOURCE}
  )
endforeach()

set(CMAKE_HIP_FLAGS "${CMAKE_HIP_FLAGS} -fgpu-rdc")

add_executable(testHIPSeparable testCudaSeparable.hip)
target_link_libraries(testHIPSeparable hiplib)