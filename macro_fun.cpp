#include <iostream>
#include "macros.h"

template <typename T>
void disp(const T& x, std::string name, std::string indent)
{
    std::cout << indent << name << ": " << x << std::endl;
}

#define CALL_DISP(x) disp(x, #x, "");
#define CALL_DISP_MEM(x) disp(s.x, #x, indent);

#define DISPLAYABLE(Type, ...) \
void disp(const Type &s, std::string name, std::string indent) \
{ \
    std::cout << indent << name << ":" << std::endl; \
    indent += "   "; \
    APPLY(CALL_DISP_MEM, __VA_ARGS__) \
}

struct A_1
{
    int ival_1;
};

struct A_2
{
    float fval_1;
    int ival_2;
    A_1 a_1;
};

struct A
{
    int ival;
    bool bval;
    A_1 a_1_1;
    A_1 a_1_2;
    A_2 a_2;
};

DISPLAYABLE(A_1, ival_1)
DISPLAYABLE(A_2, fval_1, ival_2, a_1)
DISPLAYABLE(A, ival, bval, a_1_1, a_1_2, a_2)

int main()
{
    A a;
    CALL_DISP(a);
}