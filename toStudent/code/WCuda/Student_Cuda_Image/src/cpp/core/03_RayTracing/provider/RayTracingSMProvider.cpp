#include "MathTools.h"
#include "Grid.h"
#include "RayTracingSMProvider.h"
#include "RayTracingSM.h"

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

/**
 * Override
 */
Animable_I<uchar4>* RayTracingSMProvider::createAnimable()
    {
    // Spheres amount
    int spheres = 50;

    // Animation;
    float dt =  0.1;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    // Grid Cuda
    dim3 dg = dim3(48, 1, 1);		// to optimize
    dim3 db = dim3(192, 1, 1);		// to optimize
    Grid grid(dg,db);

    return new RayTracingSM(grid, dw, dh, dt, spheres);
    }

/**
 * Override
 */
Image_I* RayTracingSMProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 1, 1); // white
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
