#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/tmpl/Category.h"
#include "err/defn/type/Char.h"
#include "err/defn/type/Output.h"
#include "err/defn/type/sys/categ/Value.h"
#include "err/defn/type/sys/code/Value.h"
#include "err/defn/type/sys/cond/Value.h"
#include "err/msg/String.h"
#include "err/sys/tmpl/categ/defn/type/code/set/Value.h"
#include "err/sys/tmpl/categ/defn/type/cond/set/Value.h"
#include "err/sys/Code.h"
#include "err/sys/Condition.h"
#include "macro/HasStaticMemberFunction.h"

#include <vector>
#include <type_traits>
#include <sstream>

BASIC_TEST_CONSTRUCT;

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasGetInstance, _HasGetInstance, T, TRet,
    TArgs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, GetInstance);

typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;
typedef basic::err::sys::Code CodeType;
typedef basic::err::sys::Condition ConditionType;
typedef basic::err::msg::String StringType;

typedef basic::err::sys::tmpl::categ::msg::tag::Code CodeTagType;
typedef basic::err::sys::tmpl::categ::msg::tag::Condition
    ConditionTagType;

StringType codeMsg{"code msg"};
StringType condMsg{"condition msg"};
StringType codeMsgTag{"code msg tag"};
StringType condMsgTag{"condition msg tag"};
StringType emptyMsg{""};

enum class CodeEnum1
{
    value1 = 4
};
enum class ConditionEnum1
{
    value1 = 4
};

constexpr std::size_t IDefaultCode1 = 0;
constexpr std::size_t IDefaultCode2 = 1;
constexpr std::size_t IDefaultCodeValue = 2;
constexpr std::size_t IDefaultCondition1 = 3;
constexpr std::size_t IDefaultCondition2 = 4;
constexpr std::size_t IDefaultConditionValue = 5;
constexpr std::size_t IEquivalent1 = 6;
constexpr std::size_t IEquivalent2 = 7;
constexpr std::size_t IMessage1 = 8;
constexpr std::size_t IMessage2 = 9;
constexpr std::size_t IName = 10;
constexpr std::size_t IToCodeValue = 11;
constexpr std::size_t IToConditionValue = 12;
constexpr std::size_t IValue = 13;

std::vector<int> CategoryTrait1CallCount(14, 0);

const char * CategoryTrait1Cstr = "CategoryTrait1"; 

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
    typedef ConditionEnum1 ConditionEnumType;
    int m_value;
    CategoryTrait1(int val) : m_value(val){};
    CategoryTrait1() : m_value(44){};
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCode1];
        return {4, categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCode(const CodeValueType & code,
        const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCode2];
        return {code, categ};
    }
    CodeValueType DefaultCodeValue() const
    {
        ++CategoryTrait1CallCount[IDefaultCodeValue];
        return 4;
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeType & code,
        const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCondition1];
        return {static_cast<ConditionValueType>(code.Value() - 4), categ};
    }
    template<typename TRet, typename TCategory>
    TRet DefaultCondition(const CodeValueType & code,
        const TCategory & categ) const
    {
        ++CategoryTrait1CallCount[IDefaultCondition2];
        return {static_cast<ConditionValueType>(code - 4), categ};
    }
    ConditionValueType DefaultConditionValue() const
    {
        ++CategoryTrait1CallCount[IDefaultConditionValue];
        return 4;
    }
    bool Equivalent(const CodeValueType & code, 
        const ConditionType & cond) const
    {
        ++CategoryTrait1CallCount[IEquivalent1];
        return code == cond.Value();
    }
    bool Equivalent(const CodeType & code, 
        const ConditionValueType & cond) const
    {
        ++CategoryTrait1CallCount[IEquivalent2];
        return code.Value() == cond;
    }
    static CategoryTrait1 Instance()
    {
        return CategoryTrait1{4};
    }
    StringType Message(const CodeType & code) const
    {
        ++CategoryTrait1CallCount[IMessage1];
        return codeMsg;
    }
    StringType Message(const ConditionType & cond) const
    {
        ++CategoryTrait1CallCount[IMessage2];
        return condMsg;
    }
    const CharType * Name() const
    {
        ++CategoryTrait1CallCount[IName];
        return CategoryTrait1Cstr;
    }
    CodeValueType ToCodeValue(const CodeEnum1 & code) const
    {
        ++CategoryTrait1CallCount[IToCodeValue];
        return static_cast<CodeValueType>(code) + 10;
    }
    ConditionValueType ToConditionValue(const ConditionEnum1 & cond) const
    {
        ++CategoryTrait1CallCount[IToConditionValue];
        return static_cast<ConditionValueType>(cond) + 10;
    }
    CategoryValueType Value() const
    {
        ++CategoryTrait1CallCount[IValue];
        return 1;
    }
};

struct CategoryTrait2
{
    CategoryValueType Value() const
    {
        return 2;
    }
};

const char * BoolToString(bool && b)
{
    return (b ? "true" : "false");
}

struct TestBaseOfCategoryBase {};
struct TestBaseOfImplementCategory {};
struct TestBaseOfImplementExit {};
struct TestAliasTraitType {};
struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestAliasValueType {};
struct TestAliasCodeValueType {};
struct TestAliasConditionValueType {};
struct TestAliasStringType {};
struct TestAliasCodeSetValueType {};
struct TestAliasConditionSetValueType {};
struct TestAliasCodeType {};
struct TestAliasConditionType {};
struct TestHasStaticFuncGetInstance {};
struct TestCallDefaultCode1 {};
struct TestCallDefaultCode2 {};
struct TestCallDefaultCodeValue {};
struct TestCallDefaultCondition1 {};
struct TestCallDefaultCondition2{};
struct TestCallDefaultConditionValue {};
struct TestCallEquivalent1 {};
struct TestCallEquivalent2 {};
struct TestCallMessage1 {};
struct TestCallMessage2 {};
struct TestCallName {};
struct TestCallToCodeValue {};
struct TestCallToConditionValue {};
struct TestCallValue {};
struct TestOutput {};
struct TestComparisonEqual {};
struct TestComparisonLess {};

template<typename TCategoryTrait, typename TOtherCategoryTrait>
using VariableTestCategory = basic::test::Variable<
    TCategoryTrait,
    basic::err::sys::tmpl::categ::Base<TCategoryTrait>,
    basic::err::sys::tmpl::imp::Category<TCategoryTrait,
        basic::err::sys::tmpl::Category<TCategoryTrait>>,
    basic::err::sys::tmpl::imp::Exit<TCategoryTrait>,
    basic::err::sys::tmpl::Category<TCategoryTrait>,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::defn::type::sys::categ::Value,
    basic::err::defn::type::sys::code::Value,
    basic::err::defn::type::sys::cond::Value,
    basic::err::msg::String,
    basic::err::sys::tmpl::categ::defn::type::code::set::Value<TCategoryTrait>,
    basic::err::sys::tmpl::categ::defn::type::cond::set::Value<TCategoryTrait>,
    basic::err::sys::Code,
    basic::err::sys::Condition,
    basic::test::Value<const char *>,
    basic::err::sys::tmpl::Category<TOtherCategoryTrait>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::test::type::Function<const char *(bool &&), &BoolToString>>;

constexpr std::size_t ICategoryTraitType = 0;
constexpr std::size_t ICategoryBaseType = 1;
constexpr std::size_t IImplCategoryType = 2;
constexpr std::size_t IImplExitType = 3;
constexpr std::size_t ICategoryType = 4;
constexpr std::size_t ICharType = 5;
constexpr std::size_t IOutputType = 6;
constexpr std::size_t ICategoryValueType = 7;
constexpr std::size_t ICodeValueType = 8;
constexpr std::size_t IConditionValueType = 9;
constexpr std::size_t IStringType = 10;
constexpr std::size_t ICodeSetValueType = 11;
constexpr std::size_t IConditionSetValueType = 12;
constexpr std::size_t ICodeType = 13;
constexpr std::size_t IConditionType = 14;
constexpr std::size_t IOutputValue = 15;
constexpr std::size_t IOtherCategoryType = 16;
constexpr std::size_t IComparisonEqualValue = 17;
constexpr std::size_t IComparisonLessValue = 18;
constexpr std::size_t IBoolToStringFunc = 19;

typedef basic::test::msg::Argument<TestBaseOfCategoryBase,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICategoryBaseType>>
        ArgTestBaseOfCategoryBase;

typedef basic::test::msg::Base<TestBaseOfCategoryBase, char, 
    ArgTestBaseOfCategoryBase, ArgTestBaseOfCategoryBase, 
    ArgTestBaseOfCategoryBase> MessageBaseTestBaseOfCategoryBase;

typedef basic::test::msg::Argument<TestBaseOfImplementCategory,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IImplCategoryType>>
        ArgTestBaseOfImplementCategory;

typedef basic::test::msg::Base<TestBaseOfImplementCategory, char, 
    ArgTestBaseOfImplementCategory, ArgTestBaseOfImplementCategory, 
    ArgTestBaseOfImplementCategory> MessageBaseTestBaseOfImplementCategory;

typedef basic::test::msg::Argument<TestBaseOfImplementExit,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IImplCategoryType>>
        ArgTestBaseOfImplementExit;

typedef basic::test::msg::Base<TestBaseOfImplementExit, char, 
    ArgTestBaseOfImplementExit, ArgTestBaseOfImplementExit, 
    ArgTestBaseOfImplementExit> MessageBaseTestBaseOfImplementExit;

typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICharType>>
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IOutputType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestAliasValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICategoryValueType>>
        ArgTestAliasValueType;

typedef basic::test::msg::Base<TestAliasValueType, char, 
    ArgTestAliasValueType, ArgTestAliasValueType, 
    ArgTestAliasValueType> MessageBaseTestAliasValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasConditionValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionValueType>>
        ArgTestAliasConditionValueType;

typedef basic::test::msg::Base<TestAliasConditionValueType, char, 
    ArgTestAliasConditionValueType, ArgTestAliasConditionValueType, 
    ArgTestAliasConditionValueType> MessageBaseTestAliasConditionValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IStringType>>
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;

typedef basic::test::msg::Argument<TestAliasCodeSetValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeSetValueType>>
        ArgTestAliasCodeSetValueType;

typedef basic::test::msg::Base<TestAliasCodeSetValueType, char, 
    ArgTestAliasCodeSetValueType, ArgTestAliasCodeSetValueType, 
    ArgTestAliasCodeSetValueType> MessageBaseTestAliasCodeSetValueType;

typedef basic::test::msg::Argument<TestAliasConditionSetValueType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionSetValueType>>
        ArgTestAliasConditionSetValueType;

typedef basic::test::msg::Base<TestAliasConditionSetValueType, char, 
    ArgTestAliasConditionSetValueType, ArgTestAliasConditionSetValueType, 
    ArgTestAliasConditionSetValueType> 
        MessageBaseTestAliasConditionSetValueType;

typedef basic::test::msg::Argument<TestAliasCodeType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeType>>
        ArgTestAliasCodeType;

typedef basic::test::msg::Base<TestAliasCodeType, char, 
    ArgTestAliasCodeType, ArgTestAliasCodeType, 
    ArgTestAliasCodeType> MessageBaseTestAliasCodeType;

typedef basic::test::msg::Argument<TestAliasConditionType,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestAliasConditionType;

typedef basic::test::msg::Base<TestAliasConditionType, char, 
    ArgTestAliasConditionType, ArgTestAliasConditionType, 
    ArgTestAliasConditionType> MessageBaseTestAliasConditionType;

typedef basic::test::msg::Argument<TestHasStaticFuncGetInstance,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestHasStaticFuncGetInstance;

typedef basic::test::msg::Base<TestHasStaticFuncGetInstance, char, 
    ArgTestHasStaticFuncGetInstance, ArgTestHasStaticFuncGetInstance, 
    ArgTestHasStaticFuncGetInstance> MessageBaseTestHasStaticFuncGetInstance;

typedef basic::test::msg::Argument<TestCallDefaultCode1,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestCallDefaultCode1;

typedef basic::test::msg::Base<TestCallDefaultCode1, char, 
    ArgTestCallDefaultCode1, ArgTestCallDefaultCode1, 
    ArgTestCallDefaultCode1> MessageBaseTestCallDefaultCode1;

typedef basic::test::msg::Argument<TestCallDefaultCode2,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestCallDefaultCode2;

typedef basic::test::msg::Base<TestCallDefaultCode2, char, 
    ArgTestCallDefaultCode2, ArgTestCallDefaultCode2, 
    ArgTestCallDefaultCode2> MessageBaseTestCallDefaultCode2;

typedef basic::test::msg::Argument<TestCallDefaultCodeValue,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestCallDefaultCodeValue;

typedef basic::test::msg::Base<TestCallDefaultCodeValue, char, 
    ArgTestCallDefaultCodeValue, ArgTestCallDefaultCodeValue, 
    ArgTestCallDefaultCodeValue> MessageBaseTestCallDefaultCodeValue;

typedef basic::test::msg::Argument<TestCallDefaultCondition1,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeType>>
        ArgTestCallDefaultCondition1;

typedef basic::test::msg::Base<TestCallDefaultCondition1, char, 
    ArgTestCallDefaultCondition1, ArgTestCallDefaultCondition1, 
    ArgTestCallDefaultCondition1> MessageBaseTestCallDefaultCondition1;

typedef basic::test::msg::Argument<TestCallDefaultCondition2,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>>
        ArgTestCallDefaultCondition2;

typedef basic::test::msg::Base<TestCallDefaultCondition2, char, 
    ArgTestCallDefaultCondition2, ArgTestCallDefaultCondition2, 
    ArgTestCallDefaultCondition2> MessageBaseTestCallDefaultCondition2;

typedef basic::test::msg::Argument<TestCallDefaultConditionValue,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestCallDefaultConditionValue;

typedef basic::test::msg::Base<TestCallDefaultConditionValue, char, 
    ArgTestCallDefaultConditionValue, ArgTestCallDefaultConditionValue, 
    ArgTestCallDefaultConditionValue> MessageBaseTestCallDefaultConditionValue;

typedef basic::test::msg::Argument<TestCallEquivalent1,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeValueType>,
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestCallEquivalent1;

typedef basic::test::msg::Base<TestCallEquivalent1, char, 
    ArgTestCallEquivalent1, ArgTestCallEquivalent1, 
    ArgTestCallEquivalent1> MessageBaseTestCallEquivalent1;

typedef basic::test::msg::Argument<TestCallEquivalent2,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IConditionValueType>>
        ArgTestCallEquivalent2;

typedef basic::test::msg::Base<TestCallEquivalent2, char, 
    ArgTestCallEquivalent2, ArgTestCallEquivalent2, 
    ArgTestCallEquivalent2> MessageBaseTestCallEquivalent2;

typedef basic::test::msg::Argument<TestCallMessage1,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeType>>
        ArgTestCallMessage1;

typedef basic::test::msg::Base<TestCallMessage1, char, 
    ArgTestCallMessage1, ArgTestCallMessage1, 
    ArgTestCallMessage1> MessageBaseTestCallMessage1;

typedef basic::test::msg::Argument<TestCallMessage2,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestCallMessage2;

typedef basic::test::msg::Base<TestCallMessage2, char, 
    ArgTestCallMessage2, ArgTestCallMessage2, 
    ArgTestCallMessage2> MessageBaseTestCallMessage2;

typedef basic::test::msg::Argument<TestCallName,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestCallName;

typedef basic::test::msg::Base<TestCallName, char, 
    ArgTestCallName, ArgTestCallName, 
    ArgTestCallName> MessageBaseTestCallName;

typedef basic::test::msg::Argument<TestCallToCodeValue,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<ICodeSetValueType>>
        ArgTestCallToCodeValue;

typedef basic::test::msg::Base<TestCallToCodeValue, char, 
    ArgTestCallToCodeValue, ArgTestCallToCodeValue, 
    ArgTestCallToCodeValue> MessageBaseTestCallToCodeValue;

typedef basic::test::msg::Argument<TestCallToConditionValue,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IConditionSetValueType>>
        ArgTestCallToConditionValue;

typedef basic::test::msg::Base<TestCallToConditionValue, char, 
    ArgTestCallToConditionValue, ArgTestCallToConditionValue, 
    ArgTestCallToConditionValue> MessageBaseTestCallToConditionValue;

typedef basic::test::msg::Argument<TestCallValue,
    basic::test::msg::arg::type::Name<ICategoryType>>
        ArgTestCallValue;

typedef basic::test::msg::Base<TestCallValue, char, 
    ArgTestCallValue, ArgTestCallValue, 
    ArgTestCallValue> MessageBaseTestCallValue;

typedef basic::test::msg::Argument<TestOutput,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::Value<IOutputValue>>
        ArgTestOutput;

typedef basic::test::msg::Base<TestOutput, char, 
    ArgTestOutput, ArgTestOutput, 
    ArgTestOutput> MessageBaseTestOutput;

typedef basic::test::msg::Argument<TestComparisonEqual,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IOtherCategoryType>,
    basic::test::msg::arg::type::Function<IBoolToStringFunc,
        basic::test::msg::arg::Value<IComparisonEqualValue>>>
            ArgTestComparisonEqual;

typedef basic::test::msg::Base<TestComparisonEqual, char, 
    ArgTestComparisonEqual, ArgTestComparisonEqual, 
    ArgTestComparisonEqual> MessageBaseTestComparisonEqual;

typedef basic::test::msg::Argument<TestComparisonLess,
    basic::test::msg::arg::type::Name<ICategoryType>,
    basic::test::msg::arg::type::Name<IOtherCategoryType>,
    basic::test::msg::arg::type::Function<IBoolToStringFunc,
        basic::test::msg::arg::Value<IComparisonLessValue>>>
            ArgTestComparisonLess;

typedef basic::test::msg::Base<TestComparisonLess, char, 
    ArgTestComparisonLess, ArgTestComparisonLess, 
    ArgTestComparisonLess> MessageBaseTestComparisonLess;

template<typename TCases, typename... TVariables>
struct TestCategory :
    public basic::test::Message<BASIC_TEST, TestCategory<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCategory<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCategory<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfCategoryBase,
    public MessageBaseTestBaseOfImplementCategory,
    public MessageBaseTestBaseOfImplementExit,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestAliasValueType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasConditionValueType,
    public MessageBaseTestAliasStringType,
    public MessageBaseTestAliasCodeSetValueType,
    public MessageBaseTestAliasConditionSetValueType,
    public MessageBaseTestAliasCodeType,
    public MessageBaseTestAliasConditionType,
    public MessageBaseTestHasStaticFuncGetInstance,
    public MessageBaseTestCallDefaultCode1,
    public MessageBaseTestCallDefaultCode2,
    public MessageBaseTestCallDefaultCodeValue,
    public MessageBaseTestCallDefaultCondition1,
    public MessageBaseTestCallDefaultCondition2,
    public MessageBaseTestCallDefaultConditionValue,
    public MessageBaseTestCallEquivalent1,
    public MessageBaseTestCallEquivalent2,
    public MessageBaseTestCallMessage1,
    public MessageBaseTestCallMessage2,
    public MessageBaseTestCallName,
    public MessageBaseTestCallToCodeValue,
    public MessageBaseTestCallToConditionValue,
    public MessageBaseTestCallValue,
    public MessageBaseTestOutput,
    public MessageBaseTestComparisonEqual,
    public MessageBaseTestComparisonLess
{
public:
    using basic::test::Case<TestCategory<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCategory<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfCategoryBase::Format;
    using MessageBaseTestBaseOfCategoryBase::SetFormat;
    using MessageBaseTestBaseOfCategoryBase::Argument;
    using MessageBaseTestBaseOfImplementCategory::Format;
    using MessageBaseTestBaseOfImplementCategory::SetFormat;
    using MessageBaseTestBaseOfImplementCategory::Argument;
    using MessageBaseTestBaseOfImplementExit::Format;
    using MessageBaseTestBaseOfImplementExit::SetFormat;
    using MessageBaseTestBaseOfImplementExit::Argument;
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
    using MessageBaseTestAliasCodeSetValueType::Format;
    using MessageBaseTestAliasCodeSetValueType::SetFormat;
    using MessageBaseTestAliasCodeSetValueType::Argument;
    using MessageBaseTestAliasConditionSetValueType::Format;
    using MessageBaseTestAliasConditionSetValueType::SetFormat;
    using MessageBaseTestAliasConditionSetValueType::Argument;
    using MessageBaseTestAliasCodeType::Format;
    using MessageBaseTestAliasCodeType::SetFormat;
    using MessageBaseTestAliasCodeType::Argument;
    using MessageBaseTestAliasConditionType::Format;
    using MessageBaseTestAliasConditionType::SetFormat;
    using MessageBaseTestAliasConditionType::Argument;
    using MessageBaseTestHasStaticFuncGetInstance::Format;
    using MessageBaseTestHasStaticFuncGetInstance::SetFormat;
    using MessageBaseTestHasStaticFuncGetInstance::Argument;
    using MessageBaseTestCallDefaultCode1::Format;
    using MessageBaseTestCallDefaultCode1::SetFormat;
    using MessageBaseTestCallDefaultCode1::Argument;
    using MessageBaseTestCallDefaultCode2::Format;
    using MessageBaseTestCallDefaultCode2::SetFormat;
    using MessageBaseTestCallDefaultCode2::Argument;
    using MessageBaseTestCallDefaultCodeValue::Format;
    using MessageBaseTestCallDefaultCodeValue::SetFormat;
    using MessageBaseTestCallDefaultCodeValue::Argument;
    using MessageBaseTestCallDefaultCondition1::Format;
    using MessageBaseTestCallDefaultCondition1::SetFormat;
    using MessageBaseTestCallDefaultCondition1::Argument;
    using MessageBaseTestCallDefaultCondition2::Format;
    using MessageBaseTestCallDefaultCondition2::SetFormat;
    using MessageBaseTestCallDefaultCondition2::Argument;
    using MessageBaseTestCallDefaultConditionValue::Format;
    using MessageBaseTestCallDefaultConditionValue::SetFormat;
    using MessageBaseTestCallDefaultConditionValue::Argument;
    using MessageBaseTestCallEquivalent1::Format;
    using MessageBaseTestCallEquivalent1::SetFormat;
    using MessageBaseTestCallEquivalent1::Argument;
    using MessageBaseTestCallEquivalent2::Format;
    using MessageBaseTestCallEquivalent2::SetFormat;
    using MessageBaseTestCallEquivalent2::Argument;
    using MessageBaseTestCallMessage1::Format;
    using MessageBaseTestCallMessage1::SetFormat;
    using MessageBaseTestCallMessage1::Argument;
    using MessageBaseTestCallMessage2::Format;
    using MessageBaseTestCallMessage2::SetFormat;
    using MessageBaseTestCallMessage2::Argument;
    using MessageBaseTestCallName::Format;
    using MessageBaseTestCallName::SetFormat;
    using MessageBaseTestCallName::Argument;
    using MessageBaseTestCallToCodeValue::Format;
    using MessageBaseTestCallToCodeValue::SetFormat;
    using MessageBaseTestCallToCodeValue::Argument;
    using MessageBaseTestCallToConditionValue::Format;
    using MessageBaseTestCallToConditionValue::SetFormat;
    using MessageBaseTestCallToConditionValue::Argument;
    using MessageBaseTestCallValue::Format;
    using MessageBaseTestCallValue::SetFormat;
    using MessageBaseTestCallValue::Argument;
    using MessageBaseTestOutput::Format;
    using MessageBaseTestOutput::SetFormat;
    using MessageBaseTestOutput::Argument;
    using MessageBaseTestComparisonEqual::Format;
    using MessageBaseTestComparisonEqual::SetFormat;
    using MessageBaseTestComparisonEqual::Argument;
    using MessageBaseTestComparisonLess::Format;
    using MessageBaseTestComparisonLess::SetFormat;
    using MessageBaseTestComparisonLess::Argument;
public:
    TestCategory(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCategory<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCategory<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCategory<TCases, TVariables...>, 
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

        TestBaseOfImplementCategory testBaseOfImplementCategory;
        SetFormat(info, testBaseOfImplementCategory, 
            "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfImplementCategory, 
            "Test %s is base of %s\n");
        SetFormat(err, testBaseOfImplementCategory, 
            "Error Test %s is not base of %s\n");

        TestBaseOfImplementExit testBaseOfImplementExit;
        SetFormat(info, testBaseOfImplementExit, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfImplementExit, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfImplementExit, 
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

        TestAliasCodeSetValueType testAliasCodeSetValueType;
        SetFormat(info, testAliasCodeSetValueType, "Test alias type "
            "%s::CodeSetValueType is same with %s\n");
        SetFormat(debug, testAliasCodeSetValueType, "Test alias type "
            "%s::CodeSetValueType is same with %s\n");
        SetFormat(err, testAliasCodeSetValueType, "Error alias type "
            "%s::CodeSetValueType is not same with %s\n");

        TestAliasConditionSetValueType testAliasConditionSetValueType;
        SetFormat(info, testAliasConditionSetValueType, "Test alias type "
            "%s::ConditionSetValueType is same with %s\n");
        SetFormat(debug, testAliasConditionSetValueType, "Test alias type "
            "%s::ConditionSetValueType is same with %s\n");
        SetFormat(err, testAliasConditionSetValueType, "Error alias type "
            "%s::ConditionSetValueType is not same with %s\n");

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

        TestHasStaticFuncGetInstance testHasStaticFuncGetInstance;
        SetFormat(info, testHasStaticFuncGetInstance, "Test has static "
            "member function %s::GetInstance()\n");
        SetFormat(debug, testHasStaticFuncGetInstance, "Test has static "
            "member function %s::GetInstance()\n");
        SetFormat(err, testHasStaticFuncGetInstance, "Error function "
            "%s::GetInstance() is not static member \n");

        TestCallDefaultCode1 testCallDefaultCode1;
        SetFormat(info, testCallDefaultCode1, "Test call "
            "%s::DefaultCode() and called once\n");
        SetFormat(debug, testCallDefaultCode1, "Test call "
            "%s::DefaultCode() and called once\n");
        SetFormat(err, testCallDefaultCode1, "Error member function "
            "%s::DefaultCode() not called once\n");

        TestCallDefaultCode2 testCallDefaultCode2;
        SetFormat(info, testCallDefaultCode2, "Test call "
            "%s::DefaultCode(%s) and called once\n");
        SetFormat(debug, testCallDefaultCode2, "Test call "
            "%s::DefaultCode(%s) and called once\n");
        SetFormat(err, testCallDefaultCode2, "Error member function "
            "%s::DefaultCode(%s) not called once\n");

        TestCallDefaultCodeValue testCallDefaultCodeValue;
        SetFormat(info, testCallDefaultCodeValue, "Test call "
            "%s::DefaultCodeValue() and called once\n");
        SetFormat(debug, testCallDefaultCodeValue, "Test call "
            "%s::DefaultCodeValue() and called once\n");
        SetFormat(err, testCallDefaultCodeValue, "Error member function "
            "%s::DefaultCodeValue() once\n");

        TestCallDefaultCondition1 testCallDefaultCondition1;
        SetFormat(info, testCallDefaultCondition1, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(debug, testCallDefaultCondition1, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(err, testCallDefaultCondition1, "Error member function "
            "%s::DefaultCondition(%s) not called once\n");

        TestCallDefaultCondition2 testCallDefaultCondition2;
        SetFormat(info, testCallDefaultCondition2, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(debug, testCallDefaultCondition2, "Test call "
            "%s::DefaultCondition(%s) and called once\n");
        SetFormat(err, testCallDefaultCondition2, "Error member function "
            "%s::DefaultCondition(%s) not called once\n");

        TestCallDefaultConditionValue testCallDefaultConditionValue;
        SetFormat(info, testCallDefaultConditionValue, "Test call "
            "%s::DefaultConditionValue() and called once\n");
        SetFormat(debug, testCallDefaultConditionValue, "Test call "
            "%s::DefaultConditionValue() and called once\n");
        SetFormat(err, testCallDefaultConditionValue, "Error member function "
            "%s::DefaultConditionValue() not called once\n");

        TestCallEquivalent1 testCallEquivalent1;
        SetFormat(info, testCallEquivalent1, "Test call "
            "%s::Equivalent(%s, %s) and called once\n");
        SetFormat(debug, testCallEquivalent1, "Test call "
            "%s::Equivalent(%s, %s) and called once\n");
        SetFormat(err, testCallEquivalent1, "Error member function "
            "%s::Equivalent(%s, %s) not called once\n");

        TestCallEquivalent2 testCallEquivalent2;
        SetFormat(info, testCallEquivalent2, "Test call "
            "%s::Equivalent(%s, %s) and called once\n");
        SetFormat(debug, testCallEquivalent2, "Test call "
            "%s::Equivalent(%s, %s) and called once\n");
        SetFormat(err, testCallEquivalent2, "Error member function "
            "%s::Equivalent(%s, %s) not called once\n");

        TestCallMessage1 testCallMessage1;
        SetFormat(info, testCallMessage1, "Test call "
            "%s::Message(%s) and called once\n");
        SetFormat(debug, testCallMessage1, "Test call "
            "%s::Message(%s) and called once\n");
        SetFormat(err, testCallMessage1, "Error member function "
            "%s::Message(%s) not called once\n");

        TestCallMessage2 testCallMessage2;
        SetFormat(info, testCallMessage2, "Test call "
            "%s::Message(%s) and called once\n");
        SetFormat(debug, testCallMessage2, "Test call "
            "%s::Message(%s) and called once\n");
        SetFormat(err, testCallMessage2, "Error member function "
            "%s::Message(%s) not called once\n");

        TestCallName testCallName;
        SetFormat(info, testCallName, "Test call "
            "%s::Name() and called once\n");
        SetFormat(debug, testCallName, "Test call "
            "%s::Name() and called once\n");
        SetFormat(err, testCallName, "Error member function "
            "%s::Name() not called once\n");

        TestCallToCodeValue testCallToCodeValue;
        SetFormat(info, testCallToCodeValue, "Test call "
            "%s::ToCodeValue(%s) and called once\n");
        SetFormat(debug, testCallToCodeValue, "Test call "
            "%s::ToCodeValue(%s) and called once\n");
        SetFormat(err, testCallToCodeValue, "Error member function "
            "%s::ToCodeValue(%s) not called once\n");

        TestCallToConditionValue testCallToConditionValue;
        SetFormat(info, testCallToConditionValue, "Test call "
            "%s::ToConditionValue(%s) and called once\n");
        SetFormat(debug, testCallToConditionValue, "Test call "
            "%s::ToConditionValue(%s) and called once\n");
        SetFormat(err, testCallToConditionValue, "Error member function "
            "%s::ToConditionValue(%s) not called once\n");

        TestCallValue testCallValue;
        SetFormat(info, testCallValue, "Test call "
            "%s::Value() and called once\n");
        SetFormat(debug, testCallValue, "Test call "
            "%s::Value() and called once\n");
        SetFormat(err, testCallValue, "Error member function "
            "%s::Value() not called once\n");

        TestOutput testOutput;
        SetFormat(info, testOutput, "Test output of %s "
            "is equal \"%s\"\n");
        SetFormat(debug, testOutput, "Test output of %s "
            "is equal \"%s\"\n");
        SetFormat(err, testOutput, "Error output of %s "
            "is not equal \"%s\"\n");

        TestComparisonEqual testComparisonEqual;
        SetFormat(info, testComparisonEqual, "Test %s::GetInstance() == "
            "%s::GetInstance() is %s\n");
        SetFormat(debug, testComparisonEqual, "Test %s::GetInstance() == "
            "%s::GetInstance() is %s\n");
        SetFormat(err, testComparisonEqual, "Test %s::GetInstance() == "
            "%s::GetInstance() is not %s\n");

        TestComparisonLess testComparisonLess;
        SetFormat(info, testComparisonLess, "Test %s::GetInstance() < "
            "%s::GetInstance() is %s\n");
        SetFormat(debug, testComparisonLess, "Test %s::GetInstance() < "
            "%s::GetInstance() is %s\n");
        SetFormat(err, testComparisonLess, "Test %s::GetInstance() < "
            "%s::GetInstance() is not %s\n");
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestBaseOfCategoryBase &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICategoryBaseType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::
            Category<TCategoryTrait>>::value;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestBaseOfImplementCategory &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IImplCategoryType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::
            Category<TCategoryTrait>>::value;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestBaseOfImplementExit &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IImplExitType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type BaseType;
        return std::is_base_of<BaseType, basic::err::sys::tmpl::
            Category<TCategoryTrait>>::value;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasCharType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICharType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type CharType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::CharType).hash_code() == 
            typeid(CharType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasOutputType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IOutputType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type OutputType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasValueType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICategoryValueType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type ValueType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::ValueType).hash_code() == 
            typeid(ValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasCodeValueType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICodeValueType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type CodeValueType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::CodeValueType).hash_code() == 
            typeid(CodeValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasConditionValueType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IConditionValueType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type ConditionValueType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::ConditionValueType).hash_code() == 
            typeid(ConditionValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasStringType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IStringType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type StringType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::StringType).hash_code() == 
            typeid(StringType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasCodeSetValueType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICodeSetValueType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type CodeSetValueType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::CodeSetValueType).hash_code() == 
            typeid(CodeSetValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasConditionSetValueType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IConditionSetValueType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type ConditionSetValueType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::ConditionSetValueType).hash_code() == 
            typeid(ConditionSetValueType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasCodeType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICodeType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type CodeType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::CodeType).hash_code() == 
            typeid(CodeType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestAliasConditionType &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<IConditionType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type ConditionType;
        return typeid(typename basic::err::sys::tmpl::
            Category<TCategoryTrait>::ConditionType).hash_code() == 
            typeid(ConditionType).hash_code();
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestHasStaticFuncGetInstance &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        typedef typename basic::test::var::Element<ICategoryType,
            VariableTestCategory<TCategoryTrait, TOtherCategoryTrait>>::
            Type CategoryType;
        return HasGetInstance<CategoryType, const CategoryType &>::Value;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultCode1 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.DefaultCode();
        return CategoryTrait1CallCount[IDefaultCode1] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultCode2 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeValueType code{4};
        get.DefaultCode(code);
        return CategoryTrait1CallCount[IDefaultCode2] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultCodeValue &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.DefaultCodeValue();
        return CategoryTrait1CallCount[IDefaultCodeValue] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultCondition1 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeType code{1, get};
        get.DefaultCondition(code);
        return CategoryTrait1CallCount[IDefaultCondition1] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultCondition2 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeValueType code{4};
        get.DefaultCondition(code);
        return CategoryTrait1CallCount[IDefaultCondition2] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallDefaultConditionValue &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.DefaultConditionValue();
        return CategoryTrait1CallCount[IDefaultConditionValue] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallEquivalent1 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeValueType code_val = 1;
        ConditionType cond{1, get};
        get.Equivalent(code_val, cond);
        return CategoryTrait1CallCount[IEquivalent1] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallEquivalent2 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeType code{1, get};
        ConditionValueType cond_val = 1;
        get.Equivalent(code, cond_val);
        return CategoryTrait1CallCount[IEquivalent2] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallMessage1 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        CodeType code{1, get};
        return CategoryTrait1CallCount[IMessage1] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallMessage2 &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        ConditionType cond{1, get};
        return CategoryTrait1CallCount[IMessage2] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallName &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.Name();
        return CategoryTrait1CallCount[IName] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallToCodeValue &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.ToCodeValue(CodeEnum1::value1);
        return CategoryTrait1CallCount[IToCodeValue] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallToConditionValue &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.ToConditionValue(ConditionEnum1::value1);
        return CategoryTrait1CallCount[IToConditionValue] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestCallValue &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        get.Value();
        return CategoryTrait1CallCount[IValue] == 1;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestOutput &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        auto & str = basic::test::var::At<IOutputValue>(var).Get().Get();
        std::stringstream ss;
        const basic::err::intf::Output & out = 
            static_cast<const basic::err::intf::Output &>(get);
        out >> ss;
        return ss.str().compare(str) == 0;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestComparisonEqual &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        auto & other = basic::err::sys::tmpl::Category<TOtherCategoryTrait>::
            GetInstance();
        auto & res = basic::test::var::At<IComparisonEqualValue>(var).
            Get().Get();
        return (get == other) == res;
    }
    template<typename TCategoryTrait, typename TOtherCategoryTrait>
    bool Result(const TestComparisonLess &, 
        VariableTestCategory<TCategoryTrait, TOtherCategoryTrait> & var)
    {
        auto & get = basic::err::sys::tmpl::Category<TCategoryTrait>::
            GetInstance();
        auto & other = basic::err::sys::tmpl::Category<TOtherCategoryTrait>::
            GetInstance();
        auto & res = basic::test::var::At<IComparisonLessValue>(var).
            Get().Get();
        return (get < other) == res;
    }
};

typedef basic::test::type::Parameter<
    TestBaseOfCategoryBase,
    TestBaseOfImplementCategory,
    TestBaseOfImplementExit,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasValueType,
    TestAliasCodeValueType,
    TestAliasConditionValueType,
    TestAliasStringType,
    TestAliasCodeSetValueType,
    TestAliasConditionSetValueType,
    TestAliasCodeType,
    TestAliasConditionType,
    TestHasStaticFuncGetInstance,
    TestCallMessage1,
    TestCallMessage2,
    TestCallDefaultCodeValue,
    TestCallDefaultCode1,
    TestCallDefaultCode2,
    TestCallDefaultConditionValue,
    TestCallDefaultCondition1,
    TestCallDefaultCondition2,
    TestCallEquivalent1,
    TestCallEquivalent2,
    TestCallName,
    TestCallToCodeValue,
    TestCallToConditionValue,
    TestCallValue,
    TestOutput,
    TestComparisonEqual,
    TestComparisonLess> Case1;


typedef VariableTestCategory<CategoryTrait1, CategoryTrait2> T1Var1;

const char * category1_cstr= "category CategoryTrait1:1";

T1Var1 t1_var1{category1_cstr, false, true};

REGISTER_TEST(t1, new TestCategory<Case1, T1Var1>(t1_var1));

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

BASIC_TEST_TYPE_NAME("basic::err::msg::String", 
    basic::err::msg::String);

BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);
BASIC_TEST_TYPE_NAME("ConditionEnum1", ConditionEnum1);

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

template<typename TArg, bool B>
struct basic::test::type::Name<basic::err::sys::tmpl::imp::Exit<TArg, B>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::imp::Exit<%s, %s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + 
            tArgCStr.Size() + 5, _format, *tArgCStr, (B?"true":"false"));
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
            std::move(basic::test::type::Name<TArg>::CStr());
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

