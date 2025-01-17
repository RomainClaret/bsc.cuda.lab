#include <iostream>
#include "ReductionTools.h"
#include "CommunDevices.h"
#include "curand_kernel.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
__global__ void computeMontecarlo(int* ptrDevResult, curandState* ptrDevTabGenerators, int nbGen);
__device__ int generatorDevice(curandState* ptrDevTabGenerators, int nbGen);
__device__ void generatePoints(curandState* ptrDevGenerator, float xMin, float xMax, float yMin, float yMax, float* x, float* y);


/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void computeMontecarlo(int* ptrDevResult, curandState* ptrDevTabGenerators, int nbGen)
    {
    __shared__ int ptrDevArraySM[4096]; // sm_52

    ptrDevArraySM[Indice1D::tidLocal()] = generatorDevice(ptrDevTabGenerators, nbGen);

    __syncthreads();

    ReductionTools::template reductionIntraBlock<int>(ptrDevArraySM, Indice1D::nbThreadBlock());
    ReductionTools::template reductionInterBlock<int>(ptrDevArraySM, ptrDevResult);
    }


__device__ int generatorDevice(curandState* ptrDevTabGenerators, int nbGen)
    {
    const int NB_THREADS= Indice1D::nbThread();
    const int TID = Indice1D::tid();

    float sum = 0.0;
    float dx;
    float dy;
    int s = TID;
    while (s < nbGen)
	{
	generatePoints(&ptrDevTabGenerators[TID], 0, 0, 1, 4, &dx, &dy);

	if (CommunDevices::calcPi(dx) > dy)
	    {
	    sum++;
	    }

	s += NB_THREADS;
	}

    return sum;
    }

__device__ void generatePoints(curandState* ptrDevGenerator, float xMin, float yMin, float xMax, float yMax, float* dx, float* dy)
    {
    *dx = curand_uniform(ptrDevGenerator) * (xMax - xMin) + xMin;
    *dy = curand_uniform(ptrDevGenerator) * (yMax - yMin) + yMin;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

