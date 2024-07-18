#include <array>

struct A
{
    int ival;
};

namespace ns_1
{

struct B
{
    float fval = 3.14;
    int ival = 42;
    A a;
    std::array<int, 3> iarray{1, 2, 3};
};

} // namespace ns_2

namespace ns_2
{

struct C
{
    int ival;
    bool bval;
    A a;
    ns_1::B b;
};

} // namespace ns_2