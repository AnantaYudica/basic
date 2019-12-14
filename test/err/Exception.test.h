#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/Exception.h"

#include <cstdio>
#include <cstring>
#include <utility>
#include <type_traits>
#include <sstream>
#include <new>

struct TestBaseOfT {};
struct TestSameOfT {};
struct TestAliasTriggerType {};
struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestCallConstructor {};
struct TestCallFillConstructor {};
struct TestCallCopyConstructor {};
struct TestCallMoveConstructor {};
struct TestValueMessage {};
struct TestValueIntfOutput {};
struct TestValueIdGet {};

#define BUFFER_FORMAT_CSTRING 256

const char * ToString(const basic::err::Identification * && id)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    if (id->IsSystem())
    {
        const auto & errsys = id->ErrorSystem();
        snprintf(tmp, BUFFER_FORMAT_CSTRING, "{flag:%x, category:%d, "
            "code:%d}", reinterpret_cast<const unsigned char&>(id->Flag()), 
            errsys.Category(), errsys.Code());
        return tmp;
    }
    const auto & err = id->Error();
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "{flag:%x, code:%d}", 
        reinterpret_cast<const unsigned char&>(id->Flag()), err.Code());
    return tmp;
}

template<typename TException, typename TSameOrBaseOf, 
    typename TIdentification, typename TTrigger, typename TChar,
    typename TOutput, typename TIntfOutput, typename ... TArgs>
using VariableTestException = basic::test::Variable<
    TException,
    TSameOrBaseOf,
    TIdentification,
    TTrigger,
    TChar,
    TOutput,
    TIntfOutput,
    basic::test::type::Parameter<TArgs ...>,
    basic::test::Value<TException *>,
    basic::test::val::Parameter<TArgs &...>,
    basic::test::Value<TException *>,
    basic::test::Value<const TChar *>,
    basic::test::Value<const TChar *>,
    basic::test::Value<const TChar *>,
    basic::test::Value<TIdentification *>,
    basic::test::type::Function<
        const char *(const basic::err::Identification * &&), &ToString>>;

enum : std::size_t
{
    IExceptionType,
    ISameOrBaseOfType,
    IIdentificationType,
    ITriggerType,
    ICharType,
    IOutputType,
    IIntfOutputType,
    IParameterType,
    IExceptionValue,
    IParameterValue,
    IOtherExceptionValue,
    IExceptionNameValue,
    IMessageValue,
    IOutputValue,
    IIdentificationValue,
    IIndentificationToStringTypeFunc
};

typedef basic::test::msg::Argument<TestBaseOfT,
    basic::test::msg::arg::Value<IExceptionNameValue>,
    basic::test::msg::arg::type::Name<ISameOrBaseOfType>> ArgTestBaseOfT;

typedef basic::test::msg::Base<TestBaseOfT, char, 
    ArgTestBaseOfT, ArgTestBaseOfT, 
    ArgTestBaseOfT> MessageBaseTestBaseOfT;

typedef basic::test::msg::Argument<TestSameOfT,
    basic::test::msg::arg::Value<IExceptionNameValue>,
    basic::test::msg::arg::type::Name<ISameOrBaseOfType>> ArgTestSameOfT;

typedef basic::test::msg::Base<TestSameOfT, char, 
    ArgTestSameOfT, ArgTestSameOfT, 
    ArgTestSameOfT> MessageBaseTestSameOfT;

typedef basic::test::msg::Argument<TestAliasTriggerType,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<ITriggerType>> ArgTestAliasTriggerType;

typedef basic::test::msg::Base<TestAliasTriggerType, char, 
    ArgTestAliasTriggerType, ArgTestAliasTriggerType, 
    ArgTestAliasTriggerType> MessageBaseTestAliasTriggerType;

typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<ICharType>> ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<IOutputType>> ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestCallConstructor,
    basic::test::msg::arg::type::Name<IExceptionType>> 
        ArgTestCallConstructor;

typedef basic::test::msg::Base<TestCallConstructor, char, 
    ArgTestCallConstructor, ArgTestCallConstructor, 
    ArgTestCallConstructor> MessageBaseTestCallConstructor;

typedef basic::test::msg::Argument<TestCallFillConstructor,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::param::Name<IParameterType>> 
        ArgTestCallFillConstructor;

typedef basic::test::msg::Base<TestCallFillConstructor, char, 
    ArgTestCallFillConstructor, ArgTestCallFillConstructor, 
    ArgTestCallFillConstructor> MessageBaseTestCallFillConstructor;

typedef basic::test::msg::Argument<TestCallCopyConstructor,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<IExceptionType>> 
        ArgTestCallCopyConstructor;

typedef basic::test::msg::Base<TestCallCopyConstructor, char, 
    ArgTestCallCopyConstructor, ArgTestCallCopyConstructor, 
    ArgTestCallCopyConstructor> MessageBaseTestCallCopyConstructor;

typedef basic::test::msg::Argument<TestCallMoveConstructor,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<IExceptionType>> 
        ArgTestCallMoveConstructor;

typedef basic::test::msg::Base<TestCallMoveConstructor, char, 
    ArgTestCallMoveConstructor, ArgTestCallMoveConstructor, 
    ArgTestCallMoveConstructor> MessageBaseTestCallMoveConstructor;

typedef basic::test::msg::Argument<TestValueMessage,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<ICharType>,
    basic::test::msg::arg::Value<IMessageValue>> 
        ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, 
    ArgTestValueMessage> MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestValueIntfOutput,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Name<ICharType>,
    basic::test::msg::arg::Value<IOutputValue>> 
        ArgTestValueIntfOutput;

typedef basic::test::msg::Base<TestValueIntfOutput, char, 
    ArgTestValueIntfOutput, ArgTestValueIntfOutput, 
    ArgTestValueIntfOutput> MessageBaseTestValueIntfOutput;

typedef basic::test::msg::Argument<TestValueIdGet,
    basic::test::msg::arg::type::Name<IIdentificationType>,
    basic::test::msg::arg::type::Name<IExceptionType>,
    basic::test::msg::arg::type::Function<IIndentificationToStringTypeFunc,
        basic::test::msg::arg::Value<IIdentificationValue>>>
        ArgTestValueIdGet;

typedef basic::test::msg::Base<TestValueIdGet, char, 
    ArgTestValueIdGet, ArgTestValueIdGet, 
    ArgTestValueIdGet> MessageBaseTestValueIdGet;

template<typename TCases, typename... TVariables>
struct TestException :
    public basic::test::Message<BASIC_TEST, TestException<TCases, 
        TVariables...>>,
    public basic::test::Case<TestException<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestException<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfT,
    public MessageBaseTestSameOfT,
    public MessageBaseTestAliasTriggerType,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestCallConstructor,
    public MessageBaseTestCallFillConstructor,
    public MessageBaseTestCallCopyConstructor,
    public MessageBaseTestCallMoveConstructor,
    public MessageBaseTestValueMessage,
    public MessageBaseTestValueIntfOutput,
    public MessageBaseTestValueIdGet
{
public:
    using basic::test::Case<TestException<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestException<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfT::Format;
    using MessageBaseTestBaseOfT::SetFormat;
    using MessageBaseTestBaseOfT::Argument;
    using MessageBaseTestSameOfT::Format;
    using MessageBaseTestSameOfT::SetFormat;
    using MessageBaseTestSameOfT::Argument;
    using MessageBaseTestAliasTriggerType::Format;
    using MessageBaseTestAliasTriggerType::SetFormat;
    using MessageBaseTestAliasTriggerType::Argument;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestCallConstructor::Format;
    using MessageBaseTestCallConstructor::SetFormat;
    using MessageBaseTestCallConstructor::Argument;
    using MessageBaseTestCallFillConstructor::Format;
    using MessageBaseTestCallFillConstructor::SetFormat;
    using MessageBaseTestCallFillConstructor::Argument;
    using MessageBaseTestCallCopyConstructor::Format;
    using MessageBaseTestCallCopyConstructor::SetFormat;
    using MessageBaseTestCallCopyConstructor::Argument;
    using MessageBaseTestCallMoveConstructor::Format;
    using MessageBaseTestCallMoveConstructor::SetFormat;
    using MessageBaseTestCallMoveConstructor::Argument;
    using MessageBaseTestValueMessage::Format;
    using MessageBaseTestValueMessage::SetFormat;
    using MessageBaseTestValueMessage::Argument;
    using MessageBaseTestValueIntfOutput::Format;
    using MessageBaseTestValueIntfOutput::SetFormat;
    using MessageBaseTestValueIntfOutput::Argument;
    using MessageBaseTestValueIdGet::Format;
    using MessageBaseTestValueIdGet::SetFormat;
    using MessageBaseTestValueIdGet::Argument;
public:
    TestException(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestException<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestException<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestException<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestBaseOfT testBaseOfT;
        SetFormat(info, testBaseOfT, "Test type %s is base type of %s \n");
        SetFormat(debug, testBaseOfT, "Test type %s is base type of %s \n");
        SetFormat(err, testBaseOfT, "Error Test type %s is not base type of %s \n");

        TestSameOfT testSameOfT;
        SetFormat(info, testSameOfT, "Test type %s is same type of %s \n");
        SetFormat(debug, testSameOfT, "Test type %s is same type of %s \n");
        SetFormat(err, testSameOfT, "Error Test type %s is not same type of %s \n");

        TestAliasTriggerType testAliasTriggerType;
        SetFormat(info, testAliasTriggerType, "Test type %s::TriggerType "
            "is same type of %s \n");
        SetFormat(debug, testAliasTriggerType, "Test type %s::TriggerType "
            "is same type of %s \n");
        SetFormat(err, testAliasTriggerType, "Error Test type %s::TriggerType "
            "is not same type of %s \n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test type %s::CharType "
            "is same type of %s \n");
        SetFormat(debug, testAliasCharType, "Test type %s::CharType "
            "is same type of %s \n");
        SetFormat(err, testAliasCharType, "Error Test type %s::CharType "
            "is not same type of %s \n");

        TestAliasOutputType testAliasOutputType;
        SetFormat(info, testAliasOutputType, "Test type %s::OutputType "
            "is same type of %s \n");
        SetFormat(debug, testAliasOutputType, "Test type %s::OutputType "
            "is same type of %s \n");
        SetFormat(err, testAliasOutputType, "Error Test type %s::OutputType "
            "is not same type of %s \n");

        TestCallConstructor testCallConstructor;
        SetFormat(info, testCallConstructor, "Test call constructor of "
            "%s() is pass \n");
        SetFormat(debug, testCallConstructor, "Test call constructor of "
            "%s() is pass \n");
        SetFormat(err, testCallConstructor, "Error Test call constructor of "
            "%s() is not pass \n");

        TestCallFillConstructor testCallFillConstructor;
        SetFormat(info, testCallFillConstructor, "Test call constructor of "
            "%s(%s) is pass \n");
        SetFormat(debug, testCallFillConstructor, "Test call constructor of "
            "%s(%s) is pass \n");
        SetFormat(err, testCallFillConstructor, "Error Test call constructor of "
            "%s(%s) is not pass \n");

        TestCallCopyConstructor testCallCopyConstructor;
        SetFormat(info, testCallCopyConstructor, "Test call copy constructor of "
            "%s(const %s &) is pass \n");
        SetFormat(debug, testCallCopyConstructor, "Test call copy constructor of "
            "%s(const %s &) is pass \n");
        SetFormat(err, testCallCopyConstructor, "Error Test call copy constructor of "
            "%s(const %s &) is not pass \n");

        TestCallMoveConstructor testCallMoveConstructor;
        SetFormat(info, testCallMoveConstructor, "Test call move constructor of "
            "%s (%s &&) is pass \n");
        SetFormat(debug, testCallMoveConstructor, "Test call move constructor of "
            "%s (%s &&) is pass \n");
        SetFormat(err, testCallMoveConstructor, "Error Test call move constructor of "
            "%s (%s &&) is not pass \n");

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test value of %s::Message() is same "
            "with const %s * {\"%s\"}\n");
        SetFormat(debug, testValueMessage, "Test value of %s::Message() is same "
            "with const %s * {\"%s\"}\n");
        SetFormat(err, testValueMessage, "Error Test value of %s::Message() is not same  "
            "with const %s * {\"%s\"}\n");

        TestValueIntfOutput testValueIntfOutput;
        SetFormat(info, testValueIntfOutput, "Test value of %s::operator>>() is same "
            "with const %s * {\"%s\"}\n");
        SetFormat(debug, testValueIntfOutput, "Test value of %s::operator>>() is same "
            "with const %s * {\"%s\"}\n");
        SetFormat(err, testValueIntfOutput, "Error Test value of %s::operator>>() is not same  "
            "with const %s * {\"%s\"}\n");

        TestValueIdGet testValueIdGet;
        SetFormat(info, testValueIdGet, "Test value of basic::err::id::Get(%s) is same "
            "with %s {%s}\n");
        SetFormat(debug, testValueIdGet, "Test value of basic::err::id::Get(%s) is same "
            "with %s {%s}\n");
        SetFormat(err, testValueIdGet, "Error Test value of basic::err::id::Get(%s) is not same  "
            "with %s {%s}\n");
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfT &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ISameOrBaseOfType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        return std::is_base_of<BaseType, ExceptionType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestSameOfT &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ISameOrBaseOfType,
            basic::test::Variable<TArgs...>>::Type SameType;
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        return std::is_same<SameType, ExceptionType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasTriggerType &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ITriggerType,
            basic::test::Variable<TArgs...>>::Type TriggerType;
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        return std::is_same<TriggerType, typename ExceptionType::TriggerType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasCharType &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICharType,
            basic::test::Variable<TArgs...>>::Type CharType;
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        return std::is_same<CharType, typename ExceptionType::CharType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasOutputType &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        return std::is_same<OutputType, typename ExceptionType::OutputType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestCallConstructor &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        new (instance) ExceptionType{};
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallFillConstructor &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        if (!instance) return false;
        basic::test::var::At<IParameterValue>(var).Get().
            template Fill(*instance);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallCopyConstructor &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        auto * other = basic::test::var::At<IOtherExceptionValue>(var).Get().Get();
        if (!instance) return false;
        new (instance) ExceptionType(*other);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallMoveConstructor &, basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        auto * other = basic::test::var::At<IOtherExceptionValue>(var).Get().Get();
        if (!instance) return false;
        new (instance) ExceptionType(std::move(*other));
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestValueMessage &, basic::test::Variable<TArgs...> & var)
    {
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        auto * compare = basic::test::var::At<IMessageValue>(var).Get().Get();
        return strcmp(instance->Message(), compare) == 0;
    }
    template<typename... TArgs>
    bool Result(const TestValueIntfOutput &, basic::test::Variable<TArgs...> & var)
    {
        auto * instance = basic::test::var::At<IExceptionValue>(var).Get().Get();
        auto * compare = basic::test::var::At<IOutputValue>(var).Get().Get();
        auto * base = dynamic_cast<basic::err::intf::Output *>(instance);
        std::stringstream ss;
        ss << (*base);
        return strcmp(ss.str().c_str(), compare) == 0;
    }
    template<typename... TArgs>
    bool Result(const TestValueIdGet &, basic::test::Variable<TArgs...> & var)
    {
        auto * compare = basic::test::var::At<IIdentificationValue>(var).Get().Get();
        typedef typename basic::test::var::Element<IExceptionType,
            basic::test::Variable<TArgs...>>::Type ExceptionType;
        auto id = basic::err::id::Get(ExceptionType());
        return id.IsDefault() == compare->IsDefault() &&
            id.IsBad() == compare->IsBad() &&
            id.IsCatch() == compare->IsCatch() &&
            id.IsStandard() == compare->IsStandard() &&
            id.IsSystem() == compare->IsSystem();
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

BASIC_TEST_TYPE_NAME("basic::Error<basic::err::tag::Trigger>", 
    basic::Error<basic::err::tag::Trigger>);
BASIC_TEST_TYPE_NAME("basic::err::Identification", 
    basic::err::Identification);

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
