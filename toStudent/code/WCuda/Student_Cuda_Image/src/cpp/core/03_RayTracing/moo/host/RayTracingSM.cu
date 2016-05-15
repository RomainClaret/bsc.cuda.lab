#include "RayTracingSM.h"

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
extern __global__ void rayTracingSM(uchar4* ptrDevPixels, int w, int h, int spheres, int t, Sphere* ptrSpheres);

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
RayTracingSM::RayTracingSM(const Grid& grid, uint w, uint h, float dt, int spheres):
	Animable_I<uchar4>(grid, w, h, "RayTracing_SM_Cuda"),
	RayTracing(w,h)
    {
    this->dt = dt;
    this->nbSpheres = nbSpheres;
    this->ptrSpheres = new Sphere[this->nbSpheres];

    this->t = 0.0;

    RayTracing::populateSpheres(this->nbSpheres, this->ptrSpheres);
    }

RayTracingSM::~RayTracingSM()
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
void RayTracingSM::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Sphere* ptrDevSphere=NULL;
    size_t currentSize = this->nbSpheres * sizeof(Sphere);

    HANDLE_ERROR(cudaMalloc(&ptrDevSphere,currentSize));
    HANDLE_ERROR(cudaMemcpy(ptrDevSphere, this->ptrSpheres, currentSize, cudaMemcpyHostToDevice));

    rayTracingSM<<<dg,db>>>(ptrDevPixels, w, h, this->nbSpheres, this->t, ptrDevSphere);

    HANDLE_ERROR(cudaFree(ptrDevSphere));
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracingSM::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

