

#Makefile

#compiler
CC = gcc
CFLAGS = -Wall -g

#target for round robin and sjf
RR_TARGET = rr
SJF_TARGET = sjf

all: $(RR_TARGET) $(SJF_TARGET)

$(RR_TARGET): RR_inital.o
	$(CC) $(CFLAGS) -o $(RR_TARGET) RR_inital.o

$(SJF_TARGET): SJF_inital.o
	$(CC) $(CFLAGS) -o $(SJF_TARGET) SJF_inital.o

#compile rr source file into obj file
RR_inital.o: RR_inital.c
	$(CC) $(CFLAGS) -c RR_inital.c

#compile sjf source file into obj file
SJF_inital.o: SJF_inital.c
	$(CC) $(CFLAGS) -c SJF_inital.c

#clean files
clean:
	rm -f *.o $(RR_TARGET) $(SJF_TARGET)

#run executables together
run: $(RR_TARGET) $(SJF_TARGET)
	./$(RR_TARGET)
	./$(SJF_TARGET)

.PHONY: clean all run

