#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/DefaultConditionValue.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;

struct CategoryTrait1
{
    CategoryTrait1() = default;
    ConditionValueType DefaultConditionValue() const
    {
        return 4;
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    CategoryTrait2() = default;
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct TestValueDefaultConditionValue {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait>
using VariableTestDefaultConditionValue = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    ConditionValueType,
    basic::test::Value<ConditionValueType *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t IConditionValueType = 2;
constexpr std::size_t IConditionValueValue = 3;

typedef basic::test::msg::Argument<TestValueDefaultConditionValue,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<IConditionValueType>,
    basic::test::msg::arg::Value<IConditionValueValue>> 
        ArgTestValueDefaultConditionValue;

typedef basic::test::msg::Base<TestValueDefaultConditionValue, char, 
    ArgTestValueDefaultConditionValue, ArgTestValueDefaultConditionValue, 
    ArgTestValueDefaultConditionValue> 
        MessageBaseTestValueDefaultConditionValue;

template<typename TCases, typename... TVariables>
struct TestDefaultConditionValue :
    public basic::test::Message<BASIC_TEST, TestDefaultConditionValue<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefaultConditionValue<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefaultConditionValue<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefaultConditionValue
{
public:
    using MessageBaseTestValueDefaultConditionValue::Format;
    using MessageBaseTestValueDefaultConditionValue::SetFormat;
    using MessageBaseTestValueDefaultConditionValue::Argument;
public:
    using basic::test::Case<TestDefaultConditionValue<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefaultConditionValue<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefaultConditionValue(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefaultConditionValue<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefaultConditionValue<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefaultConditionValue<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueDefaultConditionValue testValueDefaultConditionValue;
        SetFormat(info, testValueDefaultConditionValue, "Test value "
            "%s::DefaultConditionValue(%s()) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultConditionValue, "Test value "
            "%s::DefaultConditionValue(%s()) is same with %s {%s}\n");
        SetFormat(err, testValueDefaultConditionValue, "Error value "
            "%s::DefaultConditionValue(%s()) is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait>
    bool Result(const TestValueDefaultConditionValue &, 
        VariableTestDefaultConditionValue<TCategoryTrait> & var)
    {
        auto * code_value = basic::test::var::At<IConditionValueValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultConditionValue(TCategoryTrait {});
        return res == *code_value;
    }

};

typedef basic::test::type::Parameter<TestValueDefaultConditionValue> Case1;

typedef VariableTestDefaultConditionValue<CategoryTrait1> T1Var1;
typedef VariableTestDefaultConditionValue<CategoryTrait2> T1Var2;

CodeValueType code_value1{4};
CodeValueType code_value2{0};

T1Var1 t1_var1{&code_value1};
T1Var2 t1_var2{&code_value2};

REGISTER_TEST(t1, new TestDefaultConditionValue<Case1, T1Var1, T1Var2>(t1_var1,
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

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
struct basic::test::out::Argument<ConditionValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionValueType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
    static const char * Value(ConditionValueType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionValueType *>::ms_cstr;
