
#include "Error.test.h"

#include "err/tag/System.h"

#include <utility>

BASIC_TEST_TYPE_NAME("basic::err::tag::System", basic::err::tag::System);

typedef basic::test::type::Parameter<
    TestBaseOfInformation,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasCategoryValueType,
    TestAliasCodeValueType,
    TestAliasIdType,
    TestAliasInfoType,
    TestValueMessage,
    TestValueCategory,
    TestValueCode,
    TestValueOutput> Case1;

typedef VariableTestError<basic::err::tag::System,
    basic::err::defn::type::sys::code::Value> T1Var1;

basic::err::id::System id2{10, 4};
basic::Error<basic::err::tag::System> err1;
basic::Error<basic::err::tag::System> err2{id2};
basic::Error<basic::err::tag::System> err3{err2};
basic::Error<basic::err::tag::System> err4{err3};
basic::Error<basic::err::tag::System> err5{std::move(err4)};
const char * msg1 = "";
const char * msg2 = "";
basic::err::Information info1;
basic::err::Information info2{id2};
basic::err::defn::type::sys::categ::Value categ1;
basic::err::defn::type::sys::categ::Value categ2{10};
basic::err::defn::type::sys::code::Value code1;
basic::err::defn::type::sys::code::Value code2{4};
const char * out1 = "";
const char * out2 = "id 0x100A0004";

T1Var1 t1_var1{&err1, msg1, &info1, &categ1, &code1, nullptr, out1};
T1Var1 t1_var2{&err2, msg2, &info2, &categ2, &code2, nullptr, out2};
T1Var1 t1_var3{&err3, msg2, &info2, &categ2, &code2, nullptr, out2};
T1Var1 t1_var4{&err4, msg2, &info2, &categ2, &code2, nullptr, out2};
T1Var1 t1_var5{&err5, msg2, &info2, &categ2, &code2, nullptr, out2};

REGISTER_TEST(t1, new TestError<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    return RUN_TEST();
}
