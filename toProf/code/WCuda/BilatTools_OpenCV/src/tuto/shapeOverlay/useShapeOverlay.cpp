#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void tuto_01_simple();
extern void tuto_02_allShape();
extern void tuto_03_transparance();
extern void tuto_04_bigline();

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useShapeOverlay();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useShapeOverlay()
    {
    tuto_01_simple();
    tuto_02_allShape();
    tuto_03_transparance();
    tuto_04_bigline();

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

