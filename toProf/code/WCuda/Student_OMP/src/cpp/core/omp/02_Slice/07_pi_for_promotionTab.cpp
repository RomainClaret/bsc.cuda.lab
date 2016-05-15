#include <omp.h>
#include "MathTools.h"
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

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread,int n);
static void syntaxeFull(double* tabSumThread,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    const double dx = 1 / (double) n;
    double x_i;
    double sum = 0;
    double* ptr_thread = new double[NB_THREAD];

    // Initialisation of the table
    for (int i=0; i<NB_THREAD; i++)
	{
    	ptr_thread[i] = 0;
    	}

#pragma omp parallel for private(x_i)
        for (int i=0; i<n; i++ )
            {
            int TID = OmpTools::getTid();;
            x_i = i * dx;
            ptr_thread[TID] += fpi(x_i);
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

