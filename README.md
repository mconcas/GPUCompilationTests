# GPUSeparableCompilationTest
Test some features with CUDA and HIP separable compilation

## Build
```bash
mkdir build && cd build && cmake .. && make
```

## Test
From `build` directory:
```bash
$> ./build/cuda/bin/testCudaSeparable
Kernel on library -> a: 42, b: 3.140000, c: 2.718282
Kernel on main executable -> a: 42, b: 3.140000, c: 2.718282
$> ./build/hip/bin/testHIPSeparable
Kernel on library -> a: 42, b: 3.140000, c: 2.718282
Kernel on main executable -> a: 42, b: 3.140000, c: 2.718282
```
