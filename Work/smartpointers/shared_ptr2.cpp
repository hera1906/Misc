#include <iostream>
#include <memory>

#include "c.hpp"

int main(int argc, char* argv[])
{
    std::cout << "shared_ptr example 2 (crashes):" << std::endl;

    C* rp = new C(1);
    std::shared_ptr<C> sp1{rp};
    {
        std::shared_ptr<C> sp2{rp}; // BAD!
        std::cout << "sp1 use_count is " <<  sp1.use_count() << std::endl;
        std::cout << "sp2 use_count is " <<  sp2.use_count() << std::endl;

        // sp2 goes out of scope and deletes the raw pointer rp
    }


    // crash: sp1 goes out of scope and also deletes the raw pointer rp!
}
