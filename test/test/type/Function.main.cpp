#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Function.h"

#include <cstdio>

int Foo1()
{
    printf("Foo1()\n");
    return 1;
}

void Foo2(const int& i)
{
    printf("Foo2(i = %d)\n", i);
}

int main()
{
    typedef basic::test::type::Function<int(), &Foo1> Function1;
    Function1 f1;
    printf("ret = %d\n", f1());
    Function1::Call();

    Function1::Pointer();

    typedef basic::test::type::Function<decltype(Foo2), &Foo2> Function2;
    Function2 f2;
    f2(4);
    Function2::Call(14);
}
