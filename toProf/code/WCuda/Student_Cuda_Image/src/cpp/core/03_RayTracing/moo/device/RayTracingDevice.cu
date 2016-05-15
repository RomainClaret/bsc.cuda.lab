#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "ConstantMemoryLink.h"

#include "Sphere.h"
#include "RayTracingMath.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void rayTracingGM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);
__global__ void rayTracingCM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);
__global__ void rayTracingSM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
static __device__ void work(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);
static __device__ void gm2sm(Sphere* ptrSpheresGM, Sphere* ptrSpheresSM, int size);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    __global__
    void rayTracingGM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres)
	{
	work(ptrDevPixels, w, h, spheres, t, ptrSpheres);
	}

    __global__
    void rayTracingCM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres)
	{
	work(ptrDevPixels, w, h, spheres, t, ptrSpheres);
	}

    __global__
    void rayTracingSM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres)
	{
	extern __shared__ Sphere ptrSpheresSM[];

	gm2sm(ptrSpheres, ptrSpheresSM, spheres);

	__syncthreads();
	work(ptrDevPixels, w, h, spheres, t, ptrSpheresSM);
	}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

    __device__
    void work(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres)
	{
	RayTracingMath rayTracingMath = RayTracingMath(t);

	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w*h;

	int i;
	int j;

	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);

	    rayTracingMath.colorIJ(&ptrDevPixels[s], i, j, t, ptrSpheres, spheres);

	    s += NB_THREAD;
	    }
	}

    __device__
    void gm2sm(Sphere* ptrSpheresGM, Sphere* ptrSpheresSM, int size)
	{
	const int TID_LOCAL = Indice2D::tidLocal();
	const int NB_THREAD_BLOCK = Indice2D::nbThreadBlock();

	int s = TID_LOCAL;
	while (s < size)
	    {
	    ptrSpheresSM[s] = ptrSpheresGM[s];
	    s += NB_THREAD_BLOCK;
	    }
	}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

