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
    const double DX = 1 / (double) n;
    double xi;
    double sum = 0;
    // Une seule ligne modifie l'exécution parallèle ou séquentielle du code
#pragma omp parallel for reduction(+:sum) private(xi) // share(sum) --> default
    for (int i = 1; i <= n; i++)
	{
	xi = i * DX;
	sum += fpi(xi);
	}
    return sum / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

