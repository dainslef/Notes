CC = clang
CFLAGS = -std=gnu11

ifeq ($(shell uname), Linux)
	LDFLAGS = -lpthread
endif

objects = sysv_shm_before sysv_shm_after

all: $(objects)

sysv_shm_before:
sysv_shm_before.o:

sysv_shm_after:
sysv_shm_after.o:

.PHONY: clean
clean:
	-rm $(objects) *.o
