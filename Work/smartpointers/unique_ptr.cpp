#include <iostream>
#include <memory>
#include <assert.h>

#include "c.hpp"

std::unique_ptr<C> createPtr(int id)
{
    auto up = std::make_unique<C>(id);
    return up; // No need for std::move
}

int main(int argc, char* argv[])
{
    std::cout << "unique_ptr examples:" << std::endl << std::endl;

    C* rp = new C(1);
    std::unique_ptr<C> up1{rp};
    assert(up1);

    std::unique_ptr<C> up2{std::make_unique<C>(2)};
    assert(up2);

    //auto up3 = up2; // Will not compile, cannot copy unique_ptr
    auto up3 = std::move(up2); // up2 is now empty

    assert(!up2);
    assert(up3);

    auto up4 = createPtr(3);
    assert(up4);

    if (up1) // Test for not empty
        assert(up1.release() == rp); // Clear pointer and return raw pointer
    delete rp;

    if (up3 != nullptr) // Test for not empty
        up3.reset(nullptr); // Clear pointer and delete raw pointer

    assert(!up1);
    assert(!up2);
    assert(!up3);
    assert(up4);
}
