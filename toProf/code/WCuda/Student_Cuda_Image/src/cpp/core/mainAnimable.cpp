#include <iostream>
#include <stdlib.h>

#include "RipplingProvider.h"
#include "JuliaProvider.h"
#include "MandelbrotProvider.h"
#include "RayTracingGMProvider.h"

#include "Animateur_GPU.h"
#include "Settings_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainAnimable(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rippling();
static void julia();
static void mandelbrot();
static void raytracingGM();

// Tools
template<typename T>
static void animer(Provider_I<T>* ptrProvider, int nbIteration);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainAnimable(Settings& settings)
    {
    cout << "\n[Animable] mode" << endl;

    // Attention : pas tous a la fois

    rippling();
    //julia();
    //mandelbrot();
    //raytracingGM();

    cout << "\n[Animable] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling()
    {
    const int NB_ITERATION = 50000;

    RipplingProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

void julia()
    {
    const int NB_ITERATION = 50000;

    JuliaProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

void mandelbrot()
    {
    const int NB_ITERATION = 50000;

    MandelbrotProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

void raytracingGM()
    {
    const int NB_ITERATION = 50000;

    RayTracingGMProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

template<typename T>
void animer(Provider_I<T>* ptrProvider, int nbIteration)
    {
    Animateur<T> animateur(ptrProvider, nbIteration);
    animateur.run();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

