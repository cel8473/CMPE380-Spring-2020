/* Applied Programming Examples: sorting.c
 * student copy
 *
 * Uses qsort() to sort an array of random polar data
 *
 * Use compiler directive -DN=size to change the size of the array
 *
 * Reference: A. Kelley and I Pohl "A book on C" 4th Ed.
 * Revised: 3/31/2015 (JCCK)
 */
 
#include <stdio.h>  
#include <math.h>
#include <float.h>
#include <stdlib.h> /* for qsort()    */

/* The polar data structure */
typedef struct {double mag; double ang;} polar;

/* Add your polar compare function prototype here */
int cmppolar(const void *p1, const void *p2);
/* 
 Initialize an array of doubles of size N, with random numbers
 between -50 and 50, sort it and print it 
*/
int main(int argc, char *argv[]) {

   polar *array;
   int num;
   int i;
   
   // Check the command line entry
   if(argv[1] != NULL){
	num = atoi(argv[1]);
   }
   if(argc == 1){
	printf("Enter an argument\n");
	return 1;
   }
   if(argc > 2){
	printf("Only 1 number is allowed in the arguments\n");
	return 2;
   }
   if(num < 2){
	printf("Enter a number larger than 1\n");
	return 1;
   }
   // Get the memory
   array = (polar *) malloc(2 * num * sizeof(double));

   // Initialize the array with random data, make one magnitude identical
   for(i = 0; i < num-1; ++i) {
      array[i].mag = (rand() % 1001) /10.0 - 50.0;
      array[i].ang = (rand() % 1001) /10.0 - 50.0;
   }
   // Identical 
   array[i].mag = array[i-1].mag;
   array[i].ang = (rand() % 1001) /10.0 - 50.0;
   
   // Sort the data
   qsort(array, num, 2*sizeof(double), cmppolar);
   
   // Print the sorted dat
   for(i = 0; i < num; ++i) {
      printf("%10.1f %10.1f\n", array[i].mag, array[i].ang);
   }
   printf("\n");   
   free(array);
return(0);
}  
 
/*---------------------------------------------------------------------------
  The compare function to use.  Cast p1 and p2 to polar in this case
---------------------------------------------------------------------------*/
// add your function and code here
int cmppolar(const void *p1, const void *p2){
	polar* ptr1 = (polar *) p1;
	polar* ptr2 = (polar *) p2;
	polar i = *ptr1;
	polar j = *ptr2;
	double mag1 = i.mag;
	double mag2 = j.mag;
	double ang1 = i.ang;
	double ang2 = j.ang;
	if(mag1 > mag2) return 1;
	else if(mag1 < mag2) return -1;
	else{
		if(ang1 > ang2) return 1;
		else if(ang1 < ang2) return -1;
		else return 0;
	}
}
