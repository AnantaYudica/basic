
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "error/Definition.h"

#include "error/id/Record.h"
#include "error/defn/type/Char.h"
#include "error/defn/type/Output.h"
#include "error/defn/type/code/Value.h"
#include "error/defn/type/id/Record.h"
#include "error/defn/type/msg/str/Storage.h"
#include "error/defn/type/output/Char.h"
#include "error/defn/type/output/CharTrait.h"
#include "error/defn/type/system/categ/Value.h"
#include "error/defn/type/system/code/Value.h"
#include "error/defn/type/system/condition/Value.h"
#include "error/defn/func/output/Operator.h"

#include <typeinfo>
#include <utility>

struct TestIsSameType {};
struct TestSizeofAType {};
struct TestCallOutputOperator {};

template<typename TIsSameA, typename TIsSameB, typename TOutputFuncParam,
    typename TOutputFuncArg, typename ... TOutputFuncArgs>
using VariableDefinition = basic::test::Variable<
    basic::test::Value<const char *>, TIsSameA, 
    basic::test::Value<const char *>, TIsSameB,
    basic::test::Value<std::size_t>,
    basic::test::Value<const char *>,
    basic::test::val::Function<TOutputFuncParam & (TOutputFuncParam &, 
        TOutputFuncArgs && ...)>,
    basic::test::Value<const char *>,
    basic::test::val::Function<bool (TOutputFuncArg &)>,
    TOutputFuncParam &, 
    basic::test::type::Parameter<TOutputFuncArgs...>,
    basic::test::val::Parameter<TOutputFuncArg &, TOutputFuncArgs...>>;

constexpr std::size_t IIsSameAName = 0;
constexpr std::size_t IIsSameAType = 1;
constexpr std::size_t IIsSameBName = 2;
constexpr std::size_t IIsSameBType = 3;
constexpr std::size_t ISizeofAType = 4;
constexpr std::size_t IOutputOperatorFuncName = 5;
constexpr std::size_t IOutputOperatorFunc = 6;
constexpr std::size_t IOutputResultCBFuncName = 7;
constexpr std::size_t IOutputResultCBFunc = 8;
constexpr std::size_t IOutputType = 9;
constexpr std::size_t IParameterType = 10;
constexpr std::size_t IParameterVal = 11;

template<typename TOutput, typename ... TArgs>
TOutput & DefaultOperator(TOutput & out, TArgs && ...)
{
    return out;
}

template<typename TOutput>
bool DefaultResultCallBack(TOutput &)
{
    return false;
}

template<typename T1, typename T2>
struct VariableIsSameType : public VariableDefinition<T1, T2, 
    std::basic_ostream<char>, std::basic_ostream<char>>
{
    typedef VariableDefinition<T1, T2, std::basic_ostream<char>,
        std::basic_ostream<char>> BaseType;
    VariableIsSameType(const char * arg1, const char * arg2) :
        BaseType(arg1, arg2, 0, "DefaultOperator", 
            &DefaultOperator<std::basic_ostream<char>>, "DefaultResultCallBack",
            &DefaultResultCallBack<std::basic_ostream<char>>, std::cout)
    {}
};

template<typename T1, typename T2>
struct VariableIsSameAndSizeofAType : public VariableDefinition<T1, T2, 
    std::basic_ostream<char>, std::basic_ostream<char>>
{
    typedef VariableDefinition<T1, T2, std::basic_ostream<char>,
        std::basic_ostream<char>> BaseType;
    VariableIsSameAndSizeofAType(const char * arg1, const char * arg2, 
        const std::size_t & size) :
            BaseType(arg1, arg2, size, "DefaultOperator", 
                &DefaultOperator<std::basic_ostream<char>>, "DefaultResultCallBack",
                &DefaultResultCallBack<std::basic_ostream<char>>, std::cout)
    {}
};


template<typename TOutput, typename TArg, typename ... TArgs>
struct VariableCallOutputOperator : public VariableDefinition<void, void, 
    TOutput, TArg, TArgs...>
{
    typedef VariableDefinition<void, void, TOutput, TArg, TArgs...> BaseType;
    VariableCallOutputOperator(const char * oprName, 
        TOutput & (&operatorFunc) (TOutput &, TArgs && ...), 
        const char * resultCBName, bool (&resultCBFunc)(TArg &),
        TArg & arg, TArgs && ... args) :
            BaseType("undefined", "undefined", 0, oprName, operatorFunc,
                resultCBName, resultCBFunc, arg, std::forward<TArgs>(args) ...)
    {}
};

typedef basic::test::msg::Argument<TestIsSameType,
    basic::test::msg::arg::Value<IIsSameAName>,
    basic::test::msg::arg::type::Name<IIsSameAType>,
    basic::test::msg::arg::Value<IIsSameBName>,
    basic::test::msg::arg::type::Name<IIsSameBType>> ArgTestIsSameType;

typedef basic::test::msg::Base<TestIsSameType, char, 
    ArgTestIsSameType, ArgTestIsSameType, 
    ArgTestIsSameType> MessageBaseTestIsSameType;

typedef basic::test::msg::Argument<TestSizeofAType,
    basic::test::msg::arg::Value<IIsSameAName>,
    basic::test::msg::arg::type::Name<IIsSameAType>,
    basic::test::msg::arg::Value<ISizeofAType>> ArgTestSizeofAType;

typedef basic::test::msg::Base<TestSizeofAType, char, 
    ArgTestSizeofAType, ArgTestSizeofAType, 
    ArgTestSizeofAType> MessageBaseTestSizeofAType;

typedef basic::test::msg::Argument<TestCallOutputOperator,
    basic::test::msg::arg::Value<IOutputOperatorFuncName>,
    basic::test::msg::arg::type::Name<IOutputType>,
    basic::test::msg::arg::type::param::Name<IParameterType>> 
        ArgInfoTestIsSameType;

typedef basic::test::msg::Argument<TestCallOutputOperator,
    basic::test::msg::arg::Value<IOutputOperatorFuncName>,
    basic::test::msg::arg::type::Name<IOutputType>,
    basic::test::msg::arg::type::param::Name<IParameterType>,
    basic::test::msg::arg::Value<IOutputResultCBFuncName>,
    basic::test::msg::arg::type::Name<IOutputType>> 
        ArgErrorTestIsSameType;

typedef basic::test::msg::Base<TestCallOutputOperator, char, 
    ArgInfoTestIsSameType, ArgInfoTestIsSameType, 
    ArgErrorTestIsSameType> MessageBaseTestCallOutputOperator;


template<typename TCases, typename... TVariables>
class TestDefinition :
    public MessageBaseTestIsSameType,
    public MessageBaseTestSizeofAType,
    public MessageBaseTestCallOutputOperator,
    public basic::test::Message<BASIC_TEST, TestDefinition<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefinition<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefinition<TCases, TVariables...>, 
        TVariables...>
{
public:
    using MessageBaseTestIsSameType::Format;
    using MessageBaseTestIsSameType::SetFormat;
    using MessageBaseTestIsSameType::Argument;
    using MessageBaseTestSizeofAType::Format;
    using MessageBaseTestSizeofAType::SetFormat;
    using MessageBaseTestSizeofAType::Argument;
    using MessageBaseTestCallOutputOperator::Format;
    using MessageBaseTestCallOutputOperator::SetFormat;
    using MessageBaseTestCallOutputOperator::Argument;
    using basic::test::Case<TestDefinition<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefinition<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefinition(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefinition<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefinition<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefinition<TCases, TVariables...>, 
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

        TestSizeofAType testSizeofAType;
        basic::test::msg::Format<char> formatSizeofAType("Test size of %s{%s}"
            " is %zu bytes\n");
        SetFormat(debug, testSizeofAType, formatSizeofAType);
        SetFormat(info, testSizeofAType, std::move(formatSizeofAType));
        SetFormat(error, testSizeofAType, "Error size of %s{%s}"
            " is not %zu bytes\n");

        TestCallOutputOperator testCallOutputOperator;
        basic::test::msg::Format<char> formatCallOutputOperatorType("Test "
            "call Output operator function %s(%s, %s)\n");
        SetFormat(debug, testCallOutputOperator, formatCallOutputOperatorType);
        SetFormat(info, testCallOutputOperator, 
            std::move(formatCallOutputOperatorType));
        SetFormat(error, testCallOutputOperator, "Error call Output operator "
            "function %s(%s, %s) cause return value of %s(%s) is false\n");

    }
public:
    template<typename T1, typename T2, typename TOutput, 
        typename TValOutput, typename ... TArgs>
    bool Result(const TestIsSameType &, 
        VariableDefinition<T1, T2, TOutput, TValOutput, TArgs...> & var)
    {
        return typeid(T1).hash_code() == typeid(T2).hash_code();
    }
    template<typename T1, typename T2, typename TOutput, 
        typename TValOutput, typename ... TArgs>
    bool Result(const TestSizeofAType &, 
        VariableDefinition<T1, T2, TOutput, TValOutput, TArgs...> & var)
    {
        return sizeof(T1) == 
            basic::test::var::At<ISizeofAType>(var).Get().Get();
    }
    template<typename T1, typename T2, typename TOutput, 
        typename TValOutput, typename ... TArgs>
    bool Result(const TestCallOutputOperator &, 
        VariableDefinition<T1, T2, TOutput, TValOutput, TArgs...> & var)
    {
        basic::test::var::At<IParameterVal>(var).Get().template Fill<
            TOutput &>(basic::test::var::At<IOutputOperatorFunc>(var).Get().Get());
        return basic::test::var::At<IOutputResultCBFunc>(var).Get().
            Call(basic::test::var::At<IParameterVal>(var).Get().template At<0>());
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

BASIC_TEST_TYPE_NAME("float", float);

BASIC_TEST_TYPE_NAME("char *", char *);
BASIC_TEST_TYPE_NAME("const char *", const char *);

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
            tArg1CStr.Size() + tArg2CStr.Size(), _format, 
            *tArg1CStr, *tArg2CStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<std::basic_stringstream<TArg1, TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_stringstream<%s, %s, %s>";
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
struct basic::test::type::Name<std::allocator<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::allocator<%s>";
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

template<typename TArg>
struct basic::test::type::Name<TArg &>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "%s &";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

