#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Fractal.h"
using namespace gpu;



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void julia(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n);
extern __global__ void mandelbrot(uchar4* ptrTabPixels, int w, int h, DomaineMath domaineMath, int n);

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
Fractal::Fractal(const Grid& grid, uint w, uint h, int nMin, int nMax, float dt, const DomaineMath& domaineMath, bool isJulia):
	Animable_I<uchar4>(grid, w, h, "Fractal_Cuda_Julia_Mandelbrot", domaineMath),
	variateurAnimation(Interval<float>(nMin, nMax), 1)
    {
    this->n = nMax;
    this->dt = dt;
    this->whoProcess = isJulia ? &Fractal::processFractalJulia : &Fractal::processFractalMandelbrot;
    }

Fractal::~Fractal()
    {
   // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void Fractal::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    (this->*whoProcess)(ptrDevPixels, w, h, domaineMath);
    }


void Fractal::processFractalJulia(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    julia<<<this->dg, this->db>>>(ptrDevPixels, w, h, domaineMath, this->n);
    }

void Fractal::processFractalMandelbrot(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    mandelbrot<<<this->dg, this->db>>>(ptrDevPixels, w, h, domaineMath, this->n);
    }

/**
 * Override
 * Call periodicly by the API
 */
void Fractal::animationStep()
    {
    this->n = variateurAnimation.varierAndGet(); // in [0,2pi]
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

