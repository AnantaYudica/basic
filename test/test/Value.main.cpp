#include "test/Value.h"

#include <cstdio>
#include <cassert>

int main()
{
    basic::test::Value<int> a_int1(4);
    printf("a_int1.Get() : %d\n", a_int1.Get());
    assert(a_int1.Get() == 4);

    a_int1.Get() = 14;
    printf("a_int1.Get() : %d\n", a_int1.Get());
    assert(a_int1.Get() == 14);

    auto a_int2(a_int1);
    printf("a_int2.Get() : %d\n", a_int2.Get());
    assert(a_int2.Get() == 14);
    
    basic::test::Value<int> a_int3(44);
    printf("a_int3.Get() : %d\n", a_int3.Get());
    assert(a_int3.Get() == 44);

    a_int3 = a_int2;
    printf("a_int3.Get() : %d\n", a_int3.Get());
    assert(a_int3.Get() == 14);

    const auto a_int4 = a_int3;
    printf("a_int4.Get() : %d\n", a_int4.Get());
    assert(a_int4.Get() == 14);

}
