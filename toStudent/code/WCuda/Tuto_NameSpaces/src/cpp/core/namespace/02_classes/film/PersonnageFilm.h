#pragma once

#include <string>

using std::string;

// les noms des namespace peuvent �tre assigner grace a un define, mais pas forc�ment
#define NS_FILM film

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace NS_FILM
    {
    class Personnage
	{

	    /*-------------------------------------*\
	     |*		Constructor		    *|
	     \*-------------------------------------*/

	public:

	    Personnage(string name);

	    virtual ~Personnage();

	    /*-------------------------------------*\
	     |*		Methode			    *|
	     \*-------------------------------------*/

	public:

	    string getName() const;

	    /*-------------------------------------*\
	     |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	    //Input
	    string name;
	};
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
