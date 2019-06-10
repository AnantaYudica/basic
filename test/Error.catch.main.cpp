
#include "Error.test.h"

#include "err/tag/Catch.h"

#include <utility>

BASIC_TEST_TYPE_NAME("basic::err::tag::Catch", basic::err::tag::Catch<>);
BASIC_TEST_TYPE_NAME("basic::err::tag::Trigger", basic::err::tag::Trigger);

typedef basic::test::type::Parameter<
    TestBaseOfTrigger,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasTriggerType,
    TestAliasIdType,
    TestAliasInfoType,
    TestValueMessage,
    TestValueTrigger,
    TestValueOutput> Case1;

typedef VariableTestError<basic::err::tag::Catch<>, 
    basic::err::defn::type::code::Value,
    basic::Error<basic::err::tag::Trigger>> T1Var1;

basic::Error<basic::err::tag::Trigger> trr1;
basic::Error<basic::err::tag::Trigger> trr2{4};
basic::err::id::Catch id2{10};
basic::Error<basic::err::tag::Catch<>> err1;
basic::Error<basic::err::tag::Catch<>> err2{trr2, id2};
basic::Error<basic::err::tag::Catch<>> err3{err2};
basic::Error<basic::err::tag::Catch<>> err4{err3};
basic::Error<basic::err::tag::Catch<>> err5{std::move(err4)};
const char * msg1 = "";
const char * msg2 = "";
basic::err::Information info1;
basic::err::Information info2{id2};
const char * out1 = "";
const char * out2 = "in catch ";

T1Var1 t1_var1{&err1, msg1, &info1, nullptr, nullptr, &trr1, out1};
T1Var1 t1_var2{&err2, msg2, &info2, nullptr, nullptr, &trr2, out2};
T1Var1 t1_var3{&err3, msg2, &info2, nullptr, nullptr, &trr2, out2};
T1Var1 t1_var4{&err4, msg2, &info2, nullptr, nullptr, &trr2, out2};
T1Var1 t1_var5{&err5, msg2, &info2, nullptr, nullptr, &trr2, out2};

REGISTER_TEST(t1, new TestError<Case1, T1Var1, T1Var1, T1Var1, 
    T1Var1, T1Var1>(t1_var1, t1_var2, t1_var3, t1_var4, t1_var5));

int main()
{
    return RUN_TEST();
}
