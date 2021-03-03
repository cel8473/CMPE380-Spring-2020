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

#define A p.polyCoef[0]
#define B p.polyCoef[1]
#define C p.polyCoef[2]
#define A_P p->polyCoef[0]
#define B_P p->polyCoef[1]
#define C_P p->polyCoef[2]


/************************************************************************
   Simple code to test complex support  
************************************************************************/
int main(int argc, char* argv[]){ 
	/****************************************************************
	Timer Declaration and start
	****************************************************************/
	DECLARE_TIMER(root_timer)
	START_TIMER(root_timer)

	/****************************************************************
	   Variable Declaration
	****************************************************************/
	double a = NAN;
	double b = NAN;
	double c = NAN;
	int a_i = 0;
	int b_i = 0;
	int c_i = 0;
	polynomial p;
	initPoly(&p, 3);
	double complex rootList;

	/****************************************************************
	   getopt_long_only() declarations
	****************************************************************/
	int rc;
	int option_index = 0;
	char *getoptOptions = "a:b:c:";
	
	struct option long_options[] = {
	{"a",		required_argument, 0, 'a'},
	{"anum",	required_argument, 0, 'a'},
	{"b",		required_argument, 0, 'b'},
	{"bnum",	required_argument, 0, 'b'},
	{"c",		required_argument, 0, 'c'},
	{"cnum",	required_argument, 0, 'c'},
	{0, 0, 0, 0}
	};

	opterr = 1;

	while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, &option_index)) != -1) {
		printf("getopt_long_only() returned = '%c' index = '%d'\n", rc, option_index);
		switch(rc){
			case '0':
				if (long_options[option_index].flag != 0){
					break;
				}/*End if statement*/
				if (optarg){
					printf("with arg %s\n", optarg);
				}/*End if statement*/
				break;
			case 'a':
				if (atoi(optarg) == 0){
					fprintf(stderr, "Undefined Error: 'a' or 'anum' cannot be 0\n");
					exit(PGM_INTERNAL_ERROR);
				}/*End if statement*/
				a = atof(optarg);
				a_i = atoi(optarg);
				break;
			case 'b':
				b = atof(optarg);
				b_i = atoi(optarg);
				break;
			case 'c':
				c = atof(optarg);
				c_i = atoi(optarg);
			case '?':
				break;
			default:
				printf("Internal error: undefined option %0xX\n", rc);
				exit(PGM_INTERNAL_ERROR);
		}/*end switch statement*/
	}/*End while loop*/

	if ((optind < argc)){

		while (optind < argc){
			fprintf(stderr, "'%s'\n", argv[optind++]);
		}/*end syntax errorwhile loop*/
		fflush(stderr);
		return (PGM_INTERNAL_ERROR);
	}/*end syntax error if*/

	/*Quadratic root calculations and print statement*/

	A = (double complex) a;
	B = (double complex) b;
	C = (double complex) c;

	quadraticRoots(&p, &rootList);
	
	/*Print appropriate roots based ion imaginary constraints*/
	printf("\n\n%f\n\n", ((b*b)-(4*a*c)));

	if (((b_i*b_i)-(4*a_i*c_i)) < 0){
		printf("The roots of %fx**2 +%fx + %f:\n", creal(A), creal(B), creal(C));
		printf("Root1: %f + i%f\n", creal(rootList), cimag(rootList));
		printf("Root2: %f - i%f\n", creal(rootList), cimag(rootList));
	}/*Imaginary roots*/
	else{
		printf("The roots of %fx**2 +%fx + %f:\n", creal(A), creal(B), creal(C));
		printf("Root1: %f\n", (creal(rootList) - cimag(rootList)));
		printf("Root2: %f\n", (creal(rootList) + cimag(rootList)));
	}/*Real Roots*/
	
	/*Free allocated blocks*/
	freePoly(&p);
	
	/*Stop, Print, and reset timer*/
	STOP_TIMER(root_timer)
	PRINT_TIMER(root_timer)
	RESET_TIMER(root_timer)

	/*Reset a, b, and c to NAN value*/
	a = b = c = NAN;

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
	//temporary root declaration
	double real_temp;
	double imag_temp;

	//imaginary
	imag_temp = (csqrt(cabs((B_P * B_P) - (4 * A_P * C_P))))/(2 * A_P);

	//real
	real_temp = ((-1 * B_P))/(2 * A_P);
	
	//Assign to storage location
	*rootList = real_temp + imag_temp*_Complex_I;

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
	int i;
	p->polyCoef = (double complex*)malloc(sizeof(double complex)*nterms);
	if (p->polyCoef == NULL){
		fprintf(stderr, "Malloc Error: quadTest.c->initPoly");
		exit(MALLOC_ERROR);
	}/*End malloc error check*/

	//Loop to preset all array real and imaginary values to NAN
	for (i = 0; i < nterms; i++){
		p->polyCoef[i] = NAN;
	}/*End for loop*/
	p->nterms = nterms;
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

