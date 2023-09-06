#include <cstdio>
#include "data.h"

template <typename T>
void discardResult(const T&)
{
}

extern __constant__ Data d_data;

extern "C" void runLibKernel();
__global__ void mainKernel()
{
    printf("Kernel on main executable -> a: %d, b: %f, c: %f\n", d_data.a, d_data.b, d_data.c);
}

void runMainKernel()
{
    mainKernel<<<1, 1>>>();
    discardResult(cudaDeviceSynchronize());
}

int main()
{
    Data h_data = {42, 3.14f, 2.718281828459045};
    discardResult(cudaMemcpyToSymbol(d_data, &h_data, sizeof(Data)));

    runLibKernel();
    runMainKernel();
    return 0;
}