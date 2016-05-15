#pragma once

#include "FractalMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class JuliaMath: public FractalMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	JuliaMath(float c1, float c2): FractalMath()
	    {
	    this->c1 = c1;
	    this->c2 = c2;
	    }

	__device__
	virtual ~JuliaMath()
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
	    float a = x;
	    float b = y;
	    int k = 0;

	    while (!this->isDivergent(a, b) && k <= n)
		{
		float aCopy = a;
		a = (aCopy * aCopy - b * b) + this->c1;
		b = 2.0 * aCopy * b + this->c2;
		k++;
		}
	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float c1;
	float c2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
