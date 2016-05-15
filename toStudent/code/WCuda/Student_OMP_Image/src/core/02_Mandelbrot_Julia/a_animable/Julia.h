#ifndef SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_JULIA_H_
#define SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_JULIA_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "Fractale.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Julia: public Fractale
    {
    public:
	Julia(float x, float y, int n);
	virtual ~Julia();
	virtual int mandelbrotJulia(float x, float y);

    private:
	float c1;
	float c2;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
