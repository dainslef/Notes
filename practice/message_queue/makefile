CC = clang
CFLAGS = -std=gnu11

objects = sysv_msgsnd sysv_msgrcv posix_mq_send posix_mq_receive

all: $(objects)

sysv_msgsnd:
sysv_msgsnd.o: sysv_msg.h

sysv_msgrcv:
sysv_msgrcv.o: sysv_msg.h

posix_mq_send: posix_mq_send.o
	$(CC) -lrt $< -o $@
posix_mq_send.o: posix_mq.h

posix_mq_receive: posix_mq_receive.o
	$(CC) -lrt $< -o $@
posix_mq_receive.o: posix_mq.h

.PHONY: clean
clean:
	-rm $(objects) *.o
