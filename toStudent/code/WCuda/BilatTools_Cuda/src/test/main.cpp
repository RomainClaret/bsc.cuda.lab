#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/



/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

extern bool mainCPP();
extern bool mainCU();

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(void)
    {
    cout << "[BilatTools_Cuda] : just inlcude to force compilation" << endl;

    bool isOk=true;

    isOk&=mainCPP();
    isOk&=mainCU();

    return isOk?EXIT_SUCCESS:EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
