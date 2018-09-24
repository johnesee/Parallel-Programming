
CC = gcc
OBJS = timer.o
FLAGS = -fopenmp -O3
SEQFLAGS = -O3 

EXEC = knapSeq 

all: $(EXEC)

knapSeq: knap.c timer.o
	$(CC)  $(SEQFLAGS) -o knapSeq knap.c $(OBJS) 

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS)

tar: Makefile report.pdf knap1.c knap2.c knap3.c
	tar cvf PA3.tar Makefile report.pdf knap1.c knap2.c knap3.c
