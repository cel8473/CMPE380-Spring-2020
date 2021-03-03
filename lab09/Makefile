CC = gcc
FLAGS = -g -Wall -std=c99 -O2 -pedantic -lm
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG = quadTest
SOURCE = quadTest.c
OBJS = quadTest.o
TIME = -DEN_TIME
OUT = out.txt 2>&1
MEM = mem.txt 2>&1

.SILENT:
.PHONY:all, tests, mem, clean, help

all: $(PROG)

.c.o: $(SOURCE)
	$(CC) $(FLAGS) -c $< 

$(PROG): $(OBJS)
	echo "Linking $(PROG)"
	$(CC) $(FLAGS) $(TIME) $(SOURCE) -o $(PROG)

tests:$(PROG)
	echo "Testing $(PROG) 3 times and sending to $(OUT)"
	echo "Test 1"
	./$(PROG) -a 0 -b 0 -c 1 &> $(OUT)
	echo "Test 2"
	./$(PROG) -a 1 -b 0 &>> $(OUT)
	echo "Test 3"
	./$(PROG) -a 1 -b 0 -c 1 &>> $(OUT)

mem:$(PROG)
	echo "Running Valgrind for $(PROG) and sending to $(MEM)"
	$(CC) $(FLAGS) $(SOURCE) -o $(PROG)
	$(VALGRIND) ./$(PROG) -a 1 -b 1 -c 1 > $(MEM)

clean:
	-rm -f $(PROG)
	-rm -f *.o

help:
	echo "Make options: all, tests, help, mem, clean"
