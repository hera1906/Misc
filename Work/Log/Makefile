all:	logexample

clean:
	rm -f *.o logexample

Log.o: Log.cpp Log.hpp
	c++ -c -std=c++2a Log.cpp

logexample : logexample.cpp Log.o
	c++ -std=c++2a -o logexample  logexample.cpp Log.o -lstdc++ -lsystemd
