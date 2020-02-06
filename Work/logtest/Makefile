all:	logtest

clean:
	rm -f *.o logtest

logtest : logtest.cpp
	g++ -o logtest logtest.cpp -lpthread -lsystemd -lbk_common
