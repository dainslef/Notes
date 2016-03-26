CC = clang
CFLAGS = -std=c11

libs = -lpthread
objects = client_tcp server_tcp server_tcp_select server_tcp_select_single_thread client_udp server_udp
epoll_objects = server_tcp_epoll server_tcp_epoll_et


os := $(shell uname)
ifeq ($(os), Linux)
	objects += $(epoll_objects)
endif


all: $(objects)

client_tcp: client_tcp.o
	$(CC) $(libs) $< -o $@
client_tcp.o:

server_tcp: server_tcp.o
	$(CC) $(libs) $< -o $@
server_tcp.o:

server_tcp_select: server_tcp_select.o
	$(CC) $(libs) $< -o $@
server_tcp_select.o:

server_tcp_select_single_thread: server_tcp_select_single_thread.o
	$(CC) $< -o $@
server_tcp_select_single_thread.o:

client_udp: client_udp.o
	$(CC) $< -o $@
client_udp.o:

server_udp: server_udp.o
	$(CC) $< -o $@
server_udp.o:


epoll: $(epoll_objects)

server_tcp_epoll: server_tcp_epoll.o
	$(CC) $< -o $@
server_tcp_epoll.o:

server_tcp_epoll_et: server_tcp_epoll_et.o
	$(CC) $< -o $@
server_tcp_epoll_et.o:


.PHONY: clean
clean:
	-rm $(objects) *.o
