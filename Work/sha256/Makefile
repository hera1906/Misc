all:	stest 

clean:
	rm -f *.o stest 

stest : main.cpp
	c++ -std=c++14 -o stest  main.cpp -lboost_system -lcryptopp
