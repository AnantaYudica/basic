
#include "Error.test.h"

#include "err/tag/Trigger.h"

#include <utility>

BASIC_TEST_TYPE_NAME("basic::err::tag::Trigger", basic::err::tag::Trigger);

typedef basic::test::type::Parameter<
    TestBaseOfInformation,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasCodeValueType,
    TestAliasIdType,
    TestAliasInfoType,
    TestValueMessage,
    TestValueCode,
    TestValueOutput> Case1;

typedef VariableTestError<basic::err::tag::Trigger> T1Var1;

basic::err::Identification id2{4};
basic::Error<basic::err::tag::Trigger> err1;
basic::Error<basic::err::tag::Trigger> err2{id2};
basic::Error<basic::err::tag::Trigger> err3{err2};
basic::Error<basic::err::tag::Trigger> err4{err3};
basic::Error<basic::err::tag::Trigger> err5{std::move(err4)};
const char * msg1 = "";
const char * msg2 = "";
basic::err::Information info1;
basic::err::Information info2{id2};
basic::err::defn::type::code::Value code1;
basic::err::defn::type::code::Value code2{4};
const char * out1 = "";
const char * out2 = "id 0x000004";

T1Var1 t1_var1{&err1, msg1, &info1, nullptr, &code1, nullptr, out1};
T1Var1 t1_var2{&err2, msg2, &info2, nullptr, &code2, nullptr, out2};
T1Var1 t1_var3{&err3, msg2, &info2, nullptr, &code2, nullptr, out2};
T1Var1 t1_var4{&err4, msg2, &info2, nullptr, &code2, nullptr, out2};
T1Var1 t1_var5{&err5, msg2, &info2, nullptr, &code2, nullptr, out2};

REGISTER_TEST(t1, new TestError<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    return RUN_TEST();
}
