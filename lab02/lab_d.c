/****************************************************************************
Lab 2 student file
 
 To enable gdb logging
   gdb <binary>
   set logging file <file>
   set logging overwrite on
   set logging on
   
         gcc -std=c99  -g -O0 lab_d.c -o lab_d
         
 10/05/2019 R. Repka    Initial release
****************************************************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>


int main(int argc, char *argv[]) {
   char *text_p;        // do not change
      
   /*------------------------------------------------------------------------
     Add code here
   ------------------------------------------------------------------------*/
	text_p = malloc(12);
	if(text_p == NULL){
		printf("Memory allocation failed");
		return -1;
	}
	strcpy(text_p, "CMPE380 lab malloc try 1");
 	printf("'%s'\n", text_p);
	text_p = realloc(text_p,20);
	if(text_p == NULL){
		printf("Memory allocation failed");
		return -1;
	}
	strcat(text_p, "-- Realloc");
	printf("'%s'\n", text_p);
	free(text_p);
	
}
