/****************************************************************************
 The purpose of this example is to exercise using data and function pointers.
 It also demonstrates the value of using NULL assignments to identify pointer
 issues.
 
 student version 
 
 
 gcc -O1 -Wall -std=c99 -pedantic -g  lab_b.c -o lab_b
 valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./lab_b
 
 
 09/09/2019 R. Repka    Minor formatting changes
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
   int entry;
   char string [40];
} Data;

int fun2x(int num);
int fun3x(int num);

Data ramData;


int main(int argc, char *argv[]) {
   int(*function_p)(int);
   int answer;
   Data stackData;
   static Data staticData;
   Data *heapData_p;
   heapData_p = malloc(sizeof(Data));
   
   // Print out the addresses of items   
   printf("Program : %8p\n", &main);           
   printf("Static data : %8p\n", &staticData);
   printf("Ram data : %8p\n", &ramData);
   printf("Heap data : %8p\n", heapData_p);
   printf("Stack data: %8p\n", &stackData);

   // Using function pointers
   function_p = &fun2x;
   answer = (*function_p)(2);
   printf("\nPassing the 2x function a 2, I got %d\n", answer);
   function_p = &fun3x;
   answer = (*function_p)(2);
   printf("Passing the 3x function a 2, I got %d\n", answer);

   // Initialize the stack data
   stackData.entry = 1;
   strncpy(stackData.string, "Stack", 39);
   printf("Stack data values before free : %d '%s'\n", stackData.entry, stackData.string);

   // Initialize the heap data, free it and use it
   heapData_p->entry = 2;
   strncpy(heapData_p->string, "Pointer", 39);
   printf("Heap data values before free : %d '%s'\n", heapData_p->entry, heapData_p->string);
   free(heapData_p);
   heapData_p = NULL;
   printf("Heap data values after free : %d '%s'\n", heapData_p->entry, heapData_p->string);

   //heapData_p = NULL;
   return 0;
}


int fun2x(int num) {
   return(num*2);
}
int fun3x(int num) {
   return(num*3);
}
