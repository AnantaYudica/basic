#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Output.h"

#include <cstdio>
#include <cstring>
#include <cstddef>
#include <type_traits>
#include <sstream>

#define BUFFER_FORMAT_CSTRING 256

struct TestDefnOutputType {};
struct TestCompareValue {};

template<typename TError, typename TOutput>
using VariableTestOutput = basic::test::Variable<
    TError,
    TOutput,
    const char *,
    basic::test::Value<TError *>,
    basic::test::Value<const char *>,
    basic::test::Value<const char *>>;

enum : std::size_t
{
    IErrorType,
    IOutputType,
    ICompareType,
    IErrorValue,
    ICompareValue,
    IDefnOutputNameValue
};

typedef basic::test::msg::Argument<TestDefnOutputType,
    basic::test::msg::arg::Value<IDefnOutputNameValue>,
    basic::test::msg::arg::type::Name<IOutputType>>
        ArgTestDefnOutputType;

typedef basic::test::msg::Base<TestDefnOutputType, char, 
    ArgTestDefnOutputType, ArgTestDefnOutputType, 
    ArgTestDefnOutputType> MessageBaseTestDefnOutputType;

typedef basic::test::msg::Argument<TestCompareValue,
    basic::test::msg::arg::type::Name<IOutputType>,
    basic::test::msg::arg::type::Name<IOutputType>,
    basic::test::msg::arg::type::Name<IErrorType>,
    basic::test::msg::arg::type::Name<ICompareType>,
    basic::test::msg::arg::Value<ICompareValue>>
        ArgTestCompareValue;

typedef basic::test::msg::Base<TestCompareValue, char, 
    ArgTestCompareValue, ArgTestCompareValue, 
    ArgTestCompareValue> MessageBaseTestCompareValue;


template<typename TCases, typename... TVariables>
struct TestOutput :
    public basic::test::Message<BASIC_TEST, TestOutput<TCases, 
        TVariables...>>,
    public basic::test::Case<TestOutput<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestOutput<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestDefnOutputType,
    public MessageBaseTestCompareValue
{
public:
    using basic::test::Case<TestOutput<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestOutput<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestDefnOutputType::Format;
    using MessageBaseTestDefnOutputType::SetFormat;
    using MessageBaseTestDefnOutputType::Argument;
    using MessageBaseTestCompareValue::Format;
    using MessageBaseTestCompareValue::SetFormat;
    using MessageBaseTestCompareValue::Argument;
public:
    TestOutput(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestOutput<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestOutput<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestOutput<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestDefnOutputType testDefnOutputType;
        SetFormat(info, testDefnOutputType, "Test type definition %s "
            "is same with %s \n");
        SetFormat(debug, testDefnOutputType, "Test type definition %s "
            "is same with %s \n");
        SetFormat(err, testDefnOutputType, "Error Test type definition %s "
            "is same with %s \n");

        TestCompareValue testCompareValue;
        SetFormat(info, testCompareValue, "Test compare value between "
            "return value function %s basic::err::Output(%s, %s) and "
            "%s {\"%s\"} is same \n");
        SetFormat(debug, testCompareValue, "Test compare value between "
            "return value function %s basic::err::Output(%s, %s) and "
            "%s {\"%s\"} is same \n");
        SetFormat(err, testCompareValue, "Error Test compare value between "
            "return value function %s basic::err::Output(%s, %s) and "
            "%s {\"%s\"} is not same \n");
    }
    template<typename... TArgs>
    bool Result(const TestDefnOutputType &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        return typeid(basic::err::defn::type::Output).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestCompareValue &, basic::test::Variable<TArgs...> & var)
    {
        auto * error = basic::test::var::At<IErrorValue>(var).Get().Get();
        auto * com_val = basic::test::var::At<ICompareValue>(var).Get().Get();
        std::stringstream ss;
        basic::err::Output(ss, *error);
        return strcmp(ss.str().c_str(), com_val) == 0;
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
    TestDefnOutputType> Case1;

typedef basic::test::type::Parameter<
    TestCompareValue> Case2;

template<typename TError, typename TOutput>
using T1Var1 = VariableTestOutput<TError, TOutput>;

const char * empty = "";

T1Var1<void, std::basic_ostream<char>> t1_var1{nullptr, empty, 
    "basic::err::defn::type::Output"};

REGISTER_TEST(t1, new TestOutput<Case1, 
    T1Var1<void, basic::err::defn::type::Output>>(t1_var1));

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

struct Err4 : public basic::err::intf::Output
{
    Err4() : basic::err::intf::Output() {};
    const Err4 & operator>>(ValueType & val) const noexcept
    {
        val << "err4 basic::err::intf::Output";
        return *this;
    }
};

BASIC_TEST_TYPE_NAME("Err1", Err1);
BASIC_TEST_TYPE_NAME("Err2", Err2);
BASIC_TEST_TYPE_NAME("Err3", Err3);
BASIC_TEST_TYPE_NAME("Err4", Err4);

Err1 err1{};
const char * res1 = "err1";
Err2 err2{};
const char * res2 = "err2";
Err3 err3{};
const char * res3 = "err3 what";
Err4 err4{};
const char * res4 = "err4 basic::err::intf::Output";


T1Var1<Err1, basic::err::defn::type::Output> t2_var1{&err1, res1, empty};
T1Var1<Err2, basic::err::defn::type::Output> t2_var2{&err2, res2, empty};
T1Var1<Err3, basic::err::defn::type::Output> t2_var3{&err3, res3, empty};
T1Var1<Err4, basic::err::defn::type::Output> t2_var4{&err4, res4, empty};

REGISTER_TEST(t2, new TestOutput<Case2, 
    T1Var1<Err1, basic::err::defn::type::Output>, 
    T1Var1<Err2, basic::err::defn::type::Output>, 
    T1Var1<Err3, basic::err::defn::type::Output>,
    T1Var1<Err4, basic::err::defn::type::Output>>(t2_var1, t2_var2, 
        t2_var3, t2_var4));

int main()
{
    return RUN_TEST();
}

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<std::basic_ostream<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_ostream<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, *tArg1CStr,
            *tArg2CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<std::char_traits<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::char_traits<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

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
