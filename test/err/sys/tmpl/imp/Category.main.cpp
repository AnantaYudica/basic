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
#include <vector>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;

typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;

template<typename ... TArgs, typename T, typename D>
auto HasDefaultCode_(const basic::err::sys::tmpl::imp::Category<T, D>& t) -> 
    decltype(t.DefaultCode(std::declval<TArgs>()...), std::true_type());

template<typename T, typename ... TArgs>
std::false_type HasDefaultCode_(...);

template<typename T, typename... TArgs>
struct HasDefaultCode
{
    static constexpr bool Value = 
        decltype(HasDefaultCode_<TArgs...>(std::declval<T>()))::value;
};

template<typename ... TArgs, typename T, typename D>
auto HasDefaultCondition_(const  basic::err::sys::tmpl::imp::
    Category<T, D>& t) -> decltype(t.DefaultCondition(
        std::declval<TArgs>()...), std::true_type());

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

constexpr std::size_t IDefaultCode = 0;
constexpr std::size_t IDefaultCondition = 1;

std::vector<std::size_t> CategoryTrait1CallCount(2);

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeEnumType & code,
        const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCode];
        return {4, categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeEnumType & code,
        const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCondition];
        return {static_cast<ConditionValueType>(code), categ};
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

struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestAliasValueType {};
struct TestAliasCodeValueType {};
struct TestAliasConditionValueType {};
struct TestAliasStringType {};
struct TestAliasCodeType {};
struct TestAliasConditionType {};
struct TestAliasCodeSetValueType {};
struct TestBaseOfCategoryBase {};
struct TestBaseOfInterfaceCategory {};
struct TestHasDefaultCodeWithCodeEnum {};
struct TestHasDefaultConditionWithConditionEnum {};
struct TestCallDefaultCode {};
struct TestCallDefaultCondition {};


template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
using VariableTestImpCategory = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::categ::Base<TCategoryTrait>,
    basic::err::sys::intf::Category,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    basic::err::sys::tmpl::imp::Category<TCategoryTrait,
        basic::err::sys::tmpl::Category<TCategoryTrait>>,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::defn::type::sys::categ::Value,
    basic::err::defn::type::sys::code::Value,
    basic::err::defn::type::sys::cond::Value,
    basic::err::msg::String,
    basic::err::sys::Code,
    basic::err::sys::Condition,
    basic::err::sys::tmpl::categ::defn::type::code::set::Value<TCategoryTrait>,
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
constexpr std::size_t ITmplCategoryBaseType = 1;
constexpr std::size_t IInterfaceCategoryType = 2;
constexpr std::size_t ITmplCategoryType = 3;
constexpr std::size_t ITmplImpCategoryType = 4;
constexpr std::size_t IAliasCharType = 5;
constexpr std::size_t IAliasOutputType = 6;
constexpr std::size_t IAliasValueType = 7;
constexpr std::size_t IAliasCodeValueType = 8;
constexpr std::size_t IAliasConditionValueType = 9;
constexpr std::size_t IAliasStringType = 10;
constexpr std::size_t IAliasCodeType = 11;
constexpr std::size_t IAliasConditionType = 12;
constexpr std::size_t IAliasCodeSetValueType = 13;
constexpr std::size_t ICodeType = 14;
constexpr std::size_t IConditionType = 15;
constexpr std::size_t ICodeEnumType = 16;
constexpr std::size_t ICodeValueType = 17;
constexpr std::size_t ICodeEnumValue = 18;
constexpr std::size_t ICodeValueValue = 19;
constexpr std::size_t IHasDefaultCodeEnumValue = 20;
constexpr std::size_t IHasDefaultCodeValueValue = 21;
constexpr std::size_t IHasDefaultConditionEnumValue = 22;
constexpr std::size_t IHasDefaultConditionValueValue = 23;
constexpr std::size_t ICodeValue = 24;
constexpr std::size_t IConditionValue = 25;

typedef basic::test::msg::Argument<TestBaseOfCategoryBase,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<ITmplCategoryBaseType>>
        ArgTestBaseOfCategoryBase;

typedef basic::test::msg::Base<TestBaseOfCategoryBase, char, 
    ArgTestBaseOfCategoryBase, ArgTestBaseOfCategoryBase, 
    ArgTestBaseOfCategoryBase> MessageBaseTestBaseOfCategoryBase;

typedef basic::test::msg::Argument<TestBaseOfInterfaceCategory,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IInterfaceCategoryType>>
        ArgTestBaseOfInterfaceCategory;

typedef basic::test::msg::Base<TestBaseOfInterfaceCategory, char, 
    ArgTestBaseOfInterfaceCategory, ArgTestBaseOfInterfaceCategory, 
    ArgTestBaseOfInterfaceCategory> MessageBaseTestBaseOfInterfaceCategory;

typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasCharType>>
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasOutputType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestAliasValueType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasValueType>>
        ArgTestAliasValueType;

typedef basic::test::msg::Base<TestAliasValueType, char, 
    ArgTestAliasValueType, ArgTestAliasValueType, 
    ArgTestAliasValueType> MessageBaseTestAliasValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasCodeValueType>>
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasConditionValueType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasConditionValueType>>
        ArgTestAliasConditionValueType;

typedef basic::test::msg::Base<TestAliasConditionValueType, char, 
    ArgTestAliasConditionValueType, ArgTestAliasConditionValueType, 
    ArgTestAliasConditionValueType> MessageBaseTestAliasConditionValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasStringType>>
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;

typedef basic::test::msg::Argument<TestAliasCodeType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasCodeType>>
        ArgTestAliasCodeType;

typedef basic::test::msg::Base<TestAliasCodeType, char, 
    ArgTestAliasCodeType, ArgTestAliasCodeType, 
    ArgTestAliasCodeType> MessageBaseTestAliasCodeType;

typedef basic::test::msg::Argument<TestAliasConditionType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasConditionType>>
        ArgTestAliasConditionType;

typedef basic::test::msg::Base<TestAliasConditionType, char, 
    ArgTestAliasConditionType, ArgTestAliasConditionType, 
    ArgTestAliasConditionType> MessageBaseTestAliasConditionType;

typedef basic::test::msg::Argument<TestAliasCodeSetValueType,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<IAliasCodeSetValueType>>
        ArgTestAliasCodeSetValueType;

typedef basic::test::msg::Base<TestAliasCodeSetValueType, char, 
    ArgTestAliasCodeSetValueType, ArgTestAliasCodeSetValueType, 
    ArgTestAliasCodeSetValueType> MessageBaseTestAliasCodeSetValueType;

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

typedef basic::test::msg::Argument<TestCallDefaultCode,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>> 
        ArgTestCallDefaultCode;

typedef basic::test::msg::Base<TestCallDefaultCode, char, 
    ArgTestCallDefaultCode, ArgTestCallDefaultCode, 
    ArgTestCallDefaultCode> MessageBaseTestCallDefaultCode;

typedef basic::test::msg::Argument<TestCallDefaultCondition,
    basic::test::msg::arg::type::Name<ITmplImpCategoryType>,
    basic::test::msg::arg::type::Name<ICodeEnumType>> 
        ArgTestCallDefaultCondition;

typedef basic::test::msg::Base<TestCallDefaultCondition, char, 
    ArgTestCallDefaultCondition, ArgTestCallDefaultCondition, 
    ArgTestCallDefaultCondition> MessageBaseTestCallDefaultCondition;

template<typename TCases, typename... TVariables>
struct TestImpCategory :
    public basic::test::Message<BASIC_TEST, TestImpCategory<TCases, 
        TVariables...>>,
    public basic::test::Case<TestImpCategory<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestImpCategory<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfCategoryBase,
    public MessageBaseTestBaseOfInterfaceCategory,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestAliasValueType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasConditionValueType,
    public MessageBaseTestAliasStringType,
    public MessageBaseTestAliasCodeType,
    public MessageBaseTestAliasConditionType,
    public MessageBaseTestAliasCodeSetValueType,
    public MessageBaseTestHasDefaultCodeWithCodeEnum,
    public MessageBaseTestHasDefaultConditionWithConditionEnum,
    public MessageBaseTestCallDefaultCode,
    public MessageBaseTestCallDefaultCondition
{
public:
    using basic::test::Case<TestImpCategory<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestImpCategory<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfCategoryBase::Format;
    using MessageBaseTestBaseOfCategoryBase::SetFormat;
    using MessageBaseTestBaseOfCategoryBase::Argument;
    using MessageBaseTestBaseOfInterfaceCategory::Format;
    using MessageBaseTestBaseOfInterfaceCategory::SetFormat;
    using MessageBaseTestBaseOfInterfaceCategory::Argument;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestAliasValueType::Format;
    using MessageBaseTestAliasValueType::SetFormat;
    using MessageBaseTestAliasValueType::Argument;
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestAliasConditionValueType::Format;
    using MessageBaseTestAliasConditionValueType::SetFormat;
    using MessageBaseTestAliasConditionValueType::Argument;
    using MessageBaseTestAliasStringType::Format;
    using MessageBaseTestAliasStringType::SetFormat;
    using MessageBaseTestAliasStringType::Argument;
    using MessageBaseTestAliasCodeType::Format;
    using MessageBaseTestAliasCodeType::SetFormat;
    using MessageBaseTestAliasCodeType::Argument;
    using MessageBaseTestAliasConditionType::Format;
    using MessageBaseTestAliasConditionType::SetFormat;
    using MessageBaseTestAliasConditionType::Argument;
    using MessageBaseTestAliasCodeSetValueType::Format;
    using MessageBaseTestAliasCodeSetValueType::SetFormat;
    using MessageBaseTestAliasCodeSetValueType::Argument;
    using MessageBaseTestHasDefaultCodeWithCodeEnum::Format;
    using MessageBaseTestHasDefaultCodeWithCodeEnum::SetFormat;
    using MessageBaseTestHasDefaultCodeWithCodeEnum::Argument;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::Format;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::SetFormat;
    using MessageBaseTestHasDefaultConditionWithConditionEnum::Argument;
    using MessageBaseTestCallDefaultCode::Format;
    using MessageBaseTestCallDefaultCode::SetFormat;
    using MessageBaseTestCallDefaultCode::Argument;
    using MessageBaseTestCallDefaultCondition::Format;
    using MessageBaseTestCallDefaultCondition::SetFormat;
    using MessageBaseTestCallDefaultCondition::Argument;
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

        TestBaseOfCategoryBase testBaseOfCategoryBase;
        SetFormat(info, testBaseOfCategoryBase, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfCategoryBase, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfCategoryBase, 
            "Error Test %s is not base of %s\n");

        TestBaseOfInterfaceCategory testBaseOfInterfaceCategory;
        SetFormat(info, testBaseOfInterfaceCategory, 
            "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfInterfaceCategory, 
            "Test %s is base of %s\n");
        SetFormat(err, testBaseOfInterfaceCategory, 
            "Error Test %s is not base of %s\n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(err, testAliasCharType, "Error alias type "
            "%s::CharType is not same with %s\n");

        TestAliasOutputType testAliasOutputType;
        SetFormat(info, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(debug, testAliasOutputType, "Test alias type "
            "%s::OutputType is same with %s\n");
        SetFormat(err, testAliasOutputType, "Error alias type "
            "%s::OutputType is not same with %s\n");

        TestAliasValueType testAliasValueType;
        SetFormat(info, testAliasValueType, "Test alias type "
            "%s::ValueType is same with %s\n");
        SetFormat(debug, testAliasValueType, "Test alias type "
            "%s::ValueType is same with %s\n");
        SetFormat(err, testAliasValueType, "Error alias type "
            "%s::ValueType is not same with %s\n");

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(err, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType is not same with %s\n");

        TestAliasConditionValueType testAliasConditionValueType;
        SetFormat(info, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(debug, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(err, testAliasConditionValueType, "Error alias type "
            "%s::ConditionValueType is not same with %s\n");

        TestAliasStringType testAliasStringType;
        SetFormat(info, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(debug, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(err, testAliasStringType, "Error alias type "
            "%s::StringType is not same with %s\n");

        TestAliasCodeType testAliasCodeType;
        SetFormat(info, testAliasCodeType, "Test alias type "
            "%s::CodeType is same with %s\n");
        SetFormat(debug, testAliasCodeType, "Test alias type "
            "%s::CodeType is same with %s\n");
        SetFormat(err, testAliasCodeType, "Error alias type "
            "%s::CodeType is not same with %s\n");

        TestAliasConditionType testAliasConditionType;
        SetFormat(info, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(debug, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(err, testAliasConditionType, "Error alias type "
            "%s::ConditionType is not same with %s\n");

        TestAliasCodeSetValueType testAliasCodeSetValueType;
        SetFormat(info, testAliasCodeSetValueType, "Test alias type "
            "%s::CodeSetValueType is same with %s\n");
        SetFormat(debug, testAliasCodeSetValueType, "Test alias type "
            "%s::CodeSetValueType is same with %s\n");
        SetFormat(err, testAliasCodeSetValueType, "Error alias type "
            "%s::CodeSetValueType is not same with %s\n");

        TestHasDefaultCodeWithCodeEnum testHasDefaultCodeWithCodeEnum;
        SetFormat(info, testHasDefaultCodeWithCodeEnum, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultCodeWithCodeEnum, "Test %s has member "
            "function DefaultCode(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultCodeWithCodeEnum, "Error %s has member "
            "function DefaultCode(%s{%s}) is not %s\n");

        TestHasDefaultConditionWithConditionEnum 
            testHasDefaultConditionWithConditionEnum;
        SetFormat(info, testHasDefaultConditionWithConditionEnum, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(debug, testHasDefaultConditionWithConditionEnum, "Test %s "
            "has member function DefaultCondition(%s{%s}) is %s\n");
        SetFormat(err, testHasDefaultConditionWithConditionEnum, "Error %s "
            "has member function DefaultCondition(%s{%s}) is not %s\n");

        TestCallDefaultCode testCallDefaultCode;
        SetFormat(info, testCallDefaultCode, "Test call "
            "%s::DefaultCode(%s) and called once\n");
        SetFormat(debug, testCallDefaultCode, "Test call "
            "%s::DefaultCode(%s) and called once\n");
        SetFormat(err, testCallDefaultCode, "Error member function "
            "%s::DefaultCode(%s) once\n");

        TestCallDefaultCondition testCallDefaultCondition;
        SetFormat(info, testCallDefaultCondition, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(debug, testCallDefaultCondition, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(err, testCallDefaultCondition, "Error member function "
            "%s::DefaultCondition(%s) once\n");

    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestBaseOfCategoryBase &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<ITmplCategoryBaseType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>>::value;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestBaseOfInterfaceCategory &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IInterfaceCategoryType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>>::value;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasCharType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasCharType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type CharType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::CharType).hash_code() == 
            typeid(CharType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasOutputType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasOutputType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type OutputType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasValueType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasValueType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type ValueType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::ValueType).hash_code() == 
            typeid(ValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasCodeValueType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasCodeValueType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type CodeValueType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::CodeValueType).hash_code() == 
            typeid(CodeValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasConditionValueType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasConditionValueType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type ConditionValueType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::ConditionValueType).hash_code() == 
            typeid(ConditionValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasStringType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasStringType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type StringType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::StringType).hash_code() == 
            typeid(StringType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasCodeType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasCodeType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type CodeType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::CodeType).hash_code() == 
            typeid(CodeType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasConditionType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasConditionType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type ConditionType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::ConditionType).hash_code() == 
            typeid(ConditionType).hash_code();
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestAliasCodeSetValueType &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        typedef typename basic::test::var::Element<IAliasCodeSetValueType,
            VariableTestImpCategory<TCategoryTrait, TCodeEnum, 
            TCodeValue>>::Type CodeSetValueType;
        return typeid(typename basic::err::sys::tmpl::imp::
            Category<TCategoryTrait, basic::err::sys::tmpl::Category<
            TCategoryTrait>>::CodeSetValueType).hash_code() == 
            typeid(CodeSetValueType).hash_code();
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
    bool Result(const TestCallDefaultCode &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        auto & code = basic::test::var::At<ICodeEnumValue>(var).Get().Get();
        get.DefaultCode(*code);
        return CategoryTrait1CallCount[IDefaultCode] == 1;
    }
    template<typename TCategoryTrait, typename TCodeEnum, typename TCodeValue>
    bool Result(const TestCallDefaultCondition &, 
        VariableTestImpCategory<TCategoryTrait, TCodeEnum, TCodeValue> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        auto & code = basic::test::var::At<ICodeEnumValue>(var).Get().Get();
        get.DefaultCondition(*code);
        return CategoryTrait1CallCount[IDefaultCondition] == 1;
    }
};

typedef basic::test::type::Parameter<
    TestBaseOfCategoryBase,
    TestBaseOfInterfaceCategory,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasValueType,
    TestAliasCodeValueType,
    TestAliasConditionValueType,
    TestAliasStringType,
    TestAliasCodeType,
    TestAliasConditionType,
    TestAliasCodeSetValueType,
    TestHasDefaultCodeWithCodeEnum,
    TestHasDefaultConditionWithConditionEnum,
    TestCallDefaultCode,
    TestCallDefaultCondition> Case1;

typedef basic::test::type::Parameter<
    TestBaseOfCategoryBase,
    TestBaseOfInterfaceCategory,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasValueType,
    TestAliasCodeValueType,
    TestAliasConditionValueType,
    TestAliasStringType,
    TestAliasCodeType,
    TestAliasConditionType,
    TestAliasCodeSetValueType,
    TestHasDefaultCodeWithCodeEnum,
    TestHasDefaultConditionWithConditionEnum> Case2;

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

BASIC_TEST_TYPE_NAME("basic::err::msg::String", 
    basic::err::msg::String);
BASIC_TEST_TYPE_NAME("basic::err::sys::intf::Category",
    basic::err::sys::intf::Category);

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::categ::Base<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::Base<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

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

template<typename TArg, typename D, bool B>
struct basic::test::type::Name<
    basic::err::sys::tmpl::imp::Category<TArg, D, B>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::imp::Category<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<D>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + tArg1CStr.Size() +
            tArg2CStr.Size() + 5, _format, *tArg1CStr, *tArg2CStr, 
            (B ? "true" : "false"));
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<std::basic_ostream<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::basic_ostream<%s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArg1CStr.Size() + tArg2CStr.Size(), _format, *tArg1CStr,
            *tArg2CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<std::char_traits<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "std::char_traits<%s>";
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
