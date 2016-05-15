#include <iostream>
#include "Indice1D.h"
#include "Indice2D.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
__global__ void histogramDevice(int* ptrDevInput, int* ptrDevOut, int n, int size);

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
__global__ void histogramDevice(int* ptrDevInput, int* ptrDevOut, int n, int size)
    {
    extern __shared__ int tabData[];

    const int THREADS = Indice1D::tid();

    int s = Indice2D::nbThreadX();

    if(Indice1D::tidLocal() < size)
	{
	tabData[Indice1D::tidLocal()] = 0;
	}

    __syncthreads();

    while(s < n)
	{
	atomicAdd(&tabData[ptrDevInput[s]], 1);
	s += THREADS;
	}

    __syncthreads();

    if(Indice1D::tidLocal() < size)
	{
	atomicAdd(&ptrDevOut[Indice1D::tidLocal()], tabData[Indice1D::tidLocal()]);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

