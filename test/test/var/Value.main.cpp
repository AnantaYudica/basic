#include "test/Variable.h"
#include "test/var/Value.h"
#include "test/Value.h"

#include <iostream>

int main()
{
    basic::test::Variable<basic::test::Value<int>> var1(4);
    std::cout << "value : " << **var1 << std::endl;
    basic::test::Variable<int, basic::test::Value<int>> var2(6);
    basic::test::Variable<basic::test::Value<int>, int,
        basic::test::Value<int>, char> var3(4, 6);
}
