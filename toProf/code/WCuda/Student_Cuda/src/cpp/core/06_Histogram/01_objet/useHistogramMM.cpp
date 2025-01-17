#include <iostream>

/*----------------------------------------------------------------------*\
|*			Declaration                     *|
\*---------------------------------------------------------------------*/
extern bool histogramMM(int);

/*--------------------------------------*\
|*		Imported	    *|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/



/*----------------------------------------------------------------------*\
|*			Implementation                  *|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Public			*|
\*-------------------------------------*/
bool useHistogramMM() {
  std::cout << "histogram Map Memory" << std::endl << std::endl;

  return histogramMM(256e2);
}

/*--------------------------------------*\
|*		Private			*|
\*-------------------------------------*/

/*----------------------------------------------------------------------*\
|*			End	                    *|
\*---------------------------------------------------------------------*/

