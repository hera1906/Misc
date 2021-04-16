all:	unique_ptr shared_ptr1 shared_ptr2 weak_ptr

clean:
	rm -f *.o unique_ptr shared_ptr1 shared_ptr2 weak_ptr

unique_ptr : unique_ptr.cpp c.hpp
	c++ -std=c++2a -o unique_ptr  unique_ptr.cpp -lstdc++

shared_ptr1 : shared_ptr1.cpp c.hpp
	c++ -std=c++2a -o shared_ptr1  shared_ptr1.cpp -lstdc++

shared_ptr2 : shared_ptr2.cpp c.hpp
	c++ -std=c++2a -o shared_ptr2  shared_ptr2.cpp -lstdc++

weak_ptr : weak_ptr.cpp c.hpp
	c++ -std=c++2a -o weak_ptr  weak_ptr.cpp -lstdc++
