#include "RayTracingGM.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
#include "AleaTools.h"

using namespace gpu;



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
extern __global__ void rayTracingGM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);

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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/
RayTracingGM::RayTracingGM(const Grid& grid, uint w, uint h, float dt, int nbSpheres):
	Animable_I<uchar4>(grid, w, h, "RayTracing_GM_Cuda"),
	RayTracing(w,h)
    {
    this->dt = dt;
    this->nbSpheres = nbSpheres;
    this->ptrSpheres = new Sphere[this->nbSpheres];

    this->t = 0.0;

    RayTracing::populateSpheres(this->nbSpheres, this->ptrSpheres);
    }

RayTracingGM::~RayTracingGM()
    {
    delete[] ptrSpheres;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void RayTracingGM::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Sphere* ptrDevSphere=NULL;
    size_t currentSize = this->nbSpheres * sizeof(Sphere);

    HANDLE_ERROR(cudaMalloc(&ptrDevSphere, currentSize));
    HANDLE_ERROR(cudaMemcpy(ptrDevSphere, this->ptrSpheres, currentSize, cudaMemcpyHostToDevice));

    rayTracingGM<<<dg,db>>>(ptrDevPixels, w, h, this->nbSpheres, this->t, ptrDevSphere);

    HANDLE_ERROR(cudaFree(ptrDevSphere));
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracingGM::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

