#define CL_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_ENABLE_EXCEPTIONS

#ifdef __APPLE__
#include <CL/opencl.hpp>
#else
#include <CL/cl2.hpp>
#endif
#include <iostream>
#include <vector>

const std::string kernelSource =
    "__kernel void helloWorld(__global int* deviceId) {  \
        printf(\"Hello, World! From device %d %x\\n\", *deviceId, as_uint(*deviceId)); \
    }";

int main()
{
    try
    {
        // Get all platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.empty())
        {
            std::cerr << "No platforms found. Check OpenCL installation!\n";
            exit(1);
        }

        for (auto &platform : platforms)
        {
            std::string platformName;
            platform.getInfo(CL_PLATFORM_NAME, &platformName);
            std::cout << "Platform: " << platformName << std::endl;

            // Get all devices for this platform
            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
            if (devices.empty())
            {
                std::cout << " No devices found on platform.\n";
                continue;
            }

            for (int j = 0; j < devices.size(); ++j)
            {
                std::string deviceName;
                devices[j].getInfo(CL_DEVICE_NAME, &deviceName);
                std::cout << "    Device: " << deviceName << std::endl;

                int deviceId = j;

                // Create context and queue for current device
                cl::Context context(devices[j]);
                cl::CommandQueue queue(context, devices[j]);

                // Create a buffer for the device ID
                cl::Buffer deviceIdBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), &deviceId);

                // Build kernel program
                cl::Program::Sources source;
                source.push_back({kernelSource.c_str(), kernelSource.length()});
                cl::Program program(context, source);
                program.build({devices[j]});

                // Create kernel and set argument
                cl::Kernel kernel(program, "helloWorld");
                kernel.setArg(0, deviceIdBuffer);

                // Execute the kernel
                queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NullRange);
                queue.finish();
            }
        }
    }
    catch (cl::Error &e)
    {
        std::cerr << "OpenCL error: " << e.what() << ", " << e.err() << std::endl;
        return 1;
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}