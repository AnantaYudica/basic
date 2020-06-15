#include "test/Variable.h"
#include "test/var/val/Sequence.h"
#include "test/val/Sequence.h"

#include "test/var/At.h"

#include <cstdio>
#include <cstring>
#include <cassert>

#define VALUE1_INT 4
#define VALUE1_CSTR "4"
#define VALUE2_INT 14
#define VALUE2_CSTR "14"
#define VALUE3_INT 44
#define VALUE3_CSTR "44"
#define VALUE4_INT 114
#define VALUE4_CSTR "114"

int main()
{

    basic::test::Variable<
        basic::test::val::Sequence<int, 0>> var0;

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>> var1(VALUE1_INT);

    printf("var1 at 0 : %d\n", var1.Get().template At<0>());
    assert(var1.Get().At<0>() == VALUE1_INT);
    
    const basic::test::Variable<
        basic::test::val::Sequence<int, 1>>&var1_1(var1); 
    printf("var1_1 at 0 : %d\n", var1_1.Get().template At<0>());
    assert(var1_1.Get().At<0>() == VALUE1_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 2>> var2(VALUE1_INT, VALUE2_INT);
    printf("var2 at 0 : %d\n", var2.Get().template At<0>());
    assert(var2.Get().At<0>() == VALUE1_INT);
    printf("var2 at 1 : %d\n", var2.Get().template At<1>());
    assert(var2.Get().At<1>() == VALUE2_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 4>> var3(VALUE1_INT, VALUE2_INT, 
            VALUE3_INT, VALUE4_INT);
    printf("var3 at 0 : %d\n", var3.Get().template At<0>());
    assert(var3.Get().At<0>() == VALUE1_INT);
    printf("var3 at 1 : %d\n", var3.Get().template At<1>());
    assert(var3.Get().At<1>() == VALUE2_INT);
    printf("var3 at 2 : %d\n", var3.Get().template At<2>());
    assert(var3.Get().At<2>() == VALUE3_INT);
    printf("var3 at 3 : %d\n", var3.Get().template At<3>());
    assert(var3.Get().At<3>() == VALUE4_INT);

    basic::test::Variable<
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>,
        basic::test::val::Sequence<int, 1>> var4(VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT);

    printf("At<0>(var4) At 0 : %d\n", basic::test::var::At<0>(var4).
        Get().template At<0>());
    assert(basic::test::var::At<0>(var4).Get().template At<0>() ==
        VALUE1_INT);
    printf("At<1>(var4) At 0 : %d\n", basic::test::var::At<1>(var4).
        Get().template At<0>());
    assert(basic::test::var::At<1>(var4).Get().template At<0>() ==
        VALUE2_INT);
    printf("At<2>(var4) At 0 : %d\n", basic::test::var::At<2>(var4).
        Get().template At<0>());
    assert(basic::test::var::At<2>(var4).Get().template At<0>() ==
        VALUE3_INT);
    printf("At<3>(var4) At 0 : %d\n", basic::test::var::At<3>(var4).
        Get().template At<0>());
    assert(basic::test::var::At<3>(var4).Get().template At<0>() ==
        VALUE4_INT);

}
