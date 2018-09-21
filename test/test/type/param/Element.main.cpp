#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/param/Element.h"

#include <cassert>
#include <cstdio>
#include <typeinfo>

int main()
{
    typedef basic::test::type::Parameter<char, short, 
        int, long, long long> TInteger;

    typedef typename basic::test::type::param::Element<0, TInteger>::type
        TIntegerIndex0A;
    typedef typename basic::test::type::param::Element<0, TInteger>::Type
        TIntegerIndex0B;
    printf("%s == %s?\n", typeid(char).name(), typeid(TIntegerIndex0A).name());
    assert(typeid(char).hash_code() == typeid(TIntegerIndex0A).hash_code());
    printf("%s == %s?\n", typeid(TIntegerIndex0A).name(), 
        typeid(TIntegerIndex0B).name());
    assert(typeid(TIntegerIndex0A).hash_code() == 
        typeid(TIntegerIndex0B).hash_code());
    
    typedef typename basic::test::type::param::Element<1, TInteger>::type
        TIntegerIndex1A;
    typedef typename basic::test::type::param::Element<1, TInteger>::Type
        TIntegerIndex1B;
    printf("%s == %s?\n", typeid(short).name(), typeid(TIntegerIndex1A).name());
    assert(typeid(short).hash_code() == typeid(TIntegerIndex1A).hash_code());
    printf("%s == %s?\n", typeid(TIntegerIndex1A).name(), 
        typeid(TIntegerIndex1B).name());
    assert(typeid(TIntegerIndex1A).hash_code() == 
        typeid(TIntegerIndex1B).hash_code());
    
    typedef typename basic::test::type::param::Element<2, TInteger>::type
        TIntegerIndex2A;
    typedef typename basic::test::type::param::Element<2, TInteger>::Type
        TIntegerIndex2B;
    printf("%s == %s?\n", typeid(int).name(), typeid(TIntegerIndex2A).name());
    assert(typeid(int).hash_code() == typeid(TIntegerIndex2A).hash_code());
    printf("%s == %s?\n", typeid(TIntegerIndex2A).name(), 
        typeid(TIntegerIndex2B).name());
    assert(typeid(TIntegerIndex2A).hash_code() == 
        typeid(TIntegerIndex2B).hash_code());
        
    typedef typename basic::test::type::param::Element<4, TInteger>::type
        TIntegerIndex4A;
    typedef typename basic::test::type::param::Element<4, TInteger>::Type
        TIntegerIndex4B;
    printf("%s == %s?\n", typeid(long long).name(), 
        typeid(TIntegerIndex4A).name());
    assert(typeid(long long).hash_code() == 
        typeid(TIntegerIndex4A).hash_code());
    printf("%s == %s?\n", typeid(TIntegerIndex4A).name(), 
        typeid(TIntegerIndex4B).name());
    assert(typeid(TIntegerIndex4A).hash_code() == 
        typeid(TIntegerIndex4B).hash_code());
}
