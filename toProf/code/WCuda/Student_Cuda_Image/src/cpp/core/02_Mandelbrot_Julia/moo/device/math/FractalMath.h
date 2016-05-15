#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "Calibreur_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	FractalMath(): calibreur(Interval<float>(-1,1), Interval<float>(0,1))
	    {
	    // rien
	    }

	__device__
	virtual ~FractalMath()
	{
	// rien
	}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x, float y, int n)
	    {
	    int k = this->k_level(x, y, n);

	    if (k > n)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hue = (1.0 / (float) n) * k;
		ColorTools::HSB_TO_RVB(hue, ptrColor);
		}

	    ptrColor->w = 255; // opaque
	    }

    protected:

	__device__
	virtual int k_level(float x, float y, int n) = 0;

	__device__
	bool isDivergent(float a, float b)
	    {
	    return (a*a + b*b) > 4.0;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
