CC = clang
CFLAGS = -std=gnu11

objects = sysv_msgsnd sysv_msgrcv

all: $(objects)

sysv_msgsnd:
sysv_msgsnd.o: my_msg.h

sysv_msgrcv:
sysv_msgrcv.o: my_msg.h

.PHONY: clean
clean:
	-rm $(objects) *.o
