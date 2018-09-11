#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Parameter.h"

#include <cstdio>

template<typename T1, typename T2>
struct A
{
};

template<>
struct A<int, int>
{
    void Call(int t1, int t2)
    {
        printf("A<int,int>::Call(t1=%d, t2=%d)\n", t1, t2);
    }
    void Call(int t1, int t2) const
    {
        printf("A<int,int>::Call(t1=%d, t2=%d) const\n", t1, t2);
    }
};

void CallFoo1(int i1, int i2)
{
    printf("CallFoo1(i1=%d, i2=%d)\n", i1, i2);
}

int main()
{
    typedef basic::test::type::Parameter<int, int> ParamA1;
    typedef typename ParamA1::template FilledType<A> FilledA1;
    FilledA1 a1;
    a1.Call(1, 4);
    ParamA1::template Call<void>(&CallFoo1, 4, 6);
    ParamA1::template Call<void>(&FilledA1::Call, a1, 4, 6);
    const FilledA1& const_a1 = a1;
    ParamA1::template Call<void>(&FilledA1::Call, const_a1, 1, 1);
}
