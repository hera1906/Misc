#include <iostream>
#include <memory>
#include <assert.h>
#include "c.hpp"

int main(int argc, char* argv[])
{
    std::cout << "weak_ptr example:" << std::endl;

    std::weak_ptr<C> wp;
    assert(wp.use_count() == 0); // No one is using the weak_ptr
    assert(wp.expired());

    {
        std::shared_ptr<C> sp1{std::make_shared<C>(1)};
        wp = sp1;

        assert(sp1.use_count() == 1);
        assert(wp.use_count() == 1);
        assert(!wp.expired());

        if (auto sp = wp.lock())
            assert(sp->m_id == 1);
        else
            assert(false); // weak pointer should be valid here


        // sp1 goes out of scope and also deletes the raw pointer since use count now is 0
    }

    assert(wp.use_count() == 0); // No one is using the weak_ptr
    assert(wp.expired());
    assert(!wp.lock());
}
