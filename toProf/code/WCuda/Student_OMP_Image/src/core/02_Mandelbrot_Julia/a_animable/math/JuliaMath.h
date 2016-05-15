#ifndef SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_JULIAMATH_H_
#define SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_MATH_JULIAMATH_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "../Fractale"
#include <math.c>
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

class JuliaMath
    {

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:
	JuliaMath(Fractal* fractal, int n)
	{
	this->fractal = fractal;
	this->n = n;
	}

	virtual ~JuliaMath()
	    {

	    }

	void colorIJ(uchar4* ptrColorIJ, float i, float j, float t)
	    {
	    int k = fractal->mandelbrotJulia(i, j);
	    if (k <= this->n)
		{
		double color = h(k);
		ColorTools::HSB_TO_RVB(color, ptrColorIJ);
		}
	    else
		{
		ptrColorIJ->x = 0;
		ptrColorIJ->y = 0;
		}

	    ptrColorIJ->z = 0;
	    ptrColorIJ->w = 255;
	    }
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
    private:
	double h(int k)
	    {
	    return (1.0 / this->n) * k;
	    }

/*--------------------------------------*\
 |*		Protected		*|
 \*-------------------------------------*/
    protected:
	Fractal *fractal;
	int n;


    };

#endif
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

