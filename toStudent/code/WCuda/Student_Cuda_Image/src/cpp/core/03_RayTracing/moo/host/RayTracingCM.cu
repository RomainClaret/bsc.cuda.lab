#include "RayTracingCM.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
#include "AleaTools.h"
#include "ConstantMemoryLink.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#define NB_SPHERE 50
//__constant__ Sphere CM_DATA[NB_SPHERE];

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
extern __global__ void rayTracingCM(uchar4* ptrDevPixels, int w, int h, int nbSpheres, int t, Sphere* ptrSpheres);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
ConstantMemoryLink constantMemoryLink(void)
{
    Sphere* ptrDevCML;
    size_t currentSize = NB_SPHERE * sizeof(Sphere);
//    HANDLE_ERROR(cudaGetSymbolAddress((void **) &ptrDevCM, CM_DATA));
    ConstantMemoryLink cmLink;
    cmLink.n = NB_SPHERE;
    cmLink.ptrDevTab = (void**) ptrDevCML;
    cmLink.sizeAll = currentSize;
    return cmLink;
}

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/
RayTracingCM::RayTracingCM(const Grid& grid, uint w, uint h, float dt, int spheres):
	Animable_I<uchar4>(grid, w, h, "RayTracing_CM_Cuda")
    {
    this->dt = dt;
    this->nbSpheres = nbSpheres;
    this->ptrSpheres = new Sphere[this->nbSpheres];

    this->t = 0.0;

    this->ptrSpheres = new Sphere[NB_SPHERE];

    AleaTools aleaTools = AleaTools();
    float bord = 200.0f;

    float rayon;
    float3 centre;
    float hue;

    for(int i=0;i<NB_SPHERE;i++)
	{
	rayon = aleaTools.uniformeAB(20, w/10);

	centre.x = aleaTools.uniformeAB(bord, h-bord);
	centre.y = aleaTools.uniformeAB(bord, w-bord);
	centre.z = aleaTools.uniformeAB(10, 2*w);

	hue = aleaTools.uniforme01();

	ptrSpheres[i] = *(new Sphere(centre, rayon, hue));
	}

    ConstantMemoryLink cmLink = constantMemoryLink();
    ptrDevCML = (Sphere*)cmLink.ptrDevTab;
    size_t currentSize = cmLink.sizeAll;
    HANDLE_ERROR(cudaMemcpy(ptrDevCML, ptrSpheres, currentSize, cudaMemcpyHostToDevice));

    }

RayTracingCM::~RayTracingCM()
    {
//    delete[] CM_DATA;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void RayTracingCM::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    rayTracingCM<<<dg,db>>>(ptrDevPixels, w, h, NB_SPHERE, this->t, ptrDevCML);
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracingCM::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

