#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/DefaultCondition.h"
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
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const basic::err::sys::Code & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code.Value() + 10), categ};
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    CategoryTrait2() = default;
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const
    {
        return {static_cast<ConditionValueType>(code - 4), categ};
    }
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct CategoryTrait3
{
    CategoryTrait3() = default;
    CategoryValueType Value() const
    {
        return 111;
    }
};

struct TestValueDefaultCondition {};

char namespaceFuncName[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TCode>
using VariableTestDefaultCondition = basic::test::Variable<
    basic::test::type::Value<const char *, namespaceFuncName>,
    TCategoryTrait,
    TCode,
    basic::err::sys::Condition,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    basic::test::Value<const basic::err::sys::tmpl::
        Category<TCategoryTrait> *>,
    basic::test::Value<TCode *>,
    basic::test::Value<basic::err::sys::Condition *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t IConditionType = 3;
constexpr std::size_t ITmplCategoryType = 4;
constexpr std::size_t ITmplCategoryValue = 5;
constexpr std::size_t ICodeValue = 6;
constexpr std::size_t IConditionValue = 7;

typedef basic::test::msg::Argument<TestValueDefaultCondition,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::Value<IConditionValue>> 
        ArgTestValueDefaultCondition;

typedef basic::test::msg::Base<TestValueDefaultCondition, char, 
    ArgTestValueDefaultCondition, ArgTestValueDefaultCondition, 
    ArgTestValueDefaultCondition> MessageBaseTestValueDefaultCondition;

template<typename TCases, typename... TVariables>
struct TestDefaultCondition :
    public basic::test::Message<BASIC_TEST, TestDefaultCondition<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefaultCondition
{
public:
    using MessageBaseTestValueDefaultCondition::Format;
    using MessageBaseTestValueDefaultCondition::SetFormat;
    using MessageBaseTestValueDefaultCondition::Argument;
public:
    using basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefaultCondition(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefaultCondition<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefaultCondition<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefaultCondition<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueDefaultCondition testValueDefaultCondition;
        SetFormat(info, testValueDefaultCondition, "Test value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCondition, "Test value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCondition, "Error value of "
            "%s::DefaultCondition<%s>(%s(), %s {%s}) is not same with "
            "%s {%s}\n");

    }
    template<typename TCategoryTrait, typename TCode>
    bool Result(const TestValueDefaultCondition &, 
        VariableTestDefaultCondition<TCategoryTrait, TCode> & var)
    {
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto * cond = basic::test::var::At<IConditionValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultCondition(TCategoryTrait {}, *code, *categ);
        return res == *cond;
    }
};

typedef basic::test::type::Parameter<TestValueDefaultCondition> Case1;

typedef VariableTestDefaultCondition<CategoryTrait1, 
    basic::err::sys::Code> T1Var1;
typedef VariableTestDefaultCondition<CategoryTrait2, 
    CodeValueType> T1Var2;
typedef VariableTestDefaultCondition<CategoryTrait3,
    basic::err::sys::Code> T1Var3;
typedef VariableTestDefaultCondition<CategoryTrait3,
    CodeValueType> T1Var4;

auto & tmplCategory1 = basic::err::sys::tmpl::
    Category<CategoryTrait1>::GetInstance();
auto & tmplCategory2 = basic::err::sys::tmpl::
    Category<CategoryTrait2>::GetInstance();
auto & tmplCategory3 = basic::err::sys::tmpl::
    Category<CategoryTrait3>::GetInstance();

basic::err::sys::Code code1{4, tmplCategory1};
basic::err::sys::Condition cond1{14, tmplCategory1};
CodeValueType code2{14};
basic::err::sys::Condition cond2{10, tmplCategory2};
basic::err::sys::Code code3{11, tmplCategory3};
basic::err::sys::Condition cond3{11, tmplCategory3};
CodeValueType code4{44};
basic::err::sys::Condition cond4{44, tmplCategory3};

T1Var1 t1_var1{&tmplCategory1, &code1, &cond1};
T1Var2 t1_var2{&tmplCategory2, &code2, &cond2};
T1Var3 t1_var3{&tmplCategory3, &code3, &cond3};
T1Var4 t1_var4{&tmplCategory3, &code4, &cond4};

REGISTER_TEST(t1, new TestDefaultCondition<Case1, T1Var1, T1Var2,
    T1Var3, T1Var4>(t1_var1, t1_var2, t1_var3, t1_var4));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("basic::err::sys::Code", 
    basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

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
struct basic::test::out::Argument<basic::err::sys::Condition *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Condition * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Condition * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Condition *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::err::sys::Code *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Code * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Code * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", code->Value()));
        return *ms_cstr;
    }
};
basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Code *>::ms_cstr;
