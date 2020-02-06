#include <iostream>

void dump(int depth)
{
    if (depth > 0)
    {
        dump(depth - 1);
        return;
    }
    std::cout << "Dumping core" << std::endl;
    int i = 1;
    int j = 0;
    int k = i / j;
    std::cout << "i = " << i << " j = " << j << " k = " << k << std::endl;


    std::cout << "Writing to address 0" << std::endl;
    int *p = 0;
    *p = 12121212;
    std::cout << "Writing to address 0x1234" << std::endl;
    p = (int*) 0x1234;
    *p = 0x4321;
    std::cout << "Didnt work" << std::endl;

}
int main()
{
    dump(3); // Make callstack 3 deep
}
