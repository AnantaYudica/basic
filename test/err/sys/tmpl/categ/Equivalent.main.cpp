#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Equivalent.h"
#include "err/sys/tmpl/Category.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

struct CategoryTrait1
{
    CategoryTrait1() = default;
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        return code.Value() == cond;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        return code == cond.Value();
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

struct TestValueEquivalent {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TCode, typename TCondition>
using VariableTestEquivalent = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    TCode,
    TCondition,
    basic::test::Value<TCode *>,
    basic::test::Value<TCondition *>,
    basic::test::Value<bool *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t IConditionType = 3;
constexpr std::size_t ICodeValue = 4;
constexpr std::size_t IConditionValue = 5;
constexpr std::size_t IBoolValue = 6;

typedef basic::test::msg::Argument<TestValueEquivalent,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::Value<IConditionValue>,
    basic::test::msg::arg::Value<IBoolValue>> 
        ArgTestValueEquivalent;

typedef basic::test::msg::Base<TestValueEquivalent, char, 
    ArgTestValueEquivalent, ArgTestValueEquivalent, 
    ArgTestValueEquivalent> MessageBaseTestValueEquivalent;

template<typename TCases, typename... TVariables>
struct TestEquivalent :
    public basic::test::Message<BASIC_TEST, TestEquivalent<TCases, 
        TVariables...>>,
    public basic::test::Case<TestEquivalent<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestEquivalent<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueEquivalent
{
public:
    using MessageBaseTestValueEquivalent::Format;
    using MessageBaseTestValueEquivalent::SetFormat;
    using MessageBaseTestValueEquivalent::Argument;
public:
    using basic::test::Case<TestEquivalent<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestEquivalent<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestEquivalent(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestEquivalent<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestEquivalent<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestEquivalent<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueEquivalent testValueEquivalent;
        SetFormat(info, testValueEquivalent, "Test value "
            "%s::Equivalent(%s(), %s {%s}, %s {%s}) is same with %s\n");
        SetFormat(debug, testValueEquivalent, "Test value "
            "%s::Equivalent(%s(), %s {%s}, %s {%s}) is same with %s\n");
        SetFormat(err, testValueEquivalent, "Error value "
            "%s::Equivalent(%s(), %s {%s}, %s {%s}) is not same with "
            "%s\n");

    }
    template<typename TCategoryTrait, typename TCode, typename TCondition>
    bool Result(const TestValueEquivalent &, 
        VariableTestEquivalent<TCategoryTrait, TCode, TCondition> & var)
    {
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto * cond = basic::test::var::At<IConditionValue>(var).
            Get().Get();
        auto * b = basic::test::var::At<IBoolValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Equivalent(TCategoryTrait {}, *code, *cond);
        return res == *b;
    }

};

typedef basic::test::type::Parameter<TestValueEquivalent> Case1;

typedef VariableTestEquivalent<CategoryTrait1, CodeType, 
    ConditionValueType> T1Var1;
typedef VariableTestEquivalent<CategoryTrait1, CodeValueType,
    ConditionType> T1Var2;
    typedef VariableTestEquivalent<CategoryTrait2, CodeType, 
    ConditionValueType> T1Var3;
typedef VariableTestEquivalent<CategoryTrait2, CodeValueType,
    ConditionType> T1Var4;

auto & tmplCategory1 = basic::err::sys::tmpl::
    Category<CategoryTrait1>::GetInstance();
auto & tmplCategory2 = basic::err::sys::tmpl::
    Category<CategoryTrait2>::GetInstance();

CodeType code1{4, tmplCategory1};
ConditionType cond1{14, tmplCategory1};
ConditionValueType cond_value1{4};
CodeValueType code_value1{14};
bool bool_1{true};

CodeType code2{4, tmplCategory2};
ConditionType cond2{14, tmplCategory2};
ConditionValueType cond_value2{4};
CodeValueType code_value2{14};
bool bool_2{false};

T1Var1 t1_var1{&code1, &cond_value1, &bool_1};
T1Var2 t1_var2{&code_value1, &cond1, &bool_1};
T1Var3 t1_var3{&code2, &cond_value2, &bool_2};
T1Var4 t1_var4{&code_value2, &cond2, &bool_2};

REGISTER_TEST(t1, new TestEquivalent<Case1, T1Var1, T1Var2, T1Var3,
    T1Var4>(t1_var1, t1_var2, t1_var3, t1_var4));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

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

template<>
struct basic::test::out::Argument<CodeType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeType * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(CodeType * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeType *>::ms_cstr;

struct Void1 {};

template<>
struct basic::test::out::Argument<typename std::conditional<std::is_same<
    ConditionValueType, CodeValueType>::value, Void1, 
    ConditionValueType>::type *>
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
    Argument<typename std::conditional<std::is_same<ConditionValueType, 
    CodeValueType>::value, Void1, ConditionValueType>::type *>::ms_cstr;

template<>
struct basic::test::out::Argument<ConditionType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionType * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(ConditionType * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", cond->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionType *>::ms_cstr;


template<>
struct basic::test::out::Argument<bool *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(bool * & b)
    {
        return *b ? "true" : "false"; 
    }
    static const char * Value(bool * && b)
    {
        return *b ? "true" : "false";
    }
};

