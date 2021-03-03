CC = gcc
FLAGS = -g $(SOURCE) DynamicArrays.c -DHW8 -std=c99 -lgsl -lgslcblas
CFLAGS = -g -Wall -pedantic -std=c99 
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG = hw11
SOURCE = hw11.c
CORRECT = correction
CORSOURCE = correction.c
OBJS = hw11.o
COBJS = correction.o
REAL = realDevice
DERROR = detError
DIFF = diffVal
PLOT = myplot
PNG = correction.png
DATA = data.txt
ALLDATA = alldata.txt 2>&1
RTXT = realdevice.txt 2>&1
CTXT = correction.txt 2>&1
MEM = mem.txt 2>&1

.SILENT:
.PHONY: all, base, correct, plot, mem, x, clean, help

all:$(PROG) $(CORRECT)

$(PROG): 
	echo "Linking $(PROG)"
	$(CC) $(FLAGS) -o $(PROG)

$(CORRECT):
	echo "Linking $(CORRECT)"
	$(CC) $(CFLAGS) $(CORSOURCE) -o $(CORRECT)

base:$(REAL) $(DERROR)
	./$(REAL) | ./$(DERROR)

correct:$(REAL) $(CORRECT) $(DERROR) 
	./$(REAL) | ./$(CORRECT) | ./$(DERROR)

plot:$(REAL) $(CORRECTION)
	echo "Redirecting the outputs of $(REAL) and $(CORRECT) to $(RTXT) and $(CTXT)"
	./$(REAL) > $(RTXT)
	./$(REAL) | ./$(CORRECT) > $(CTXT)
	echo "Pasting the combined files into $(ALLDATA) and creating $(PNG)"
	paste $(RTXT) $(CTXT) > $(ALLDATA)
	./myplot -in $(ALLDATA) -out $(PNG)

mem:$(PROG)
	echo "Running valgrind on $(PROG): order 3, points $(DATA)"
	$(VALGRIND) ./$(PROG) -order 3 -p $(DATA) > $(MEM)

x:$(REAL) $(DERROR) $(PLOT) $(DIFF)
	echo "Chmod for all necessary files"
	chmod +x $(REAL)
	chmod +x $(DERROR)
	chmod +x $(PLOT)
	chmod +x $(DIFF)

clean:
	-rm -f $(RTXT)
	-rm -f $(CTXT)
	-rm -f $(ALLDATA)
	-rm -f $(MEM)
	-rm -f $(PNG)
	-rm -f $(PROG)
	-rm -f $(CORRECT)
	-rm -f *.o

help:
	echo "Make options: all, base, correct, plot, mem, x, clean, help"

