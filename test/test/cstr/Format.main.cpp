#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/cstr/Format.h"

#include <cstdio>
#include <cstring>
#include <cassert>

#define VALUE_FORMAT_CSTR "format test"

#define VALUE_LONG 123456789L

#define VALUE_CSTR "123456789"
#define VALUE0_CSTR ""
#define VALUE4_CSTR "1234"

#define VALUE_A_CSTR "test1"
#define VALUE_B_INT 4
#define VALUE_B_CSTR "4"

int main()
{
    auto cstr1 = basic::test::cstr::Format(sizeof(VALUE_FORMAT_CSTR), 
        VALUE_FORMAT_CSTR);
    printf("cstr1 : \"%s\"\n", *cstr1);
    assert(strcmp(*cstr1, VALUE_FORMAT_CSTR) == 0);

    auto cstr2 = basic::test::cstr::Format(11, "%ld", VALUE_LONG);
    printf("cstr2 : \"%s\"\n", *cstr2);
    assert(strcmp(*cstr2, VALUE_CSTR) == 0);

    auto cstr3 = basic::test::cstr::Format(0, "%ld", VALUE_LONG);
    printf("cstr3 : \"%s\"\n", *cstr3);
    assert(strcmp(*cstr3, VALUE0_CSTR) == 0);

    auto cstr4 = basic::test::cstr::Format(5, "%ld", VALUE_LONG);
    printf("cstr4 : \"%s\"\n", *cstr4);
    assert(strcmp(*cstr4, VALUE4_CSTR) == 0);

    auto cstr5 = basic::test::cstr::Format(10, "%s%d", VALUE_A_CSTR, 
        VALUE_B_INT);
    printf("cstr5 : \"%s\"\n", *cstr5);
    assert(strcmp(*cstr5, VALUE_A_CSTR VALUE_B_CSTR) == 0);
}