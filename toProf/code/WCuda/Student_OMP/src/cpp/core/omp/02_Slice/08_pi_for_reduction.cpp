#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforReduction_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforReduction(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforReduction_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforReduction, n, "Pi OMP for reduction-integrer");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern omp usefull : idem desyncronisation-promotionTab ,mais avec syntaxe plus courte!
 * Si on enleve le pragma, le code est le meme que le sequentiel!
 */
double piOMPforReduction(int n)
    {
    const double dx = 1 / (double)n;
    double x_i;
    double sum = 0;

#pragma omp parallel for reduction(+:sum) private(x_i) //share(sum) -> default
    for (int i=0; i<n; i++ )
	{
	x_i = i * dx;
	sum += fpi(x_i);
    	}

    return sum / n;
    }




/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

