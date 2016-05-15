
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "JuliaProvider.h"
#include "Julia.h"
#include "MathTools.h"
#include "ImageAnimable_CPU.h"

using namespace cpu;

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
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
//Animable_I<uchar4>* JuliaProvider::createAnimable(void)
//    {
//    // Animation
//    float dt = 1;
//
//    // Dimension
//    float dw = 16 * 60;
//    float dh = 16 * 60;
//
//    return new Julia(dw, dh, dt);
//    }

/**
 * Override
 */
Image_I* JuliaProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // green
    return new ImageAnimable_RGBA_uchar4(createAnimable(),colorTexte);
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
