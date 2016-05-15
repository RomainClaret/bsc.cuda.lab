#pragma once

#include "RayTracingMath.h"
#include "Sphere.h"

#include "cudaTools.h"
#include "MathTools.h"

#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#ifndef MAX_SPHERES
#define MAX_SPHERES 2300
#endif

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracing
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	RayTracing(uint w, uint h);
	void populateSpheres(int nbSpheres, Sphere *ptrSpheres);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/
    private:
	uint w;
	uint h;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
