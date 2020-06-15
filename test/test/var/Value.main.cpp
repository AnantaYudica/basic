#include "test/Variable.h"
#include "test/var/Value.h"
#include "test/Value.h"

#include "test/var/At.h"

#include <cstdio>
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
        basic::test::Value<int>> var1(VALUE1_INT);
    assert(var1.Get().Get() == VALUE1_INT);

    basic::test::Variable<
        basic::test::Value<int>,
        basic::test::Value<int>> var2(VALUE1_INT, VALUE2_INT);
    assert(var2.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var2).Get().Get() == VALUE2_INT);

    basic::test::Variable<
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>> var3(VALUE1_INT, VALUE2_INT,
            VALUE3_INT);
    assert(var3.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var3).Get().Get() == VALUE2_INT);
    assert(basic::test::var::At<2>(var3).Get().Get() == VALUE3_INT);

    basic::test::Variable<
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>,
        basic::test::Value<int>> var4(VALUE1_INT, VALUE2_INT,
            VALUE3_INT, VALUE4_INT);
    assert(var4.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var4).Get().Get() == VALUE2_INT);
    assert(basic::test::var::At<2>(var4).Get().Get() == VALUE3_INT);
    assert(basic::test::var::At<3>(var4).Get().Get() == VALUE4_INT);
}
