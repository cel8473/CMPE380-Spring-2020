/*-----------------------------------------------------------------------
  Simple program to dump IEEE single precision floating point numbers
  student copy
-----------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>


int main( int argc, char *argv[] ) {
 float epsilon     = 1.0;
 float lastEpsilon;
 
 // Loop until the addition does not change the result
 while ((float)(1.0 + epsilon) != (float)1.0) {
   printf("%10.8g\t%.20f\n",epsilon,(1.0 + epsilon));

   // Insert your code here
   lastEpsilon = epsilon;
   epsilon = epsilon/2;
   printf("The last 'previous epsilon' was %2.6g\n", lastEpsilon);
 }  

 // Print out the calculated and actual Epsilon
 printf("Calculated Machine Epsilon: %2.6g\n",  FLT_EPSILON);
 printf("Actual Machine Epsilon:     %2.6g\n",  lastEpsilon);
 
 epsilon = 1.0;
 /*------------------------------------------------------------------------
   Insert your double precision code here when instructed
 ------------------------------------------------------------------------*/
 
 while ((1.0 + epsilon) != 1.0) {
   printf("%10.8g\t%.20f\n",epsilon,(1.0 + epsilon));

   // Insert your code here
   lastEpsilon = epsilon;
   epsilon = epsilon/2;
   printf("The last 'previous epsilon' was %2.6g\n", lastEpsilon);
 }  

 // Print out the calculated and actual Epsilon
 printf("Calculated Machine Epsilon: %2.6g\n",  DBL_EPSILON);
 printf("Actual Machine Epsilon:     %2.6g\n",  lastEpsilon);
 return 0;
} 

