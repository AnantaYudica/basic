#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/DefaultCode.h"
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
    TRet DefaultCode(const TCategory & categ) const
    {
        return {4, categ};
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

struct TestValueDefaultCode {};

char namespaceFuncName[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait>
using VariableTestDefaultCode = basic::test::Variable<
    basic::test::type::Value<const char *, namespaceFuncName>,
    TCategoryTrait,
    basic::err::sys::Code,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    basic::test::Value<const basic::err::sys::tmpl::
        Category<TCategoryTrait> *>,
    basic::test::Value<basic::err::sys::Code *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t ITmplCategoryType = 3;
constexpr std::size_t ITmplCategoryValue = 4;
constexpr std::size_t ICodeValue = 5;

typedef basic::test::msg::Argument<TestValueDefaultCode,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::Value<ITmplCategoryValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>> 
        ArgTestValueDefaultCode;

typedef basic::test::msg::Base<TestValueDefaultCode, char, 
    ArgTestValueDefaultCode, ArgTestValueDefaultCode, 
    ArgTestValueDefaultCode> MessageBaseTestValueDefaultCode;

template<typename TCases, typename... TVariables>
struct TestDefaultCode :
    public basic::test::Message<BASIC_TEST, TestDefaultCode<TCases, 
        TVariables...>>,
    public basic::test::Case<TestDefaultCode<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueDefaultCode
{
public:
    using MessageBaseTestValueDefaultCode::Format;
    using MessageBaseTestValueDefaultCode::SetFormat;
    using MessageBaseTestValueDefaultCode::Argument;
public:
    using basic::test::Case<TestDefaultCode<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestDefaultCode(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestDefaultCode<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestDefaultCode<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestDefaultCode<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueDefaultCode testValueDefaultCode;
        SetFormat(info, testValueDefaultCode, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCode, "Test value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCode, "Error value of "
            "%s::DefaultCode<%s>(%s(), %s {%s}) is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait>
    bool Result(const TestValueDefaultCode &, 
        VariableTestDefaultCode<TCategoryTrait> & var)
    {
        auto * categ = basic::test::var::At<ITmplCategoryValue>(var).
            Get().Get();
        auto * code = basic::test::var::At<ICodeValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            DefaultCode(TCategoryTrait {}, *categ);
        return res == *code;
    }

};

typedef basic::test::type::Parameter<TestValueDefaultCode> Case1;

typedef VariableTestDefaultCode<CategoryTrait1> T1Var1;
typedef VariableTestDefaultCode<CategoryTrait2> T1Var2;

auto & tmplCategory1 = basic::err::sys::tmpl::
    Category<CategoryTrait1>::GetInstance();
auto & tmplCategory2 = basic::err::sys::tmpl::
    Category<CategoryTrait2>::GetInstance();

basic::err::sys::Code code1{4, tmplCategory1};
basic::err::sys::Code code2{0, tmplCategory2};

T1Var1 t1_var1{&tmplCategory1, &code1};
T1Var2 t1_var2{&tmplCategory2, &code2};

REGISTER_TEST(t1, new TestDefaultCode<Case1, T1Var1, T1Var2>(t1_var1,
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);

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
