#include <iostream>

#include "Device.h"
#include "cudaTools.h"
#include "curandTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern __global__ void computeMontecarlo(int* ptrDevResult, curandState* ptrDevTabGenerators, int nbGen);
float computeMontecarloMono(int n);
float computeMontecarloMulti(int n);

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
float computeMontecarloMono(int n)
    {
    int* ptrDevResult;
    curandState* ptrDevTabGenerators;
    int resultPoints;
    const int GENERATIONS = n;

    const int BLOCKS = 256; //M6000
    const int THREADS = 64; //M6000
    dim3 dg(BLOCKS, 1, 1);
    dim3 db(THREADS, 1, 1);

    Device::gridAssert(dg, db);

    float elapsed=0;
    cudaEvent_t start, stop;

    HANDLE_ERROR(cudaEventCreate(&start));
    HANDLE_ERROR(cudaEventCreate(&stop));
    HANDLE_ERROR(cudaEventRecord(start, 0));

    HANDLE_ERROR(cudaMalloc(&ptrDevResult, sizeof(int)));
    HANDLE_ERROR(cudaMalloc(&ptrDevTabGenerators, BLOCKS * THREADS * sizeof(curandState)));
    HANDLE_ERROR(cudaMemset(ptrDevResult, 0, sizeof(int)));

    setup_kernel_rand<<<dg,db>>>(ptrDevTabGenerators, 0);
    computeMontecarlo<<<dg,db>>>(ptrDevResult, ptrDevTabGenerators, GENERATIONS);

    HANDLE_ERROR(cudaMemcpy(&resultPoints, ptrDevResult, sizeof(int), cudaMemcpyDeviceToHost));
    HANDLE_ERROR(cudaFree(ptrDevResult));
    HANDLE_ERROR(cudaFree(ptrDevTabGenerators));

    HANDLE_ERROR(cudaEventRecord(stop, 0));
    HANDLE_ERROR(cudaEventSynchronize (stop) );

    HANDLE_ERROR(cudaEventElapsedTime(&elapsed, start, stop) );

    HANDLE_ERROR(cudaEventDestroy(start));
    HANDLE_ERROR(cudaEventDestroy(stop));

    std::cout << "The elapsed time in GPU was " << elapsed << " ms" << std::endl;

    return resultPoints * 4.0 / GENERATIONS;
    }

float computeMontecarloMulti(int n)
    {
    const int GENERATIONS = n;
    const int DEVICES = Device::getDeviceCount();
    const int DEVICE_GENERATIONS = GENERATIONS / DEVICES;
    int deviceResults[DEVICES];

    const int BLOCKS = 256; //M6000
    const int THREADS = 64; //M6000

#pragma omp parallel for
    for (int i = 0; i < DEVICES; i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));

	dim3 dg(BLOCKS, 1, 1);
	dim3 db(THREADS, 1, 1);

	Device::gridAssert(dg, db);

	int* ptrDevResult;
	curandState* ptrDevTabGenerators;

	float elapsed=0;
	cudaEvent_t start, stop;

	HANDLE_ERROR(cudaEventCreate(&start));
	HANDLE_ERROR(cudaEventCreate(&stop));
	HANDLE_ERROR(cudaEventRecord(start, 0));

	HANDLE_ERROR(cudaMalloc(&ptrDevResult, sizeof(int)));
	HANDLE_ERROR(cudaMalloc(&ptrDevTabGenerators, BLOCKS * THREADS * sizeof(curandState)));
	HANDLE_ERROR(cudaMemset(ptrDevResult, 0, sizeof(int)));

	setup_kernel_rand<<<dg,db>>>(ptrDevTabGenerators, i);
	computeMontecarlo<<<dg,db>>>(ptrDevResult, ptrDevTabGenerators, DEVICE_GENERATIONS);

	HANDLE_ERROR(cudaMemcpy(&deviceResults[i], ptrDevResult, sizeof(int), cudaMemcpyDeviceToHost));
	HANDLE_ERROR(cudaFree(ptrDevResult));
	HANDLE_ERROR(cudaFree(ptrDevTabGenerators));

	HANDLE_ERROR(cudaEventRecord(stop, 0));
	HANDLE_ERROR(cudaEventSynchronize (stop) );

	HANDLE_ERROR(cudaEventElapsedTime(&elapsed, start, stop) );

	HANDLE_ERROR(cudaEventDestroy(start));
	HANDLE_ERROR(cudaEventDestroy(stop));

	std::cout << "The elapsed time in GPU " << i << ": " << elapsed << " ms" << std::endl;
	}

    int sum = 0;
    for (int i = 0 ; i < DEVICES ; i++) {
	sum += deviceResults[0];
    }

    return sum * 4.0 / (DEVICES * DEVICE_GENERATIONS);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

