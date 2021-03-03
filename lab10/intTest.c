/**************************************************************************
  intTest.c - for students
  This program demonstrates the speed advantages of integer versus floating
  point math.
 12/28/2015 - R. Repka  Initial version
 10/12/2016 - R. Repka  Switched to PRINT_RTIMER() macro
 03/25/2018 - R. Repka  Switched to timing macros 
 11/18/2019 - R. Repka  Polynomial comment error 
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"

/****************************************************************************
  Use this to define the number of iterations in your performance measurements
  ----------- You will need to adjust this number  --------
****************************************************************************/
#define ITERATIONS   (500000)
#define BI_LIMIT (1000)
/* Optional verbose flag, compile with -DVERBOSE or not */
#ifdef VERBOSE
   #undef VERBOSE 
   #define VERBOSE (1)
#else
   #undef VERBOSE 
   #define VERBOSE (0)
#endif

/****************************************************************************
  Remember to set the QN value in rootfinding.h
****************************************************************************/

/************************************************************************
   Simple code to test Qn performance vs floating point  
************************************************************************/
int main(int argc, char* argv[])
    {
    double Result;          /* The result from floating point calculation   */
    long  iResult;          /* The result from floating point calculation   */
    
    /* The bisection guesses and tolerance value                        */
    double a = -25.0;
    double b = 25.0;
    double tol= 0.000001;

    /* You many need to modify the timing code for your macro implementation! */
    DECLARE_TIMER(timer);
    DECLARE_REPEAT_VAR(tloop)

    /************************************************************************
     Run the Qn format test 
    ************************************************************************/
    /* You many need to modify the timing code for your macro implementation! */
    long qnumA = FLOAT_TO_FIX(a);
    long qnumB = FLOAT_TO_FIX(b);
    long qTol = FLOAT_TO_FIX(tol);
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
         iResult = ibisection(&iPoly, qnumA, qnumB, qTol, VERBOSE);
    END_REPEAT_TIMING
    STOP_TIMER(timer);

    if(iNAN == iResult)
        {
        fprintf(stderr, "Qn %d bisection couldn't find a root. \n", QN);
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using Qn %d bisection.\n",
                        FIX_TO_FLOAT(iResult ), QN);
        }      
    PRINT_RTIMER(timer, ITERATIONS);

    /************************************************************************
     Run the floating point format test 
    ************************************************************************/
    RESET_TIMER(timer);
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
        Result = bisection(&rPoly, a, b, tol, VERBOSE);
    END_REPEAT_TIMING
    STOP_TIMER(timer);

    if(NAN == Result)
        {
        fprintf(stderr, "Float bisection couldn't find a root. \n");
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using float bisection.\n",
                        Result);
        }
    PRINT_RTIMER(timer, ITERATIONS);
    
    /* Display the percentage error */
    float iFloat = FIX_TO_FLOAT(iResult);
    Result = (abs(Result - iFloat)/ Result) * 100;
    fprintf(stderr, "Qn %d error= %f\n", QN, Result);
    return 0;
    } /* End main */   
    
/******************************************************************************
 Purpose: Finds a root of scalar, non-linear function f using the integer 
 bisection  method. a and b make up the initial bracket to start bisecting from.
 Only implement this after you have the floating point function implemented
 
 Where: ifunc1arg f - INTEGER function whose root is to be determined
                      must take a single argument of type long and return
        long a      - initial Qn root bracket guess
        long b      - initial Qn root bracket guess
        long atol   - absolute Qn error termination tolerance,
        int verb    - verbose flag, 1 = TRUE, 0 = FALSE
        
Returns: long - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN                 
******************************************************************************/
long ibisection(ifunc1arg f, long a, long b, long atol, int verb)
{
    long c; /* midpoint */
    long fc; /* the value at the midpoint */
    int i=0; /* iterator */
    long two = FLOAT_TO_FIX(2.0);

    if ((abs(a-b) < atol) ||  SIGN(f(a))==SIGN(f(b))){
        fprintf(stderr, "A and B do not center a root\n");
        return(iNAN);
    }

    /* Limit the number of attempts */
    while(i < BI_LIMIT)
    {
        /* Calculate the mid point, evaluate it */
        c = Qn_DIVIDE((a+b),two);
        fc = f(c);
        
        /* Did we find a root? - check the function */
         // not working if ((fabs(fc) <= atol) || ((fabs(a-b)/2.0) <= atol)) 
        if (abs(fc) <= atol)
        {
            return c;
        }
        
        /* Did we find a root? - check the range */
        if (abs(Qn_DIVIDE((a-b),two)) <= atol) 
        {
           return c;
        }
        
        if(verb)
        {
            fprintf(stderr, "iter:%d	a:%f	b:%f	x:%f	err:%f\n",
                    i, FIX_TO_FLOAT(a), FIX_TO_FLOAT(b), FIX_TO_FLOAT(c), FIX_TO_FLOAT(abs(b-c)));
        }
        
        /* Pick the next bracket */
        if (SIGN(f(a))==SIGN(fc))
        {
            a = c;
        }
        else
        {
            b = c;
        }
        i++;
    }
    fprintf(stderr, "Bisection could not find a root with %d iterations\n", BI_LIMIT);
    return(iNAN);
}    
    
/******************************************************************************
 Purpose: Finds a root of scalar, nonlinear function f using the bisection  
 method. a and b make up the initial bracket to start bisecting from.
 
 Where: func1arg f  - function whose root is to be determined
                      must take a single argument of type double and return
        double a    - initial root bracket guess
        double b    - initial root bracket guess
        double atol - absolute error termination tolerance,
        int verb    - verbose flag, 1 = TRUE, 0 = FALSE
        
Returns: double - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN                    
******************************************************************************/
double bisection(func1arg f, double a, double b, double atol, int verb)
{
    double c; /* midpoint */
    double fc; /* the value at the midpoint */
    int i=0; /* iterator */
    
    if ((fabs(a-b) < atol) ||  SIGN(f(a))==SIGN(f(b))){
        fprintf(stderr, "A and B do not center a root\n");
        return(NAN);
    }

    /* Limit the number of attempts */
    while(i < BI_LIMIT)
    {
        /* Calculate the mid point, evaluate it */
        c = (a+b)/2.0;
        fc = f(c);
        
        /* Did we find a root? - check the function */
         // not working if ((fabs(fc) <= atol) || ((fabs(a-b)/2.0) <= atol)) 
        if (fabs(fc) <= atol)
        {
            return c;
        }
        
        /* Did we find a root? - check the range */
        if (fabs(a-b)/2.0 <= atol) 
        {
           return c;
        }
        
        if(verb)
        {
            fprintf(stderr, "iter:%d	a:%f	b:%f	x:%f	err:%f\n",
                    i, a, b, c, fabs(b-c));
        }
        
        /* Pick the next bracket */
        if (SIGN(f(a))==SIGN(fc))
        {
            a = c;
        }
        else
        {
            b = c;
        }
        i++;
    }
    fprintf(stderr, "Bisection could not find a root with %d iterations\n", BI_LIMIT);
    return(NAN);
}

/*---------------------------------------------------------------------------
  This function implements the real polynomial equation to be solved.  
  
  Where:   double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double rPoly(double x){
    //x**3-.0001x**2-676X+.0676    
    return(x*(x*(x-.0001)-676.0)+.0676);
}


/*---------------------------------------------------------------------------
  This function implements the integer polynomial equation to be solved.  
  
  Where:    long x - the value to evaluate
  Returns: long - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
long iPoly(long x){
    //x**3-.0001x**2-676X+.0676    
    return(MUL_FIX(x, MUL_FIX(x, x-FLOAT_TO_FIX(0.0001)) - FLOAT_TO_FIX(676.0)) + FLOAT_TO_FIX(0.0676));
}
