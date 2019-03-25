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
auto HasDefaultCode_(const basic::err::sys::tmpl::imp::Category<T>& t) -> 
    decltype(t.DefaultCode(std::declval<TArgs>()...), std::true_type());

template<typename T, typename ... TArgs>
std::false_type HasDefaultCode_(...);

template<typename T, typename... TArgs>
struct HasDefaultCode
{
    static constexpr bool Value = 
        decltype(HasDefaultCode_<TArgs...>(std::declval<T>()))::value;
};

template<typename ... TArgs, typename T>
auto HasDefaultCondition_(const  basic::err::sys::tmpl::imp::Category<T>& t) ->
    decltype(t.DefaultCondition(std::declval<TArgs>()...), std::true_type());

template<typename T, typename ... TArgs>
std::false_type HasDefaultCondition_(...);

template<typename T, typename... TArgs>
struct HasDefaultCondition
{
    static constexpr bool Value = 
        decltype(HasDefaultCondition_<TArgs...>(std::declval<T>()))::value;
};

enum class CodeEnum1
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
struct TestValueDefaultCodeWithCodeEnum {};
struct TestValueDefaultCodeWithCodeValue {};
struct TestValueDefaultConditionWithConditionEnum {};
struct TestValueDefaultConditionWithConditionValue {};

template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
using VariableTestImpCategory = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    CodeType,
    ConditionType,
    TCodeEnum,
    TCodeValue,
    basic::test::Value<TCodeEnum *>,
    basic::test::Value<TCodeValue *>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::Value<CodeType *>,
    basic::test::Value<ConditionType *>>;

constexpr std::size_t ICategoryTraitType = 0;
constexpr std::size_t ITmplCategoryType = 1;
constexpr std::size_t ICodeType = 2;
constexpr std::size_t IConditionType = 3;
constexpr std::size_t ICodeEnumType = 4;
constexpr std::size_t ICodeValueType = 5;
constexpr std::size_t ICodeEnumValue = 6;
constexpr std::size_t ICodeValueValue = 7;
constexpr std::size_t IHasDefaultCodeEnumValue = 8;
constexpr std::size_t IHasDefaultCodeValueValue = 9;
constexpr std::size_t IHasDefaultConditionEnumValue = 10;
constexpr std::size_t IHasDefaultConditionValueValue = 11;
constexpr std::size_t ICodeValue = 12;
constexpr std::size_t IConditionValue = 13;

typedef basic::test::msg::Argument<TestHasDefaultCodeWithCodeEnum,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::Value<IHasDefaultCodeEnumValue>> 
        ArgTestHasDefaultCodeWithCodeEnum;

typedef basic::test::msg::Base<TestHasDefaultCodeWithCodeEnum, char, 
    ArgTestHasDefaultCodeWithCodeEnum, ArgTestHasDefaultCodeWithCodeEnum, 
    ArgTestHasDefaultCodeWithCodeEnum> 
        MessageBaseTestHasDefaultCodeWithCodeEnum;

typedef basic::test::msg::Argument<TestHasDefaultCodeWithCodeValue,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValueValue>,
    basic::test::msg::arg::Value<IHasDefaultCodeValueValue>> 
        ArgTestHasDefaultCodeWithCodeValue;

typedef basic::test::msg::Base<TestHasDefaultCodeWithCodeValue, char, 
    ArgTestHasDefaultCodeWithCodeValue, ArgTestHasDefaultCodeWithCodeValue, 
    ArgTestHasDefaultCodeWithCodeValue> 
        MessageBaseTestHasDefaultCodeWithCodeValue;

typedef basic::test::msg::Argument<TestHasDefaultConditionWithConditionEnum,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::Value<IHasDefaultConditionEnumValue>> 
        ArgTestHasDefaultConditionWithConditionEnum;

typedef basic::test::msg::Base<TestHasDefaultConditionWithConditionEnum, char, 
    ArgTestHasDefaultConditionWithConditionEnum, 
    ArgTestHasDefaultConditionWithConditionEnum, 
    ArgTestHasDefaultConditionWithConditionEnum> 
        MessageBaseTestHasDefaultConditionWithConditionEnum;

typedef basic::test::msg::Argument<TestHasDefaultConditionWithConditionValue,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValueValue>,
    basic::test::msg::arg::Value<IHasDefaultConditionValueValue>> 
        ArgTestHasDefaultConditionWithConditionValue;

typedef basic::test::msg::Base<TestHasDefaultConditionWithConditionValue, char,
    ArgTestHasDefaultConditionWithConditionValue, 
    ArgTestHasDefaultConditionWithConditionValue, 
    ArgTestHasDefaultConditionWithConditionValue> 
        MessageBaseTestHasDefaultConditionWithConditionValue;

typedef basic::test::msg::Argument<TestValueDefaultCodeWithCodeEnum,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>> 
        ArgTestValueDefaultCodeWithCodeEnum;

typedef basic::test::msg::Base<TestValueDefaultCodeWithCodeEnum, char,
    ArgTestValueDefaultCodeWithCodeEnum, ArgTestValueDefaultCodeWithCodeEnum, 
    ArgTestValueDefaultCodeWithCodeEnum> 
        MessageBaseTestValueDefaultCodeWithCodeEnum;

typedef basic::test::msg::Argument<TestValueDefaultCodeWithCodeValue,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValueValue>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<ICodeValue>> 
        ArgTestValueDefaultCodeWithCodeValue;

typedef basic::test::msg::Base<TestValueDefaultCodeWithCodeValue, char,
    ArgTestValueDefaultCodeWithCodeValue, ArgTestValueDefaultCodeWithCodeValue,
    ArgTestValueDefaultCodeWithCodeValue> 
        MessageBaseTestValueDefaultCodeWithCodeValue;

typedef basic::test::msg::Argument<TestValueDefaultConditionWithConditionEnum,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>,
    basic::test::msg::arg::Value<ICodeEnumValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::Value<IConditionValue>> 
        ArgTestValueDefaultConditionWithConditionEnum;

typedef basic::test::msg::Base<TestValueDefaultConditionWithConditionEnum, 
    char, ArgTestValueDefaultConditionWithConditionEnum, 
    ArgTestValueDefaultConditionWithConditionEnum,
    ArgTestValueDefaultConditionWithConditionEnum> 
        MessageBaseTestValueDefaultConditionWithConditionEnum;

typedef basic::test::msg::Argument<TestValueDefaultConditionWithConditionValue,
    basic::test::msg::arg::type::Name<ITmplCategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::Value<ICodeValueValue>,
    basic::test::msg::arg::type::Name<IConditionType>,
    basic::test::msg::arg::Value<IConditionValue>> 
        ArgTestValueDefaultConditionWithConditionValue;

typedef basic::test::msg::Base<TestValueDefaultConditionWithConditionValue, 
    char, ArgTestValueDefaultConditionWithConditionValue, 
    ArgTestValueDefaultConditionWithConditionValue,
    ArgTestValueDefaultConditionWithConditionValue> 
        MessageBaseTestValueDefaultConditionWithConditionValue;

template<typename TCases, typename... TVariables>
struct TestImpCategory :
    public basic::test::Message<BASIC_TEST, TestImpCategory<TCases, 
        TVariables...>>,
    public basic::test::Case<TestImpCategory<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestImpCategory<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestHasDefaultCodeWithCodeEnum,
    public MessageBaseTestHasDefaultCodeWithCodeValue,
    public MessageBaseTestHasDefaultConditionWithConditionEnum,
    public MessageBaseTestHasDefaultConditionWithConditionValue,
    public MessageBaseTestValueDefaultCodeWithCodeEnum,
    public MessageBaseTestValueDefaultCodeWithCodeValue,
    public MessageBaseTestValueDefaultConditionWithConditionEnum,
    public MessageBaseTestValueDefaultConditionWithConditionValue
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
    using MessageBaseTestHasDefaultCodeWithCodeValue::Format;
    using MessageBaseTestHasDefaultCodeWithCodeValue::SetFormat;
    using MessageBaseTestHasDefaultCodeWithCodeValue::Argument;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::Format;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::SetFormat;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::Argument;
    using MessageBaseTestHasDefaultConditionWithConditionValue::Format;
    using MessageBaseTestHasDefaultConditionWithConditionValue::SetFormat;
    using MessageBaseTestHasDefaultConditionWithConditionValue::Argument;
    using MessageBaseTestValueDefaultCodeWithCodeEnum::Format;
    using MessageBaseTestValueDefaultCodeWithCodeEnum::SetFormat;
    using MessageBaseTestValueDefaultCodeWithCodeEnum::Argument;
    using MessageBaseTestValueDefaultCodeWithCodeValue::Format;
    using MessageBaseTestValueDefaultCodeWithCodeValue::SetFormat;
    using MessageBaseTestValueDefaultCodeWithCodeValue::Argument;
    using MessageBaseTestValueDefaultConditionWithConditionEnum::Format;
    using MessageBaseTestValueDefaultConditionWithConditionEnum::SetFormat;
    using MessageBaseTestValueDefaultConditionWithConditionEnum::Argument;
    using MessageBaseTestValueDefaultConditionWithConditionValue::Format;
    using MessageBaseTestValueDefaultConditionWithConditionValue::SetFormat;
    using MessageBaseTestValueDefaultConditionWithConditionValue::Argument;
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

        TestHasDefaultCodeWithCodeValue testHasDefaultCodeWithCodeValue;
        SetFormat(info, testHasDefaultCodeWithCodeValue, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultCodeWithCodeValue, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultCodeWithCodeValue, "Test %s has member "
            "function DefaultCode(%s{%s}) is not %s\n");

        TestHasDefaultConditionWithConditionEnum 
            testHasDefaultConditionWithConditionEnum;
        SetFormat(info, testHasDefaultConditionWithConditionEnum, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultConditionWithConditionEnum, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultConditionWithConditionEnum, "Test %s "
            "has member function DefaultCondition(%s{%s}) is not %s\n");

        TestHasDefaultConditionWithConditionValue
            testHasDefaultConditionWithConditionValue;
        SetFormat(info, testHasDefaultConditionWithConditionValue, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultConditionWithConditionValue, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultConditionWithConditionValue, "Test %s "
            "has member function DefaultCondition(%s{%s}) is not %s\n");

        TestValueDefaultCodeWithCodeEnum testValueDefaultCodeWithCodeEnum;
        SetFormat(info, testValueDefaultCodeWithCodeEnum, "Test "
            "value %s::DefaultCode(%s{%s}) is same with %s{%s}\n");
        SetFormat(debug, testValueDefaultCodeWithCodeEnum, "Test "
            "value %s::DefaultCode(%s{%s}) is same with %s{%s}\n");
        SetFormat(err, testValueDefaultCodeWithCodeEnum, "Test "
            "value %s::DefaultCode(%s{%s}) is not same with %s{%s}\n");
        
        TestValueDefaultCodeWithCodeValue testValueDefaultCodeWithCodeValue;
        SetFormat(info, testValueDefaultCodeWithCodeValue, "Test "
            "value %s::DefaultCode(%s{%s}) is same with %s{%s}\n");
        SetFormat(debug, testValueDefaultCodeWithCodeValue, "Test "
            "value %s::DefaultCode(%s{%s}) is same with %s{%s}\n");
        SetFormat(err, testValueDefaultCodeWithCodeValue, "Test "
            "value %s::DefaultCode(%s{%s}) is not same with %s{%s}\n");

        TestValueDefaultConditionWithConditionEnum 
            testValueDefaultConditionWithConditionEnum;
        SetFormat(info, testValueDefaultConditionWithConditionEnum, "Test "
            "value %s::DefaultCondition(%s{%s}) is same with %s{%s}\n");
        SetFormat(debug, testValueDefaultConditionWithConditionEnum, "Test "
            "value %s::DefaultCondition(%s{%s}) is same with %s{%s}\n");
        SetFormat(err, testValueDefaultConditionWithConditionEnum, "Test "
            "value %s::DefaultCondition(%s{%s}) is not same with %s{%s}\n");

        TestValueDefaultConditionWithConditionValue
            testValueDefaultConditionWithConditionValue;
        SetFormat(info, testValueDefaultConditionWithConditionValue, "Test "
            "value %s::DefaultCondition(%s{%s}) is same with %s{%s}\n");
        SetFormat(debug, testValueDefaultConditionWithConditionValue, "Test "
            "value %s::DefaultCondition(%s{%s}) is same with %s{%s}\n");
        SetFormat(err, testValueDefaultConditionWithConditionValue, "Test "
            "value %s::DefaultCondition(%s{%s}) is not same with %s{%s}\n");
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestHasDefaultCodeWithCodeEnum &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        bool has_default_code_enum = basic::test::var::
            At<IHasDefaultCodeEnumValue>(var).Get().Get();
        constexpr bool result = HasDefaultCode<
            basic::err::sys::tmpl::Category<TCategoryTrait>,
            const TCodeEnum &>::Value;
        return has_default_code_enum == result;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestHasDefaultCodeWithCodeValue &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        bool has_default_code_value = basic::test::var::
            At<IHasDefaultCodeValueValue>(var).Get().Get();
        constexpr bool result = HasDefaultCode<
            basic::err::sys::tmpl::Category<TCategoryTrait>,
            const TCodeValue &>::Value;
        return has_default_code_value == result;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestHasDefaultConditionWithConditionEnum &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        bool has_default_cond_enum = basic::test::var::
            At<IHasDefaultConditionEnumValue>(var).Get().Get();
        constexpr bool result = HasDefaultCondition<
            basic::err::sys::tmpl::Category<TCategoryTrait>,
            const TCodeEnum &>::Value;
        return has_default_cond_enum == result;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestHasDefaultConditionWithConditionValue &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        bool has_default_cond_value = basic::test::var::
            At<IHasDefaultConditionValueValue>(var).Get().Get();
        constexpr bool result = HasDefaultCondition<
            basic::err::sys::tmpl::Category<TCategoryTrait>,
            const TCodeValue &>::Value;
        return has_default_cond_value == result;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestValueDefaultCodeWithCodeEnum &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto * code = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * code_enum = basic::test::var::At<ICodeEnumValue>(var).
            Get().Get();
        auto result = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance().DefaultCode(*code_enum);
        return code->Value() == result.Value();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestValueDefaultCodeWithCodeValue &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto * code = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * code_value = basic::test::var::At<ICodeValueValue>(var).
            Get().Get();
        auto result = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance().DefaultCode(*code_value);
        return code->Value() == result.Value();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestValueDefaultConditionWithConditionEnum &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto * cond = basic::test::var::At<IConditionValue>(var).Get().Get();
        auto * code_enum = basic::test::var::At<ICodeEnumValue>(var).
            Get().Get();
        auto result = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance().DefaultCode(*code_enum);
        return cond->Value() == result.Value();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestValueDefaultConditionWithConditionValue &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto * cond = basic::test::var::At<IConditionValue>(var).Get().Get();
        auto * code_value = basic::test::var::At<ICodeValueValue>(var).
            Get().Get();
        auto result = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance().DefaultCode(*code_value);
        return cond->Value() == result.Value();
    }
};

typedef basic::test::type::Parameter<
    TestHasDefaultCodeWithCodeEnum,
    TestHasDefaultCodeWithCodeValue,
    TestHasDefaultConditionWithConditionEnum,
    TestHasDefaultConditionWithConditionValue,
    TestValueDefaultCodeWithCodeEnum,
    TestValueDefaultCodeWithCodeValue,
    TestValueDefaultConditionWithConditionEnum,
    TestValueDefaultConditionWithConditionValue> Case1;

typedef basic::test::type::Parameter<
    TestHasDefaultCodeWithCodeEnum,
    TestHasDefaultCodeWithCodeValue,
    TestHasDefaultConditionWithConditionEnum,
    TestHasDefaultConditionWithConditionValue,
    TestValueDefaultCodeWithCodeValue,
    TestValueDefaultConditionWithConditionValue> Case2;

typedef VariableTestImpCategory<CategoryTrait1, CodeEnum1,
    CodeValueType> T1Var1;
typedef VariableTestImpCategory<CategoryTrait2, CodeEnum1,
    CodeValueType> T1Var2;

CodeEnum1 code_enum1 = CodeEnum1::value1;
CodeValueType code_value1 = 4;
CodeType code1(code_value1, 
    basic::err::sys::tmpl::Category<CategoryTrait1>::GetInstance());
CodeType code2(code_value1, 
    basic::err::sys::tmpl::Category<CategoryTrait2>::GetInstance());
ConditionType cond1(code_value1, 
    basic::err::sys::tmpl::Category<CategoryTrait1>::GetInstance());
ConditionType cond2(code_value1, 
    basic::err::sys::tmpl::Category<CategoryTrait2>::GetInstance());

T1Var1 t1_var1{&code_enum1, &code_value1, true, true, true, true,
    &code1, &cond1};
T1Var2 t1_var2{&code_enum1, &code_value1, false, true, false, true,
    &code2, &cond2};

REGISTER_TEST(t1, new TestImpCategory<Case1, T1Var1>(t1_var1));
REGISTER_TEST(t2, new TestImpCategory<Case2, T1Var2>(t1_var2));

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

template<>
struct basic::test::out::Argument<basic::err::sys::Condition *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Condition * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Condition * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "Value : %d", cond->Value()));
        return *ms_cstr;
    }
};
basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Condition *>::ms_cstr;
