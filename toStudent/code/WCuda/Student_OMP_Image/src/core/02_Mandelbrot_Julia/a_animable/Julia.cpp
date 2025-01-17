/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "Julia.h"
#include <omp.h>
#include "OmpTools.h"
#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Julia::Julia(float x, float y, int n): Fractale(n)
      {
      this->c1 = x;
      this->c2 = y;
      }

Julia::~Julia()
    {

    }

int Julia::mandelbrotJulia(float x, float y)
    {
    float a = x;
    float b = y;
    int k = 0;

    while((Fractale::indiceArret(a,b)) && k <= this->n)
    	 {
	float aCopy = a;
    	 a = (a*a - b*b) + c1;
    	 b = 2 * aCopy * b + c2;
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

