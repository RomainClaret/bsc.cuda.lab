#include <iostream>

#include "cudaTools.h"
#include "Device.h"
#include "math.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern __global__ void histogramDevice(int* ptrDevInput, int* ptrDevOut, int n, int size);

bool runHisto(int n);
int randomInt(int min, int max);
bool histogramGM(int n);
void printFrequencies(int* ptrOut, int n);

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
int randomInt(int min, int max)
    {
    return (int)( (max-min) * ( (float)(rand()) / (float)RAND_MAX ) + min);
    }

bool histogramGM(int n)
    {
    return runHisto(n);
    }

bool runHisto(int n)
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
    HANDLE_ERROR(cudaMemcpy(ptrDevInput, ptrInput, n_size, cudaMemcpyHostToDevice));

    HANDLE_ERROR(cudaMalloc((void**)&ptrDevOut, max_size));
    HANDLE_ERROR(cudaMemcpy(ptrDevOut, ptrOut, max_size, cudaMemcpyHostToDevice));

    histogramDevice<<<dg, db, max_size>>>(ptrDevInput, ptrDevOut, n, N_MAX_VALUE);
    Device::lastCudaError("histogramDeviceGM");

    HANDLE_ERROR(cudaMemcpy(ptrOut, ptrDevOut, max_size, cudaMemcpyDeviceToHost));
    HANDLE_ERROR(cudaFree(ptrDevOut));
    HANDLE_ERROR(cudaFree(ptrDevInput));

    //printFrequencies(ptrOut, n);

    bool isOk = true;
    for(int i = 0; isOk && i < N_MAX_VALUE-1; ++i)
	{
	isOk &= (ptrOut[i] == ptrOut[i+1]);
	}

    delete[] ptrInput;
    delete[] ptrOut;

    return isOk;
    }

void printFrequencies(int* ptrOut, int n)
    {
    for(int i=0; i<n; i++)
	{
	std::cout << "i = " << i << " | frequence = " << ptrOut[i] << std::endl;
	}
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

