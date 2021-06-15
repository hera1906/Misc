#include <iostream>
#include <list>
#include <assert.h>


class C
{
    public:

    // Constructor
    C(int i)
    {
        std::cout << "Constructor: " << i << std::endl;

        data = new int;
        *data = i;

    }

    // Copy constructor:
    C(const C& source) : C(*source.data)
    {
        std::cout << "Copy constructor: " << *source.data  << std::endl;
    }

    // Destructor
    ~C()
    {
        if (data == nullptr)
        {
            std::cout << "Desctructor: data: null"  << std::endl;
        }
        else
        {
            std::cout << "Desctructor: data: " << *data  << std::endl;
            delete data;
        }
    }

    int* data;
}; // class C

int main(int argc, char* argv[])
{
    std::cout << "shared_ptr example 1:" << std::endl;
    std::list<C> collection;

    std::cout << "===== push_back C(10) =====" << std::endl;
    collection.push_back(C(10));

    std::cout << "===== push_back C(20) =====" << std::endl;
    collection.push_back(C(20));

    std::cout << "===== push_back C(30) =====" << std::endl;
    auto c30 = C(30);
    collection.push_back(c30);
    std::cout << "  c30.data is " << (c30.data == nullptr ? "null" : "not null") << std::endl;

    std::cout << "===== push_back C(40) =====" << std::endl;
    auto c40 = C(40);
    collection.push_back(std::move(c40));
    std::cout << "  c40.data is " << (c40.data == nullptr ? "null" : "not null") << std::endl;

    std::cout << "===== Done            =====" << std::endl;

    return 0;
}
