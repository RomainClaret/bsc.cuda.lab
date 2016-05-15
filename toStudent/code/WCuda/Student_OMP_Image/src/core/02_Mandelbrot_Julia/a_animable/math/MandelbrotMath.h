#ifndef SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_MANDELBROTMATH_H_
#define SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_MANDELBROTMATH_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "../Fractale.h"
#include <math.h>
#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/
class MandelbrotMath
    {
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:
	MandelbrotMath(Fractal* fractal, int n)
	    {
	    this->n = n;
	    this->fractal = fractal;
	    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Protected		*|
 \*-------------------------------------*/
    protected:
    	int n;
    	Fractal *fractal;

    };
#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

