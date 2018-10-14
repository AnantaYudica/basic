#include "test/var/Element.h"
#include "test/Variable.h"

#include <cstdio>
#include <cassert>
#include <typeinfo>

int main()
{
    typedef basic::test::Variable<char> TVar1;

    assert(typeid(char).hash_code() ==
        typeid(typename basic::test::var::
            Element<0, TVar1>::Type).hash_code());

    typedef basic::test::Variable<char, short> TVar2;
    assert(typeid(char).hash_code() ==
        typeid(typename basic::test::var::
            Element<0, TVar2>::Type).hash_code());
    assert(typeid(short).hash_code() ==
        typeid(typename basic::test::var::
            Element<1, TVar2>::Type).hash_code());

    typedef basic::test::Variable<char, short, int> TVar3;
    assert(typeid(char).hash_code() ==
        typeid(typename basic::test::var::
            Element<0, TVar3>::Type).hash_code());
    assert(typeid(short).hash_code() ==
        typeid(typename basic::test::var::
            Element<1, TVar3>::Type).hash_code());
    assert(typeid(int).hash_code() ==
        typeid(typename basic::test::var::
            Element<2, TVar3>::Type).hash_code());

    typedef basic::test::Variable<char, short, int, long> TVar4;
    assert(typeid(char).hash_code() ==
        typeid(typename basic::test::var::
            Element<0, TVar4>::Type).hash_code());
    assert(typeid(short).hash_code() ==
        typeid(typename basic::test::var::
            Element<1, TVar4>::Type).hash_code());
    assert(typeid(int).hash_code() ==
        typeid(typename basic::test::var::
            Element<2, TVar4>::Type).hash_code());
    assert(typeid(long).hash_code() ==
        typeid(typename basic::test::var::
            Element<3, TVar4>::Type).hash_code());

}