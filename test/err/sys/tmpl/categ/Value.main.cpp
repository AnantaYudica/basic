#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/Value.h"
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
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{};

struct TestValueValue {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait>
using VariableTestValue = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    CategoryValueType,
    basic::test::Value<CategoryValueType *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t ICategoryValueType = 2;
constexpr std::size_t ICategoryValueValue = 3;

typedef basic::test::msg::Argument<TestValueValue,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<ICategoryValueType>,
    basic::test::msg::arg::Value<ICategoryValueValue>> 
        ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, 
    ArgTestValueValue> MessageBaseTestValueValue;

template<typename TCases, typename... TVariables>
struct TestValue :
    public basic::test::Message<BASIC_TEST, TestValue<TCases, 
        TVariables...>>,
    public basic::test::Case<TestValue<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestValue<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueValue
{
public:
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Argument;
public:
    using basic::test::Case<TestValue<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestValue<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestValue(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestValue<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestValue<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestValue<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test value "
            "%s::Value(%s()) is same with %s {%s}\n");
        SetFormat(debug, testValueValue, "Test value "
            "%s::Value(%s()) is same with %s {%s}\n");
        SetFormat(err, testValueValue, "Error value "
            "%s::Value(%s()) is not same with %s {%s}\n");

    }
    template<typename TCategoryTrait>
    bool Result(const TestValueValue &, 
        VariableTestValue<TCategoryTrait> & var)
    {
        auto * categ = basic::test::var::At<ICategoryValueValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            Value(TCategoryTrait{});
        return *categ == res;
    }

};

typedef basic::test::type::Parameter<TestValueValue> Case1;

typedef VariableTestValue<CategoryTrait1> T1Var1;
typedef VariableTestValue<CategoryTrait2> T1Var2;

CategoryValueType categ1 = CategoryTrait1{}.Value();
CategoryValueType categ2 = 0;

T1Var1 t1_var1{&categ1};
T1Var2 t1_var2{&categ2};

REGISTER_TEST(t1, new TestValue<Case1, T1Var1, T1Var2>(t1_var1, 
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

template<>
struct basic::test::out::Argument<CategoryValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CategoryValueType * & categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *categ));
        return *ms_cstr;
    }
    static const char * Value(CategoryValueType * && categ)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *categ));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CategoryValueType *>::ms_cstr;

