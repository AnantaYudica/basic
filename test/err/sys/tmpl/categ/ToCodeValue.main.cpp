#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/ToCodeValue.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>
#include <cstring>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

enum class CodeEnum1
{
    value1 = 4
};

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
    CodeValueType ToCodeValue(const CodeEnum1 & code) const
    {
        return static_cast<CodeValueType>(code) + 10;
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    typedef CodeEnum1 CodeEnumType;
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct TestValueToCodeValue {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TCodeEnum>
using VariableTestToCodeValue = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    TCodeEnum,
    basic::test::Value<TCodeEnum *>,
    basic::test::Value<CodeValueType *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeEnumType = 2;
constexpr std::size_t ICodeEnumValue = 3;
constexpr std::size_t IToCodeValueValue = 4;

typedef basic::test::msg::Argument<TestValueToCodeValue,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::Value<IToCodeValueValue>> 
        ArgTestValueToCodeValue;

typedef basic::test::msg::Base<TestValueToCodeValue, char, 
    ArgTestValueToCodeValue, ArgTestValueToCodeValue, 
    ArgTestValueToCodeValue> MessageBaseTestValueToCodeValue;

template<typename TCases, typename... TVariables>
struct TestToCodeValue :
    public basic::test::Message<BASIC_TEST, TestToCodeValue<TCases, 
        TVariables...>>,
    public basic::test::Case<TestToCodeValue<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestToCodeValue<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueToCodeValue
{
public:
    using MessageBaseTestValueToCodeValue::Format;
    using MessageBaseTestValueToCodeValue::SetFormat;
    using MessageBaseTestValueToCodeValue::Argument;
public:
    using basic::test::Case<TestToCodeValue<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestToCodeValue<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestToCodeValue(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestToCodeValue<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestToCodeValue<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestToCodeValue<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueToCodeValue testValueToCodeValue;
        SetFormat(info, testValueToCodeValue, "Test value "
            "%s::ToCodeValue(%s(), %s{%s}) is same with %s\n");
        SetFormat(debug, testValueToCodeValue, "Test value "
            "%s::ToCodeValue(%s(), %s{%s}) is same with %s\n");
        SetFormat(err, testValueToCodeValue, "Error value "
            "%s::ToCodeValue(%s(), %s{%s}) is not same with %s\n");

    }
    template<typename TCategoryTrait, typename TCodeEnum>
    bool Result(const TestValueToCodeValue &, 
        VariableTestToCodeValue<TCategoryTrait, TCodeEnum> & var)
    {
        auto * code_enum = basic::test::var::At<ICodeEnumValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<IToCodeValueValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            ToCodeValue(TCategoryTrait{}, *code_enum);
        return *code == res;
    }

};

typedef basic::test::type::Parameter<TestValueToCodeValue> Case1;

typedef VariableTestToCodeValue<CategoryTrait1, CodeEnum1> T1Var1;
typedef VariableTestToCodeValue<CategoryTrait2, CodeEnum1> T1Var2;

CodeEnum1 code_enum1 = CodeEnum1::value1;
CodeValueType code_val1 = static_cast<CodeValueType>(code_enum1) + 10;
CodeValueType code_val2 = static_cast<CodeValueType>(code_enum1);

T1Var1 t1_var1{&code_enum1, &code_val1};
T1Var2 t1_var2{&code_enum1, &code_val2};

REGISTER_TEST(t1, new TestToCodeValue<Case1, T1Var1, T1Var2>(t1_var1, 
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

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

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::Category<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::Category<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TCategoryTrait>
struct basic::test::out::Argument<const basic::err::sys::tmpl::
    Category<TCategoryTrait> *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
    static const char * Value(const basic::err::sys::tmpl::
        Category<TCategoryTrait> * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", categ->Value()));
        return *ms_cstr;
    }
};

template<typename TCategoryTrait>
basic::test::CString<char> basic::test::out::Argument<const basic::err::
    sys::tmpl::Category<TCategoryTrait> *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1 * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<CodeValueType>(*code)));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1 * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<CodeValueType>(*code)));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<CodeEnum1 *>::ms_cstr;


template<>
struct basic::test::out::Argument<CodeValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeValueType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(CodeValueType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeValueType *>::ms_cstr;

