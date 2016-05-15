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

bool isPiOMPforCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforCritique(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforCritique, n, "Pi OMP for critique");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforCritique(int n)
    {
    const double dx = 1 / (double) n;
    double x_i;
    double sum = 0;

#pragma omp parallel for private(x_i)
    for (int i=1; i<n; i++ )
    	{
    	x_i = i * dx;

// Catastrophic
#pragma omp critical (whatever)
    	{
    	sum += fpi(x_i);
    	}

    	}

    return sum / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

