#include "RayTracing.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
#include "AleaTools.h"

using namespace gpu;



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/
RayTracing::RayTracing(uint w, uint h)
    {
    this->w = w;
    this->h = h;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/
void RayTracing::populateSpheres(int nbSpheres, Sphere *ptrSpheres)
    {
    // Populate spheres
    AleaTools aleaTools = AleaTools();
    float bord = 200.0f;

    float rayon;
    float3 centre;
    float hue;
    for (int i = 0; i < nbSpheres; i++)
	{
	rayon = aleaTools.uniformeAB(20, w/10);

	centre.x = aleaTools.uniformeAB(bord, h-bord);
	centre.y = aleaTools.uniformeAB(bord, w-bord);
	centre.z = aleaTools.uniformeAB(10, 2*w);

	hue = aleaTools.uniforme01();

	ptrSpheres[i] = Sphere(centre, rayon, hue);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

