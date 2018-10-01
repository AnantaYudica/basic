#include "Test.h"

#include "test/type/param/Filler.h"

#include <cstdio>

template<typename T1, typename T2, typename T3>
struct A
{};

template<>
struct A<int ,char, float>
{
    static void Print()
    {
        printf("A<int, char, float>\n");
    }
};

int main()
{
    typedef basic::test::type::param::Filler<
        basic::test::type::Parameter<int, char, float>> F1;

    F1::template Type<A>::Print();

}
