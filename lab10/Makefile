CC = gcc
FLAGS = -g -Wall -std=c99 -O3 -pedantic -lm
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG = intTest
SOURCE = intTest.c
OBJS = $(patsubst %.c,%.o,$(SOURCE))
VERB = -DVERBOSE
TIME = -DEN_TIME
OUT = out.txt 2>&1 
MEM = mem.txt 2>&1

.SILENT:
.PHONY: all, test, mem, clean, help

all:$(PROG)

$(PROG):$(OBJS)
	echo "Linking $(PROG)"
	$(CC) $(FLAGS) $(VERB) $(SOURCE) -o $(PROG)
	$(CC) $(FLAGS) $(TIME) $(SOURCE) -o $(PROG)_time

.c.o:
	echo "Compiling $(PROG)"
	$(CC) $(CFLAGS) -c $<

test:$(PROG)
	echo "Testing $(PROG) with VERBOSE on and then testing with EN_TIME on, sending to out.txt"
	echo "Verb Test" > $(OUT)
	./$(PROG) >> $(OUT)
	echo "Time Test" >> $(OUT)
	./$(PROG)_time >> $(OUT)

mem:$(PROG)
	echo "Running Valgrind for $(PROG) and sending to $(MEM)"
	$(CC) $(FLAGS) $(VERB) $(SOURCE) -o $(PROG)
	$(VALGRIND) ./$(PROG) > $(MEM)

clean:
	-rm -f $(PROG)
	-rm -f *.o

help:
	echo "Make options: all, test, help, mem, clean"
