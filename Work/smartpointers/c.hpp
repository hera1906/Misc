//#include <iostream>

class C
{
  public:
    C(int id)
    {
        m_id = id;
        std::cout << "Creating C(" << m_id << ")" << std::endl;
    }
    ~C()
    {
        std::cout << "Destructing C(" << m_id << ")" << std::endl;
    }
    int m_id;
};
