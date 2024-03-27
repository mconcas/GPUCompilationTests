# GPUSeparableCompilationTest
Minimal project to be used as baseline for tests on CUDA, HIP and OpenCL tests, eg. separable compilation

## Build
```bash
mkdir build && cd build && cmake .. && make
```

## Tests
### Separable compilation
From `build` directory:
```bash
$> ./build/cuda/bin/testCudaSeparable
Kernel on library -> a: 42, b: 3.140000, c: 2.718282
Kernel on main executable -> a: 42, b: 3.140000, c: 2.718282
$> ./build/hip/bin/testHIPSeparable
Kernel on library -> a: 42, b: 3.140000, c: 2.718282
Kernel on main executable -> a: 42, b: 3.140000, c: 2.718282
```
### GPU memory benchmark
```bash
# CUDA
$> ./build/cuda/benchmark/gpu-memory-benchmark-cuda -p239
# HIP
$> ./build/hip/benchmark/gpu-memory-benchmark-hip -p239
```
