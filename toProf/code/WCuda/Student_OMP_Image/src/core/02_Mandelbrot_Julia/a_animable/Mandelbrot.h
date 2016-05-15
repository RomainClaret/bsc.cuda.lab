#ifndef SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_MANDELBROT_H_
#define SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_MANDELBROT_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "Fractale.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Mandelbrot: public Fractale
    {
    public:
	Mandelbrot(int n);
	virtual ~Mandelbrot();
	virtual int mandelbrotJulia(float x, float y);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
