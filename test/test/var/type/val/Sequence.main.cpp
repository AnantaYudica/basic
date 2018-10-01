#include "test/Variable.h"
#include "test/var/type/val/Sequence.h"
#include "test/type/val/Sequence.h"

#include <iostream>

int main()
{
    basic::test::Variable<basic::test::type::val::Sequence<int, 4>> var1;
    std::cout << "var1 at 0 : " << var1.Get().At<0>() << std::endl;
    basic::test::Variable<basic::test::type::val::Sequence<int, 4, 14>> var2;
    std::cout << "var2 at 0 : " << var2.Get().At<0>() << std::endl;
    std::cout << "var2 at 1 : " << var2.Get().At<1>() << std::endl;
    basic::test::Variable<int, basic::test::type::val::
        Sequence<int, 6, 12, 24, 32>> var3;
    basic::test::Variable<basic::test::type::val::Sequence<int, 1, 2, 3>, int,
        basic::test::type::val::Sequence<int, 14, 4, 22, 11>, char> var4;
}
