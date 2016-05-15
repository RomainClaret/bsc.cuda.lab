#include "Fractal.h"

#include "MathTools.h"
#include "Grid.h"

#include "DomaineMath_GPU.h"

#include "JuliaMath.h"
#include "JuliaProvider.h"
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
Animable_I<uchar4>* JuliaProvider::createAnimable()
    {
    const DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

    // Animation
    float dt =  2 * PI / 8000;

    // Dimension
    int dw = 16 * 60 * 2;
    int dh = 16 * 60;

    // Grid Cuda
    dim3 dg = dim3(24, 1, 1);  		// bruteforce values CUDA2 GPU4
    dim3 db = dim3(128, 1, 1);   	// bruteforce values CUDA2 GPU4
    Grid grid(dg,db);

    int nMin = 30;
    int nMax = 100;

    bool isJulia = true;

    return new Fractal(grid, dw, dh,nMin, nMax, dt, domaineMath, isJulia);
    }

/**
 * Override
 */
Image_I* JuliaProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
