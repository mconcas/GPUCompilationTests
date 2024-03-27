#include <stdio.h>
#include <stdlib.h>

#define CL_TARGET_OPENCL_VERSION 120
#include <CL/cl.h>

const char *kernelSource =
    "__kernel void helloWorld(__global int* deviceId) {  \
        printf(\"Hello, World! From device %d %x\\n\", *deviceId, as_uint(*deviceId)); \
    }";

int main()
{
    cl_platform_id *platforms;
    cl_device_id *device_list;
    cl_uint num_platforms;
    cl_uint num_devices;
    cl_int ret;

    // Get the number of platforms
    clGetPlatformIDs(0, NULL, &num_platforms);
    platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms);

    // Get the platforms
    clGetPlatformIDs(num_platforms, platforms, NULL);

    // Iterate over platforms
    for (cl_uint i = 0; i < num_platforms; i++)
    {
        char platformName[128];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 128, platformName, NULL);
        printf("Platform: %s\n", platformName);

        // Get the number of devices for the current platform
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
        device_list = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices);

        // Get the devices
        clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, num_devices, device_list, NULL);

        // Iterate over devices
        for (cl_uint j = 0; j < num_devices; j++)
        {
            char deviceName[128];
            clGetDeviceInfo(device_list[j], CL_DEVICE_NAME, 128, deviceName, NULL);
            printf("    Device: %s\n", deviceName);

            int deviceId = j;

            // Create an OpenCL context
            cl_context context = clCreateContext(NULL, 1, &device_list[j], NULL, NULL, &ret);

            // Create a buffer for the device ID
            cl_mem deviceIdBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), &deviceId, &ret);

            // Create a command queue
            cl_command_queue command_queue = clCreateCommandQueue(context, device_list[j], 0, &ret);

            // Create a program from the kernel source
            cl_program program = clCreateProgramWithSource(context, 1, (const char **)&kernelSource, NULL, &ret);

            // Build the program
            ret = clBuildProgram(program, 1, &device_list[j], NULL, NULL, NULL);

            // Create the OpenCL kernel
            cl_kernel kernel = clCreateKernel(program, "helloWorld", &ret);

            // Set the kernel argument for the device ID
            ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &deviceIdBuffer);

            // Execute the OpenCL kernel on the device
            size_t global_item_size = 1; // Process the entire lists
            size_t local_item_size = 1;  // Process in groups of 1
            ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

            // Clean up
            ret = clFlush(command_queue);
            ret = clFinish(command_queue);
            ret = clReleaseKernel(kernel);
            ret = clReleaseProgram(program);
            ret = clReleaseCommandQueue(command_queue);
            ret = clReleaseContext(context);

            // After execution, release the device ID buffer
            ret = clReleaseMemObject(deviceIdBuffer);
        }

        free(device_list);
    }

    free(platforms);
    return 0;
}