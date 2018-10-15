#include "test/var/Definition.h"
#include "test/Variable.h"

#include <cstdio>
#include <cassert>
#include <typeinfo>

int main()
{
    typedef basic::test::Variable<> TVar0;
    typedef basic::test::Variable<char> TVar1;
    typedef basic::test::Variable<char, short> TVar2;
    typedef basic::test::Variable<char, short, int> TVar3;
    typedef basic::test::Variable<char, short, int, long> TVar4;

    typedef basic::test::var::Definition<0, TVar0> DefTVar0At0;
    assert(typeid(TVar0).hash_code() == 
        typeid(typename DefTVar0At0::Type).hash_code());

    typedef basic::test::var::Definition<0, TVar1> DefTVar1At0;
    typedef basic::test::var::Definition<1, TVar1> DefTVar1At1;
    assert(typeid(TVar1).hash_code() ==
        typeid(typename DefTVar1At0::Type).hash_code());
    assert(typeid(TVar0).hash_code() ==
        typeid(typename DefTVar1At1::Type).hash_code());

    typedef basic::test::var::Definition<0, TVar2> DefTVar2At0;
    typedef basic::test::var::Definition<1, TVar2> DefTVar2At1;
    typedef basic::test::var::Definition<2, TVar2> DefTVar2At2;
    typedef basic::test::Variable<short> TVar2_1;
    assert(typeid(TVar2).hash_code() ==
        typeid(typename DefTVar2At0::Type).hash_code());
    assert(typeid(TVar2_1).hash_code() ==
        typeid(typename DefTVar2At1::Type).hash_code());
    assert(typeid(TVar0).hash_code() ==
        typeid(typename DefTVar2At2::Type).hash_code());

    typedef basic::test::var::Definition<0, TVar3> DefTVar3At0;
    typedef basic::test::var::Definition<1, TVar3> DefTVar3At1;
    typedef basic::test::var::Definition<2, TVar3> DefTVar3At2;
    typedef basic::test::var::Definition<3, TVar3> DefTVar3At3;
    typedef basic::test::Variable<short, int> TVar3_1;
    typedef basic::test::Variable<int> TVar3_2;
    assert(typeid(TVar3).hash_code() ==
        typeid(typename DefTVar3At0::Type).hash_code());
    assert(typeid(TVar3_1).hash_code() ==
        typeid(typename DefTVar3At1::Type).hash_code());
    assert(typeid(TVar3_2).hash_code() ==
        typeid(typename DefTVar3At2::Type).hash_code());
    assert(typeid(TVar0).hash_code() ==
        typeid(typename DefTVar3At3::Type).hash_code());

    typedef basic::test::var::Definition<0, TVar4> DefTVar4At0;
    typedef basic::test::var::Definition<1, TVar4> DefTVar4At1;
    typedef basic::test::var::Definition<2, TVar4> DefTVar4At2;
    typedef basic::test::var::Definition<3, TVar4> DefTVar4At3;
    typedef basic::test::var::Definition<4, TVar4> DefTVar4At4;
    typedef basic::test::Variable<short, int, long> TVar4_1;
    typedef basic::test::Variable<int, long> TVar4_2;
    typedef basic::test::Variable<long> TVar4_3;
    assert(typeid(TVar4).hash_code() ==
        typeid(typename DefTVar4At0::Type).hash_code());
    assert(typeid(TVar4_1).hash_code() ==
        typeid(typename DefTVar4At1::Type).hash_code());
    assert(typeid(TVar4_2).hash_code() ==
        typeid(typename DefTVar4At2::Type).hash_code());
    assert(typeid(TVar4_3).hash_code() ==
        typeid(typename DefTVar4At3::Type).hash_code());
    assert(typeid(TVar0).hash_code() ==
        typeid(typename DefTVar4At4::Type).hash_code());
}
