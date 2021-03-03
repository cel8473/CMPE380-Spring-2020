/******************************************************************
 * Program to correct the data for the sensor
 * Note: Each student gets unique data, so this exact equation will
 * differ for each students solution
 * Be sure to use Honer's factorization  
 * ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define POLY(x) (x*x+2x+5)
/* Runs the data through the fitting line */

int main(int argc, char *argv[])
{
    int res, real, ideal;
    while(scanf("%d %d", &ideal, &real) != EOF)
    {
     /* Insert your polynomial here, be sure to round properly */
        double x = (double) real;
        double hold =  18.593 + 0.128131*(x) + 3.88032e-05*(x*x) + -1.39931e-08*(x*x*x); 
        if(hold >= 0){
		hold += 0.5;
	}
        if(hold < 0){
		hold -= 0.5;
	}
 	res = real-(int)hold;
        printf("%d %d\n", ideal, res);
    }
    return 0;
}

