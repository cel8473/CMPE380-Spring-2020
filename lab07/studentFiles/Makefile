CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -DEN_TIME -O1
VALG = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG = hw7
SOURCE = hw7.c
OBJS = $(patsubst %.c,%.o,$(SOURCE))
ROOT = rootfinding.c
EQN = eqn2solve.c
OUT = out.txt
MEM = mem.txt
VERB = -v

.SILENT:
.PHONY: all, bisection, secant, newton, opts, tests, clean, help, mem
####################################################################
#THE GUESSES NEED TO BE CHANGED WHEN YOU GO TO THE FINAL FUNCTION
####################################################################
all: $(PROG)

$(PROG):$(ROOT) $(EQN) $(SOURCE)
	echo "Linking $(PROG) with $(ROOT) and $(EQN)"
	$(CC) $(CFLAGS) $(SOURCE) $(ROOT) $(EQN) -o $(PROG) -lm

.c.o:$(SOURCE) $(ROOT) $(EQN)
	echo "Compiling $(PROG)"
	$(CC) $(CFLAGS) -c $<

bisection:$(PROG)
	echo "Testing bisection function of $(PROG)"
	./$(PROG) -b -t 0.000001 -ga -2.5 -gb 2.5 $(VERB)

secant:$(PROG)
	echo "Testing secant function of $(PROG)"
	./$(PROG) -s -t 0.000001 -ga -1.5 -gb -1.6 $(VERB)

newton:$(PROG)
	echo "Testing newton function of $(PROG)"
	./$(PROG) -n -t 0.000001 -ga -1.5 $(VERB)

tests:$(PROG)
	echo "Running the Lab 07 tests and outputting to $(OUT)"
	./$(PROG) -b -t 0.000001 -ga -2.5 -gb 2.5 $(VERB) > $(OUT) 2>&1
	./$(PROG) -n -t 0.000001 -ga -1.5 $(VERB) >> $(OUT) 2>&1
	./$(PROG) -n -t 0.000001 -ga 1.5 $(VERB) >> $(OUT) 2>&1
	./$(PROG) -s -t 0.000001 -ga -1.5 -gb -1.6 $(VERB) >> $(OUT) 2>&1

opts:$(PROG)
	echo "Running the bisection test using specific abbreviations, last test gets redirected to $(OUT)"
	./$(PROG) -b -tol 1E-6 -ga -2 -gb 3 -verb
	./$(PROG) -b -t 1E-6 -g -2 -u 3 $(VERB)
	./$(PROG) -b -t 1E-6 -ba -2 -bb 3 $(VERB) >> $(OUT)
	
mem:$(PROG)
	echo "Valgrind on $(PROG)"
	$(VALG) ./$(PROG) -b -t 0.000001 -ga -2.5 -gb 2.5 $(VERB) > $(MEM) 2>&1
	$(VALG) ./$(PROG) -s -t 0.000001 -ga -1.5 -gb -1.6 $(VERB) >> $(MEM) 2>&1
	$(VALG) ./$(PROG) -n -t 0.000001 -ga -1.5 -gb -1.6 $(VERB) >> $(MEM) 2>&1

clean:
	-rm -f $(PROG)
	-rm -f *.o

help:
	echo "Make options: all, bisection, secant, newton, opts, tests, clean, help, mem"
