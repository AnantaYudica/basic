#define USING_BASIC_TEST_MEMORY
#define USING_BASIC_ERR_EXCEPTION
#include "Exception.test.h"

BASIC_TEST_CONSTRUCT;

BASIC_TEST_TYPE_NAME("basic::err::Exception", basic::err::Exception);

const char * exception_name = "basic::err::Exception";

using Case1 = basic::test::type::Parameter<TestBaseOfT>;
using Case2 = basic::test::type::Parameter<TestSameOfT>;
using Case3 = basic::test::type::Parameter<TestAliasTriggerType,
    TestAliasCharType, TestAliasOutputType>;
using Case4 = basic::test::type::Parameter<TestCallConstructor,
    TestValueMessage, TestValueIntfOutput>;
using Case5 = basic::test::type::Parameter<TestCallCopyConstructor,
    TestValueMessage, TestValueIntfOutput>;
using Case6 = basic::test::type::Parameter<TestCallMoveConstructor,
    TestValueMessage, TestValueIntfOutput>;
using Case7 = basic::test::type::Parameter<
    TestValueMessage, TestValueIntfOutput>;

template<typename TSameOrBaseOf, typename ... TArgs>
using T1_2Var = VariableTestException<basic::err::Exception, 
    TSameOrBaseOf,
    basic::err::Identification,
    basic::Error<basic::err::tag::Trigger>,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::intf::Output,
    TArgs...>;

template<typename ... TArgs>
using TVar = VariableTestException<basic::err::Exception, 
    void,
    basic::err::Identification,
    basic::Error<basic::err::tag::Trigger>,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::intf::Output,
    TArgs...>;

T1_2Var<basic::Error<basic::err::tag::Trigger>> t1var1{nullptr, 
    nullptr, exception_name, nullptr, nullptr, nullptr};

REGISTER_TEST(t1, new TestException<Case1, 
    T1_2Var<basic::Error<basic::err::tag::Trigger>>>(t1var1));

T1_2Var<basic::err::Exception> t2var1{nullptr, 
    nullptr, exception_name, nullptr, nullptr, nullptr};

REGISTER_TEST(t2, new TestException<Case2, 
    T1_2Var<basic::err::Exception>>(t2var1));

TVar<> t3var1{nullptr, nullptr, exception_name, nullptr, nullptr, nullptr};

REGISTER_TEST(t3, new TestException<Case3, TVar<>>(t3var1));

basic::err::Exception e4_var1;
const char * msg4_var1 = "Exception";
const char * output4_var1 = "Exception id 0x000001";

TVar<> t4var1{&e4_var1, nullptr, exception_name, msg4_var1,
    output4_var1, nullptr};

REGISTER_TEST(t4, new TestException<Case4, TVar<>>(t4var1));

basic::err::Exception e5_var1;

TVar<> t5var1{&e5_var1, &e4_var1, exception_name, msg4_var1, 
    output4_var1, nullptr};

REGISTER_TEST(t5, new TestException<Case5, TVar<>>(t5var1));

basic::err::Exception e6_var1;

TVar<> t6var1{&e6_var1, &e5_var1, exception_name, msg4_var1, 
    output4_var1, nullptr};

REGISTER_TEST(t6, new TestException<Case6, TVar<>>(t6var1));

TVar<> t7var1{&e5_var1, nullptr, exception_name, msg4_var1, 
    output4_var1, nullptr};

REGISTER_TEST(t7, new TestException<Case7, TVar<>>(t7var1));

int main()
{
    return RUN_TEST();
}