#ifndef SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_FRACTALE_H_
#define SRC_CORE_02_MANDELBROT_JULIA_A_ANIMABLE_FRACTALE_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractale
    {
    public:
	Fractale(int n);
	virtual ~Fractale();
	virtual int mandelbrotJulia(float x, float y)=0;

    protected:
	int n;
	bool indiceArret(float x, float y);
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
