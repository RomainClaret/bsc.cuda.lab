#pragma once

#include <math.h>
#include "MathTools.h"

#ifndef PI
#define PI 3.141592653589793f
#endif

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Sphere
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__host__
	Sphere(float3 centre, float rayon, float hue)
	    {
	    // Inputs
	    this->centre = centre;
	    this->r = rayon;
	    this->hueStart = hue;
	    // Tools
	    this->rCarre = rayon * rayon;
	    }

	__host__
	Sphere()
	    {
	    // rien
	    }

	__host__
	virtual ~Sphere()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	float hCarre(float2 xySol)
	    {
	    float a = (centre.x - xySol.x);
	    float b = (centre.y - xySol.y);
	    return a * a + b * b;
	    }

	__device__
	bool isEnDessous(float hCarre)
	    {
	    return hCarre < rCarre;
	    }

	__device__
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }

	__device__
	float brightness(float dz)
	    {
	    return dz / r;
	    }

	__device__
	float distance(float dz)
	    {
	    return centre.z - dz;
	    }

	__device__
	float getHueStart()
	    {
	    return hueStart;
	    }

	__device__
	float hue(float t)// usefull for animation
	    {
	    return 0.5 + 0.5 * sinf(t + T + 3 * PI / 2);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    private:
	// Inputs
	float r;
	float3 centre;
	float hueStart;

	// Tools
	float rCarre;
	float T ; // usefull for animation

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
