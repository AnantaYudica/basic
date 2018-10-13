#include "test/Variable.h"
#include "test/var/type/Value.h"
#include "test/type/Value.h"

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
        basic::test::type::Value<int, VALUE1_INT>> var1;
    assert(var1.Get().Get() == VALUE1_INT);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE1_INT>,
        basic::test::type::Value<int, VALUE2_INT>> var2;
    assert(var2.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var2).Get().Get() == VALUE2_INT);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE1_INT>,
        basic::test::type::Value<int, VALUE2_INT>,
        basic::test::type::Value<int, VALUE3_INT>> var3;
    assert(var3.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var3).Get().Get() == VALUE2_INT);
    assert(basic::test::var::At<2>(var3).Get().Get() == VALUE3_INT);

    basic::test::Variable<
        basic::test::type::Value<int, VALUE1_INT>,
        basic::test::type::Value<int, VALUE2_INT>,
        basic::test::type::Value<int, VALUE3_INT>,
        basic::test::type::Value<int, VALUE4_INT>> var4;
    assert(var4.Get().Get() == VALUE1_INT);
    assert(basic::test::var::At<1>(var4).Get().Get() == VALUE2_INT);
    assert(basic::test::var::At<2>(var4).Get().Get() == VALUE3_INT);
    assert(basic::test::var::At<3>(var4).Get().Get() == VALUE4_INT);
}
