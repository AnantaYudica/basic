
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/Definition.h"

#include "error/defn/type/Char.h"
#include "error/defn/type/Output.h"
#include "error/defn/type/code/Value.h"
#include "error/defn/type/id/Record.h"
#include "error/defn/type/msg/str/Storage.h"
#include "error/defn/type/output/Char.h"
#include "error/defn/type/output/CharTrait.h"
#include "error/defn/type/system/category/Value.h"
#include "error/defn/type/system/code/Value.h"
#include "error/defn/type/system/condition/Value.h"

#include <typeinfo>

struct TestIsSameType {};

template<typename T1, typename T2>
using VariableIsSameType = basic::test::Variable<
    basic::test::Value<const char *>, T1, 
    basic::test::Value<const char *>, T2>;

typedef basic::test::msg::Argument<TestIsSameType,
    basic::test::msg::arg::Value<0>,
    basic::test::msg::arg::type::Name<1>,
    basic::test::msg::arg::Value<2>,
    basic::test::msg::arg::type::Name<3>> ArgTestIsSameType;

typedef basic::test::msg::Base<TestIsSameType, char, 
    ArgTestIsSameType, ArgTestIsSameType, 
    ArgTestIsSameType> MessageBaseTestIsSameType;

template<typename... TVariables>
class TestDefinition :
    public MessageBaseTestIsSameType,
    public basic::test::Message<BASIC_TEST, TestDefinition<TVariables...>>,
    public basic::test::Case<TestDefinition<TVariables...>,
        basic::test::type::Parameter<TestIsSameType>>,
    public basic::test::Base<TestDefinition<TVariables...>, TVariables...>
{
public:
    using MessageBaseTestIsSameType::Format;
    using MessageBaseTestIsSameType::SetFormat;
    using MessageBaseTestIsSameType::Argument;
    using basic::test::Case<TestDefinition<TVariables...>,
        basic::test::type::Parameter<TestIsSameType>>::Run;
    using basic::test::Base<TestDefinition<TVariables...>, TVariables...>::Run;
public:
    TestDefinition(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefinition<TVariables...>>(*this),
        basic::test::Case<TestDefinition<TVariables...>,
            basic::test::type::Parameter<TestIsSameType>>(*this),
        basic::test::Base<TestDefinition<TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        TestIsSameType testIsSameType;

        basic::test::msg::Format<char> formatIsSameType("Test %s{%s} "
            "and %s{%s} is same type\n");
        SetFormat(debug, testIsSameType, formatIsSameType);
        SetFormat(info, testIsSameType, std::move(formatIsSameType));
        SetFormat(error, testIsSameType, "Error %s{%s} and %s{%s}"
            " is not same type\n");

    }
public:
    template<typename T1, typename T2>
    bool Result(const TestIsSameType &, VariableIsSameType<T1, T2> & var)
    {
        return typeid(T1).hash_code() == typeid(T2).hash_code();
    }
};

BASIC_TEST_TYPE_NAME("char", char);
BASIC_TEST_TYPE_NAME("short", short);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("long", long);
BASIC_TEST_TYPE_NAME("long long", long long);
BASIC_TEST_TYPE_NAME("unsigned char", unsigned char);
BASIC_TEST_TYPE_NAME("unsigned short", unsigned short);
BASIC_TEST_TYPE_NAME("unsigned int", unsigned int);
BASIC_TEST_TYPE_NAME("unsigned long", unsigned long);
BASIC_TEST_TYPE_NAME("unsigned long long", unsigned long long);

BASIC_TEST_TYPE_NAME("char *", char *);

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
        return basic::test::cstr::Format(sizeof(_format) - 6 + tArg1CStr.Size() +
            tArg2CStr.Size(), _format, *tArg1CStr, *tArg2CStr);
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

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<basic::error::id::Record<TArg1, TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::id::Record<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size(), 
            _format, *tArg1CStr, *tArg2CStr, *tArg3CStr);
    }
};

