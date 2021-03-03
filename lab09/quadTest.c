/**************************************************************************
  quadTest.c - for the student
  This program demonstrates C99's complex support.
 
 12/22/2018 - R. Repka  Initial version
 03/27/2019 - R. Repka  b**2 typo
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include </usr/include/complex.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"
#define REPEATS (10)

/************************************************************************
   Simple code to test complex support  
************************************************************************/
int main(int argc, char* argv[]){ 

   DECLARE_TIMER(quadTimer)
   DECLARE_REPEAT_VAR(quadVar)

   /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
   double a = NAN;
   double b = NAN;
   double c = NAN;
   polynomial p;  
   int nterms = 3;
   double complex rootArray[2];
   double complex* rootList = rootArray;
   int aBool = 0;
   int bBool = 0;
   int cBool = 0;
   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;
  
   /* This contains the short command line parameters list */
   char *getoptOptions = "v";    /* add lots of stuff here */
  
   /* This contains the long command line parameter list, it should mostly 
     match the short list                                                  */
   struct option long_options[] = {
      {"a",	 required_argument, 0, 'a'},
      {"b",	 required_argument, 0, 'b'},
      {"c",	 required_argument, 0, 'c'},
      {0, 0, 0, 0}
   };
  
   opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, 
                                                    &option_index)) != -1) {
      /* Detect the end of the options. */
      switch (rc)
        {
	case 'a':
	   a = atof(optarg);
	   aBool = 1;
	   break;
	case 'b':
	   b = atof(optarg);
	   bBool = 1;
	   break;
	case 'c':
	   c = atof(optarg);
	   cBool = 1;
	   break;
        case '?':  /* Handled by the default error handler */
          break;

       default:
          printf ("Internal error: undefined option %0xX\n", rc);
          exit(PGM_INTERNAL_ERROR);
       } // End switch 
   } /* end while */
   /*------------------------------------------------------------------------
     Check for command line syntax errors
   ------------------------------------------------------------------------*/
   if (aBool == 0 || bBool == 0 || cBool == 0 || a == 0){
	if(aBool == 0 || a == 0){
		fprintf(stderr, "*********************************\n");
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please select a non-zero value for A\n");
		fprintf(stderr, "*********************************\n");
	}
	else if(bBool == 0){
		fprintf(stderr, "*********************************\n");
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please select a value for B\n");
		fprintf(stderr, "*********************************\n");
	}
	else if(cBool == 0){
		fprintf(stderr, "*********************************\n");
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please select a value for C\n");
		fprintf(stderr, "*********************************\n");
	}
	else{
		fprintf(stderr, "Tests quadratic solver\n");
	      	fprintf(stderr, "usage: quadTest -[num]a ANUM -[num]b BNUM -[num]c CNUM\n");
		fprintf(stderr, "B and C can be set to zero, A cannot.\n");
	      	fprintf(stderr, " e.g:   hw7 -a 1 -b 1 -c 1\n"); 
	      	fflush(stderr);
	      	return(PGM_INTERNAL_ERROR);
	}
   } /* End if error */
   START_TIMER(quadTimer)
   initPoly(&p, nterms);
   BEGIN_REPEAT_TIMING(REPEATS, quadVar)
   /*insert function calls here*/
   p.polyCoef[0] = a;
   p.polyCoef[1] = b;
   p.polyCoef[2] = c;
   quadraticRoots(&p, rootList);
   printf("The roots of:%fx**2 + %fx + %f\n", a, b, c);
   printf("  Root0: %f + %fi\n", creal(rootList[0]), cimag(rootList[0]));
   printf("  Root1: %f + %fi\n", creal(rootList[1]), cimag(rootList[1]));
   /***************************/
    END_REPEAT_TIMING
    freePoly(&p);
    STOP_TIMER(quadTimer)
    PRINT_RTIMER(quadTimer, REPEATS)
    printf("\n");
    RESET_TIMER(quadTimer)
    return PGM_SUCCESS;
} /* End main */


 /*---------------------------------------------------------------------------
  Returns the two roots from a quadratic polynomial
  
    =  -b +-sqrt(b**2-4ac)
       ----------------------
                 2a
  
  Where: polynomial *p              - Pointer to a 2nd order polynomial
  Returns: double complex* rootList - A pointer to a complex root pair.
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void quadraticRoots(polynomial *p, double complex *rootList){
	double a = p->polyCoef[0];
	double b = p->polyCoef[1];
	double c = p->polyCoef[2];
	rootList[0] = (-b + csqrt((b*b)-(4*a*c))/(2*a));
	rootList[1] = (-b - csqrt((b*b)-(4*a*c))/(2*a));
}


/*---------------------------------------------------------------------------
  This function allocates an array of "nterm" double complex elements and then
  initializes the terms of the polynomial to NAN (not a number).
  We initialize the terms of the polynomial to NAN to prevent the users from
  accidentally using the polynomial before valid values are set.
  
  Where: polynomial *p       - Pointer to polynomial data structure to create
         unsigned int nterms - The number of elements to create
  Returns: nothing
  Errors:  prints an error and exits
---------------------------------------------------------------------------*/
void initPoly(polynomial *p, unsigned int nterms){
	p->nterms = nterms;
	p->polyCoef = malloc(3*sizeof(double complex));
	for(int i = 0; i < nterms; i++){
		p->polyCoef[i] = NAN;
	}
}


/*---------------------------------------------------------------------------
  Destroys/frees a polynomial
  
  Where: polynomial *p - Pointer to polynomial data structure to destroy
  Returns: nothing
  Errors:  none
---------------------------------------------------------------------------*/
void freePoly(polynomial *p){
	free(p->polyCoef);
	p->polyCoef = NULL;
}
