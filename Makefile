CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -pedantic -std=gnu99 -O3
LDFLAGS=

EX2_PROG=matrixMultiply

EX3_PROG=transpose

PROGS=$(EX2_PROG) $(EX3_PROG)

all: $(PROGS)

ex2: $(EX2_PROG)
	$(CC) -o $(EX2_PROG) $(CFLAGS) $(EX2_PROG).c
	./$(EX2_PROG)
	./$(EX2_PROG) 2

ex3: $(EX3_PROG)
	$(CC) -o $(EX3_PROG) $(CFLAGS) $(EX3_PROG).c
	./$(EX3_PROG)

clean:
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(PROGS) *.dSYM
