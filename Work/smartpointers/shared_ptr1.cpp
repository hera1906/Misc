#include <iostream>
#include <memory>
#include <assert.h>
#include "c.hpp"

int main(int argc, char* argv[])
{
    std::cout << "shared_ptr example 1:" << std::endl;

    std::shared_ptr<C> sp1{std::make_shared<C>(1)};
    {
        std::shared_ptr<C> sp2{sp1};
        std::cout << "sp1 use_count is " <<  sp1.use_count() << std::endl;
        std::cout << "sp2 use_count is " <<  sp1.use_count() << std::endl;
        assert(sp1.get() == sp2.get());

        // sp2 goes out of scope and does not delete the raw pointer rp since use count now is 1
    }

    C* rp = sp1.get();
    assert(sp1->m_id == rp->m_id);

    std::cout << "sp1 use_count is " <<  sp1.use_count() << std::endl;
    // sp1 goes out of scope and also deletes the raw pointer since use count now is 0
}
