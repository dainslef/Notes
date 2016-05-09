CC = clang
CFLAGS = -std=gnu11

objects = sysv_sem_before sysv_sem_after

all: $(objects)

sysv_sem_before:
sysv_sem_before.o: sysv_sem.h


sysv_sem_after:
sysv_sem_after.o: sysv_sem.h

.PHONY: clean
clean:
	-rm $(objects) *.o
