
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "Mandelbrot.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

 Mandelbrot::Mandelbrot(int n): Fractale(n)
     {
     }

 Mandelbrot::~Mandelbrot()
     {
     }

 int Mandelbrot::mandelbrotJulia(float x=0, float y=0)
     {
     float a = x;
     float b = y;
     int k = 0;

     while ((Fractale::indiceArret(a,b)) && k <= this->n)
	 {
	 float aCopy = a;
	 a = (a*a - b*b)+x;
	 b = 2 * aCopy * b + y;
	 k++;
	 }

     return k;
     }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
