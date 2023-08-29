add_library(cudalib SHARED cudalib.cu)

set_target_properties(cudalib PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
set_target_properties(cudalib PROPERTIES CUDA_ARCHITECTURES "61")