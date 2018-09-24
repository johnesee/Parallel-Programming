OBJS = timer.o
H_FILE = timer.h

EXEC = jac jacOMP jacMPI

all: $(EXEC)

jac: jac.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ jac.c $(OBJS)

jacOMP: jacOMP.c $(OBJS) $(H_FILE)
	gcc -O3 -o $@ jacOMP.c $(OBJS)

jacMPI: jacMPI.c $(OBJS) $(H_FILE)
	mpicc -O3 -o $@ jacMPI jacMPI.c $(OBJS)

clean:
	rm -f $(EXEC)

tar:
	tar cvf PA4.tar Makefile jacOMP.c jacMPI.c report.pdf
