#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"

#include "FractalMath.h"
#include "JuliaMath.h"
#include "MandelbrotMath.h"
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

__device__ void fractal(uchar4* ptrDevPixels, uint width, uint height, DomaineMath domaineMath, uint n, FractalMath* fractalMath);

__global__ void julia(uchar4* ptrDevPixels, uint width, uint height, DomaineMath domaineMath, uint n);
__global__ void mandelbrot(uchar4* ptrDevPixels, uint width, uint height, DomaineMath domaineMath, uint n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__ void fractal(uchar4* ptrDevPixels, int w, int h, DomaineMath mathDomain, int n, FractalMath* fractalMath)
    {
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    uchar4 color;

    // math
    double x;
    double y;
    // screen
    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	mathDomain.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)

	fractalMath->colorXY(&color, x, y, n); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    }

__global__ void julia(uchar4* ptrDevPixels, int width, int height, DomaineMath domaineMath, int n)
    {
    float c1 = -0.12;
    float c2 = 0.85;
    FractalMath* fractalMath = new JuliaMath(c1, c2);

    fractal(ptrDevPixels, width, height, domaineMath, n, fractalMath);

    delete fractalMath;
    }

__global__ void mandelbrot(uchar4* ptrDevPixels, int width, int height, DomaineMath domaineMath, int n)
    {
    FractalMath* fractalMath = new MandelbrotMath();

    fractal(ptrDevPixels, width, height, domaineMath, n, fractalMath);

    delete fractalMath;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

