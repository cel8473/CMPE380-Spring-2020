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

// QN math functions which pass the number of bits "n" 
#define Qn_MULTIPLY(A,B,n) ((A>>(n/2))*(B >>(n-(n/2))))
#define Qn_DIVIDE(A,B,n) ((int) (((long int)(A)<<n)/(B) ))
#define DECIMAL_EQUATION(x) ((x*x*x) - 0.0001*(x*x) - 676*x + 0.0676)
#define FRACTION_EQUATION(x) ((x*x*x) - ((x*x)/10000) - 676*x + (169/2500))

// QN math and printing functions
void  printBinary(unsigned num, short N);
int  floatToFixed(double x, int n);
float fixedToFloat(int x, int n); 

/*---------------------------------------------------------------------------
  QN testing framework 
---------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
   // QN testing variables, add more as necessary
   double fnum1, fnum2, fnum3;
   int  qnum1, qnum2, qnum3, qnval;
   clock_t  time1, time2;
   unsigned i;


   //------------------------------------------------------------------------
   // Examine the division utilities
   //------------------------------------------------------------------------   
   fnum1 = -0.0625;
   qnval = 18;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum1, qnval);
   
   printf("\nDivision test\n");
   while(qnum1 != 0 || qnum2 != 0){
	qnum1 /= 2;
	qnum2 = Qn_DIVIDE(qnum2, 2, 0);
	fnum1 /= 2;
        fnum2 = fixedToFloat(qnum1, qnval);
        fnum3 = fixedToFloat(qnum2, qnval);
	printf("%f %d %d %f %f\n", fnum1, qnum1, qnum2, fnum2, fnum3);
   }
   printf("\nDivision Absolute Value Test\n");
   fnum1 = -0.0625;
   qnval = 18;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum1, qnval);

   while(qnum1 != 0 || qnum2 != 0){
	qnum1 /= 2;
	qnum2 = Qn_DIVIDE(qnum2, 2, 0);
	fnum1 /= 2;
        fnum2 = fixedToFloat(qnum1, qnval);
        fnum3 = fixedToFloat(qnum2, qnval);
	printf("%f %d %d %f %f\n", fabs(fnum1), abs(qnum1), abs(qnum2), fabs(fnum2), fabs(fnum3));
   }
   //------------------------------------------------------------------------
   // Examine the multiplication utilities
   //------------------------------------------------------------------------   
   fnum1 = 64.125;
   fnum2 = 0.755;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum2, qnval);
   qnum3 = Qn_MULTIPLY(qnum1, qnum2, 18);
   fnum3 = fnum1 * fnum2;
   fnum2 = fixedToFloat(qnum3, qnval);
   printf("\nMultiplication test\n");
   printf("Product = %f float, Qnx product = %d dec, converted back %f float\n", fnum3, qnum3, fnum2);

   //------------------------------------------------------------------------
   // Implement floating point scientific equations two different ways
   // using normal fractions and using decimal fractions
   //------------------------------------------------------------------------
   fnum1 = DECIMAL_EQUATION(1.0);
   fnum2 = FRACTION_EQUATION(1.0);
   qnum1 = floatToFixed(1.0, qnval);
   qnum2 = Qn_MULTIPLY(Qn_MULTIPLY(qnum1, qnum1, qnval), qnum1, qnval) - 0.0001*Qn_MULTIPLY(qnum1, qnum1, qnval) - 676 * qnum1 + 0.0676;
   fnum3 = fixedToFloat(qnum2, qnval);
   printf("\nComplex calculations test\n");
   //---------------------------------------------------------------------
   // Implement QN scientific equations: x**3-.0001x**2-676X+.0676
   //------------------------------------------------------------------------   
  
   // print all 3 answers
   printf("The resulting value of the decimal equation: %f\n", fnum1);
   printf("The resulting value of the fraction equation: %f\n", fnum2);
   printf("The resulting value of the Qn equation: %f\n", fnum3);
   //------------------------------------------------------------------------
   // Examine the performance 
   //------------------------------------------------------------------------
   fnum1 = 3.1415;
   fnum2 = -674.9325;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum2, qnval);
   printf("\nPerformance test\n");

   // Floating point addition
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      fnum3 = fnum1 + fnum2;
   }
   time1 = clock()-time1;
   
   // QN addition
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      qnum3 = qnum1 + qnum2;
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Clock ticks for time1 is %d and time2 is %d\n", (int) time1, (int) time2);
   if(time1 < time2){ printf("Time1/Floating point was faster than Time2/Qn for addition\n");}
   else{ printf("Time2/Qn was faster than Time1/Floating point for addition\n");}
   
   // Floating multiplication
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      fnum3 = fnum1 * fnum2;
   }
   time1 = clock()-time1;
   
   // QN multiplication
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      qnum3 = Qn_MULTIPLY(qnum1, qnum2, qnval);
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Clock ticks for time1 is %d and time2 is %d\n", (int) time1, (int) time2);
   if(time1 < time2){ printf("Time1/Floating point was faster than Time2/Qn for multiplication\n");}
   else{ printf("Time2/Qn was faster than Time1/Floating point for multiplication\n");}

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

