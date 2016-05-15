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

class RayTracingCM: public Animable_I<uchar4>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	RayTracingCM(const Grid& grid, uint w, uint h, float dt, int nbSpheres);
	virtual ~RayTracingCM(void);

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
	Sphere* ptrDevCML;

	// Tools
	float dt;


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
