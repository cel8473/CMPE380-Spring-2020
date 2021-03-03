/*---------------------------------------------------------------------------
  This prints out argv and env variables 
  student copy
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
   //your code here 
   printf("Argc = %d\n", argc);
   
   for(int i = 1; i < argc; i++){
	printf("Argv[%d] = %s\n", i, argv[i]);
   }

   int i = 0;
   while(env[i] != NULL){
	printf("Env[%d] = %s\n", i, env[i]);
	i++;
   }
   return 0;
}
