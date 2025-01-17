#include <iostream>

#include "Device.h"
#include "cudaTools.h"
#include "math.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern __global__ void computePi(float* ptrDevResult, int nbSlices);
float computePi();

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
float computePi()
    {
    float piValue;
    float* ptrDevResult;
    const int SLICES = 1e7;

    const int BLOCKS = 256; //M6000
    const int THREADS = 64; //M6000
    dim3 dg = dim3(BLOCKS,1,1);
    dim3 db = dim3(THREADS,1,1);
    Device::gridAssert(dg, db);

    HANDLE_ERROR(cudaMalloc(&ptrDevResult, sizeof(float)));
    HANDLE_ERROR(cudaMemset(ptrDevResult, 0, sizeof(float)));

    computePi<<<dg,db>>>(ptrDevResult, SLICES);

    HANDLE_ERROR(cudaMemcpy(&piValue, ptrDevResult, sizeof(float), cudaMemcpyDeviceToHost));
    HANDLE_ERROR(cudaFree(ptrDevResult));

    return piValue;
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

