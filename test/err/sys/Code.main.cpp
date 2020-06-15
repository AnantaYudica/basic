#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"

#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include <type_traits>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <utility>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

int ToInt(basic::err::defn::type::sys::code::Value * && val_ptr)
{
    return *val_ptr;
};

const char * ToString0(const basic::err::sys::intf::Category * && categ_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"%s:%d\"",
        categ_ptr->Name(), categ_ptr->Value());
    return tmp;
};

const char * ToString0(basic::err::sys::Condition * && cond_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"condition:%d\"",
        cond_ptr->Value());
    return tmp;
};

const char * ToString0(basic::err::sys::Code * && code_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"code:%d\"", code_ptr->Value());
    return tmp;
};

const char * ToString1(basic::err::sys::Code * && code_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"code:%d\"", code_ptr->Value());
    return tmp;
};

const char * ToString0(basic::err::defn::type::sys::code::Value * && code_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"%d\"", *code_ptr);
    return tmp;
};

template<typename TEnum>
const char * ToString0(TEnum * && code_ptr)
{
    static char tmp[BUFFER_FORMAT_CSTRING];
    snprintf(tmp, BUFFER_FORMAT_CSTRING, "\"%s:%d\"", 
        basic::test::type::Name<TEnum>::CStr(),
        static_cast<int>(*code_ptr));
    return tmp;
};

const char * ToString0(bool && b)
{
    static char true_cstr[] = "true";
    static char false_cstr[] = "false";
    return b ? true_cstr : false_cstr;
};

struct TestBaseOfIntfOutput {};
struct TestBaseOfIntfExit {};
struct TestAliasCharType {};
struct TestAliasOutputType {};
struct TestAliasValueType {};
struct TestAliasStringType {};
struct TestAliasCategoryType {};
struct TestAliasConditionType {};
struct TestCallCopyAssignment {};
struct TestCallMoveAssignment {};
struct TestCallAssignment {};
struct TestCallAssign {};
struct TestCallClear {};
struct TestCallCleanup {};
struct TestValueValue {};
struct TestValueCategory {};
struct TestValueDefaultCondition {};
struct TestValueMessage {};
struct TestOutput {};
struct TestComparisonNotEqual {};
struct TestValueComparisonMore {};

enum class CodeEnum1
{
    value1 = 4,
    value2 = 8,
    value3 = 16
};
enum class ConditionEnum1
{
    value1 = 4
};

#define CATEGORY_TRAIT1_MESSAGE "CategoryTrait1::Message"

char CategoryTrait1Message0[] = "";
char CategoryTrait1Message1[] = CATEGORY_TRAIT1_MESSAGE;

struct CategoryTrait1
{
    typedef CodeEnum1 CodeEnumType;
    typedef ConditionEnum1 ConditionEnumType;
    CategoryTrait1() = default;
    const char * Name() const
    {
        static char tmp[] = "CategoryTrait1";
        return tmp;
    }
    basic::err::msg::String 
    Message(const basic::err::defn::type::sys::code::Value & code) const
    {
        return basic::err::msg::String{CategoryTrait1Message1};
    }
    basic::err::defn::type::sys::categ::Value Value() const
    {
        return 14;
    }

};

template<>
struct basic::err::sys::make::Category<CodeEnum1>
{
    Category() = delete;
    static const sys::Category & GetInstance() noexcept
    {
        return tmpl::Category<CategoryTrait1>::GetInstance();
    }
};

template<>
struct basic::err::sys::code::has::Enum<CodeEnum1>
{
    static constexpr bool Value = true;
};

template<
    typename TCallParamType, 
    typename TCallParamValue,
    typename TComparison0ParamType,
    typename TComparison1ParamType,
    typename TComparison0ParamValue,
    typename TComparison1ParamValue,
    std::size_t NComparison>
using VariableTestCode_ = basic::test::Variable<
    basic::err::sys::Code,
    basic::err::sys::Condition,
    basic::err::intf::Output,
    basic::err::intf::Exit,
    basic::err::sys::intf::Category,
    basic::err::defn::type::Char,
    basic::err::defn::type::Output,
    basic::err::defn::type::sys::code::Value,
    basic::err::msg::String,
    basic::test::Value<basic::err::sys::Code *>,
    TCallParamType,
    TCallParamValue,
    basic::test::Value<
        basic::err::defn::type::sys::code::Value *>,
    basic::test::Value<
        const basic::err::sys::intf::Category *>,
    basic::test::Value<basic::err::sys::Condition *>,
    basic::test::Value<const char *>,
    basic::test::Value<const char *>,
    TComparison0ParamType,
    TComparison1ParamType,
    TComparison0ParamValue,
    TComparison1ParamValue,
    basic::test::val::Sequence<bool, NComparison>,
    basic::test::type::Function<
        int(basic::err::defn::type::sys::code::Value *&&), &ToInt>,
    basic::test::type::Function<
        const char *(const basic::err::sys::intf::Category *&&), &ToString0>,
    basic::test::type::Function<
        const char *(basic::err::sys::Code *&&), &ToString0>,
    basic::test::type::Function<
        const char *(basic::err::sys::Code *&&), &ToString1>,
    basic::test::type::Function<
        const char *(basic::err::sys::Condition *&&), &ToString0>,
    basic::test::type::Function<
        const char *(basic::err::defn::type::sys::code::Value *&&), 
            &ToString0>,
    basic::test::type::Function<const char *(bool &&), &ToString0>>;

template<typename TCallArgs, typename TComparison0Args, 
    typename TComparison1Args>
struct VariableTestCode {};

template<typename... TCallArgs, typename... TComparison0Args,
    typename... TComparison1Args>
struct VariableTestCode<basic::test::type::Parameter<TCallArgs...>,
    basic::test::type::Parameter<TComparison0Args...>,
    basic::test::type::Parameter<TComparison1Args...>> : 
        VariableTestCode_< 
            basic::test::type::Parameter<TCallArgs...>,
            basic::test::val::Parameter<TCallArgs *...>,
            basic::test::type::Parameter<TComparison0Args...>,
            basic::test::type::Parameter<TComparison1Args...>,
            basic::test::val::Parameter<TComparison0Args *...>,
            basic::test::val::Parameter<TComparison1Args *...>,
            sizeof...(TComparison0Args)>
{
    typedef VariableTestCode_<
        basic::test::type::Parameter<TCallArgs...>,
        basic::test::val::Parameter<TCallArgs *...>,
        basic::test::type::Parameter<TComparison0Args...>,
        basic::test::type::Parameter<TComparison1Args...>,
        basic::test::val::Parameter<TComparison0Args *...>,
        basic::test::val::Parameter<TComparison1Args *...>,
        sizeof...(TComparison0Args)> BaseType;

    template<typename... TValArgs>
    VariableTestCode(TValArgs&&... val_args) :
        BaseType(std::forward<TValArgs>(val_args)...)
    {}
};

enum : std::size_t
{
    ICodeType,
    IConditionType,
    IIntfOutputType,
    IIntfExitType,
    IIntfCategoryType,
    ICharType,
    IOutputType,
    IValueType,
    IStringType,
    ICodeValue,
    IArgsParamType,
    IArgsParamValue,
    IValueValue,
    ICategoryValue,
    IConditionValue,
    IMessageValue,
    IOutputValue,
    IComparisonArgs0ParamType,
    IComparisonArgs1ParamType,
    IComparisonArgs0ParamValue,
    IComparisonArgs1ParamValue,
    IComparisonResultSeqValue,
    IToIntTypeFunc,
    ICategToString0TypeFunc,
    ICodeToString0TypeFunc,
    ICodeToString1TypeFunc,
    ICondToString0TypeFunc,
    ICodeValToString0TypeFunc,
    IBoolToString0TypeFunc,
};

typedef basic::test::msg::Argument<TestBaseOfIntfOutput,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IIntfOutputType>>
        ArgTestBaseOfIntfOutput;

typedef basic::test::msg::Base<TestBaseOfIntfOutput, char, 
    ArgTestBaseOfIntfOutput, ArgTestBaseOfIntfOutput, 
    ArgTestBaseOfIntfOutput> MessageBaseTestBaseOfIntfOutput;

typedef basic::test::msg::Argument<TestBaseOfIntfExit,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IIntfExitType>>
        ArgTestBaseOfIntfExit;

typedef basic::test::msg::Base<TestBaseOfIntfExit, char, 
    ArgTestBaseOfIntfExit, ArgTestBaseOfIntfExit, 
    ArgTestBaseOfIntfExit> MessageBaseTestBaseOfIntfExit;

typedef basic::test::msg::Argument<TestAliasCharType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<ICharType>>
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasOutputType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IOutputType>>
        ArgTestAliasOutputType;

typedef basic::test::msg::Base<TestAliasOutputType, char, 
    ArgTestAliasOutputType, ArgTestAliasOutputType, 
    ArgTestAliasOutputType> MessageBaseTestAliasOutputType;

typedef basic::test::msg::Argument<TestAliasValueType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IValueType>>
        ArgTestAliasValueType;

typedef basic::test::msg::Base<TestAliasValueType, char, 
    ArgTestAliasValueType, ArgTestAliasValueType, 
    ArgTestAliasValueType> MessageBaseTestAliasValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IStringType>>
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;

typedef basic::test::msg::Argument<TestAliasCategoryType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IIntfCategoryType>>
        ArgTestAliasCategoryType;

typedef basic::test::msg::Base<TestAliasCategoryType, char, 
    ArgTestAliasCategoryType, ArgTestAliasCategoryType, 
    ArgTestAliasCategoryType> MessageBaseTestAliasCategoryType;

typedef basic::test::msg::Argument<TestAliasConditionType,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestAliasConditionType;

typedef basic::test::msg::Base<TestAliasConditionType, char, 
    ArgTestAliasConditionType, ArgTestAliasConditionType, 
    ArgTestAliasConditionType> MessageBaseTestAliasConditionType;

typedef basic::test::msg::Argument<TestCallCopyAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallCopyAssignment;

typedef basic::test::msg::Base<TestCallCopyAssignment, char, 
    ArgTestCallCopyAssignment, ArgTestCallCopyAssignment, 
    ArgTestCallCopyAssignment> MessageBaseTestCallCopyAssignment;

typedef basic::test::msg::Argument<TestCallMoveAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallMoveAssignment;

typedef basic::test::msg::Base<TestCallMoveAssignment, char, 
    ArgTestCallMoveAssignment, ArgTestCallMoveAssignment, 
    ArgTestCallMoveAssignment> MessageBaseTestCallMoveAssignment;

typedef basic::test::msg::Argument<TestCallAssignment,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallAssignment;

typedef basic::test::msg::Base<TestCallAssignment, char, 
    ArgTestCallAssignment, ArgTestCallAssignment, 
    ArgTestCallAssignment> MessageBaseTestCallAssignment;

typedef basic::test::msg::Argument<TestCallAssign,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallAssign;

typedef basic::test::msg::Base<TestCallAssign, char, 
    ArgTestCallAssign, ArgTestCallAssign, 
    ArgTestCallAssign> MessageBaseTestCallAssign;

typedef basic::test::msg::Argument<TestCallClear,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallClear;

typedef basic::test::msg::Base<TestCallClear, char, 
    ArgTestCallClear, ArgTestCallClear, 
    ArgTestCallClear> MessageBaseTestCallClear;

typedef basic::test::msg::Argument<TestCallCleanup,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::param::Name<IArgsParamType>>
        ArgTestCallCleanup;

typedef basic::test::msg::Base<TestCallCleanup, char, 
    ArgTestCallCleanup, ArgTestCallCleanup, 
    ArgTestCallCleanup> MessageBaseTestCallCleanup;

typedef basic::test::msg::Argument<TestValueValue,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Function<IToIntTypeFunc,
        basic::test::msg::arg::Value<IValueValue>>,
    basic::test::msg::arg::type::Name<IValueType>> 
        ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, 
    ArgTestValueValue> MessageBaseTestValueValue;

typedef basic::test::msg::Argument<TestValueCategory,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Function<ICategToString0TypeFunc,
        basic::test::msg::arg::Value<ICategoryValue>>, 
    basic::test::msg::arg::type::Name<IIntfCategoryType>>
        ArgTestValueCategory;

typedef basic::test::msg::Base<TestValueCategory, char, 
    ArgTestValueCategory, ArgTestValueCategory, 
    ArgTestValueCategory> MessageBaseTestValueCategory;

typedef basic::test::msg::Argument<TestValueDefaultCondition,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::type::Function<ICondToString0TypeFunc,
        basic::test::msg::arg::Value<IConditionValue>>, 
    basic::test::msg::arg::type::Name<IConditionType>>
        ArgTestValueDefaultCondition;

typedef basic::test::msg::Base<TestValueDefaultCondition, char, 
    ArgTestValueDefaultCondition, ArgTestValueDefaultCondition, 
    ArgTestValueDefaultCondition> MessageBaseTestValueDefaultCondition;

typedef basic::test::msg::Argument<TestValueMessage,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<IMessageValue>>
        ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, 
    ArgTestValueMessage> MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestOutput,
    basic::test::msg::arg::type::Name<ICodeType>,
    basic::test::msg::arg::Value<IOutputValue>>
        ArgTestOutput;

typedef basic::test::msg::Base<TestOutput, char, 
    ArgTestOutput, ArgTestOutput, 
    ArgTestOutput> MessageBaseTestOutput;

typedef basic::test::msg::Argument<TestComparisonNotEqual,
    basic::test::msg::arg::type::Index<IComparisonArgs0ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Index<IComparisonArgs1ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Function<IBoolToString0TypeFunc,
        basic::test::msg::arg::type::Index<IComparisonResultSeqValue,
            basic::test::msg::arg::val::seq::At>>>
                ArgTestComparisonNotEqual;

typedef basic::test::msg::Base<TestComparisonNotEqual, char, 
    ArgTestComparisonNotEqual, ArgTestComparisonNotEqual, 
    ArgTestComparisonNotEqual> MessageBaseTestComparisonNotEqual;

typedef basic::test::msg::Argument<TestValueComparisonMore,
    basic::test::msg::arg::type::Index<IComparisonArgs0ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Index<IComparisonArgs1ParamType,
        basic::test::msg::arg::type::param::name::At>,
    basic::test::msg::arg::type::Function<IBoolToString0TypeFunc,
        basic::test::msg::arg::type::Index<IComparisonResultSeqValue,
            basic::test::msg::arg::val::seq::At>>>
                ArgTestValueComparisonMore;

typedef basic::test::msg::Base<TestValueComparisonMore, char, 
    ArgTestValueComparisonMore, ArgTestValueComparisonMore, 
    ArgTestValueComparisonMore> MessageBaseTestValueComparisonMore;

template<typename TCases, typename... TVariables>
struct TestCode :
    public basic::test::Message<BASIC_TEST, TestCode<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCode<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCode<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestBaseOfIntfOutput,
    public MessageBaseTestBaseOfIntfExit,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasOutputType,
    public MessageBaseTestAliasValueType,
    public MessageBaseTestAliasStringType,
    public MessageBaseTestAliasCategoryType,
    public MessageBaseTestAliasConditionType,
    public MessageBaseTestCallCopyAssignment,
    public MessageBaseTestCallMoveAssignment,
    public MessageBaseTestCallAssignment,
    public MessageBaseTestCallAssign,
    public MessageBaseTestCallClear,
    public MessageBaseTestCallCleanup,
    public MessageBaseTestValueValue,
    public MessageBaseTestValueCategory,
    public MessageBaseTestValueDefaultCondition,
    public MessageBaseTestValueMessage,
    public MessageBaseTestOutput,
    public MessageBaseTestComparisonNotEqual,
    public MessageBaseTestValueComparisonMore
{
public:
    using basic::test::Case<TestCode<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCode<TCases, TVariables...>, 
        TVariables...>::Run;
public:
    using MessageBaseTestBaseOfIntfOutput::SetFormat;
    using MessageBaseTestBaseOfIntfOutput::Format;
    using MessageBaseTestBaseOfIntfOutput::Argument;
    using MessageBaseTestBaseOfIntfExit::SetFormat;
    using MessageBaseTestBaseOfIntfExit::Format;
    using MessageBaseTestBaseOfIntfExit::Argument;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasOutputType::SetFormat;
    using MessageBaseTestAliasOutputType::Format;
    using MessageBaseTestAliasOutputType::Argument;
    using MessageBaseTestAliasValueType::SetFormat;
    using MessageBaseTestAliasValueType::Format;
    using MessageBaseTestAliasValueType::Argument;
    using MessageBaseTestAliasStringType::SetFormat;
    using MessageBaseTestAliasStringType::Format;
    using MessageBaseTestAliasStringType::Argument;
    using MessageBaseTestAliasCategoryType::SetFormat;
    using MessageBaseTestAliasCategoryType::Format;
    using MessageBaseTestAliasCategoryType::Argument;
    using MessageBaseTestAliasConditionType::SetFormat;
    using MessageBaseTestAliasConditionType::Format;
    using MessageBaseTestAliasConditionType::Argument;
    using MessageBaseTestCallCopyAssignment::SetFormat;
    using MessageBaseTestCallCopyAssignment::Format;
    using MessageBaseTestCallCopyAssignment::Argument;
    using MessageBaseTestCallMoveAssignment::SetFormat;
    using MessageBaseTestCallMoveAssignment::Format;
    using MessageBaseTestCallMoveAssignment::Argument;
    using MessageBaseTestCallAssignment::SetFormat;
    using MessageBaseTestCallAssignment::Format;
    using MessageBaseTestCallAssignment::Argument;
    using MessageBaseTestCallAssign::SetFormat;
    using MessageBaseTestCallAssign::Format;
    using MessageBaseTestCallAssign::Argument;
    using MessageBaseTestCallClear::SetFormat;
    using MessageBaseTestCallClear::Format;
    using MessageBaseTestCallClear::Argument;
    using MessageBaseTestCallCleanup::SetFormat;
    using MessageBaseTestCallCleanup::Format;
    using MessageBaseTestCallCleanup::Argument;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::Argument;
    using MessageBaseTestValueCategory::SetFormat;
    using MessageBaseTestValueCategory::Format;
    using MessageBaseTestValueCategory::Argument;
    using MessageBaseTestValueDefaultCondition::SetFormat;
    using MessageBaseTestValueDefaultCondition::Format;
    using MessageBaseTestValueDefaultCondition::Argument;
    using MessageBaseTestValueMessage::SetFormat;
    using MessageBaseTestValueMessage::Format;
    using MessageBaseTestValueMessage::Argument;
    using MessageBaseTestOutput::SetFormat;
    using MessageBaseTestOutput::Format;
    using MessageBaseTestOutput::Argument;
    using MessageBaseTestComparisonNotEqual::SetFormat;
    using MessageBaseTestComparisonNotEqual::Format;
    using MessageBaseTestComparisonNotEqual::Argument;
    using MessageBaseTestValueComparisonMore::SetFormat;
    using MessageBaseTestValueComparisonMore::Format;
    using MessageBaseTestValueComparisonMore::Argument;
public:
    TestCode(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCode<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCode<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCode<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        TestBaseOfIntfOutput testBaseOfIntfOutput;
        SetFormat(info, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfIntfOutput, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfIntfOutput, 
            "Error Test %s is not base of %s\n");
        
        TestBaseOfIntfExit testBaseOfIntfExit;
        SetFormat(info, testBaseOfIntfExit, "Test %s is base of %s\n");
        SetFormat(debug, testBaseOfIntfExit, "Test %s is base of %s\n");
        SetFormat(err, testBaseOfIntfExit, 
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

        TestAliasStringType testAliasStringType;
        SetFormat(info, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(debug, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(err, testAliasStringType, "Error alias type "
            "%s::StringType is not same with %s\n");

        TestAliasCategoryType testAliasCategoryType;
        SetFormat(info, testAliasCategoryType, "Test alias type "
            "%s::CategoryType is same with %s\n");
        SetFormat(debug, testAliasCategoryType, "Test alias type "
            "%s::CategoryType is same with %s\n");
        SetFormat(err, testAliasCategoryType, "Error alias type "
            "%s::CategoryType is not same with %s\n");

        TestAliasConditionType testAliasConditionType;
        SetFormat(info, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(debug, testAliasConditionType, "Test alias type "
            "%s::ConditionType is same with %s\n");
        SetFormat(err, testAliasConditionType, "Error alias type "
            "%s::ConditionType is not same with %s\n");

        TestCallCopyAssignment testCallCopyAssignment;
        SetFormat(info, testCallCopyAssignment, "Test Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallCopyAssignment, "Test Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallCopyAssignment, "Error Call %s "
            "Copy Assignment with {%s} as parameter(s) type\n");
        
        TestCallMoveAssignment testCallMoveAssignment;
        SetFormat(info, testCallMoveAssignment, "Test Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallMoveAssignment, "Test Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallMoveAssignment, "Error Call %s "
            "Move Assignment with {%s} as parameter(s) type\n");

        TestCallAssignment testCallAssignment;
        SetFormat(info, testCallAssignment, "Test Call %s "
            "Assignment with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallAssignment, "Test Call %s "
            "Assignment with {%s} as parameter(s) type\n");
        SetFormat(err, testCallAssignment, "Error Call %s "
            "Assignment with {%s} as parameter(s) type\n");

        TestCallAssign testCallAssign;
        SetFormat(info, testCallAssign, "Test Call %s::"
            "Assign with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallAssign, "Test Call %s::"
            "Assign with {%s} as parameter(s) type\n");
        SetFormat(err, testCallAssign, "Error Call %s::"
            "Assign with {%s} as parameter(s) type\n");

        TestCallClear testCallClear;
        SetFormat(info, testCallClear, "Test Call %s::"
            "Clear with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallClear, "Test Call %s::"
            "Clear with {%s} as parameter(s) type\n");
        SetFormat(err, testCallClear, "Error Call %s::"
            "Clear with {%s} as parameter(s) type\n");

        TestCallCleanup testCallCleanup;
        SetFormat(info, testCallCleanup, "Test Call %s::"
            "cleanup with {%s} as parameter(s) type\n");
        SetFormat(debug, testCallCleanup, "Test Call %s::"
            "cleanup with {%s} as parameter(s) type\n");
        SetFormat(err, testCallCleanup, "Error Call %s::"
            "cleanup with {%s} as parameter(s) type\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test Value %s::"
            "Value() is same with %d {%s}\n");
        SetFormat(debug, testValueValue, "Test Value %s::"
            "Value() is same with %d {%s}\n");
        SetFormat(err, testValueValue, "Error Value %s::"
            "Value() is not same with %d {%s}\n");
        
        TestValueCategory testValueCategory;
        SetFormat(info, testValueCategory, "Test Value %s::"
            "Category() is same with %s {%s}\n");
        SetFormat(debug, testValueCategory, "Test Value %s::"
            "Category() is same with %s {%s}\n");
        SetFormat(err, testValueCategory, "Error Value %s::"
            "Category() is not same with %s {%s}\n");

        TestValueDefaultCondition testValueDefaultCondition;
        SetFormat(info, testValueDefaultCondition, "Test Value %s::"
            "DefaultCondition() is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCondition, "Test Value %s::"
            "DefaultCondition() is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCondition, "Error Value %s::"
            "DefaultCondition() is not same with %s {%s}\n");

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test Value %s::"
            "Message() is same with \"%s\"\n");
        SetFormat(debug, testValueMessage, "Test Value %s::"
            "Message() is same with \"%s\"\n");
        SetFormat(err, testValueMessage, "Error Value %s::"
            "Message() is not same with \"%s\"\n");

        TestOutput testOutput;
        SetFormat(info, testOutput, "Test output %s "
            "is same with \"%s\"\n");
        SetFormat(debug, testOutput, "Test output %s "
            "is same with \"%s\"\n");
        SetFormat(err, testOutput, "Error output %s "
            "is not same with \"%s\"\n");

        TestComparisonNotEqual testComparisonNotEqual;
        SetFormat(info, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(debug, testComparisonNotEqual, "Test comparison equal "
            "between %s and %s is %s\n");
        SetFormat(err, testComparisonNotEqual, "Error comparison equal "
            "between %s and %s is not %s\n");

        TestValueComparisonMore testValueComparisonMore;
        SetFormat(info, testValueComparisonMore, "Test comparison more than "
            "between %s and %s is %s\n");
        SetFormat(debug, testValueComparisonMore, "Test comparison more than "
            "between %s and %s is %s\n");
        SetFormat(err, testValueComparisonMore, "Error comparison more than "
            "between %s and %s is not %s\n");
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfIntfOutput &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfOutputType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return std::is_base_of<BaseType, CodeType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestBaseOfIntfExit &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfExitType,
            basic::test::Variable<TArgs...>>::Type BaseType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return std::is_base_of<BaseType, CodeType>::value;
    }
    template<typename... TArgs>
    bool Result(const TestAliasCharType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<ICharType,
            basic::test::Variable<TArgs...>>::Type CharType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::CharType).hash_code() == 
            typeid(CharType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasOutputType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IOutputType,
            basic::test::Variable<TArgs...>>::Type OutputType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::OutputType).hash_code() == 
            typeid(OutputType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasValueType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IValueType,
            basic::test::Variable<TArgs...>>::Type ValueType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::ValueType).hash_code() == 
            typeid(ValueType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasStringType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IStringType,
            basic::test::Variable<TArgs...>>::Type StringType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::StringType).hash_code() == 
            typeid(StringType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasCategoryType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IIntfCategoryType,
            basic::test::Variable<TArgs...>>::Type CategoryType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::CategoryType).hash_code() == 
            typeid(CategoryType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestAliasConditionType &, 
        basic::test::Variable<TArgs...> & var)
    {
        typedef typename basic::test::var::Element<IConditionType,
            basic::test::Variable<TArgs...>>::Type ConditionType;
        typedef typename basic::test::var::Element<ICodeType,
            basic::test::Variable<TArgs...>>::Type CodeType;
        return typeid(typename CodeType::ConditionType).hash_code() == 
            typeid(ConditionType).hash_code();
    }
    template<typename... TArgs>
    bool Result(const TestCallCopyAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = *arg0_ptr;
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallMoveAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = std::move(*arg0_ptr);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallAssignment &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        *obj_ptr = *arg0_ptr;
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallAssign &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<0>();
        auto * arg1_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<1>();
        if (!obj_ptr || !arg0_ptr || !arg1_ptr) return false;
        obj_ptr->Assign(*arg0_ptr, *arg1_ptr);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallClear &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        if (!obj_ptr) return false;
        obj_ptr->Clear();
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestCallCleanup &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * arg0_ptr = basic::test::var::At<IArgsParamValue>(var).Get().
            template At<0>();
        if (!obj_ptr || !arg0_ptr) return false;
        auto * exit_ptr = dynamic_cast<basic::err::intf::Exit *>(obj_ptr);
        if (!exit_ptr) return false;
        exit_ptr->Cleanup(*arg0_ptr);
        return true;
    }
    template<typename... TArgs>
    bool Result(const TestValueValue &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * val_ptr = basic::test::var::At<IValueValue>(var).Get().Get();
        if (!obj_ptr || !val_ptr) return false;
        return obj_ptr->Value() == *val_ptr;
    }
    template<typename... TArgs>
    bool Result(const TestValueCategory &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * categ_ptr = basic::test::var::At<ICategoryValue>(var).
            Get().Get();
        if (!obj_ptr || !categ_ptr) return false;
        return obj_ptr->Category() == *categ_ptr;
    }
    template<typename... TArgs>
    bool Result(const TestValueDefaultCondition &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * cond_ptr = basic::test::var::At<IConditionValue>(var).
            Get().Get();
        if (!obj_ptr || !cond_ptr) return false;
        return obj_ptr->DefaultCondition() == *cond_ptr;
    }
    template<typename... TArgs>
    bool Result(const TestValueMessage &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * message = basic::test::var::At<IMessageValue>(var).
            Get().Get();
        if (!obj_ptr || !message) return false;
        return std::strcmp(obj_ptr->Message(), message) == 0;
    }
    template<typename... TArgs>
    bool Result(const TestOutput &, 
        basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<ICodeValue>(var).Get().Get();
        auto * output = basic::test::var::At<IOutputValue>(var).
            Get().Get();
        if (!obj_ptr || !output) return false;
        std::stringstream ss;
        const basic::err::intf::Output & out = 
            static_cast<const basic::err::intf::Output &>(*obj_ptr);
        out >> ss;
        return ss.str().compare(output) == 0;
    }
    template<std::size_t ICaseId, typename... TArgs>
    bool Result(const basic::test::type::Index<TestComparisonNotEqual, 
        ICaseId> &, basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<
            IComparisonArgs0ParamValue>(var).Get().template At<ICaseId>();
        auto * other_ptr = basic::test::var::At<
            IComparisonArgs1ParamValue>(var).Get().template At<ICaseId>();
        auto & res = basic::test::var::At<IComparisonResultSeqValue>(var).
            Get().template At<ICaseId>();
        if (!obj_ptr || !other_ptr) return false;
        return (*obj_ptr != *other_ptr) == res;
    }
    template<std::size_t ICaseId, typename... TArgs>
    bool Result(const basic::test::type::Index<TestValueComparisonMore, 
        ICaseId> &, basic::test::Variable<TArgs...> & var)
    {
        auto * obj_ptr = basic::test::var::At<
            IComparisonArgs0ParamValue>(var).Get().template At<ICaseId>();
        auto * other_ptr = basic::test::var::At<
            IComparisonArgs1ParamValue>(var).Get().template At<ICaseId>();
        auto & res = basic::test::var::At<IComparisonResultSeqValue>(var).
            Get().template At<ICaseId>();
        if (!obj_ptr || !other_ptr) return false;
        return (*obj_ptr > *other_ptr) == res;
    }
};

typedef basic::test::type::Parameter<
    TestBaseOfIntfOutput,
    TestBaseOfIntfExit,
    TestAliasCharType,
    TestAliasOutputType,
    TestAliasValueType,
    TestAliasStringType,
    TestAliasCategoryType,
    TestAliasConditionType,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case1;

typedef basic::test::type::Parameter<
    TestCallCopyAssignment,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case2;

typedef basic::test::type::Parameter<
    TestCallMoveAssignment,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case3;

typedef basic::test::type::Parameter<
    TestCallAssignment,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case4;

typedef basic::test::type::Parameter<
    TestCallAssign,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case5;

typedef basic::test::type::Parameter<
    TestCallClear,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case6;

typedef basic::test::type::Parameter<
    TestCallCleanup,
    TestValueValue,
    TestValueCategory,
    TestValueDefaultCondition,
    TestValueMessage,
    TestOutput> Case7;

typedef basic::test::type::Parameter<
    basic::test::type::Index<TestComparisonNotEqual, 0>,
    basic::test::type::Index<TestComparisonNotEqual, 1>,
    basic::test::type::Index<TestComparisonNotEqual, 2>,
    basic::test::type::Index<TestComparisonNotEqual, 3>,
    basic::test::type::Index<TestComparisonNotEqual, 4>,
    basic::test::type::Index<TestComparisonNotEqual, 5>,
    basic::test::type::Index<TestComparisonNotEqual, 6>> Case8;

typedef basic::test::type::Parameter<
    basic::test::type::Index<TestValueComparisonMore, 0>,
    basic::test::type::Index<TestValueComparisonMore, 1>,
    basic::test::type::Index<TestValueComparisonMore, 2>,
    basic::test::type::Index<TestValueComparisonMore, 3>,
    basic::test::type::Index<TestValueComparisonMore, 4>,
    basic::test::type::Index<TestValueComparisonMore, 5>,
    basic::test::type::Index<TestValueComparisonMore, 6>> Case9;

typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T1Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::sys::Code>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T2Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::sys::Code>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T3Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        CodeEnum1>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T4Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<
        basic::err::defn::type::sys::code::Value,
        const basic::err::sys::intf::Category>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T5Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T6Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<int>,
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<>> T7Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<
        basic::err::sys::Code,
        basic::err::sys::Code,
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value,
        basic::err::defn::type::sys::code::Value,
        CodeEnum1,
        CodeEnum1>,
    basic::test::type::Parameter<
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value,
        CodeEnum1,
        basic::err::sys::Code,
        CodeEnum1,
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value>> T8Var1;
typedef VariableTestCode<
    basic::test::type::Parameter<>,
    basic::test::type::Parameter<
        basic::err::sys::Code,
        basic::err::sys::Code,
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value,
        basic::err::defn::type::sys::code::Value,
        CodeEnum1,
        CodeEnum1>,
    basic::test::type::Parameter<
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value,
        CodeEnum1,
        basic::err::sys::Code,
        CodeEnum1,
        basic::err::sys::Code,
        basic::err::defn::type::sys::code::Value>> T9Var1;

#define BASE_TYPE(T) typename T::BaseType

auto & categ1 = basic::err::sys::tmpl::Category<CategoryTrait1>::GetInstance();

basic::err::sys::Code code1_1{CodeEnum1::value1};
basic::err::sys::Code code1_2{code1_1};
basic::err::sys::Code code1_3{code1_1};
basic::err::sys::Code code1_4{std::move(code1_3)};
basic::err::defn::type::sys::code::Value code_val1_1{4};
basic::err::defn::type::sys::code::Value code_val1_2{0};
basic::err::sys::Condition cond_val1_1{4, categ1};
basic::err::sys::Condition cond_val1_2{0, categ1};
char output1_1[] = "code 4 msg " CATEGORY_TRAIT1_MESSAGE;
char output1_2[] = "code 0 msg " CATEGORY_TRAIT1_MESSAGE;

T1Var1 t1_var1{&code1_1, &code_val1_1, &categ1, &cond_val1_1, 
    CategoryTrait1Message1, output1_1};
T1Var1 t1_var2{&code1_2, &code_val1_1, &categ1, &cond_val1_1, 
    CategoryTrait1Message1, output1_1};
T1Var1 t1_var3{&code1_4, &code_val1_1, &categ1, &cond_val1_1, 
    CategoryTrait1Message1, output1_1};
T1Var1 t1_var4{&code1_3, &code_val1_2, &categ1, &cond_val1_2, 
    CategoryTrait1Message1, output1_2};

REGISTER_TEST(t1, new TestCode<Case1, BASE_TYPE(T1Var1), BASE_TYPE(T1Var1),
    BASE_TYPE(T1Var1), BASE_TYPE(T1Var1)>(t1_var1, t1_var2, t1_var3, t1_var4));

basic::err::sys::Code code2_1_1{CodeEnum1::value1};
basic::err::sys::Code code2_1_2{CodeEnum1::value2};
basic::err::defn::type::sys::code::Value code_val2_1{8};
basic::err::sys::Condition cond_val2_1{8, categ1};
char output2[] = "code 8 msg " CATEGORY_TRAIT1_MESSAGE;

T2Var1 t2_var1{&code2_1_1, &code2_1_2, &code_val2_1, &categ1, &cond_val2_1,
    CategoryTrait1Message1, output2};

REGISTER_TEST(t2, new TestCode<Case2, BASE_TYPE(T2Var1)>(t2_var1));

basic::err::sys::Code code3_1_1{CodeEnum1::value1};
basic::err::sys::Code code3_1_2{CodeEnum1::value2};
basic::err::defn::type::sys::code::Value code_val3_1{8};
basic::err::sys::Condition cond_val3_1{8, categ1};
char output3[] = "code 8 msg " CATEGORY_TRAIT1_MESSAGE;

T3Var1 t3_var1{&code3_1_1, &code3_1_2, &code_val3_1, &categ1, &cond_val3_1,
    CategoryTrait1Message1, output3};

REGISTER_TEST(t3, new TestCode<Case3, BASE_TYPE(T3Var1)>(t3_var1));

basic::err::sys::Code code4_1_1{CodeEnum1::value1};
CodeEnum1 code4_1_2{CodeEnum1::value2};
basic::err::defn::type::sys::code::Value code_val4_1{8};
basic::err::sys::Condition cond_val4_1{8, categ1};
char output4[] = "code 8 msg " CATEGORY_TRAIT1_MESSAGE;

T4Var1 t4_var1{&code4_1_1, &code4_1_2, &code_val4_1, &categ1, &cond_val4_1,
    CategoryTrait1Message1, output4};

REGISTER_TEST(t4, new TestCode<Case4, BASE_TYPE(T4Var1)>(t4_var1));

basic::err::sys::Code code5_1_1{CodeEnum1::value1};
basic::err::defn::type::sys::code::Value code5_1_2{16};
basic::err::defn::type::sys::code::Value code_val5_1{16};
basic::err::sys::Condition cond_val5_1{16, categ1};
char output5[] = "code 16 msg " CATEGORY_TRAIT1_MESSAGE;

T5Var1 t5_var1{&code5_1_1, &code5_1_2, &categ1, &code_val5_1, &categ1,
    &cond_val5_1, CategoryTrait1Message1, output5};

REGISTER_TEST(t5, new TestCode<Case5, BASE_TYPE(T5Var1)>(t5_var1));

basic::err::sys::Code code6_1_1{CodeEnum1::value1};
basic::err::defn::type::sys::code::Value code_val6_1{0};
basic::err::sys::Condition cond_val6_1{0, categ1};
char output6[] = "code 0 msg " CATEGORY_TRAIT1_MESSAGE;

T6Var1 t6_var1{&code6_1_1, &code_val6_1, &categ1, &cond_val6_1,
    CategoryTrait1Message1, output6};

REGISTER_TEST(t6, new TestCode<Case6, BASE_TYPE(T6Var1)>(t6_var1));

basic::err::sys::Code code7_1_1{CodeEnum1::value1};
basic::err::defn::type::sys::code::Value code_val7_1{4};
basic::err::sys::Condition cond_val7_1{4, categ1};
int signal7{0};
char output7[] = "code 4 msg ";

T7Var1 t7_var1{&code7_1_1, &signal7, &code_val7_1, &categ1, &cond_val7_1,
    CategoryTrait1Message0, output7};

REGISTER_TEST(t7, new TestCode<Case7, BASE_TYPE(T7Var1)>(t7_var1));

basic::err::sys::Code code8_1{CodeEnum1::value1};
basic::err::sys::Code code8_2{CodeEnum1::value2};
basic::err::defn::type::sys::code::Value code_val8_1{4};
basic::err::defn::type::sys::code::Value code_val8_2{8};
CodeEnum1 code_enum8_1{CodeEnum1::value1};
CodeEnum1 code_enum8_2{CodeEnum1::value2};

T8Var1 t8_var1{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    &code8_1, &code8_1, &code8_1, &code_val8_1, &code_val8_1,
        &code_enum8_1, &code_enum8_1,
    &code8_2, &code_val8_2, &code_enum8_2, &code8_2, &code_enum8_2,
        &code8_2, &code_val8_2,
    true, true, true, true, true, true, true};

REGISTER_TEST(t8, new TestCode<Case8, BASE_TYPE(T8Var1)>(t8_var1));

basic::err::sys::Code code9_1{CodeEnum1::value1};
basic::err::sys::Code code9_2{CodeEnum1::value2};
basic::err::defn::type::sys::code::Value code_val9_1{4};
basic::err::defn::type::sys::code::Value code_val9_2{8};
CodeEnum1 code_enum9_1{CodeEnum1::value1};
CodeEnum1 code_enum9_2{CodeEnum1::value2};

T9Var1 t9_var1{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    &code8_2, &code8_2, &code8_2, &code_val8_2, &code_val8_2,
        &code_enum8_2, &code_enum8_2,
    &code8_1, &code_val8_1, &code_enum8_1, &code8_1, &code_enum8_1,
        &code8_1, &code_val8_1,
    true, true, true, true, true, true, true};

REGISTER_TEST(t9, new TestCode<Case9, BASE_TYPE(T9Var1)>(t9_var1));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("CategoryTrait1", CategoryTrait1);
BASIC_TEST_TYPE_NAME("CodeEnum1", CodeEnum1);
BASIC_TEST_TYPE_NAME("ConditionEnum1", ConditionEnum1);

BASIC_TEST_TYPE_NAME("basic::err::sys::Code", basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", basic::err::sys::Condition);
BASIC_TEST_TYPE_NAME("basic::err::intf::Output", basic::err::intf::Output);
BASIC_TEST_TYPE_NAME("basic::err::intf::Exit", basic::err::intf::Exit);
BASIC_TEST_TYPE_NAME("basic::err::sys::intf::Category", 
    basic::err::sys::intf::Category);

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

template<typename TArg>
struct basic::test::type::Name<const TArg>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "const %s";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};
