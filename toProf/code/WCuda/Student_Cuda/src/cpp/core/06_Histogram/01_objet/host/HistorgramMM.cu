#include <iostream>

#include "cudaTools.h"
#include "Device.h"
#include "math.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern __global__ void histogramDevice(int* ptrDevInput, int* ptrDevOut, int n, int size);
extern int randomInt(int, int);

bool runHistoMM(int n);
bool histogramMM(int n);

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
bool histogramMM(int n)
    {
    return runHistoMM(n);
    }

bool runHistoMM(int n)
    {
    const int N_MAX_VALUE = 256;
    const int BLOCKS = 256; //M6000
    const int THREADS = N_MAX_VALUE; //M6000

    dim3 dg = dim3(BLOCKS, 1, 1);
    dim3 db = dim3(THREADS, 1, 1);
    Device::gridAssert(dg, db);

    size_t max_size = N_MAX_VALUE*sizeof(int);
    size_t n_size = n*sizeof(int);

    int* ptrInput = new int[n];
    int* ptrOut = new int[N_MAX_VALUE];

    int* ptrDevInput;
    int* ptrDevOut;


    for(int i = 0; i < n; ++i)
	{
	ptrInput[i] = i%N_MAX_VALUE;
	}

    for(int i = 0; i < N_MAX_VALUE; ++i)
	{
	ptrOut[i] = 0;
	}

    for(int i = 0; i < n; ++i)
	{
	std::swap(ptrInput[randomInt(0, n-1)], ptrInput[randomInt(0, n-1)]);
	}

    HANDLE_ERROR(cudaMalloc((void**)&ptrDevInput, n_size));
    HANDLE_ERROR(cudaMemset(ptrDevInput, 0, n_size));

    HANDLE_ERROR(cudaMalloc((void**)&ptrDevOut, max_size));
    HANDLE_ERROR(cudaMemset(ptrDevOut, 0, max_size));

    histogramDevice<<<dg, db, max_size>>>(ptrDevInput, ptrDevOut, n, N_MAX_VALUE);
    Device::lastCudaError("histogramDeviceMM");

    HANDLE_ERROR(cudaMemcpy(ptrOut, ptrDevOut, max_size, cudaMemcpyDeviceToHost));

    HANDLE_ERROR(cudaFree(ptrDevOut));
    HANDLE_ERROR(cudaFree(ptrDevInput));

    //printFrequenciesMM(ptrOut, n);

    bool isOk = true;
    for(int i = 0; isOk && i < N_MAX_VALUE-1; ++i)
	{
	isOk &= (ptrOut[i] == ptrOut[i+1]);
	}

    delete[] ptrInput;
    delete[] ptrOut;

    return isOk;
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

