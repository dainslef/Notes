CC = clang
CFLAGS = -std=c11 -Wall

objects = client_tcp server_tcp server_tcp_select server_tcp_select_single_thread client_udp server_udp
epoll_objects = server_tcp_epoll server_tcp_epoll_et


os = $(shell uname)
ifeq ($(os), Linux)
	LDFLAGS = -lpthread
	objects += $(epoll_objects)
endif


all: $(objects)

client_tcp.o:
server_tcp.o:

server_tcp_select.o:
server_tcp_select_single_thread.o:

client_udp.o:
server_udp.o:


epoll: $(epoll_objects)

server_tcp_epoll.o:
server_tcp_epoll_et.o:


.PHONY: clean
clean:
	-rm $(objects) *.o
