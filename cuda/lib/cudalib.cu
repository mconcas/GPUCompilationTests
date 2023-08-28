#include <cstdio>

__global__ void testkernel() {
    printf("this is GPU!\n");
}

extern "C" void runLibKernel() {
    testkernel<<<1, 1>>>();
    cudaDeviceSynchronize();
}