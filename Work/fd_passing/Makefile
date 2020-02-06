all: server client fd-passing

clean: 
	rm -f server server.o 
	rm -f client client.o
	rm -f fd-passing fd-passing.o

server:	server.c
	cc -g -o server server.c

client:	client.c
	cc -g -o client client.c

fd-passing:	fd-passing.c
	cc -g -o fd-passing fd-passing.c
