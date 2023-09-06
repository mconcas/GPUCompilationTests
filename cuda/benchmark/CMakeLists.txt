message(STATUS "Building GPU CUDA benchmark")
add_executable(gpu-memory-benchmark-cuda benchmark.cu Kernels.cu)
target_link_libraries(gpu-memory-benchmark-cuda ${Boost_LIBRARIES})
set_target_properties(gpu-memory-benchmark-cuda PROPERTIES CUDA_ARCHITECTURES "61")