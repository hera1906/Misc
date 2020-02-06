all: server client

clean: 
	rm -f SSLserver SSLserver.o SSLclient SSLclient.o

server:	SSLserver.c
	gcc -Wall -o SSLserver SSLserver.c -L/usr/lib -lssl -lcrypto

client:	SSLclient.c
	gcc -Wall -o SSLclient SSLclient.c -L/usr/lib -lssl -lcrypto
