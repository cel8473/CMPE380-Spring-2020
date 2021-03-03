/**************************************************************************
  Student frame work.   Add and remove as you see fit.
  
  07/14/2017    R. Repka    Initial release
 * ***********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"
#define NMAX (1000)
#define REPEATS (1)
/************************************************************************
  Tests three types of root finding, secant, newton, and bisection,
  based on user input and prints out the timing results.
************************************************************************/
int main(int argc, char* argv[])
{
   DECLARE_TIMER(hw7Timer)
   DECLARE_REPEAT_VAR(hw7Var)

   /*------------------------------------------------------------------------
      UI variables with sentential values
   ------------------------------------------------------------------------*/
   int verbose = 0;
   enum modes {UNDEF, BISECT, SECANT, NEWTON} mode = UNDEF;
   double tol = 0.0;
   double guess1 = INFINITY;   
   double guess2 = INFINITY;

   /*------------------------------------------------------------------------
     These variables are used to control the getopt_long_only command line 
     parsing utility.  
   ------------------------------------------------------------------------*/
   int rc;
   /* getopt_long stores the option index here. */
   int option_index = 0;
  
   /* This contains the short command line parameters list */
   char *getoptOptions = "vbsnt:g:u:";    /* add lots of stuff here */
  
   /* This contains the long command line parameter list, it should mostly 
     match the short list                                                  */
   struct option long_options[] = {
      /* These options don’t set a flag.
         We distinguish them by their indices. */
      {"verbose",   no_argument,       0, 'v'},
      {"verb",      no_argument,       0, 'v'},
    /* add lots of stuff here */
      {"bisection", 	no_argument, 0, 'b'},
      {"b",	 	no_argument, 0, 'b'},
      {"secant", 	no_argument, 0, 's'},
      {"s", 		no_argument, 0, 's'},
      {"newton", 	no_argument, 0, 'n'},
      {"n", 		no_argument, 0, 'n'},
      {"tolerance", 	required_argument, 0, 't'},
      {"tol", 		required_argument, 0, 't'},
      {"t", 		required_argument, 0, 't'},
      {"guessa", 	required_argument, 0, 'g'},
      {"ga",	 	required_argument, 0, 'g'},
      {"g",	 	required_argument, 0, 'g'},
      {"bracket_a", 	required_argument, 0, 'g'},
      {"ba",	 	required_argument, 0, 'g'},
      {"guessb", 	required_argument, 0, 'u'},
      {"gb",	 	required_argument, 0, 'u'},
      {"bracket_b", 	required_argument, 0, 'u'},
      {"bb",	 	required_argument, 0, 'u'},
      {"u",	 	required_argument, 0, 'u'},
      {0, 0, 0, 0}
   };
  
   opterr = 1;           /* Enable automatic error reporting */
   while ((rc = getopt_long_only(argc, argv, getoptOptions, long_options, 
                                                    &option_index)) != -1) {
      
 //     printf("getopt_long_only() returned ='%c' index = '%d'\n",  rc, option_index);   
      /* Detect the end of the options. */
      switch (rc)
        {
        case 'v':                    /* Verbose */
          verbose = 1;
          break;

        /* add lots of stuff here */
	case 'b':
	   mode = BISECT;
	   break;
	case 's':
	   mode = SECANT;
	   break;
	case 'n':
	   mode = NEWTON;
	   break;
	case 't':
	   tol = atof(optarg);
	   break;
	case 'g':
	   guess1 = atof(optarg);
	   break;
	case 'u':
	   guess2 = atof(optarg);
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
   if ((optind < argc) || (tol == 0.0) || (guess1 = INFINITY) || (guess2 == INFINITY && mode != NEWTON)){
	if(mode == UNDEF){
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please select a mode: -b/-bisection or -s/-secant or -n/newton\n");
		return(PGM_SYNTAX_ERROR);
	}
	else if(tol == 0.0){
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please set a tolerance: -t/-tol/-tolerance followed by a double\n");
		return(PGM_SYNTAX_ERROR);
	}
	else if(guess1 == INFINITY){
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please set a guess1: -guessa/-ga/-g/-bracket_a/-ba followed by a double\n");
		return(PGM_SYNTAX_ERROR);
	}
	else if(guess2 == INFINITY && mode != NEWTON){
		fprintf(stderr, "Syntax Error\n");
		fprintf(stderr, "Please set a guess2: -guessb/-gb/-u/-bracket_b/-bb followed by a double\n");
		return(PGM_SYNTAX_ERROR);
	}
	else{
		fprintf(stderr, "Tests root finding methods\n");
	      	fprintf(stderr, "usage: hw7 -b[isection] | -s[ecant] | -n[ewton]   -t[ol[erance} number\n");
	      	fprintf(stderr, "          -g[uess1] number   <-g[u]ess2 number   <-verb[ose]> \n");
	      	fprintf(stderr, " e.g:   hw7 -bisection -tol 1E-6 -g1 -2 -g2 3 -verb\n"); 
	      	fflush(stderr);
	      	return(PGM_INTERNAL_ERROR);
	}
   } /* End if error */

   START_TIMER(hw7Timer)
   BEGIN_REPEAT_TIMING(REPEATS, hw7Var)
   /* Performs the root finding with bisection */
   if(mode == BISECT)
   {
	if(verbose==1) printf("Root finding with the Bisection method\n");
	bisection(&func1, guess1, guess2, tol, verbose);
   }  // End if bisection
   
   /* Performs the root finding using the secant method */
   else if(mode == SECANT)
   {
	if(verbose==1) printf("Root finding with the Secant method\n");
 	secant(&func1, guess1, guess2, NMAX, tol, verbose);
   } // End secant
   
   /* Performs the root finding using newtons method */
   else /* must be newton */
   {
	if(verbose==1) printf("Root finding with the Newton method\n");
	newton(&func1, &func1Deriv, guess1, NMAX, tol, verbose);
   } // End newton
    END_REPEAT_TIMING
    STOP_TIMER(hw7Timer)
    PRINT_RTIMER(hw7Timer, REPEATS)
    RESET_TIMER(hw7Timer)
    return PGM_SUCCESS;
}
