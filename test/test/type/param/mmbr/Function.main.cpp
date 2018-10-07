#include "Test.h"

#include "test/type/param/mmbr/Function.h"

#include <cstdio>

typedef basic::test::type::Parameter<int, char, float> P1;

class A
{
public:
    void Print1(int i, char c, float f)
    {
        printf("print1 %d, %c, %f\n", i, c, f);
    }
    void Print2(int i, char c, float f) const
    {
        printf("print2 const %d, %c, %f\n", i, c, f);
    }
    void Print2(int i, char c, float f)
    {
        printf("print2 %d, %c, %f\n", i, c, f);
    }
};

int main()
{
    typedef basic::test::type::param::mmbr::Function<P1> PF1;
    A a;
    PF1::Call<void>(&A::Print1, a, 1,'a', 3.14f);
    PF1::Call<void>(&A::Print1, &a, 1,'a', 3.14f);
    PF1::Call<void>(PF1::PointerConstType<void, A>(&A::Print2), a, 1,'a', 3.14f);
    PF1::Call<void>(PF1::PointerType<void, A>(&A::Print2), &a, 1,'a', 3.14f);

}
