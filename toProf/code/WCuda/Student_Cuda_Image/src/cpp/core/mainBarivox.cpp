#include <iostream>
#include <stdlib.h>

#include "Barivox.h"

#include "RipplingProvider.h"
#include "JuliaProvider.h"
#include "MandelbrotProvider.h"
#include "RayTracingGMProvider.h"

#include "Settings_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |* Declaration *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBarivox(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rippling();
static void julia();
static void mandelbrot();
static void raytracingGM();

// Tools
template<typename T>
static void barivox(Provider_I<T>* ptrProvider, string titre);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBarivox(Settings& settings)
    {
    cout << "\n[Barivox] mode" << endl;

    // Attention : Un a la fois seulement!

    //rippling();
    //julia();
    //mandelbrot();
    raytracingGM();

    cout << "\n[Barivox] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling()
    {
    RipplingProvider provider;
    barivox<uchar4>(&provider, "Rippling_RGBA_uchar4");
    }

void julia()
    {
    JuliaProvider provider;
    barivox<uchar4>(&provider, "Julia_RGBA_uchar4");
    }

void mandelbrot()
    {
    MandelbrotProvider provider;
    barivox<uchar4>(&provider, "Mandelbrot_RGBA_uchar4");
    }

void raytracingGM()
    {
    RayTracingGMProvider provider;
    barivox<uchar4>(&provider, "RayTracingGM_RGBA_uchar4");
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

/**
 * Grid 1d Only
 */
template<typename T>
void barivox(Provider_I<T>* ptrProvider, string titre)
    {
    cout << "\n[Barivox] : " << titre << endl;

    // Define Grid
    int mp = Device::getMPCount();
    int coreMp = Device::getCoreCountMP();
    int nbThreadBlockMax = Device::getMaxThreadPerBlock();
    int warpSize = Device::getWarpSize();

    dim3 dgStart(mp*2, 1, 1);
    VariateurData variateurDg(mp, 8 * mp, mp); 				// (min,max,step)  Attention : A definir intelligement selon le GPU !
    VariateurData variateurDb(coreMp, nbThreadBlockMax, warpSize); 	// (min,max,step)  Attention : A definir intelligement selon le GPU !

    // Run
    const bool IS_ANIMATOR_VERBOSITY_ENABLE = false;
    const bool IS_BARIVOX_VERBOSITY_ENABLE = true;
    const int NB_ITERATION = 1000;

    Barivox<T> barivox(ptrProvider, dgStart, variateurDg, variateurDb, NB_ITERATION, IS_BARIVOX_VERBOSITY_ENABLE, IS_ANIMATOR_VERBOSITY_ENABLE);
    const BarivoxOutput output = barivox.run();

    // Result
    	{
    	cout << output<<endl;
    	}

    // Save
	{
	output.save("out/barivox/barivox_" + titre);
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
