#pragma once

#include "cudaTools.h"
#include "MathTools.h"

#include "Fractal.h"

#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal: public Animable_I<uchar4>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	Fractal(const Grid& grid, uint w, uint h, int nMin, int nMax, float dt, const DomaineMath& domaineMath, bool isJulia);
	virtual ~Fractal(void);

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
	uint n;
	float dt;

	// Tools
	Variateur<float> variateurAnimation;
	void (Fractal::*whoProcess)(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);
	void processFractalJulia(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);
	void processFractalMandelbrot(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
