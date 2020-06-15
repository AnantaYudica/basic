#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Message.h"

#include <cstdio>
#include <cstring>
#include <cstddef>
#include <type_traits>
#include <sstream>

#define BUFFER_FORMAT_CSTRING 256

struct TestReturnValue {};

template<typename TError>
using VariableTestMessage = basic::test::Variable<
    TError,
    const char *,
    basic::test::Value<TError *>,
    basic::test::Value<const char *>>;

enum : std::size_t
{
    IErrorType,
    IReturnType,
    IErrorValue,
    IReturnValue
};

typedef basic::test::msg::Argument<TestReturnValue,
    basic::test::msg::arg::type::Name<IReturnType>,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::Value<IReturnValue>>
        ArgTestReturnValue;

typedef basic::test::msg::Base<TestReturnValue, char, 
    ArgTestReturnValue, ArgTestReturnValue, 
    ArgTestReturnValue> MessageBaseTestReturnValue;


template<typename TCases, typename... TVariables>
struct TestMessage :
    public basic::test::Message<BASIC_TEST, TestMessage<TCases, 
        TVariables...>>,
    public basic::test::Case<TestMessage<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestMessage<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestReturnValue
{
public:
    using basic::test::Case<TestMessage<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestMessage<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestReturnValue::Format;
    using MessageBaseTestReturnValue::SetFormat;
    using MessageBaseTestReturnValue::Argument;
public:
    TestMessage(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestMessage<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestMessage<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestMessage<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestReturnValue testReturnValue;
        SetFormat(info, testReturnValue, "Test return value of function %s "
            "basic::err::Message(%s) is same \"%s\"\n");
        SetFormat(debug, testReturnValue, "Test return value of function %s "
            "basic::err::Message(%s) is same \"%s\"\n");
        SetFormat(err, testReturnValue, "Error Test return value of "
            "function %s basic::err::Message(%s) is not same \"%s\"\n");
    }
    template<typename... TArgs>
    bool Result(const TestReturnValue &, basic::test::Variable<TArgs...> & var)
    {
        auto * error = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * ret_val = basic::test::var::At<IReturnValue>(var).Get().Get();
        return strcmp(basic::err::Message(*error), ret_val) == 0;
    }
};

BASIC_TEST_TYPE_NAME("signed char", signed char);
BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);
BASIC_TEST_TYPE_NAME("short", short);
BASIC_TEST_TYPE_NAME("unsigned short", unsigned short);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("unsigned int", unsigned int);
BASIC_TEST_TYPE_NAME("long", long);
BASIC_TEST_TYPE_NAME("unsigned long", unsigned long);
BASIC_TEST_TYPE_NAME("long long", long long);
BASIC_TEST_TYPE_NAME("unsigned long long", unsigned long long);

typedef basic::test::type::Parameter<
    TestReturnValue> Case1;

template<typename TError>
using T1Var1 = VariableTestMessage<TError>;

struct Err1
{
    const char * what() const
    {
        return "err1";
    }
};

struct Err2
{
    const char * Message() const
    {
        return "err2";
    }
};

struct Err3
{
    const char * Message() const
    {
        return "err3 Message";
    }
    const char * what() const
    {
        return "err3 what";
    }
};

BASIC_TEST_TYPE_NAME("Err1", Err1);
BASIC_TEST_TYPE_NAME("Err2", Err2);
BASIC_TEST_TYPE_NAME("Err3", Err3);

Err1 err1{};
const char * res1 = "err1";
Err2 err2{};
const char * res2 = "err2";
Err3 err3{};
const char * res3 = "err3 what";

T1Var1<Err1> t1_var1{&err1, res1};
T1Var1<Err2> t1_var2{&err2, res2};
T1Var1<Err3> t1_var3{&err3, res3};

REGISTER_TEST(t1, new TestMessage<Case1, T1Var1<Err1>, T1Var1<Err2>, 
    T1Var1<Err3>>(t1_var1, t1_var2, t1_var3));

int main()
{
    return RUN_TEST();
}

template<typename TArg>
struct basic::test::type::Name<const TArg>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "const %s";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<TArg *>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "%s *";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};
