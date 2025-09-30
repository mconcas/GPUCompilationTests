/// \author: mconcas@cern.ch

#ifndef GPU_BENCHMARK_KERNELS_H
#define GPU_BENCHMARK_KERNELS_H

#include "Utils.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <memory>
#include <chrono>

namespace o2
{
  namespace benchmark
  {

    template <class chunk_t>
    class GPUbenchmark final
    {
    public:
      GPUbenchmark() = delete; // need for a configuration
      GPUbenchmark(benchmarkOpts &opts) : mOptions{opts}
      {
      }
      virtual ~GPUbenchmark() = default;
      template <typename... T>
      float measure(void (GPUbenchmark::*)(T...), const char *, T &&...args);

      // Single stream (sequential kernels) execution
      template <typename... T>
      float runSequential(void (*kernel)(chunk_t *, size_t, T...),
                          std::pair<float, float> &chunkRanges,
                          int nLaunches,
                          int dimGrid,
                          int dimBlock,
                          T &...args);

      // Multi-streams asynchronous executions
      template <typename... T>
      std::vector<float> runConcurrent(void (*kernel)(chunk_t *, size_t, T...),
                                       std::vector<std::pair<float, float>> &chunkRanges,
                                       int nLaunches,
                                       int dimStreams,
                                       int nBlocks,
                                       int nThreads,
                                       T &...args);

      // Single stream executions on all chunks at a time by same kernel
      template <typename... T>
      float runDistributed(void (*kernel)(chunk_t **, size_t *, T...),
                           std::vector<std::pair<float, float>> &chunkRanges,
                           int nLaunches,
                           size_t nBlocks,
                           int nThreads,
                           T &...args);

      // Main interface
      void globalInit();     // Allocate scratch buffers and compute runtime parameters
      void run();            // Execute all specified callbacks
      void globalFinalize(); // Cleanup
      void printDevices();   // Dump info

      // Initializations/Finalizations of tests. Not to be measured, in principle used for report
      void initTest(Test);
      void finalizeTest(Test);

      // Kernel calling wrapper
      void runTest(Test, Mode, KernelConfig);

    private:
      gpuState<chunk_t> mState;
      benchmarkOpts mOptions;
    };

  } // namespace benchmark
} // namespace o2
#endif