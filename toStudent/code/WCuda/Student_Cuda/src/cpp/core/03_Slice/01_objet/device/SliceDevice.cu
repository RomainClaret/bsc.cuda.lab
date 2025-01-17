#include <iostream>
#include "ReductionTools.h"
#include "CommunDevices.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
__global__ void computePi(float* ptrDevResult, int nbSlices);
__device__ float sliceDevice(int nbSlices);

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
__global__ void computePi(float* ptrDevResult, int nbSlices)
    {
    __shared__ float ptrDevArraySM[4096]; // sm_52

    ptrDevArraySM[Indice1D::tidLocal()] = sliceDevice(nbSlices);

    __syncthreads();

    ReductionTools::template reductionIntraBlock<float>(ptrDevArraySM, Indice1D::nbThreadBlock());
    ReductionTools::template reductionInterBlock<float>(ptrDevArraySM, ptrDevResult);
    }


__device__ float sliceDevice(int nbSlices)
    {
    const int NB_THREADS = Indice1D::nbThread();

    float dx = 1.0 / nbSlices;

    float sum = 0.0;
    int s = Indice1D::tid();
    while (s < nbSlices)
	{
	sum += CommunDevices::calcPi(s * dx);
	s += NB_THREADS;
	}

    return sum / nbSlices;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

