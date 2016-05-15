#pragma once

#ifndef SRC_CORE_02_MANDELBROT_JULIA_B_PROVIDER_JULIAPROVIDER_H_
#define SRC_CORE_02_MANDELBROT_JULIA_B_PROVIDER_JULIAPROVIDER_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"

using namespace cpu;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class JuliaProvider: public Provider_I<uchar4>
    {
    public:
	virtual ~JuliaProvider();

	Animable_I<uchar4>* createAnimable(void);
	Image_I* createImageGL(void);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
