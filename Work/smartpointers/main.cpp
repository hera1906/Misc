#include <iostream>
#include <memory>

#include "c.hpp"

std::unique_ptr<C> createPtr(int id)
{
    auto up = std::make_unique<C>(id);
    return up; // No need for std::move
}

void unique_ptrExample()
{
    std::cout << "unique_ptr examples:" << std::endl;
    C* rp = new C(1);
    std::unique_ptr<C> up1{rp};
    std::unique_ptr<C> up2{std::make_unique<C>(2)};

    //auto up3 = up2; // Will not compile, cannot copy unique_ptr
    auto up3 = std::move(up2); // up2 is now empty
    std::cout << "up1 is " <<  (up1 ? "not empty as expected" : "empty") << std::endl;
    std::cout << "up2 is " <<  (up2 ? "not empty" : "empty as expected") << std::endl;
    auto up4 = createPtr(3);

    if (up1) // Test for not empty
        up1.release(); //Clear pointer, do not delete raw pointer
    // rp is still valid here
    if (up3 != nullptr) // Test for not empty
        up3.reset(); //Clear pointer and delete raw pointer
    std::cout << "up1 is " <<  (up1 ? "not empty" : "empty as expected") << std::endl;
    std::cout << "up2 is " <<  (up2 ? "not empty" : "empty as expected") << std::endl;
    std::cout << "up3 is " <<  (up3 ? "not empty" : "empty as expected") << std::endl;
    std::cout << "up4 is " <<  (up4 ? "not empty as expected" : "empty") << std::endl;
}

void shared_ptrExample1()
{
    std::cout << "shared_ptr example 1:" << std::endl;

    C* rp = new C(1);
    std::shared_ptr<C> sp1{rp};
    {
        std::shared_ptr<C> sp2{rp}; // BAD!
        std::cout << "sp1 use_count is " <<  sp1.use_count() << std::endl;
        std::cout << "sp2 use_count is " <<  sp1.use_count() << std::endl;

        // sp2 goes out of scope and deletes the raw pointer rp
    }


    // crash: sp1 goes out of scope and also deletes the raw pointer rp!
}

int main(int argc, char* argv[])
{
    std::cout << "smartpointer examples:" << std::endl;

    unique_ptrExample();
    shared_ptrExample1();

    return 0;
}
