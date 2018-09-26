#include "Test.h"

#include "test/type/param/Size.h"

#include <cstdio>

typedef basic::test::type::Parameter<int, float, char, int, double, short> P1;

template<typename...>
struct Param1{};

int main()
{
    printf("P1 Size : %d\n", basic::test::type::param::Size<P1>::Value);
    printf("Param1<int, int, char> : %d\n", basic::test::type::param::
        Size<Param1<int, int, char>>::Value);

}
