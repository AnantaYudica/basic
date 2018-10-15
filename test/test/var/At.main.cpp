#include "test/Variable.h"
#include "test/var/At.h"

#include <cstdio>
#include <cassert>
#include <typeinfo>

int main()
{
    typedef basic::test::Variable<char> Var1;
    typedef basic::test::Variable<char, short> Var2;
    typedef basic::test::Variable<char, short, int> Var3;
    typedef basic::test::Variable<char, short, int, long> Var4;

    Var1 var1;
    assert(&basic::test::var::At<0>(var1) ==
        dynamic_cast<Var1*>(&var1));

    const Var1& var1_1 = var1;
    assert(&basic::test::var::At<0>(var1_1) ==
        dynamic_cast<const Var1*>(&var1_1));

    Var2 var2;
    typedef basic::test::Variable<short> Var2_1;
    assert(&basic::test::var::At<0>(var2) ==
        dynamic_cast<Var2*>(&var2));
    assert(&basic::test::var::At<1>(var2) ==
        dynamic_cast<Var2_1*>(&var2));

    Var3 var3;
    typedef basic::test::Variable<short, int> Var3_1;
    typedef basic::test::Variable<int> Var3_2;
    assert(&basic::test::var::At<0>(var3) ==
        dynamic_cast<Var3*>(&var3));
    assert(&basic::test::var::At<1>(var3) ==
        dynamic_cast<Var3_1*>(&var3));
    assert(&basic::test::var::At<2>(var3) ==
        dynamic_cast<Var3_2*>(&var3));

    Var4 var4;
    typedef basic::test::Variable<short, int, long> Var4_1;
    typedef basic::test::Variable<int, long> Var4_2;
    typedef basic::test::Variable<long> Var4_3;
    assert(&basic::test::var::At<0>(var4) ==
        dynamic_cast<Var4*>(&var4));
    assert(&basic::test::var::At<1>(var4) ==
        dynamic_cast<Var4_1*>(&var4));
    assert(&basic::test::var::At<2>(var4) ==
        dynamic_cast<Var4_2*>(&var4));
    assert(&basic::test::var::At<3>(var4) ==
        dynamic_cast<Var4_3*>(&var4));

}