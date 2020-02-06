all:	download 

clean:
	rm -f *.o download 

download : main.c download.c download.h
	gcc -o download  main.c download.c -lcurl -lsystemd
