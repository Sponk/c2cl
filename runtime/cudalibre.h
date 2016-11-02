#ifndef __CUDALIBRE_H__
#define __CUDALIBRE_H__

#include <stddef.h>
#include <utility> // So std::pair can be used for kernel calls
#include <vector>
#include <memory>
#include <cstring>

#define LIBRECUDA_MAJOR 2
#define LIBRECUDA_MINOR 0

// TODO: https://www.cs.cmu.edu/afs/cs/academic/class/15668-s11/www/cuda-doc/html
//		/group__CUDART__TYPES_g3f51e3575c2178246db0a94a430e0038.html#g3f51e3575c2178246db0a94a430e0038
typedef enum cudaError
{
	cudaSuccess,
	cudaErrorMemoryAllocation,
	cudaErrorInitializationError,
	cudaErrorInvalidDevice,
	libreCudaErrorNotImplemented
}cudaError_t;

enum cudaComputeMode
{
	cudaComputeModeDefault,
	cudaComputeModeExclusive,
	cudaComputeModeProhibited
};

struct dim3
{
	dim3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	dim3(float x, float y)
		: x(x), y(y), z(0) {}

	dim3(float x)
		: x(x), y(0), z(0) {}

	dim3() : x(0), y(0), z(0) {}

	float x;
	float y;
	float z;
};

struct cudaDeviceProp 
{
	char name[256];
	size_t totalGlobalMem;
	size_t sharedMemPerBlock;
	int regsPerBlock;
	int warpSize;
	size_t memPitch;
	int maxThreadsPerBlock;
	int maxThreadsDim[3];
	int maxGridSize[3];
	size_t totalConstMem;
	int major;
	int minor;
	int clockRate;
	size_t textureAlignment;
	int deviceOverlap;
	int multiProcessorCount;
	int kernelExecTimeoutEnabled;
	int l2CacheSize;
	int integrated;
	int canMapHostMemory;
	int computeMode;
	int concurrentKernels;
	int ECCEnabled;
	int pciBusID;
	int pciDeviceID;
	int tccDriver;
};

cudaError_t cudaGetDeviceCount(int* count);
cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp* prop, int device);

/// Non-CUDA functions

typedef std::vector<std::pair<size_t, void*>> lcArgumentList;

bool lcSetSources(const char* sources);

/**
 * @brief Calls a kernel in the currently loaded program.
 *
 * @param name The name of the function to call
 * @param w The "width" of one thread block
 * @param h The "height" of one thread block
 * @param args A list of arguments
 */
bool lcCallKernel(const char* name, const dim3& gridsize, const dim3& blocksize, const lcArgumentList& args);
bool lcCallKernel(const char* name, const dim3& gridsize, const dim3& blocksize); // No args

void lcWaitForKernel();

// We don't need to actually copy the arguments since OpenCL does not keep the pointer
// and copies the data for itself.
#define LC_KERNEL_ARG(x) {sizeof(x), lcAddressOf<typeof(x)>(x)}
template<typename T> void* lcAddressOf(const T& src) { /*T* t = (T*) malloc(sizeof(T)); memcpy(t, &src, sizeof(T)); return t;*/ return (void*) &src; }

#endif
