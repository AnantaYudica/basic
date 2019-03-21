#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/imp/Category.h"
#include "err/sys/tmpl/imp/categ/HasCodeEnum.h"
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

typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

template<typename ... TArgs, typename T>
auto HasDefaultCode(const T& t) -> 
    decltype(t.DefaultCode(std::declval<TArgs>()...), std::true_type());

template<typename T, typename ... TArgs>
std::false_type HasDefaultCode(...);

enum class CodeEnum1
{
    value1 = 4
};
enum class ConditionEnum1
{
    value1 = 4
};

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
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

struct TestHasDefaultCodeWithCodeEnum {};
struct TestHasDefaultCodeWithCodeValue {};
struct TestHasDefaultConditionWithConditionEnum {};
struct TestHasDefaultConditionWithConditionValue {};

template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue,
    typename TConditionEnum, typename TConditionValue>
using VariableTestImpCategory = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    TCodeEnum,
    TCodeValue,
    TConditionEnum,
    TConditionValue,
    basic::test::Value<TCodeEnum *>,
    basic::test::Value<TCodeValue *>,
    basic::test::Value<TConditionEnum *>,
    basic::test::Value<TConditionValue *>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>>;

constexpr std::size_t ICategoryTraitType = 0;
constexpr std::size_t ITmplCategoryType = 1;
constexpr std::size_t ICodeEnumType = 2;
constexpr std::size_t ICodeValueType = 3;
constexpr std::size_t IConditionEnumType = 4;
constexpr std::size_t IConditionValueType = 5;
constexpr std::size_t ICodeEnumValue = 6;
constexpr std::size_t ICodeValueValue = 7;
constexpr std::size_t IConditionEnumValue = 8;
constexpr std::size_t IConditionValueValue = 9;
constexpr std::size_t IHasCodeEnumValue = 10;
constexpr std::size_t IHasCodeValueValue = 11;
constexpr std::size_t IHasConditionEnumValue = 12;
constexpr std::size_t IHasConditionValueValue = 13;

typedef basic::test::msg::Argument<TestHasDefaultCodeWithCodeEnum,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::Value<IHasCodeEnumValue>> 
        ArgTestHasDefaultCodeWithCodeEnum;

typedef basic::test::msg::Base<TestHasDefaultCodeWithCodeEnum, char, 
    ArgTestHasDefaultCodeWithCodeEnum, ArgTestHasDefaultCodeWithCodeEnum, 
    ArgTestHasDefaultCodeWithCodeEnum> 
        MessageBaseTestHasDefaultCodeWithCodeEnum;

template<typename TCases, typename... TVariables>
struct TestImpCategory :
    public basic::test::Message<BASIC_TEST, TestImpCategory<TCases, 
        TVariables...>>,
    public basic::test::Case<TestImpCategory<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestImpCategory<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestHasDefaultCodeWithCodeEnum
{
public:
    using basic::test::Case<TestImpCategory<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestImpCategory<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestHasDefaultCodeWithCodeEnum::Format;
    using MessageBaseTestHasDefaultCodeWithCodeEnum::SetFormat;
    using MessageBaseTestHasDefaultCodeWithCodeEnum::Argument;
public:
    TestImpCategory(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestImpCategory<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestImpCategory<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestImpCategory<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestHasDefaultCodeWithCodeEnum testHasDefaultCodeWithCodeEnum;
        SetFormat(info, testHasDefaultCodeWithCodeEnum, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultCodeWithCodeEnum, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultCodeWithCodeEnum, "Test %s has member "
            "function DefaultCode(%s{%s}) is not %s\n");
    }
    template<typename TCategoryTrait, typename TCodeEnum, 
        typename TCodeValue, typename TConditionEnum, typename TConditionValue>
    bool Result(const TestHasDefaultCodeWithCodeEnum &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue,
            TConditionEnum, TConditionValue> & var)
    {
        bool has_default_code_enum = basic::test::var::
            At<IHasCodeEnumValue>(var).Get().Get();
        auto & tmpl_Category = basic::err::sys::tmpl::
            Category<TCategoryTrait>::GetInstance();
        constexpr bool result = decltype(HasDefaultCode<
            const TCodeEnum&>(tmpl_Category))::value;
        return has_default_code_enum == result;
    }
};

typedef basic::test::type::Parameter<TestHasDefaultCodeWithCodeEnum> Case1;

typedef VariableTestImpCategory<CategoryTrait1, CodeEnum1,
    CodeValueType, ConditionEnum1, ConditionValueType> T1Var1;
typedef VariableTestImpCategory<CategoryTrait2, CodeEnum1,
    CodeValueType, ConditionEnum1, ConditionValueType> T1Var2;

CodeEnum1 code_enum1 = CodeEnum1::value1;
CodeValueType code_value1 = 4;
ConditionEnum1 cond_enum1 = ConditionEnum1::value1;
ConditionValueType cond_value1 = 4;

T1Var1 t1_var1{&code_enum1, &code_value1, &cond_enum1, &cond_value1,
    true, true, true, true};
T1Var2 t1_var2{&code_enum1, &code_value1, &cond_enum1, &cond_value1,
    false, true, false, true};

REGISTER_TEST(t1, new TestImpCategory<Case1, T1Var1, T1Var2>(t1_var1,
    t1_var2));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CategoryTrait2", CategoryTrait2);

BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);
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

template<>
struct basic::test::out::Argument<bool>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(bool & b)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%s", (b?"true":"false")));
        return *ms_cstr;
    }
    static const char * Value(bool && b)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%s", (b?"true":"false")));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<bool>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeValueType *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeValueType * & val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *val));
        return *ms_cstr;
    }
    static const char * Value(CodeValueType * && val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *val));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeValueType *>::ms_cstr;

template<>
struct basic::test::out::Argument<CodeEnum1 *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(CodeEnum1 * & val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (int)*val));
        return *ms_cstr;
    }
    static const char * Value(CodeEnum1 * && val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", (int)*val));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<CodeEnum1 *>::ms_cstr;
