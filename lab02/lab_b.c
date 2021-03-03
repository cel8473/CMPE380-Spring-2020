/****************************************************************************
 Lab 2 student file
 10/05/2019 R. Repka    Initial release
****************************************************************************/
#include <stdio.h> 
#include <stdint.h> 
#include <string.h>
   
/*---------------------------------------------------------------------------
  Student data structure
---------------------------------------------------------------------------*/
struct bandMember {
   char f_name[256]; 
   char l_name[256]; 
   int  year; 
};	
   
int main(int argc, char *args[]){
   /*------------------------------------------------------------------------
     Example union and pointer
   ------------------------------------------------------------------------*/
   union aunion  {
      uint16_t   number;   
      struct {
         uint8_t high; 
         uint8_t low;
      } bytes; 
   } aUnion;
   union aunion *aUnion_P = &aUnion;
   
   // Set byte parts of the union 
   aUnion.bytes.high= 0xee;
   aUnion.bytes.low = 0xff;
   
   // Now print out the integer parts AND the union
   printf("Size of aUnion  :%ld, aUnion.number:0x%04x\n",    sizeof(aUnion), aUnion.number);
   printf("Size of aUnion_P:%ld, aUnion_P->number:0x%04x\n\n", sizeof(aUnion_P), aUnion_P->number);
   
   /*------------------------------------------------------------------------
     Add code here
   ------------------------------------------------------------------------*/
 	union aNumber1{
		int integerA;
		float floatA;
	} aNumber1;
	aNumber1.integerA = 5;
	aNumber1.floatA = 6.0;
	
	printf("The value of aNumber1's integerA: %d\n", aNumber1.integerA);
	printf("The value of aNumber1's floatA: %f\n", aNumber1.floatA);

	struct aNumber2{
		int integerB;
		float floatB;
	}aNumber2;
	aNumber2.integerB = 5;
	aNumber2.floatB = 6.0;
	
	printf("The value of aNumber2's integerB: %d\n", aNumber2.integerB);
	printf("The value of aNumber2's floatB: %f\n", aNumber2.floatB);
	printf("The size of the union: %ld and the size of the structure: %ld\n", sizeof(aNumber1), sizeof(aNumber2));
	
	struct padd{
		int16_t number;
		char buffer[3];
	}padd;

	printf("The number of bytes in the data structure padd: %ld and I think it will be 2 bytes\n", sizeof(padd));
					
	typedef struct bandMember band;
	band beatles[4];
	strncpy(beatles[0].f_name, "John", 256);
	strncpy(beatles[0].l_name, "Lennon", 256);
	strncpy(beatles[0].l_name, "Lennon", 256);
	beatles[0].year = 1940;

	strncpy(beatles[1].f_name, "Paul", 256);
	strncpy(beatles[1].l_name, "McCartney", 256);
	beatles[1].year = 1942;
		
	strncpy(beatles[2].f_name, "George", 256);
	strncpy(beatles[2].l_name, "Harrison", 256);
	beatles[2].year = 1943;
	
	strncpy(beatles[3].f_name, "Ringo", 256);
	strncpy(beatles[3].l_name, "Starr", 256);
	beatles[3].year = 1940;

	for(int i; i< 4; i++){
		printf("Beatle %s %s born %d and is at the index: %d \n", beatles[i].f_name, beatles[i].l_name, beatles[i].year, i);
	};

	char dest[25];
	dest[0] = 0;
	for(int i; i< 4; i++){
		strncat(dest, beatles[i].f_name, sizeof(dest)-strlen(dest)-1);
	};
	printf("Run on string of first names: %s\n", dest);
} 

