#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/param/Element.h"

#include <cassert>
#include <cstdio>
#include <typeinfo>

template<typename... TArgs>
struct Param1 {};

int main()
{
    typedef basic::test::type::Parameter<char, short, 
        int, long, long long> TInteger;

    typedef typename basic::test::type::param::Element<0, TInteger>::Type
        TIntegerIndex0A;
    printf("%s == %s?\n", typeid(char).name(), typeid(TIntegerIndex0A).name());
    assert(typeid(char).hash_code() == typeid(TIntegerIndex0A).hash_code());
    
    typedef typename basic::test::type::param::Element<1, TInteger>::Type
        TIntegerIndex1A;
    printf("%s == %s?\n", typeid(short).name(), typeid(TIntegerIndex1A).name());
    assert(typeid(short).hash_code() == typeid(TIntegerIndex1A).hash_code());
    
    typedef typename basic::test::type::param::Element<2, TInteger>::Type
        TIntegerIndex2A;
    printf("%s == %s?\n", typeid(int).name(), typeid(TIntegerIndex2A).name());
    assert(typeid(int).hash_code() == typeid(TIntegerIndex2A).hash_code());
        
    typedef typename basic::test::type::param::Element<4, TInteger>::Type
        TIntegerIndex4A;
    printf("%s == %s?\n", typeid(long long).name(), 
        typeid(TIntegerIndex4A).name());
    assert(typeid(long long).hash_code() == 
        typeid(TIntegerIndex4A).hash_code());

    typedef Param1<char, short, int, long> P1;
    typedef typename basic::test::type::param::Element<0, P1>::Type
        P1_I0;
    printf("%s == %s?\n", typeid(char).name(), typeid(P1_I0).name());
    assert(typeid(char).hash_code() == typeid(P1_I0).hash_code());
    
    typedef typename basic::test::type::param::Element<1, P1>::Type
        P1_I1;
    printf("%s == %s?\n", typeid(short).name(), typeid(P1_I1).name());
    assert(typeid(short).hash_code() == typeid(P1_I1).hash_code());
    
    typedef typename basic::test::type::param::Element<2, P1>::Type
        P1_I2;
    printf("%s == %s?\n", typeid(int).name(), typeid(P1_I2).name());
    assert(typeid(int).hash_code() == typeid(P1_I2).hash_code());

    typedef typename basic::test::type::param::Element<3, P1>::Type
        P1_I3;
    printf("%s == %s?\n", typeid(long).name(), typeid(P1_I3).name());
    assert(typeid(long).hash_code() == typeid(P1_I3).hash_code());
}
