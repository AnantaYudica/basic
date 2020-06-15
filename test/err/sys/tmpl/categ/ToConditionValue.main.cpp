#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/categ/ToConditionValue.h"
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

enum class ConditionEnum1
{
    value1 = 4
};

struct CategoryTrait1
{
    typedef ConditionEnum1 ConditionEnumType;
    ConditionValueType ToConditionValue(const ConditionEnum1 & cond) const
    {
        return static_cast<ConditionValueType>(cond) + 10;
    }
    CategoryValueType Value() const
    {
        return 1;
    }
};

struct CategoryTrait2
{
    typedef ConditionEnum1 ConditionEnumType;
    CategoryValueType Value() const
    {
        return 11;
    }
};

struct TestValueToConditionValue {};

char namespace_func_name[] = "basic::err::sys::tmpl::categ";

template<typename TCategoryTrait, typename TConditionEnum>
using VariableTestToConditionValue = basic::test::Variable<
    basic::test::type::Value<const char *, namespace_func_name>,
    TCategoryTrait,
    TConditionEnum,
    basic::test::Value<TConditionEnum *>,
    basic::test::Value<ConditionValueType *>>;

constexpr std::size_t INamespaceTypeValue = 0;
constexpr std::size_t ICategoryTraitType = 1;
constexpr std::size_t IConditionEnumType = 2;
constexpr std::size_t IConditionEnumValue = 3;
constexpr std::size_t IToConditionValueValue = 4;

typedef basic::test::msg::Argument<TestValueToConditionValue,
    basic::test::msg::arg::type::Value<INamespaceTypeValue>,
    basic::test::msg::arg::type::Name<ICategoryTraitType>,
    basic::test::msg::arg::type::Name<IConditionEnumType>,
    basic::test::msg::arg::Value<IConditionEnumValue>,
    basic::test::msg::arg::Value<IToConditionValueValue>> 
        ArgTestValueToConditionValue;

typedef basic::test::msg::Base<TestValueToConditionValue, char, 
    ArgTestValueToConditionValue, ArgTestValueToConditionValue, 
    ArgTestValueToConditionValue> MessageBaseTestValueToConditionValue;

template<typename TCases, typename... TVariables>
struct TestToConditionValue :
    public basic::test::Message<BASIC_TEST, TestToConditionValue<TCases, 
        TVariables...>>,
    public basic::test::Case<TestToConditionValue<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestToConditionValue<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestValueToConditionValue
{
public:
    using MessageBaseTestValueToConditionValue::Format;
    using MessageBaseTestValueToConditionValue::SetFormat;
    using MessageBaseTestValueToConditionValue::Argument;
public:
    using basic::test::Case<TestToConditionValue<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestToConditionValue<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    TestToConditionValue(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestToConditionValue<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestToConditionValue<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestToConditionValue<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestValueToConditionValue testValueToConditionValue;
        SetFormat(info, testValueToConditionValue, "Test value "
            "%s::ToConditionValue(%s(), %s{%s}) is same with %s\n");
        SetFormat(debug, testValueToConditionValue, "Test value "
            "%s::ToConditionValue(%s(), %s{%s}) is same with %s\n");
        SetFormat(err, testValueToConditionValue, "Error value "
            "%s::ToConditionValue(%s(), %s{%s}) is not same with %s\n");

    }
    template<typename TCategoryTrait, typename TConditionEnum>
    bool Result(const TestValueToConditionValue &, 
        VariableTestToConditionValue<TCategoryTrait, TConditionEnum> & var)
    {
        auto * cond_enum = basic::test::var::At<IConditionEnumValue>(var).
            Get().Get();
        auto * cond = basic::test::var::At<IToConditionValueValue>(var).
            Get().Get();
        auto res = basic::err::sys::tmpl::categ::
            ToConditionValue(TCategoryTrait{}, *cond_enum);
        return *cond == res;
    }

};

typedef basic::test::type::Parameter<TestValueToConditionValue> Case1;

typedef VariableTestToConditionValue<CategoryTrait1, ConditionEnum1> T1Var1;
typedef VariableTestToConditionValue<CategoryTrait2, ConditionEnum1> T1Var2;

ConditionEnum1 cond_enum1 = ConditionEnum1::value1;
ConditionValueType cond_val1 = 
    static_cast<ConditionValueType>(cond_enum1) + 10;
ConditionValueType cond_val2 = static_cast<ConditionValueType>(cond_enum1);

T1Var1 t1_var1{&cond_enum1, &cond_val1};
T1Var2 t1_var2{&cond_enum1, &cond_val2};

REGISTER_TEST(t1, new TestToConditionValue<Case1, T1Var1, T1Var2>(t1_var1, 
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);
BASIC_TEST_TYPE_NAME("ConditionEnum1", ConditionEnum1);

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
struct basic::test::out::Argument<ConditionEnum1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(ConditionEnum1 * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<ConditionValueType>(*cond)));
        return *ms_cstr;
    }
    static const char * Value(ConditionEnum1 * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<ConditionValueType>(*cond)));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<ConditionEnum1 *>::ms_cstr;


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

