#include "test/Variable.h"
#include "test/var/Value.h"

#include "test/var/type/Function.h"
#include "test/var/type/Value.h"
#include "test/var/type/val/Sequence.h"

#include "test/var/val/Function.h"
#include "test/var/val/Sequence.h"
#include "test/var/val/Parameter.h"

#include "test/var/At.h"
#include "test/var/Element.h"

#include <cstdio>
#include <cassert>
#include <typeinfo>

#define FORMAT0_CSTR ""

const char* Foo0()
{
    return FORMAT0_CSTR;
}
#define VALUE_EMPTY_CSTR ""

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

#define CHAR_CSTR "char"
#define SHORT_CSTR "short"
#define INT_CSTR "int"
#define LONG_CSTR "long"
#define CONJ_CSTR ", "

int main()
{
    basic::test::Variable<> var1;

    typedef basic::test::Variable<
        char, /*0*/
        basic::test::type::Parameter<char, short, int, long>, /*1*/
        basic::test::type::Value<int, VALUE1_INT>,  /*2*/
        basic::test::type::val::Sequence<int, VALUE1_INT,
            VALUE2_INT, VALUE3_INT, VALUE4_INT>,  /*3*/
        basic::test::type::Function<const char*(), &Foo0>,  /*4*/
        basic::test::Value<int>,  /*5*/
        basic::test::val::Sequence<int, 4>,  /*6*/
        basic::test::val::Parameter<char, short, int, long>, /*7*/
        basic::test::val::Function<const char*()> /*8*/> Var2;

    Var2 var2(VALUE1_INT, VALUE1_INT, VALUE2_INT, VALUE3_INT, VALUE4_INT, 
        VALUE1_CHAR, VALUE2_SHORT, VALUE3_INT, VALUE4_LONG, &Foo0);

    assert(typeid(typename basic::test::var::Element<0,
        Var2>::Type).hash_code() == typeid(char).hash_code());

    typedef basic::test::type::Parameter<char,
        short, int, long> TypeParam1;
    assert(typeid(typename basic::test::var::Element<1,
        Var2>::Type).hash_code() == typeid(TypeParam1).hash_code());

    typedef basic::test::type::Value<int, VALUE1_INT> TypeVal1;
    assert(typeid(typename basic::test::var::Element<2,
        Var2>::Type).hash_code() == typeid(TypeVal1).hash_code());
    assert(basic::test::var::At<2>(var2).Get().Get() == VALUE1_INT);

    typedef basic::test::type::val::Sequence<int, VALUE1_INT,
        VALUE2_INT, VALUE3_INT, VALUE4_INT> TypeValSeq1;
    assert(typeid(typename basic::test::var::Element<3,
        Var2>::Type).hash_code() == typeid(TypeValSeq1).hash_code());
    assert(basic::test::var::At<3>(var2).Get().template At<0>() == VALUE1_INT);
    assert(basic::test::var::At<3>(var2).Get().template At<1>() == VALUE2_INT);
    assert(basic::test::var::At<3>(var2).Get().template At<2>() == VALUE3_INT);
    assert(basic::test::var::At<3>(var2).Get().template At<3>() == VALUE4_INT);

    typedef basic::test::type::Function<const char*(), &Foo0> TypeFoo1;
    assert(typeid(typename basic::test::var::Element<4,
        Var2>::Type).hash_code() == typeid(TypeFoo1).hash_code());
    assert(basic::test::var::At<4>(var2).Get().Get() == &Foo0);

    typedef basic::test::Value<int> Val1;
    assert(typeid(typename basic::test::var::Element<5,
        Var2>::Type).hash_code() == typeid(Val1).hash_code());
    assert(basic::test::var::At<5>(var2).Get().Get() == VALUE1_INT);

    typedef basic::test::val::Sequence<int, 4> ValSeq1;
    assert(typeid(typename basic::test::var::Element<6,
        Var2>::Type).hash_code() == typeid(ValSeq1).hash_code());
    assert(basic::test::var::At<6>(var2).Get().template At<0>() == VALUE1_INT);
    assert(basic::test::var::At<6>(var2).Get().template At<1>() == VALUE2_INT);
    assert(basic::test::var::At<6>(var2).Get().template At<2>() == VALUE3_INT);
    assert(basic::test::var::At<6>(var2).Get().template At<3>() == VALUE4_INT);

    typedef basic::test::val::Parameter<char, short, int, long> ValParam1;
    assert(typeid(typename basic::test::var::Element<7,
        Var2>::Type).hash_code() == typeid(ValParam1).hash_code());
    assert(basic::test::var::At<7>(var2).Get().template At<0>() == 
        VALUE1_CHAR);
    assert(basic::test::var::At<7>(var2).Get().template At<1>() == 
        VALUE2_SHORT);
    assert(basic::test::var::At<7>(var2).Get().template At<2>() == 
        VALUE3_INT);
    assert(basic::test::var::At<7>(var2).Get().template At<3>() == 
        VALUE4_LONG);

    typedef basic::test::val::Function<const char*()> ValFoo1;
    assert(typeid(typename basic::test::var::Element<8,
        Var2>::Type).hash_code() == typeid(ValFoo1).hash_code());
    assert(basic::test::var::At<8>(var2).Get().Get() == &Foo0);
}
