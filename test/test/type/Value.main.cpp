#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/type/Value.h"

#include <cstdio>

int main()
{
    typedef basic::test::type::Value<int, 4> ValueInt4;
    ValueInt4 i1;

    printf("%d\n", ValueInt4{}.Get());
}
