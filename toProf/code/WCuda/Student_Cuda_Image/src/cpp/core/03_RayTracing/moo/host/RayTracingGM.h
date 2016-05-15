#pragma once

#include "RayTracing.h"

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

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingGM: public Animable_I<uchar4>, public RayTracing
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	RayTracingGM(const Grid& grid, uint w, uint h, float dt, int nbSpheres);
	virtual ~RayTracingGM(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int nbSpheres;
	Sphere* ptrSpheres;

	// Tools
	float dt;


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
