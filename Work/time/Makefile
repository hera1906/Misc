all:	asctime ntptest

clean:
	rm -f *.o asctime ntptest

install: all
	scp -o StrictHostKeyChecking=no asctime ntptest ntptest.sh root@169.254.5.22:/usr/bin

asctime : asctime.cpp
	${CXX} -g -std=c++14 -o asctime  asctime.cpp

ntptest : ntptest.cpp
	${CXX} -g -std=c++14 -o ntptest  ntptest.cpp
