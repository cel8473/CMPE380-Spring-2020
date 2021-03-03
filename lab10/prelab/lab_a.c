/*---------------------------------------------------------------------------
  QN code testing and verification
  student copy
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

#define LOOP_DELAY (1<<27)
#define DBL_EPILSON (2.22045e-16)
// QN math functions which pass the number of bits "n" 
#define Qn_MULTIPLY(A,B,n) ((A>>(n/2))*(B >>(n-(n/2))))
#define Qn_DIVIDE(A,B,n) ((int) (((long int)(A)<<n)/(B) ))

// QN math and printing functions
void  printBinary(unsigned num, short N);
int  floatToFixed(double x, int n);
float fixedToFloat(int x, int n); 

/*---------------------------------------------------------------------------
  QN testing framework 
---------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
   // QN testing variables, add more as necessary
   double fnum1, fnum2;
   int  qnum1, qnval;
   short N = 16;
   
   //------------------------------------------------------------------------
   // Print data on sizes  
   //------------------------------------------------------------------------
   printf("Integers are %ld bits long\n", 8*sizeof(int));

   //------------------------------------------------------------------------
   // Prove floating point has limits 
   //------------------------------------------------------------------------
   double d = 10.0;
   printf("Adding epilson: %f + %f = %f\n", d, DBL_EPILSON, d+DBL_EPILSON);
   if(d == d+DBL_EPILSON) printf("Addition has failed %f = %f\n", d, d+DBL_EPILSON);
   
   //------------------------------------------------------------------------
   // Examine the conversion utilities
   //------------------------------------------------------------------------
   printf("\nConversion test\n");
   fnum1 = 0.0;
   qnval = 0;
   qnum1 = floatToFixed(fnum1, qnval);
   fnum2 = fixedToFloat(qnum1, qnval);
   printf("Started with %f converted to qn%d = %d decimal then back to %f\n", fnum1, qnval, qnum1, fnum2);
   printBinary(qnum1, N);

   fnum1 = 12.25;
   qnval = 3;
   qnum1 = floatToFixed(fnum1, qnval);
   fnum2 = fixedToFloat(qnum1, qnval);
   printf(" Start with %f converted to qn%d = %d decimal then back to %f\n", fnum1, qnval, qnum1, fnum2);
   printBinary(qnum1, N);

   fnum1 = 12.0625;
   qnval = 3;
   qnum1 = floatToFixed(fnum1, qnval);
   fnum2 = fixedToFloat(qnum1, qnval);
   printf(" Start with %f converted to qn%d = %d decimal then back to %f\n", fnum1, qnval, qnum1, fnum2);
   printBinary(qnum1, N);

   fnum1 = 12.0625;
   qnval = 4;
   qnum1 = floatToFixed(fnum1, qnval);
   fnum2 = fixedToFloat(qnum1, qnval);
   printf(" Start with %f converted to qn%d = %d decimal then back to %f\n", fnum1, qnval, qnum1, fnum2);
   printBinary(qnum1, N);

   return(0);
}


/*---------------------------------------------------------------------------
  This prints a number in character binary bracketed by [..]
  
  Where: unsigned num - number to print
         short N      - number of bits to print
         
  Returns: nothing
  Error handling: none
----------------------------------------------------------------------------*/
void printBinary(unsigned num, short N) { 
   unsigned i; 
   printf("\t[");
   
   for (i = 1 << (N-1); i > 0; i = i >> 1) {
      (num & i)? printf("1"): printf("0");
    }        
   printf("]\n");
   return;
} 


/*---------------------------------------------------------------------------
  This convert from Float to FP(Qn) 
  
  Where: double x  - number to convert
         int qnval - number of bits to use
         
  Returns: int    - QN encoded number
  Error handling: none
----------------------------------------------------------------------------*/
int floatToFixed(double x, int qnval) { 
   return( x * (double)(1 << qnval) );            
} 

/*---------------------------------------------------------------------------
  This converts from FP(Qn) to Float
  
  Where: int x     - number to convert
         int qnval - number of bits to use
         
  Returns: float   - converted number
  Error handling: none
----------------------------------------------------------------------------*/
float fixedToFloat(int x, int qnval) { 
   return((double)x / (double) (1 << qnval));
}

