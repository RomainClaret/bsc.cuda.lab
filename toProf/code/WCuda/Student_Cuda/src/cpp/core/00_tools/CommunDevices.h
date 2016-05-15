#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class CommunDevices
    {
 /*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
    public:
	__device__ static float calcPi(float x)
	    {
	    return 4.0 / (1 + x * x);
	    }

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
