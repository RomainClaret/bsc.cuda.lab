#pragma once

#include "Indice1D.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class ReductionTools
    {
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:
	template<typename T>
	__device__ static void reductionIntraBlock(T* arraySM, int size)
	    {
	    const int THREAD_LOCAL_ID = Indice1D::tidLocal();
	    const int NB_THREADS_LOCAL = Indice1D::nbThread();

	    int work_size = size;
	    int work_half = size / 2;
	    while (work_half >= 1)
		{
		int s = THREAD_LOCAL_ID;
		while (s < work_half)
		    {
		    arraySM[s] += arraySM[s + work_half];
		    s += NB_THREADS_LOCAL;
		    }

		__syncthreads();

		work_size = work_half;
		work_half = work_size / 2;
		}
	    }

	template<typename T>
	__device__ static void reductionInterBlock(T* arraySM, T* resultGM)
	    {
	    const int THREAD_LOCAL_ID = Indice1D::tidLocal();

	    if (THREAD_LOCAL_ID == 0)
		{
		atomicAdd(resultGM, arraySM[0]);
		}
	    }
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
