#include "test/Variable.h"
#include "test/var/val/Sequence.h"
#include "test/val/Sequence.h"

#include <iostream>

int main()
{
    typedef basic::test::val::Sequence<int, 4> ValSeq4;
    basic::test::Variable<ValSeq4> var1(1, 2, 3, 4);
    std::cout << "var1 at 0 : " << var1.Get().At<0>() << std::endl;
    std::cout << "var1 at 1 : " << var1.Get().At<1>() << std::endl;
    std::cout << "var1 at 2 : " << var1.Get().At<2>() << std::endl;
    std::cout << "var1 at 3 : " << var1.Get().At<3>() << std::endl;

    basic::test::Variable<int, basic::test::val::Sequence<int, 2>> var2(6, 11);
    auto& var2_at_1 = dynamic_cast<basic::test::Variable<
        basic::test::val::Sequence<int, 2>>&>(var2);
    std::cout << "var2_at_1 at 0 : " << var2_at_1.Get().At<0>() << std::endl;
    std::cout << "var2_at_1 at 1 : " << var2_at_1.Get().At<1>() << std::endl;

    basic::test::Variable<basic::test::val::Sequence<int, 2>, int,
        basic::test::val::Sequence<int, 1>, char> var3(4, 6, 10);
    std::cout << "var3_at_0 at 0 : " << var3.Get().At<0>() << std::endl;
    std::cout << "var3_at_0 at 1 : " << var3.Get().At<1>() << std::endl;
    
    auto& var3_at_2 = dynamic_cast<basic::test::Variable<
        basic::test::val::Sequence<int, 1>, char>&>(var3);
    std::cout << "var3_at_2 at 0 : " << var3_at_2.Get().At<0>() << std::endl;

}
