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

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab,  n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    const double dx = 1/ (double) n;
    double sum = 0;
    double* ptr_thread = new double[NB_THREAD];

#pragma omp parallel
    {
    const int TID = OmpTools::getTid();
    int s = TID;
    double x_s;
    double sum_s = 0;

    while (s < n)
	{
	x_s = s * dx;
	sum_s += fpi(x_s);
	s += NB_THREAD;
	}
    ptr_thread[TID] = sum_s;
    }

    // Reduction of the table
    for (int i=0; i<NB_THREAD; i++)
	{
	sum += ptr_thread[i];
	}

    delete[] ptr_thread;
    return sum / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

