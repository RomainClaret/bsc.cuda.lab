#pragma once

#include "FractalMath.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath: public FractalMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	MandelbrotMath(): FractalMath()
	    {
	    // rien
	    }

	__device__
	virtual ~MandelbrotMath()
	{
	// rien
	}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    protected:

	__device__
	virtual int k_level(float x, float y, int n)
	    {
	    float a = 0;
	    float b = 0;
	    int k = 0;

	    while (!isDivergent(a, b) && k <= n)
		{
		float aCopy = a;
		a = (aCopy * aCopy - b * b) + x;
		b = 2.0 * aCopy * b + y;
		k++;
		}
	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	// rien

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
