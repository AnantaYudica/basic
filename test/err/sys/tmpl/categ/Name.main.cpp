#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Name.h"
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

struct CategoryTrait1
{
    const CharType * Name() const
    {
        return "CategoryTrait1";
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct TestValueName {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait>
using VariableTestName = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    basic::test::Value<const CharType *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t INameValue = 2;

typedef basic::test::msg::Argument<TestValueName,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::Value<INameValue>> 
        ArgTestValueName;

typedef basic::test::msg::Base<TestValueName, char, 
    ArgTestValueName, ArgTestValueName, 
    ArgTestValueName> MessageBaseTestValueName;

template<typename TCases, typename... TVariables>
struct TestName :
    public basic::test::Message<BASIC_TEST, TestName<TCases, 
        TVariables...>>,
    public basic::test::Case<TestName<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestName<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueName
{
public:
    using MessageBaseTestValueName::Format;
    using MessageBaseTestValueName::SetFormat;
    using MessageBaseTestValueName::Argument;
public:
    using basic::test::Case<TestName<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestName<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestName(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestName<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestName<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestName<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueName testValueName;
        SetFormat(info, testValueName, "Test value "
            "%s::Name(%s()) is same with \"%s\"\n");
        SetFormat(debug, testValueName, "Test value "
            "%s::Name(%s()) is same with \"%s\"\n");
        SetFormat(err, testValueName, "Error value "
            "%s::Name(%s()) is not same with \"%s\"\n");

    }
    template<typename TCategoryTrait>
    bool Result(const TestValueName &, 
        VariableTestName<TCategoryTrait> & var)
    {
        auto * name = basic::test::var::At<INameValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Name(TCategoryTrait{});
        return strcmp(name, res) == 0;
    }

};

typedef basic::test::type::Parameter<TestValueName> Case1;

typedef VariableTestName<CategoryTrait1> T1Var1;
typedef VariableTestName<CategoryTrait2> T1Var2;

const CharType * ch1 = CategoryTrait1{}.Name();
const CharType * ch2 = ""; 

T1Var1 t1_var1{ch1};
T1Var2 t1_var2{ch2};

REGISTER_TEST(t1, new TestName<Case1, T1Var1, T1Var2>(t1_var1, 
    t1_var2));

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

