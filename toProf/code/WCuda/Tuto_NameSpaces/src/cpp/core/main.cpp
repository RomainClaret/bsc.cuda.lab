#include <stdlib.h>
#

// http://www.tutorialspoint.com/cplusplus/cpp_namespaces.htm
// http://www.c4learn.com/cplusplus/cpp-namespace-creation/
// http://fr.openclassrooms.com/informatique/cours/les-espaces-de-noms-namespace

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void useNameSpaceProcedure();
extern void useNameSpaceObject();

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(void);

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
    useNameSpaceProcedure();
    useNameSpaceObject();

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

