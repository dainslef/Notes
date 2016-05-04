CC = clang
CFLAGS = -std=gnu11

objects = msg_send msg_recv

all: $(objects)

msg_send:
msg_send.o: my_msg.h

msg_recv:
msg_recv.o: my_msg.h

.PHONY: clean
clean:
	-rm $(objects) *.o
