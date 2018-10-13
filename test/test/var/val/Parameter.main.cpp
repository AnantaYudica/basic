#include "test/Variable.h"
#include "test/var/val/Parameter.h"
#include "test/val/Parameter.h"

#include "test/var/At.h"

#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include <cstdio>
#include <cassert>
#include <cstring>
#include <typeinfo>

#define VALUE1_INT 4
#define VALUE1_CHAR '4'
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_SHORT short(14)
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_LONG 114
#define VALUE4_CSTR "114"

int main()
{
    basic::test::Variable<
        basic::test::val::Parameter<char>> var1(VALUE1_CHAR);
    assert(var1.Get().template At<0>() == VALUE1_CHAR);
    const basic::test::Variable<
        basic::test::val::Parameter<char>>& var1_1(var1);
    assert(var1_1.Get().template At<0>() == VALUE1_CHAR);

    basic::test::Variable<
        basic::test::val::Parameter<char>,
        basic::test::val::Parameter<short>> var2(VALUE1_CHAR, VALUE2_SHORT);
    assert(var2.Get().template At<0>() == VALUE1_CHAR);
    assert(basic::test::var::At<1>(var2).Get().
        template At<0>() == VALUE2_SHORT);

    basic::test::Variable<
        basic::test::val::Parameter<char>,
        basic::test::val::Parameter<short>,
        basic::test::val::Parameter<int>> var3(VALUE1_CHAR, VALUE2_SHORT,
            VALUE3_INT);
    assert(var3.Get().template At<0>() == VALUE1_CHAR);
    assert(basic::test::var::At<1>(var3).Get().
        template At<0>() == VALUE2_SHORT);
    assert(basic::test::var::At<2>(var3).Get().
        template At<0>() == VALUE3_INT);

    basic::test::Variable<
        basic::test::val::Parameter<char>,
        basic::test::val::Parameter<short>,
        basic::test::val::Parameter<int>,
        basic::test::val::Parameter<long>> var4(VALUE1_CHAR, VALUE2_SHORT,
            VALUE3_INT, VALUE4_LONG);
    assert(var4.Get().template At<0>() == VALUE1_CHAR);
    assert(basic::test::var::At<1>(var4).Get().
        template At<0>() == VALUE2_SHORT);
    assert(basic::test::var::At<2>(var4).Get().
        template At<0>() == VALUE3_INT);
    assert(basic::test::var::At<3>(var4).Get().
        template At<0>() == VALUE4_LONG);

}
