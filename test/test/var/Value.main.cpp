#include "test/var/Value.h"

#include <iostream>

int main()
{
    basic::test::var::Value<int> a_int1(4);
    std::cout << a_int1.Get() << std::endl;
    auto a_int2(a_int1);
    std::cout << a_int2.Get() << std::endl;
    
    basic::test::var::Value<int> a_int3(14);
    std::cout << a_int3.Get() << std::endl;
    a_int3 = a_int2;
    std::cout << a_int3.Get() << std::endl;
    const auto a_int4 = a_int3;
    std::cout << a_int4.Get() << std::endl;

}
