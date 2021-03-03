CC = gcc
CPP = g++
CFLAGS = -Wall -std=c99 -pedantic -DEN_TIME -O1
CPPFLAGS = -Wall -pedantic -DEN_TIME -O1
PROGC = hw6c
PROGCPP = hw6cpp
CSOURCE = hw6c.c
CPPSOURCE = hw6cpp.cpp
OBJC = hw6c.o
OBJCPP = hw6cpp.o
DATA = data.txt
OUT = out.txt

.SILENT:
.PHONY:all, test, clean, help

all:$(PROGC) $(PROGCPP)

$(PROGC):$(OBJC)
	echo "Linking $(PROGC)"
	$(CC) $(CFLAGS) $(CSOURCE) -o $(PROGC)

.c.o: $(CSOURCE)
	echo "Compile C"
	$(CC) $(CFLAGS) -c $<

$(PROGCPP):$(OBJCPP)
	echo "Linking $(PROGCPP)"
	$(CPP) $(CPPFLAGS) $(CPPSOURCE) -o $(PROGCPP)

.cpp.o: $(CPPSOURCE)
	echo "Compile CPP"
	$(CPP) $(CPPFLAGS) -c $<

test:$(PROGC) $(PROGCPP)
	echo "Testing $(PROGC) and $(PROGCPP) with $(DATA) and sending to $(OUT)"
	echo "Also testing for $(PROGC) where MOVE_FOPEN is on"
	./$(PROGC) $(DATA) > $(OUT) 2>&1
	./$(PROGCPP) $(DATA) >> $(OUT) 2>&1
	$(CC) $(CFLAGS) -DMOVE_FOPEN $(CSOURCE) -o $(PROGC)
	./$(PROGC) $(DATA) >> $(OUT) 2>&1
	$(CC) $(CFLAGS) $(CSOURCE) -o $(PROGC)

clean:
	-rm -f $(PROGC)
	-rm -f $(PROGCPP)
	-rm -f *.o 

help:
	echo "Make options: all, test, help, clean"
