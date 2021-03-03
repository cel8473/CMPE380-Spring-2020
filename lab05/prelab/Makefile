CC = gcc
CFLAGS = -O1 -g -Wall -std=c99 -pedantic
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG = fib
SOURCE = fib.c
OBJS = $(patsubst %.c,%.o,$(SOURCE))

.SILENT:
.PHONY:CLEAN,ALL,MEM,HELP

ALL:$(PROG) 

$(PROG):$(OBJS)
	echo "Linking $(PROG)" 
	$(CC) $(CFLAGS) $(SOURCE) -o $(PROG)
#Compiles the C file and links the .o and .c file
.c.o: $(SOURCE)
	echo "Compiling $(PROG)"
	$(CC) $(CFLAGS) -c $<
#Convert each .c file to a .o file
MEM:$(PROG)
	$(VALGRIND) ./$(PROG)
#Generates a Valgrind memory report
CLEAN:
	-rm -f $(PROG)
	-rm -f *.o
#Cleans the application up,gets rid of the executables, obj files, plots, temp files, etc.
HELP:
	echo "Make options: all, mem, clean, help"
#List all the key make targets
