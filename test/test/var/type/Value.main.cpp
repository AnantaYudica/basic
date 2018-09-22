#include "test/Variable.h"
#include "test/var/type/Value.h"
#include "test/type/Value.h"

#include <iostream>

int main()
{
    basic::test::Variable<basic::test::type::Value<int, 4>> var1;
    std::cout << "val : " << **var1 << std::endl;
    basic::test::Variable<int, basic::test::type::Value<int, 6>> var2;
    basic::test::Variable<basic::test::type::Value<int, 1>, int,
        basic::test::type::Value<int, 4>, char> var3;
}
