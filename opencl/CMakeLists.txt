add_executable(hello_world_opencl_c src/hello_world_opencl.c)
target_link_libraries(hello_world_opencl_c ${OpenCL_LIBRARY})

add_executable(hello_world_opencl_cpp src/hello_world_opencl.cpp)
target_link_libraries(hello_world_opencl_cpp ${OpenCL_LIBRARY})