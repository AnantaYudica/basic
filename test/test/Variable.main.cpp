#include "test/Variable.h"

#include <iostream>

int main()
{
    basic::test::Variable<int, basic::test::var::Value<int>> var1(4);
    std::cout << var1.GetValue<1>() << std::endl;

    basic::test::Variable<int, basic::test::var::Value<int>> var3(6);
    std::cout << var3.GetValue<1>() << std::endl;

    var3 = var1;
    std::cout << var3.GetValue<1>() << std::endl;

    basic::test::Variable<int, basic::test::var::Value<int>,
        basic::test::var::Value<int>, char> var4(4, 6);
    
    std::cout << var4.GetValue<1>() << " " <<
        var4.GetValue<2>() << std::endl;
}
