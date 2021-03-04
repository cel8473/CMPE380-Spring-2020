CC = gcc
FLAGS = -Wall -std=c99 -pedantic -g -DMOVE_IO_CLOSE
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
PROG0 = hw8c
SOURCE0 = hw8c.c
PROG1 = hw8c_opt1
SOURCE1 = hw8c_opt1.c
PROG2 = hw8c_opt2
SOURCE2 = hw8c_opt2.c
PROG3 = hw8c_opt3
SOURCE3 = hw8c_opt3.c
DATA = data.txt
OUT = out.txt
TIME = -DEN_TIME
MEM = mem.txt

.SILENT:
.PHONY:all, test, mem, clean, help,

all:$(PROG0) $(PROG1) $(PROG2) $(PROG3)

$(PROG0):
	echo "Linking $(PROG0)"
	$(CC) $(FLAGS) $(TIME) -O0 $(SOURCE0) -o $(PROG0)_0
	$(CC) $(FLAGS) $(TIME) -O1 $(SOURCE0) -o $(PROG0)
	$(CC) $(FLAGS) $(TIME) -O2 $(SOURCE0) -o $(PROG0)_2
	$(CC) $(FLAGS) $(TIME) -O3 $(SOURCE0) -o $(PROG0)_3
	$(CC) $(FLAGS) -O1 $(SOURCE0) -o $(PROG0)_mem

$(PROG1):
	echo "Linking $(PROG1)"
	$(CC) $(FLAGS) $(TIME) -O0 $(SOURCE1) -o $(PROG1)_0
	$(CC) $(FLAGS) $(TIME) -O1 $(SOURCE1) -o $(PROG1)
	$(CC) $(FLAGS) $(TIME) -O2 $(SOURCE1) -o $(PROG1)_2
	$(CC) $(FLAGS) $(TIME) -O3 $(SOURCE1) -o $(PROG1)_3
	$(CC) $(FLAGS) -O1 $(SOURCE1) -o $(PROG1)_mem

$(PROG2):
	echo "Linking $(PROG2)"
	$(CC) $(FLAGS) $(TIME) -O0 $(SOURCE2) -o $(PROG2)_0
	$(CC) $(FLAGS) $(TIME) -O1 $(SOURCE2) -o $(PROG2)
	$(CC) $(FLAGS) $(TIME) -O2 $(SOURCE2) -o $(PROG2)_2
	$(CC) $(FLAGS) $(TIME) -O3 $(SOURCE2) -o $(PROG2)_3
	$(CC) $(FLAGS) -O1 $(SOURCE2) -o $(PROG2)_mem

$(PROG3):
	echo "Linking $(PROG3)"
	$(CC) $(FLAGS) $(TIME) -O0 $(SOURCE3) -o $(PROG3)_0
	$(CC) $(FLAGS) $(TIME) -O1 $(SOURCE3) -o $(PROG3)
	$(CC) $(FLAGS) $(TIME) -O2 $(SOURCE3) -o $(PROG3)_2
	$(CC) $(FLAGS) $(TIME) -O3 $(SOURCE3) -o $(PROG3)_3
	$(CC) $(FLAGS) -O1 $(SOURCE3) -o $(PROG3)_mem

test:$(PROG0) $(PROG1) $(PROG2) $(PROG3)
	echo "Testing $(PROG0), $(PROG1), $(PROG2), and $(PROG3) with $(DATA) and sending to $(OUT)"
	echo "Each test will run 4 times for each optimization level"
	echo "Regular: Opt Level 0"
	./$(PROG0)_0 $(DATA) > $(OUT) 2>&1
	echo "Regular: Opt Level 1"
	./$(PROG0) $(DATA) >> $(OUT) 2>&1
	echo "Regular: Opt Level 2"
	./$(PROG0)_2 $(DATA) >> $(OUT) 2>&1
	echo "Regular: Opt Level 3"
	./$(PROG0)_3 $(DATA) >> $(OUT) 2>&1
	echo "Opt_1: Opt Level 0"
	./$(PROG1)_0 $(DATA) >> $(OUT) 2>&1
	echo "Opt_2: Opt Level 1"
	./$(PROG1) $(DATA) >> $(OUT) 2>&1
	echo "Opt_1: Opt Level 2"
	./$(PROG1)_2 $(DATA) >> $(OUT) 2>&1
	echo "Opt_1: Opt Level 3"
	./$(PROG1)_3 $(DATA) >> $(OUT) 2>&1
	echo "Opt_2: Opt Level 0"
	./$(PROG2)_0 $(DATA) >> $(OUT) 2>&1
	echo "Opt_2: Opt Level 1"
	./$(PROG2) $(DATA) >> $(OUT) 2>&1
	echo "Opt_2: Opt Level 2"
	./$(PROG2)_2 $(DATA) >> $(OUT) 2>&1
	echo "Opt_2: Opt Level 3"
	./$(PROG2)_3 $(DATA) >> $(OUT) 2>&1
	echo "Opt_3: Opt Level 0"
	./$(PROG3)_0 $(DATA) >> $(OUT) 2>&1
	echo "Opt_3: Opt Level 1"
	./$(PROG3) $(DATA) >> $(OUT) 2>&1
	echo "Opt_3: Opt Level 2"
	./$(PROG3)_2 $(DATA) >> $(OUT) 2>&1
	echo "Opt_3: Opt Level 3"
	./$(PROG3)_3 $(DATA) >> $(OUT) 2>&1

mem:$(PROG0) $(PROG1) $(PROG2) $(PROG3)
	echo "Running Valgrind for $(PROG0), $(PROG1), $(PROG2), and $(PROG3) with $(DATA) and sending to $(MEM)"
	echo "Regular: Mem"
	$(VALGRIND) ./$(PROG0)_mem $(DATA) > $(MEM) 2>&1
	echo "Opt_1: Mem"
	$(VALGRIND) ./$(PROG1)_mem $(DATA) >> $(MEM) 2>&1
	echo "Opt_2: Mem"
	$(VALGRIND) ./$(PROG2)_mem $(DATA) >> $(MEM) 2>&1
	echo "Opt_3: Mem"
	$(VALGRIND) ./$(PROG3)_mem $(DATA) >> $(MEM) 2>&1
	
clean:
	-rm -f $(PROG0)_0
	-rm -f $(PROG0)
	-rm -f $(PROG0)_mem
	-rm -f $(PROG0)_2
	-rm -f $(PROG0)_3
	-rm -f $(PROG1)_0
	-rm -f $(PROG1)
	-rm -f $(PROG1)_mem
	-rm -f $(PROG1)_2
	-rm -f $(PROG1)_3
	-rm -f $(PROG2)_0
	-rm -f $(PROG2)
	-rm -f $(PROG2)_mem
	-rm -f $(PROG2)_2
	-rm -f $(PROG2)_3
	-rm -f $(PROG3)_0
	-rm -f $(PROG3)
	-rm -f $(PROG3)_mem
	-rm -f $(PROG3)_2
	-rm -f $(PROG3)_3
	-rm -f *.o

help:
	echo "Make options: all, test, help, mem, clean"
