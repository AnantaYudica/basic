#include "Test.h"

#include "test/type/Index.h"
#include <cstdio>
#include <cassert>
#include <typeinfo>

int main()
{
    typedef basic::test::type::Index<char, 0> CharAt0;
    printf("%s %zd\n", typeid(typename CharAt0::Type).name(),
        CharAt0::Value);
    assert(typeid(char).hash_code() == 
        typeid(typename CharAt0::Type).hash_code());
    assert(CharAt0::Value == 0);

    typedef basic::test::type::Index<short, 1> ShortAt1;
    printf("%s %zd\n", typeid(typename ShortAt1::Type).name(),
        ShortAt1::Value);
    assert(typeid(short).hash_code() ==
        typeid(typename ShortAt1::Type).hash_code());
    assert(ShortAt1::Value == 1);

    typedef basic::test::type::Index<int, 2> IntAt2;
    printf("%s %zd\n", typeid(typename IntAt2::Type).name(),
        IntAt2::Value);
    assert(typeid(int).hash_code() ==
        typeid(typename IntAt2::Type).hash_code());
    assert(IntAt2::Value == 2);

    typedef basic::test::type::Index<long, 3> LongAt3;
    printf("%s %zd\n", typeid(typename LongAt3::Type).name(),
        LongAt3::Value);
    assert(typeid(long).hash_code() ==
        typeid(typename LongAt3::Type).hash_code());
    assert(LongAt3::Value == 3);
}
