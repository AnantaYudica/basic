#define USING_STANDARD_EXCEPTION
#define USING_EXCEPTION
#define USING_BASIC_TEST_MEMORY

#include "Exception.test.h"

BASIC_TEST_CONSTRUCT;

BASIC_TEST_TYPE_NAME("std::exception", std::exception);

const char * exception_name = "basic::err::Exception";

using Case1 = basic::test::type::Parameter<TestSameOfT>;

using Case2 = basic::test::type::Parameter<TestValueIdGet>;

template<typename TSameOrBaseOf, typename ... TArgs>
using T1Var = VariableTestException<
    basic::err::Exception, 
    TSameOrBaseOf,
    basic::err::Identification,
    void,
    basic::err::defn::type::Char,
    void,
    void,
    TArgs...>;

template<typename ... TArgs>
using TVar = VariableTestException<
    basic::err::Exception, 
    void,
    basic::err::Identification,
    void,
    basic::err::defn::type::Char,
    void,
    void,
    TArgs...>;

T1Var<std::exception> t1var1{nullptr, nullptr, exception_name, nullptr, 
    nullptr, nullptr};

REGISTER_TEST(t1, new TestException<Case1, T1Var<std::exception>>(t1var1));

std::exception e2_1;
basic::err::Identification id2_1{
    basic::err::id::flag::Standard(), basic::defn::err::exception_id};

TVar<> t2var1{&e2_1, nullptr, exception_name, nullptr, 
    nullptr, &id2_1};

REGISTER_TEST(t2, new TestException<Case2, TVar<>>(t2var1));

int main()
{
    return RUN_TEST();
}
