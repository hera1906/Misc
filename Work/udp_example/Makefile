all: server client

clean: 
	rm -f server server.o client client.o

server:	server.c
	cc -g -o server server.c

client:	client.c
	cc -g -o client client.c
