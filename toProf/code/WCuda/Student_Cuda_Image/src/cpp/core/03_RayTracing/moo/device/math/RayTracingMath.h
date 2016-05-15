#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "Calibreur_GPU.h"
#include "Sphere.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	RayTracingMath(int n): calibreur(Interval<float>(0.0, n), Interval<float>(0, 1))
	    {
	    //this->n = n;
	    }

	__device__
	virtual ~RayTracingMath()
	{
	// rien
	}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/
    public:
	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t, Sphere* ptrDevSpheres, int nbSpheres)
	    {
	    float minDistance = 999999;

	    float2 ij;
	    ij.x = i;
	    ij.y = j;

	    float3 hsb;
	    hsb.x = 0.0;
	    hsb.y = 1.0;
	    hsb.z = 0.0;

	    int minIndex = -1;
	    for (int i = 0; i < nbSpheres; i++)
		{
		float hcarre = ptrDevSpheres[i].hCarre(ij);
		float dz = ptrDevSpheres[i].dz(hcarre);
		if (ptrDevSpheres[i].distance(dz) < minDistance && ptrDevSpheres[i].isEnDessous(hcarre))
		    {
		    minDistance = ptrDevSpheres[i].distance(dz);
		    minIndex = i;
		    }
		}

	    if (minIndex != -1)
		{
		float hcarre = ptrDevSpheres[minIndex].hCarre(ij);
		float dz = ptrDevSpheres[minIndex].dz(hcarre);
		hsb.x = f(t, ptrDevSpheres[minIndex].getHueStart());
		hsb.z = ptrDevSpheres[minIndex].brightness(dz);
		}

	    ColorTools::HSB_TO_RVB(hsb, ptrColor);

	    ptrColor->w = 255; // opaque
	    }

	__device__
	float f(float t, float hueStart)
	    {
	    float mathBlock = 3 * PI_FLOAT / 2;
	    float T = asinf(2 * hueStart - 1) - mathBlock;
	    return (1.0 / 2.0) + (1.0 / 2.0) * sinf(t + mathBlock + T);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    private:
	// Inputs
	//int n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
