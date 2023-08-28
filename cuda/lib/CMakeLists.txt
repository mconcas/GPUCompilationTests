add_library(cudalib SHARED cudalib.cu)

set_target_properties(${targetName} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)