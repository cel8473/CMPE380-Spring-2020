/*---------------------------------------------------------------------------
  sleep.c - student file
  01/01/2016    R. Repka    This code is only used to verify your timing macros
  02/202016     R. Repka    Added include file hint
  10/21/2018    R. Repka    Added time.h
---------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "Timers.h"
/* add other include files as necessary */

int main()
   {
   clock_t end_t;
   int delay;

   printf("Start\n");
   /* Your macro stuff here */
 	DECLARE_TIMER(sleep)
	DECLARE_REPEAT_VAR(sleepVar)
	int reps = 3;
	START_TIMER(sleep)
	BEGIN_REPEAT_TIMING(reps,sleepVar)
   /* wait for 60 seconds */
   end_t = clock() + 2 * CLOCKS_PER_SEC;
   while (end_t > clock())
      {
      /* Consume CPU time */
      delay = 1<<19;
      while (delay) 
         {
         delay--;
         }
      }
   
   /* more of your macro stuff */  
	END_REPEAT_TIMING 
	PRINT_RTIMER(sleep, reps)
   printf("End\n");
   return 0;
}
