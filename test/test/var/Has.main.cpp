#include "test/var/Has.h"
#include "test/Variable.h"

#include "test/var/Value.h"

#include "test/var/type/Function.h"
#include "test/var/type/Value.h"
#include "test/var/type/val/Sequence.h"

#include "test/var/val/Function.h"
#include "test/var/val/Sequence.h"
#include "test/var/val/Parameter.h"

#include <cstdio>
#include <cassert>
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

void Foo1()
{}

int main()
{
    typedef basic::test::Variable<
        int, 
        basic::test::type::Function<void(), &Foo1>,
        basic::test::type::Value<int, VALUE1_INT>,
        basic::test::type::val::Sequence<int, VALUE1_INT>,
        basic::test::Value<int>,
        basic::test::val::Function<void()>,
        basic::test::val::Parameter<int, int, int>,
        basic::test::val::Sequence<int,0>> Var1;

    typedef basic::test::var::Has<0, Var1> HasVar1At0;
    assert(HasVar1At0::LValue == false);
    assert(HasVar1At0::RValue == false);
    assert(HasVar1At0::Value == false);

    typedef basic::test::var::Has<1, Var1> HasVar1At1;
    assert(HasVar1At1::LValue == false);
    assert(HasVar1At1::RValue == true);
    assert(HasVar1At1::Value == true);

    typedef basic::test::var::Has<2, Var1> HasVar1At2;
    assert(HasVar1At2::LValue == false);
    assert(HasVar1At2::RValue == true);
    assert(HasVar1At2::Value == true);

    typedef basic::test::var::Has<3, Var1> HasVar1At3;
    assert(HasVar1At3::LValue == false);
    assert(HasVar1At3::RValue == true);
    assert(HasVar1At3::Value == true);

    typedef basic::test::var::Has<4, Var1> HasVar1At4;
    assert(HasVar1At4::LValue == true);
    assert(HasVar1At4::RValue == true);
    assert(HasVar1At4::Value == true);

    typedef basic::test::var::Has<5, Var1> HasVar1At5;
    assert(HasVar1At5::LValue == true);
    assert(HasVar1At5::RValue == true);
    assert(HasVar1At5::Value == true);

    typedef basic::test::var::Has<6, Var1> HasVar1At6;
    assert(HasVar1At6::LValue == true);
    assert(HasVar1At6::RValue == true);
    assert(HasVar1At6::Value == true);

    typedef basic::test::var::Has<7, Var1> HasVar1At7;
    assert(HasVar1At7::LValue == true);
    assert(HasVar1At7::RValue == true);
    assert(HasVar1At7::Value == true);
}
