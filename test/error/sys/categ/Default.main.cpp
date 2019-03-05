#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/out/Argument.h"

#include "error/sys/categ/Default.h"

#include "constant/error/sys/Category.h"

#include "error/sys/Code.h"
#include "error/sys/Condition.h"

#include "error/sys/tmpl/Category.h"

#include "error/sys/tmpl/categ/defn/type/code/set/Value.h"
#include "error/sys/tmpl/categ/defn/type/cond/set/Value.h"

#include "error/sys/tmpl/categ/has/mmbr/defn/type/CodeEnum.h"
#include "error/sys/tmpl/categ/has/mmbr/defn/type/ConditionEnum.h"
#include "error/sys/tmpl/categ/has/mmbr/func/DefaultCode.h"
#include "error/sys/tmpl/categ/has/mmbr/func/DefaultCodeValue.h"
#include "error/sys/tmpl/categ/has/mmbr/func/DefaultCondition.h"
#include "error/sys/tmpl/categ/has/mmbr/func/DefaultConditionValue.h"
#include "error/sys/tmpl/categ/has/mmbr/func/Equivalent.h"
#include "error/sys/tmpl/categ/has/mmbr/func/Message.h"
#include "error/sys/tmpl/categ/has/mmbr/func/Name.h"
#include "error/sys/tmpl/categ/has/mmbr/func/ToCodeValue.h"
#include "error/sys/tmpl/categ/has/mmbr/func/ToConditionValue.h"
#include "error/sys/tmpl/categ/has/mmbr/func/Value.h"

#include "error/sys/tmpl/categ/has/st/mmbr/func/Instance.h"

#include <system_error>
#include <type_traits>
#include <utility>
#include <cstring>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

basic::test::CString<char> ConditionToString(basic::error::sys::
    Condition * && cond)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "m_value : %d", cond->Value());
}

basic::test::CString<char> CodeToString(basic::error::sys::
    Code * && code)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "m_value : %d", code->Value());
}

const char * BoolToString(bool && b)
{
    return (b ? "true" : "false");
}

char DefnCodeTypeString_1[] = "basic::error::sys::tmpl::"
    "categ::defn::type::code::set::Value<basic::error::sys::categ::"
    "Default>";
char DefnConditionTypeString_1[] = "basic::error::sys::tmpl::"
    "categ::defn::type::cond::set::Value<basic::error::sys::"
    "categ::Default>";

struct TestAliasCodeEnumType {};
struct TestAliasConditionEnumType {};
struct TestAliasCharType {};
struct TestAliasCategoryValueType {};
struct TestAliasCodeValueType {};
struct TestAliasConditionValueType {};
struct TestAliasStringType {};
struct TestValueDefaultCondition {};
struct TestValueEquivalent {};
struct TestValueMessage {};
struct TestValueName {};
struct TestValueValue {};
struct TestAliasDefnTypeCodeSetValueType {};
struct TestAliasDefnTypeConditionSetValueType {};
struct TestValueHasMmbrDefnTypeCodeEnum {};
struct TestValueHasMmbrDefnTypeConditionEnum {};
struct TestValueHasMmbrFuncDefaultCode {};
struct TestValueHasMmbrFuncDefaultCodeValue {};
struct TestValueHasMmbrFuncDefaultCondition {};
struct TestValueHasMmbrFuncDefaultConditionValue {};
struct TestValueHasMmbrFuncEquivalent {};
struct TestValueHasMmbrFuncMessage {};
struct TestValueHasMmbrFuncName {};
struct TestValueHasMmbrFuncToCodeValue {};
struct TestValueHasMmbrFuncToConditionValue {};
struct TestValueHasMmbrFuncValue {};
struct TestValueHasStMmbrFuncInstance {};

typedef basic::error::sys::categ::Default CategoryTraitType;
typedef basic::error::sys::tmpl::Category<CategoryTraitType>
    TmplCategoryType;
typedef std::errc CodeEnumType;
typedef std::errc ConditionEnumType;
typedef basic::error::defn::type::Char CharType;
typedef basic::error::defn::type::sys::categ::Value CategoryValueType;
typedef basic::error::defn::type::sys::code::Value CodeValueType;
typedef basic::error::defn::type::sys::cond::Value ConditionValueType;
typedef basic::error::msg::String MessageStringType;
typedef basic::error::sys::Condition ConditionType;
typedef basic::error::sys::Code CodeType;
typedef basic::test::type::Parameter<
    CodeType,
    CodeValueType> DefaultConditionParamTypeType;
typedef basic::test::val::Parameter<
    CodeType *,
    CodeValueType *> DefaultConditionParamValueType;
typedef basic::test::val::Parameter<
    ConditionType *,
    ConditionType *> DefaultConditionResultParamValueType;
typedef basic::test::type::Parameter<
    CodeType, 
    CodeValueType> EquivalentCodeParamTypeType;
typedef basic::test::val::Parameter<
    CodeType *, 
    CodeValueType *> EquivalentCodeParamValueType;
typedef basic::test::type::Parameter<
    ConditionValueType,
    ConditionType> EquivalentConditionParamTypeType;
typedef basic::test::val::Parameter<
    ConditionValueType *,
    ConditionType *> EquivalentConditionParamValueType;
typedef basic::test::val::Sequence<bool, 2> EquivalentResultSeqValueType;
typedef basic::test::type::Parameter<
    CodeType, 
    ConditionType,
    int,
    std::errc> MessageParamTypeType;
typedef basic::test::val::Parameter<
    CodeType *, 
    ConditionType *,
    int *,
    std::errc *> MessageParamValueType;
typedef basic::test::val::Sequence<const char *, 4> MessageResultSeqValueType;
typedef basic::test::Value<const char *> NameValueType;
typedef basic::test::Value<CategoryValueType> ValueValueType;
typedef basic::test::type::val::Sequence<const char *, 
    DefnCodeTypeString_1> DefnCodeTypeSeqNameValueType;
typedef basic::test::type::Parameter<std::errc> 
    DefnCodeTypeParamTypeType;
typedef basic::test::type::val::Sequence<const char *, 
    DefnConditionTypeString_1> 
        DefnConditionTypeSeqNameValueType;
typedef basic::test::type::Parameter<std::errc> 
    DefnConditionTypeParamTypeType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::defn::type::CodeEnum<
        CategoryTraitType>>
            HasMmbrDefnCodeEnumParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrDefnCodeEnumSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::defn::type::
        ConditionEnum<CategoryTraitType>>
            HasMmbrDefnConditionEnumParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrDefnConditionEnumSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::DefaultCode<
        CategoryTraitType, CodeType, TmplCategoryType>>
            HasMmbrFuncDefaultCodeParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrFuncDefaultCodeSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::
        DefaultCodeValue<CategoryTraitType>>
            HasMmbrFuncDefaultCodeValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncDefaultCodeValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::
        DefaultCondition<CategoryTraitType, ConditionType, CodeType, 
        TmplCategoryType>>HasMmbrFuncDefaultConditionParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncDefaultConditionSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::
        DefaultConditionValue<CategoryTraitType>>
            HasMmbrFuncDefaultConditionValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrFuncDefaultConditionValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::Equivalent<
        CategoryTraitType, CodeType, ConditionValueType>,
    basic::error::sys::tmpl::categ::has::mmbr::func::Equivalent<
        CategoryTraitType, CodeValueType, ConditionType>>
            HasMmbrFuncEquivalentParamTypeType;
typedef basic::test::val::Sequence<bool, 2> 
    HasMmbrFuncEquivalentSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, CodeType>,
    basic::error::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, ConditionType>,
    basic::error::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, int>,
    basic::error::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, std::errc>>
            HasMmbrFuncMessageParamTypeType;
typedef basic::test::val::Sequence<bool, 4> 
    HasMmbrFuncMessageSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::Name<
        CategoryTraitType>> HasMmbrFuncNameParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncNameSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::ToCodeValue<
        CategoryTraitType, std::errc>> HasMmbrFuncToCodeValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncToCodeValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::
        ToConditionValue<CategoryTraitType, std::errc>>
            HasMmbrFuncToConditionValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncToConditionValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::mmbr::func::Value<
        CategoryTraitType, CategoryValueType>> HasMmbrFuncValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::error::sys::tmpl::categ::has::st::mmbr::func::Instance<
        CategoryTraitType>> HasStMmbrFuncInstanceParamTypeType;
typedef basic::test::val::Sequence<bool, 1> HasStMmbrFuncInstanceSeqValueType;

using VariableTestCategoryDefault = basic::test::Variable<
    CategoryTraitType,
    CodeEnumType,
    ConditionEnumType,
    CharType,
    CategoryValueType,
    CodeValueType,
    ConditionValueType,
    MessageStringType,
    ConditionType,
    CodeType,
    DefaultConditionParamTypeType,
    DefaultConditionParamValueType,
    DefaultConditionResultParamValueType,
    EquivalentCodeParamTypeType,
    EquivalentCodeParamValueType,
    EquivalentConditionParamTypeType,
    EquivalentConditionParamValueType,
    EquivalentResultSeqValueType,
    MessageParamTypeType,
    MessageParamValueType,
    MessageResultSeqValueType,
    NameValueType,
    ValueValueType,
    DefnCodeTypeSeqNameValueType,
    DefnCodeTypeParamTypeType,
    DefnConditionTypeSeqNameValueType,
    DefnConditionTypeParamTypeType,
    HasMmbrDefnCodeEnumParamTypeType,
    HasMmbrDefnCodeEnumSeqValueType,
    HasMmbrDefnConditionEnumParamTypeType,
    HasMmbrDefnConditionEnumSeqValueType,
    HasMmbrFuncDefaultCodeParamTypeType,
    HasMmbrFuncDefaultCodeSeqValueType,
    HasMmbrFuncDefaultCodeValueParamTypeType,
    HasMmbrFuncDefaultCodeValueSeqValueType,
    HasMmbrFuncDefaultConditionParamTypeType,
    HasMmbrFuncDefaultConditionSeqValueType,
    HasMmbrFuncDefaultConditionValueParamTypeType,
    HasMmbrFuncDefaultConditionValueSeqValueType,
    HasMmbrFuncEquivalentParamTypeType,
    HasMmbrFuncEquivalentSeqValueType,
    HasMmbrFuncMessageParamTypeType,
    HasMmbrFuncMessageSeqValueType,
    HasMmbrFuncNameParamTypeType,
    HasMmbrFuncNameSeqValueType,
    HasMmbrFuncToCodeValueParamTypeType,
    HasMmbrFuncToCodeValueSeqValueType,
    HasMmbrFuncToConditionValueParamTypeType,
    HasMmbrFuncToConditionValueSeqValueType,
    HasMmbrFuncValueParamTypeType,
    HasMmbrFuncValueSeqValueType,
    HasStMmbrFuncInstanceParamTypeType,
    HasStMmbrFuncInstanceSeqValueType,
    basic::test::type::Function<basic::test::CString<char>(
        ConditionType * &&), &ConditionToString>,
    basic::test::type::Function<basic::test::CString<char>(
        CodeType * &&), &CodeToString>,
    basic::test::type::Function<const char * (bool && b), &BoolToString>>;

constexpr std::size_t IDefaultType = 0;
constexpr std::size_t ICodeEnumType = 1;
constexpr std::size_t IConditionEnumType = 2;
constexpr std::size_t ICharType = 3;
constexpr std::size_t ICategoryValueType = 4;
constexpr std::size_t ICodeValueType = 5;
constexpr std::size_t IConditionValueType = 6;
constexpr std::size_t IStringType = 7;
constexpr std::size_t IConditionType = 8;
constexpr std::size_t ICodeType = 9;
constexpr std::size_t IDefaultConditionParamType = 10;
constexpr std::size_t IDefaultConditionParamValue = 11;
constexpr std::size_t IDefaultConditionResultParamValue = 12;
constexpr std::size_t IEquivalentCodeParamType = 13;
constexpr std::size_t IEquivalentCodeParamValue = 14;
constexpr std::size_t IEquivalentConditionParamType = 15;
constexpr std::size_t IEquivalentConditionParamValue = 16;
constexpr std::size_t IEquivalentResultSeqValue = 17;
constexpr std::size_t IMessageParamType = 18;
constexpr std::size_t IMessageParamValue = 19;
constexpr std::size_t IMessageResultSeqValue = 20;
constexpr std::size_t INameValue = 21;
constexpr std::size_t IValueValue = 22;
constexpr std::size_t IDefnCodeTypeSeqNameValue = 23;
constexpr std::size_t IDefnCodeTypeParamType = 24;
constexpr std::size_t IDefnConditionTypeSeqNameValue = 25;
constexpr std::size_t IDefnConditionTypeParamType = 26;
constexpr std::size_t IHasMmbrDefnCodeEnumParamType = 27;
constexpr std::size_t IHasMmbrDefnCodeEnumSeqValue = 28;
constexpr std::size_t IHasMmbrDefnConditionEnumParamType = 29;
constexpr std::size_t IHasMmbrDefnConditionEnumSeqValue = 30;
constexpr std::size_t IHasMmbrFuncDefaultCodeParamType = 31;
constexpr std::size_t IHasMmbrFuncDefaultCodeSeqValue = 32;
constexpr std::size_t IHasMmbrFuncDefaultCodeValueParamType = 33;
constexpr std::size_t IHasMmbrFuncDefaultCodeValueSeqValue = 34;
constexpr std::size_t IHasMmbrFuncDefaultConditionParamType = 35;
constexpr std::size_t IHasMmbrFuncDefaultConditionSeqValue = 36;
constexpr std::size_t IHasMmbrFuncDefaultConditionValueParamType = 37;
constexpr std::size_t IHasMmbrFuncDefaultConditionValueSeqValue = 38;
constexpr std::size_t IHasMmbrFuncEquivalentParamType = 39;
constexpr std::size_t IHasMmbrFuncEquivalentSeqValue = 40;
constexpr std::size_t IHasMmbrFuncMessageParamType = 41;
constexpr std::size_t IHasMmbrFuncMessageSeqValue = 42;
constexpr std::size_t IHasMmbrFuncNameParamType = 43;
constexpr std::size_t IHasMmbrFuncNameSeqValue = 44;
constexpr std::size_t IHasMmbrFuncToCodeValueParamType = 45;
constexpr std::size_t IHasMmbrFuncToCodeValueSeqValue = 46;
constexpr std::size_t IHasMmbrFuncToConditionValueParamType = 47;
constexpr std::size_t IHasMmbrFuncToConditionValueSeqValue = 48;
constexpr std::size_t IHasMmbrFuncValueParamType = 49;
constexpr std::size_t IHasMmbrFuncValueSeqValue = 50;
constexpr std::size_t IHasStMmbrFuncInstanceParamType = 51;
constexpr std::size_t IHasStMmbrFuncInstanceSeqValue = 52;
constexpr std::size_t IConditionToStringFunc = 53;
constexpr std::size_t ICodeToStringFunc = 54;
constexpr std::size_t IBoolToStringFunc = 55;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;
template<std::size_t I, typename... TArgArgs>
using ArgTypeFunction = basic::test::msg::arg::type::Function<I, TArgArgs...>;
template<std::size_t I, std::size_t J>
using ArgValParamAt = basic::test::msg::arg::val::param::At<I, J>;
template<std::size_t I, template<std::size_t, std::size_t> class TT>
using ArgTypeIndex = basic::test::msg::arg::type::Index<I, TT>;
template<std::size_t I, std::size_t J>
using ArgTypeParamNameAt = basic::test::msg::arg::type::param::name::At<I, J>;
template<std::size_t I, std::size_t J>
using ArgValSeqAt = basic::test::msg::arg::val::seq::At<I, J>;
template<std::size_t I, std::size_t J>
using ArgTypeValSeqAt = basic::test::msg::arg::type::val::seq::At<I, J>;

typedef basic::test::msg::Argument<TestAliasCodeEnumType,
    ArgTypeName<IDefaultType>, ArgTypeName<ICodeEnumType>> 
        ArgTestAliasCodeEnumType;

typedef basic::test::msg::Base<TestAliasCodeEnumType, char, 
    ArgTestAliasCodeEnumType, ArgTestAliasCodeEnumType, 
    ArgTestAliasCodeEnumType> MessageBaseTestAliasCodeEnumType;

typedef basic::test::msg::Argument<TestAliasConditionEnumType,
    ArgTypeName<IDefaultType>, ArgTypeName<IConditionEnumType>> 
        ArgTestAliasConditionEnumType;

typedef basic::test::msg::Base<TestAliasConditionEnumType, char, 
    ArgTestAliasConditionEnumType, ArgTestAliasConditionEnumType, 
    ArgTestAliasConditionEnumType> MessageBaseTestAliasConditionEnumType;

typedef basic::test::msg::Argument<TestAliasCharType,
    ArgTypeName<IDefaultType>, ArgTypeName<ICharType>> 
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasCategoryValueType,
    ArgTypeName<IDefaultType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasCategoryValueType;

typedef basic::test::msg::Base<TestAliasCategoryValueType, char, 
    ArgTestAliasCategoryValueType, ArgTestAliasCategoryValueType, 
    ArgTestAliasCategoryValueType> MessageBaseTestAliasCategoryValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    ArgTypeName<IDefaultType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasConditionValueType,
    ArgTypeName<IDefaultType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasConditionValueType;

typedef basic::test::msg::Base<TestAliasConditionValueType, char, 
    ArgTestAliasConditionValueType, ArgTestAliasConditionValueType, 
    ArgTestAliasConditionValueType> MessageBaseTestAliasConditionValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    ArgTypeName<IDefaultType>, ArgTypeName<IStringType>> 
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;
 
typedef basic::test::msg::Argument<TestValueDefaultCondition,
    ArgTypeName<IDefaultType>, 
    ArgTypeIndex<IDefaultConditionParamType, ArgTypeParamNameAt>,
    ArgTypeIndex<IDefaultConditionParamValue, ArgValParamAt>,
    ArgTypeName<IConditionType>,
    ArgTypeFunction<IConditionToStringFunc,
        ArgTypeIndex<IDefaultConditionResultParamValue, ArgValParamAt>>>
            ArgTestValueDefaultCondition;

typedef basic::test::msg::Base<TestValueDefaultCondition, char, 
    ArgTestValueDefaultCondition, ArgTestValueDefaultCondition, 
    ArgTestValueDefaultCondition> MessageBaseTestValueDefaultCondition;

typedef basic::test::msg::Argument<TestValueEquivalent,
    ArgTypeName<IDefaultType>,
    ArgTypeIndex<IEquivalentCodeParamType, ArgTypeParamNameAt>,
    ArgTypeIndex<IEquivalentCodeParamValue,
        ArgValParamAt>,
    ArgTypeIndex<IEquivalentConditionParamType, ArgTypeParamNameAt>,
    ArgTypeIndex<IEquivalentConditionParamValue,
        ArgValParamAt>,
    ArgTypeFunction<IBoolToStringFunc,
        ArgTypeIndex<IEquivalentResultSeqValue, ArgValSeqAt>>> 
            ArgTestValueEquivalent;

typedef basic::test::msg::Base<TestValueEquivalent, char, 
    ArgTestValueEquivalent, ArgTestValueEquivalent, 
    ArgTestValueEquivalent> MessageBaseTestValueEquivalent;

typedef basic::test::msg::Argument<TestValueMessage,
    ArgTypeName<IDefaultType>,
    ArgTypeIndex<IMessageParamType, ArgTypeParamNameAt>,
    ArgTypeIndex<IMessageParamValue, ArgValParamAt>,
    ArgTypeIndex<IMessageResultSeqValue, ArgValSeqAt>> ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, 
    ArgTestValueMessage> MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestValueName,
    ArgTypeName<IDefaultType>,
    basic::test::msg::arg::Value<INameValue>> 
        ArgTestValueName;

typedef basic::test::msg::Base<TestValueName, char, 
    ArgTestValueName, ArgTestValueName, 
    ArgTestValueName> MessageBaseTestValueName;

typedef basic::test::msg::Argument<TestValueValue,
    ArgTypeName<IDefaultType>,
    basic::test::msg::arg::Value<IValueValue>> 
        ArgTestValueValue;

typedef basic::test::msg::Base<TestValueValue, char, 
    ArgTestValueValue, ArgTestValueValue, 
    ArgTestValueValue> MessageBaseTestValueValue;

typedef basic::test::msg::Argument<TestAliasDefnTypeCodeSetValueType,
    ArgTypeIndex<IDefnCodeTypeSeqNameValue, ArgTypeValSeqAt>,
    ArgTypeIndex<IDefnCodeTypeParamType, ArgTypeParamNameAt>> 
        ArgTestAliasDefnTypeCodeSetValueType;

typedef basic::test::msg::Base<TestAliasDefnTypeCodeSetValueType, char, 
    ArgTestAliasDefnTypeCodeSetValueType, 
    ArgTestAliasDefnTypeCodeSetValueType, 
    ArgTestAliasDefnTypeCodeSetValueType> 
        MessageBaseTestAliasDefnTypeCodeSetValueType;

typedef basic::test::msg::Argument<TestAliasDefnTypeConditionSetValueType,
    ArgTypeIndex<
        IDefnConditionTypeSeqNameValue, ArgTypeValSeqAt>,
    ArgTypeIndex<IDefnConditionTypeParamType, ArgTypeParamNameAt>>
        ArgTestAliasDefnTypeConditionSetValueType;

typedef basic::test::msg::Base<TestAliasDefnTypeConditionSetValueType, char, 
    ArgTestAliasDefnTypeConditionSetValueType, 
    ArgTestAliasDefnTypeConditionSetValueType, 
    ArgTestAliasDefnTypeConditionSetValueType> 
        MessageBaseTestAliasDefnTypeConditionSetValueType;

typedef basic::test::msg::Argument<TestValueHasMmbrDefnTypeCodeEnum,
    ArgTypeIndex<IHasMmbrDefnCodeEnumParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc,
        ArgTypeIndex<IHasMmbrDefnCodeEnumSeqValue, ArgValSeqAt>>>
            ArgTestValueHasMmbrDefnTypeCodeEnum;

typedef basic::test::msg::Base<TestValueHasMmbrDefnTypeCodeEnum, char, 
    ArgTestValueHasMmbrDefnTypeCodeEnum, ArgTestValueHasMmbrDefnTypeCodeEnum, 
    ArgTestValueHasMmbrDefnTypeCodeEnum> 
        MessageBaseTestValueHasMmbrDefnTypeCodeEnum;

typedef basic::test::msg::Argument<TestValueHasMmbrDefnTypeConditionEnum,
    ArgTypeIndex<IHasMmbrDefnConditionEnumParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc,
        ArgTypeIndex<IHasMmbrDefnConditionEnumSeqValue, 
            ArgValSeqAt>>> ArgTestValueHasMmbrDefnTypeConditionEnum;

typedef basic::test::msg::Base<TestValueHasMmbrDefnTypeConditionEnum, char, 
    ArgTestValueHasMmbrDefnTypeConditionEnum, 
    ArgTestValueHasMmbrDefnTypeConditionEnum, 
    ArgTestValueHasMmbrDefnTypeConditionEnum> 
        MessageBaseTestValueHasMmbrDefnTypeConditionEnum;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncDefaultCode,
    ArgTypeIndex<IHasMmbrFuncDefaultCodeParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncDefaultCodeSeqValue, 
            ArgValSeqAt>>> ArgTestValueHasMmbrFuncDefaultCode;

typedef basic::test::msg::Base<TestValueHasMmbrFuncDefaultCode, char, 
    ArgTestValueHasMmbrFuncDefaultCode, ArgTestValueHasMmbrFuncDefaultCode, 
    ArgTestValueHasMmbrFuncDefaultCode> 
        MessageBaseTestValueHasMmbrFuncDefaultCode;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncDefaultCodeValue,
    ArgTypeIndex<IHasMmbrFuncDefaultCodeValueParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncDefaultCodeValueSeqValue, 
            ArgValSeqAt>>> ArgTestValueHasMmbrFuncDefaultCodeValue;

typedef basic::test::msg::Base<TestValueHasMmbrFuncDefaultCodeValue, char, 
    ArgTestValueHasMmbrFuncDefaultCodeValue, 
    ArgTestValueHasMmbrFuncDefaultCodeValue, 
    ArgTestValueHasMmbrFuncDefaultCodeValue> 
        MessageBaseTestValueHasMmbrFuncDefaultCodeValue;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncDefaultCondition,
    ArgTypeIndex<IHasMmbrFuncDefaultConditionParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncDefaultConditionSeqValue, 
            ArgValSeqAt>>> ArgTestValueHasMmbrFuncDefaultCondition;

typedef basic::test::msg::Base<TestValueHasMmbrFuncDefaultCondition, char, 
    ArgTestValueHasMmbrFuncDefaultCondition, 
    ArgTestValueHasMmbrFuncDefaultCondition, 
    ArgTestValueHasMmbrFuncDefaultCondition> 
        MessageBaseTestValueHasMmbrFuncDefaultCondition;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncDefaultConditionValue,
    ArgTypeIndex<IHasMmbrFuncDefaultConditionValueParamType, 
        ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncDefaultConditionValueSeqValue, 
            ArgValSeqAt>>> ArgTestValueHasMmbrFuncDefaultConditionValue;

typedef basic::test::msg::Base<TestValueHasMmbrFuncDefaultConditionValue, char,
    ArgTestValueHasMmbrFuncDefaultConditionValue, 
    ArgTestValueHasMmbrFuncDefaultConditionValue, 
    ArgTestValueHasMmbrFuncDefaultConditionValue> 
        MessageBaseTestValueHasMmbrFuncDefaultConditionValue;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncEquivalent,
    ArgTypeIndex<IHasMmbrFuncEquivalentParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncEquivalentSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncEquivalent;

typedef basic::test::msg::Base<TestValueHasMmbrFuncEquivalent, char,
    ArgTestValueHasMmbrFuncEquivalent, ArgTestValueHasMmbrFuncEquivalent, 
    ArgTestValueHasMmbrFuncEquivalent> 
        MessageBaseTestValueHasMmbrFuncEquivalent;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncMessage,
    ArgTypeIndex<IHasMmbrFuncMessageParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncMessageSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncMessage;

typedef basic::test::msg::Base<TestValueHasMmbrFuncMessage, char,
    ArgTestValueHasMmbrFuncMessage, ArgTestValueHasMmbrFuncMessage, 
    ArgTestValueHasMmbrFuncMessage> 
        MessageBaseTestValueHasMmbrFuncMessage;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncName,
    ArgTypeIndex<IHasMmbrFuncNameParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncNameSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncName;

typedef basic::test::msg::Base<TestValueHasMmbrFuncName, char,
    ArgTestValueHasMmbrFuncName, ArgTestValueHasMmbrFuncName, 
    ArgTestValueHasMmbrFuncName> 
        MessageBaseTestValueHasMmbrFuncName;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncToCodeValue,
    ArgTypeIndex<IHasMmbrFuncToCodeValueParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncToCodeValueSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncToCodeValue;

typedef basic::test::msg::Base<TestValueHasMmbrFuncToCodeValue, char,
    ArgTestValueHasMmbrFuncToCodeValue, ArgTestValueHasMmbrFuncToCodeValue, 
    ArgTestValueHasMmbrFuncToCodeValue> 
        MessageBaseTestValueHasMmbrFuncToCodeValue;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncToConditionValue,
    ArgTypeIndex<IHasMmbrFuncToConditionValueParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncToConditionValueSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncToConditionValue;

typedef basic::test::msg::Base<TestValueHasMmbrFuncToConditionValue, char,
    ArgTestValueHasMmbrFuncToConditionValue, 
    ArgTestValueHasMmbrFuncToConditionValue, 
    ArgTestValueHasMmbrFuncToConditionValue> 
        MessageBaseTestValueHasMmbrFuncToConditionValue;

typedef basic::test::msg::Argument<TestValueHasMmbrFuncValue,
    ArgTypeIndex<IHasMmbrFuncValueParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasMmbrFuncValueSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasMmbrFuncValue;

typedef basic::test::msg::Base<TestValueHasMmbrFuncValue, char,
    ArgTestValueHasMmbrFuncValue, ArgTestValueHasMmbrFuncValue, 
    ArgTestValueHasMmbrFuncValue> 
        MessageBaseTestValueHasMmbrFuncValue;

typedef basic::test::msg::Argument<TestValueHasStMmbrFuncInstance,
    ArgTypeIndex<IHasStMmbrFuncInstanceParamType, ArgTypeParamNameAt>,
    ArgTypeFunction<IBoolToStringFunc, 
        ArgTypeIndex<IHasStMmbrFuncInstanceSeqValue, ArgValSeqAt>>> 
            ArgTestValueHasStMmbrFuncInstance;

typedef basic::test::msg::Base<TestValueHasStMmbrFuncInstance, char,
    ArgTestValueHasStMmbrFuncInstance, ArgTestValueHasStMmbrFuncInstance, 
    ArgTestValueHasStMmbrFuncInstance> 
        MessageBaseTestValueHasStMmbrFuncInstance;

template<typename TCases, typename... TVariables>
struct TestCategoryDefault :
    public basic::test::Message<BASIC_TEST, TestCategoryDefault<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCategoryDefault<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCategoryDefault<TCases, TVariables...>, 
        TVariables...>,
    public MessageBaseTestAliasCodeEnumType,
    public MessageBaseTestAliasConditionEnumType,
    public MessageBaseTestAliasCharType,
    public MessageBaseTestAliasCategoryValueType,
    public MessageBaseTestAliasCodeValueType,
    public MessageBaseTestAliasConditionValueType,
    public MessageBaseTestAliasStringType,
    public MessageBaseTestValueDefaultCondition,
    public MessageBaseTestValueEquivalent,
    public MessageBaseTestValueMessage,
    public MessageBaseTestValueName,
    public MessageBaseTestValueValue,
    public MessageBaseTestAliasDefnTypeCodeSetValueType,
    public MessageBaseTestAliasDefnTypeConditionSetValueType,
    public MessageBaseTestValueHasMmbrDefnTypeCodeEnum,
    public MessageBaseTestValueHasMmbrDefnTypeConditionEnum,
    public MessageBaseTestValueHasMmbrFuncDefaultCode,
    public MessageBaseTestValueHasMmbrFuncDefaultCodeValue,
    public MessageBaseTestValueHasMmbrFuncDefaultCondition,
    public MessageBaseTestValueHasMmbrFuncDefaultConditionValue,
    public MessageBaseTestValueHasMmbrFuncEquivalent,
    public MessageBaseTestValueHasMmbrFuncMessage,
    public MessageBaseTestValueHasMmbrFuncName,
    public MessageBaseTestValueHasMmbrFuncToCodeValue,
    public MessageBaseTestValueHasMmbrFuncToConditionValue,
    public MessageBaseTestValueHasMmbrFuncValue,
    public MessageBaseTestValueHasStMmbrFuncInstance
{
public:
    using basic::test::Case<TestCategoryDefault<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCategoryDefault<TCases, TVariables...>, 
        TVariables...>::Run;
    using MessageBaseTestAliasCodeEnumType::Format;
    using MessageBaseTestAliasCodeEnumType::SetFormat;
    using MessageBaseTestAliasCodeEnumType::Argument;
    using MessageBaseTestAliasConditionEnumType::Format;
    using MessageBaseTestAliasConditionEnumType::SetFormat;
    using MessageBaseTestAliasConditionEnumType::Argument;
    using MessageBaseTestAliasCharType::Format;
    using MessageBaseTestAliasCharType::SetFormat;
    using MessageBaseTestAliasCharType::Argument;
    using MessageBaseTestAliasCategoryValueType::Format;
    using MessageBaseTestAliasCategoryValueType::SetFormat;
    using MessageBaseTestAliasCategoryValueType::Argument;
    using MessageBaseTestAliasCodeValueType::Format;
    using MessageBaseTestAliasCodeValueType::SetFormat;
    using MessageBaseTestAliasCodeValueType::Argument;
    using MessageBaseTestAliasConditionValueType::Format;
    using MessageBaseTestAliasConditionValueType::SetFormat;
    using MessageBaseTestAliasConditionValueType::Argument;
    using MessageBaseTestAliasStringType::Format;
    using MessageBaseTestAliasStringType::SetFormat;
    using MessageBaseTestAliasStringType::Argument;
    using MessageBaseTestValueDefaultCondition::Format;
    using MessageBaseTestValueDefaultCondition::SetFormat;
    using MessageBaseTestValueDefaultCondition::Argument;
    using MessageBaseTestValueEquivalent::Format;
    using MessageBaseTestValueEquivalent::SetFormat;
    using MessageBaseTestValueEquivalent::Argument;
    using MessageBaseTestValueMessage::Format;
    using MessageBaseTestValueMessage::SetFormat;
    using MessageBaseTestValueMessage::Argument;
    using MessageBaseTestValueName::Format;
    using MessageBaseTestValueName::SetFormat;
    using MessageBaseTestValueName::Argument;
    using MessageBaseTestValueValue::Format;
    using MessageBaseTestValueValue::SetFormat;
    using MessageBaseTestValueValue::Argument;
    using MessageBaseTestAliasDefnTypeCodeSetValueType::Format;
    using MessageBaseTestAliasDefnTypeCodeSetValueType::SetFormat;
    using MessageBaseTestAliasDefnTypeCodeSetValueType::Argument;
    using MessageBaseTestAliasDefnTypeConditionSetValueType::Format;
    using MessageBaseTestAliasDefnTypeConditionSetValueType::SetFormat;
    using MessageBaseTestAliasDefnTypeConditionSetValueType::Argument;
    using MessageBaseTestValueHasMmbrDefnTypeCodeEnum::Format;
    using MessageBaseTestValueHasMmbrDefnTypeCodeEnum::SetFormat;
    using MessageBaseTestValueHasMmbrDefnTypeCodeEnum::Argument;
    using MessageBaseTestValueHasMmbrDefnTypeConditionEnum::Format;
    using MessageBaseTestValueHasMmbrDefnTypeConditionEnum::SetFormat;
    using MessageBaseTestValueHasMmbrDefnTypeConditionEnum::Argument;
    using MessageBaseTestValueHasMmbrFuncDefaultCode::Format;
    using MessageBaseTestValueHasMmbrFuncDefaultCode::SetFormat;
    using MessageBaseTestValueHasMmbrFuncDefaultCode::Argument;
    using MessageBaseTestValueHasMmbrFuncDefaultCodeValue::Format;
    using MessageBaseTestValueHasMmbrFuncDefaultCodeValue::SetFormat;
    using MessageBaseTestValueHasMmbrFuncDefaultCodeValue::Argument;
    using MessageBaseTestValueHasMmbrFuncDefaultCondition::Format;
    using MessageBaseTestValueHasMmbrFuncDefaultCondition::SetFormat;
    using MessageBaseTestValueHasMmbrFuncDefaultCondition::Argument;
    using MessageBaseTestValueHasMmbrFuncDefaultConditionValue::Format;
    using MessageBaseTestValueHasMmbrFuncDefaultConditionValue::SetFormat;
    using MessageBaseTestValueHasMmbrFuncDefaultConditionValue::Argument;
    using MessageBaseTestValueHasMmbrFuncEquivalent::Format;
    using MessageBaseTestValueHasMmbrFuncEquivalent::SetFormat;
    using MessageBaseTestValueHasMmbrFuncEquivalent::Argument;
    using MessageBaseTestValueHasMmbrFuncMessage::Format;
    using MessageBaseTestValueHasMmbrFuncMessage::SetFormat;
    using MessageBaseTestValueHasMmbrFuncMessage::Argument;
    using MessageBaseTestValueHasMmbrFuncName::Format;
    using MessageBaseTestValueHasMmbrFuncName::SetFormat;
    using MessageBaseTestValueHasMmbrFuncName::Argument;
    using MessageBaseTestValueHasMmbrFuncToCodeValue::Format;
    using MessageBaseTestValueHasMmbrFuncToCodeValue::SetFormat;
    using MessageBaseTestValueHasMmbrFuncToCodeValue::Argument;
    using MessageBaseTestValueHasMmbrFuncToConditionValue::Format;
    using MessageBaseTestValueHasMmbrFuncToConditionValue::SetFormat;
    using MessageBaseTestValueHasMmbrFuncToConditionValue::Argument;
    using MessageBaseTestValueHasMmbrFuncValue::Format;
    using MessageBaseTestValueHasMmbrFuncValue::SetFormat;
    using MessageBaseTestValueHasMmbrFuncValue::Argument;
    using MessageBaseTestValueHasStMmbrFuncInstance::Format;
    using MessageBaseTestValueHasStMmbrFuncInstance::SetFormat;
    using MessageBaseTestValueHasStMmbrFuncInstance::Argument;
public:
    TestCategoryDefault(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCategoryDefault<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCategoryDefault<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCategoryDefault<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        TestAliasCodeEnumType testAliasCodeEnumType;
        SetFormat(info, testAliasCodeEnumType, "Test alias type "
            "%s::CodeEnumType is same with %s\n");
        SetFormat(debug, testAliasCodeEnumType, "Test alias type "
            "%s::CodeEnumType is same with %s\n");
        SetFormat(error, testAliasCodeEnumType, "Error alias type "
            "%s::CodeEnumType is not same with %s\n");

        TestAliasConditionEnumType testAliasConditionEnumType;
        SetFormat(info, testAliasConditionEnumType, "Test alias type "
            "%s::ConditionEnumType is same with %s\n");
        SetFormat(debug, testAliasConditionEnumType, "Test alias type "
            "%s::ConditionEnumType is same with %s\n");
        SetFormat(error, testAliasConditionEnumType, "Error alias type "
            "%s::ConditionEnumType is not same with %s\n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(error, testAliasCharType, "Error alias type "
            "%s::CharType is not same with %s\n");
        
        TestAliasCategoryValueType testAliasCategoryValueType;
        SetFormat(info, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(debug, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(error, testAliasCategoryValueType, "Error alias type "
            "%s::CategoryValueType is not same with %s\n");

        TestAliasCodeValueType testAliasCodeValueType;
        SetFormat(info, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(debug, testAliasCodeValueType, "Test alias type "
            "%s::CodeValueType is same with %s\n");
        SetFormat(error, testAliasCodeValueType, "Error alias type "
            "%s::CodeValueType is not same with %s\n");
        
        TestAliasConditionValueType testAliasConditionValueType;
        SetFormat(info, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(debug, testAliasConditionValueType, "Test alias type "
            "%s::ConditionValueType is same with %s\n");
        SetFormat(error, testAliasConditionValueType, "Error alias type "
            "%s::ConditionValueType is not same with %s\n");

        TestAliasStringType testAliasStringType;
        SetFormat(info, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(debug, testAliasStringType, "Test alias type "
            "%s::StringType is same with %s\n");
        SetFormat(error, testAliasStringType, "Error alias type "
            "%s::StringType is not same with %s\n");

        TestValueDefaultCondition testValueDefaultCondition;
        SetFormat(info, testValueDefaultCondition, "Test value "
            "%s::DefaultCondition(%s {%s}) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCondition, "Test value "
            "%s::DefaultCondition(%s {%s}) is same with %s {%s}\n");
        SetFormat(error, testValueDefaultCondition, "Error value "
            "%s::DefaultCondition(%s {%s}) is not same with %s {%s}\n");
        
        TestValueEquivalent testValueEquivalent;
        SetFormat(info, testValueEquivalent, "Test value "
            "%s::Equivalent(%s {%s}, %s {%s}) is same with %s\n");
        SetFormat(debug, testValueEquivalent, "Test value "
            "%s::Equivalent(%s {%s}, %s {%s}) is same with %s\n");
        SetFormat(error, testValueEquivalent, "Error value "
            "%s::Equivalent(%s {%s}, %s {%s}) is not same with %s\n");

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test value "
            "%s::Message(%s {%s}) is same with \"%s\"\n");
        SetFormat(debug, testValueMessage, "Test value "
            "%s::Message(%s {%s}) is same with \"%s\"\n");
        SetFormat(error, testValueMessage, "Error value "
            "%s::Message(%s {%s}) is not same with \"%s\"\n");

        TestValueName testValueName;
        SetFormat(info, testValueName, "Test value "
            "%s::Name() is same with \"%s\"\n");
        SetFormat(debug, testValueName, "Test value "
            "%s::Name() is same with \"%s\"\n");
        SetFormat(error, testValueName, "Error value "
            "%s::Name() is not same with \"%s\"\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test value "
            "%s::Value() is same with %d\n");
        SetFormat(debug, testValueValue, "Test value "
            "%s::Value() is same with %d\n");
        SetFormat(error, testValueValue, "Error value "
            "%s::Value() is not same with %d\n");

        TestAliasDefnTypeCodeSetValueType testAliasDefnTypeCodeSetValueType;
        SetFormat(info, testAliasDefnTypeCodeSetValueType, "Test alias type "
            "%s is same with %s\n");
        SetFormat(debug, testAliasDefnTypeCodeSetValueType, "Test alias type "
            "%s is same with %s\n");
        SetFormat(error, testAliasDefnTypeCodeSetValueType, "Error alias type "
            "%s is not same with %s\n");
        
        TestAliasDefnTypeConditionSetValueType 
            testAliasDefnTypeConditionSetValueType;
        SetFormat(info, testAliasDefnTypeConditionSetValueType, "Test alias "
            "type %s is same with %s\n");
        SetFormat(debug, testAliasDefnTypeConditionSetValueType, "Test alias "
            "type %s is same with %s\n");
        SetFormat(error, testAliasDefnTypeConditionSetValueType, "Error alias "
            "type %s is not same with %s\n");

        TestValueHasMmbrDefnTypeCodeEnum testValueHasMmbrDefnTypeCodeEnum;
        SetFormat(info, testValueHasMmbrDefnTypeCodeEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrDefnTypeCodeEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrDefnTypeCodeEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrDefnTypeConditionEnum 
            testValueHasMmbrDefnTypeConditionEnum;
        SetFormat(info, testValueHasMmbrDefnTypeConditionEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrDefnTypeConditionEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrDefnTypeConditionEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCode 
            testValueHasMmbrFuncDefaultCode;
        SetFormat(info, testValueHasMmbrFuncDefaultCode, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCode, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncDefaultCode, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCodeValue
            testValueHasMmbrFuncDefaultCodeValue;
        SetFormat(info, testValueHasMmbrFuncDefaultCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncDefaultCodeValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCondition
            testValueHasMmbrFuncDefaultCondition;
        SetFormat(info, testValueHasMmbrFuncDefaultCondition, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCondition, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncDefaultCondition, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultConditionValue
            testValueHasMmbrFuncDefaultConditionValue;
        SetFormat(info, testValueHasMmbrFuncDefaultConditionValue, "Test "
            "value %s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultConditionValue, "Test "
            "value %s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncDefaultConditionValue, "Error "
            "value %s::Value is not same with %s\n");

        TestValueHasMmbrFuncEquivalent testValueHasMmbrFuncEquivalent;
        SetFormat(info, testValueHasMmbrFuncEquivalent, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncEquivalent, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncEquivalent, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncMessage testValueHasMmbrFuncMessage;
        SetFormat(info, testValueHasMmbrFuncMessage, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncMessage, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncMessage, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncName testValueHasMmbrFuncName;
        SetFormat(info, testValueHasMmbrFuncName, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncName, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncName, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncToCodeValue testValueHasMmbrFuncToCodeValue;
        SetFormat(info, testValueHasMmbrFuncToCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncToCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncToCodeValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncToConditionValue 
            testValueHasMmbrFuncToConditionValue;
        SetFormat(info, testValueHasMmbrFuncToConditionValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncToConditionValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncToConditionValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncValue testValueHasMmbrFuncValue;
        SetFormat(info, testValueHasMmbrFuncValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasMmbrFuncValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasStMmbrFuncInstance testValueHasStMmbrFuncInstance;
        SetFormat(info, testValueHasStMmbrFuncInstance, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasStMmbrFuncInstance, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(error, testValueHasStMmbrFuncInstance, "Error value "
            "%s::Value is not same with %s\n");
    }
    bool Result(const TestAliasCodeEnumType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::CodeEnumType).hash_code() == 
            typeid(CodeEnumType).hash_code();
    }
    bool Result(const TestAliasConditionEnumType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::ConditionEnumType).
            hash_code() == typeid(ConditionEnumType).hash_code();
    }
    bool Result(const TestAliasCharType &, VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::CharType).hash_code() == 
            typeid(basic::error::defn::type::Char).hash_code();
    }
    bool Result(const TestAliasCategoryValueType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::CategoryValueType).
            hash_code() == typeid(basic::error::defn::type::sys::
            categ::Value).hash_code();
    }
    bool Result(const TestAliasCodeValueType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::CodeValueType).hash_code() ==
            typeid(basic::error::defn::type::sys::code::Value).hash_code();
    }
    bool Result(const TestAliasConditionValueType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::ConditionValueType).
            hash_code() == typeid(basic::error::defn::type::sys::
            cond::Value).hash_code();
    }
    bool Result(const TestAliasStringType &, 
        VariableTestCategoryDefault & var)
    {
        return typeid(typename CategoryTraitType::StringType).hash_code() == 
            typeid(basic::error::msg::String).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<TestValueDefaultCondition, I> &, 
        VariableTestCategoryDefault & var)
    {
        auto & in_code = *basic::test::var::
            At<IDefaultConditionParamValue>(var).Get().template At<I>();
        auto & in_cond = *basic::test::var::
            At<IDefaultConditionResultParamValue>(var).Get().template At<I>();
        auto cond = CategoryTraitType::Instance().
            template DefaultCondition<basic::error::sys::Condition>(in_code,
            TmplCategoryType::GetInstance());
        return in_cond.Value() == cond.Value();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<TestValueEquivalent, I> &, 
        VariableTestCategoryDefault & var)
    {
        auto & code = *basic::test::var::
            At<IEquivalentCodeParamValue>(var).Get().template At<I>();
        auto & cond = *basic::test::var::
            At<IEquivalentConditionParamValue>(var).Get().template At<I>();
        auto & result = basic::test::var::
            At<IEquivalentResultSeqValue>(var).Get().template At<I>();
        return CategoryTraitType::Instance().Equivalent(code, cond) == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<TestValueMessage, I> &, 
        VariableTestCategoryDefault & var)
    {
        auto & value = *basic::test::var::
            At<IMessageParamValue>(var).Get().template At<I>();
        auto & result = basic::test::var::
            At<IMessageResultSeqValue>(var).Get().template At<I>();
        return strcmp(CategoryTraitType::Instance().Message(value).Value(), 
            result) == 0;
    }
    bool Result(const TestValueName &, VariableTestCategoryDefault & var)
    {
        auto & result = basic::test::var::At<INameValue>(var).Get().Get();
        return strcmp(CategoryTraitType::Instance().Name(), result) == 0;
    }
    bool Result(const TestValueValue &, VariableTestCategoryDefault & var)
    {
        auto & result = basic::test::var::At<IValueValue>(var).Get().Get();
        return CategoryTraitType::Instance().Value() == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestAliasDefnTypeCodeSetValueType, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IDefnCodeTypeParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        return typeid(typename basic::error::sys::tmpl::categ::defn::
            type::code::set::Value<CategoryTraitType>).
            hash_code() == typeid(ResultType).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestAliasDefnTypeConditionSetValueType, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IDefnConditionTypeParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        return typeid(typename basic::error::sys::tmpl::categ::defn::
            type::cond::set::Value<CategoryTraitType>).hash_code() ==
            typeid(ResultType).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrDefnTypeCodeEnum, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrDefnCodeEnumParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrDefnCodeEnumSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrDefnTypeConditionEnum, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrDefnConditionEnumParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrDefnConditionEnumSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncDefaultCode, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultCodeParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncDefaultCodeSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncDefaultCodeValue, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultCodeValueParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncDefaultCodeValueSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncDefaultCondition, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultConditionParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncDefaultConditionSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncDefaultConditionValue, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultConditionValueParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncDefaultConditionValueSeqValue>(var).Get().
            template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncEquivalent, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncEquivalentParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncEquivalentSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncMessage, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncMessageParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncMessageSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncName, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncNameParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncNameSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncToCodeValue, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncToCodeValueParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncToCodeValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncToConditionValue, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncToConditionValueParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncToConditionValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncValue, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncValueParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasStMmbrFuncInstance, I> &, 
        VariableTestCategoryDefault & var)
    {
        typedef typename basic::test::var::Element<
            IHasStMmbrFuncInstanceParamType, 
            VariableTestCategoryDefault>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasStMmbrFuncInstanceSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
};

typedef VariableTestCategoryDefault T1Var1;

typedef basic::test::type::Parameter<
    TestAliasCodeEnumType,
    TestAliasConditionEnumType,
    TestAliasCharType,
    TestAliasCategoryValueType,
    TestAliasCodeValueType,
    TestAliasConditionValueType,
    TestAliasStringType,
    basic::test::type::Index<TestValueDefaultCondition, 0>,
    basic::test::type::Index<TestValueDefaultCondition, 1>,
    basic::test::type::Index<TestValueEquivalent, 0>,
    basic::test::type::Index<TestValueEquivalent, 1>,
    basic::test::type::Index<TestValueMessage, 0>,
    basic::test::type::Index<TestValueMessage, 1>,
    basic::test::type::Index<TestValueMessage, 2>,
    basic::test::type::Index<TestValueMessage, 3>,
    TestValueName,
    TestValueValue,
    basic::test::type::Index<TestAliasDefnTypeCodeSetValueType, 0>,
    basic::test::type::Index<TestAliasDefnTypeConditionSetValueType, 0>,
    basic::test::type::Index<TestValueHasMmbrDefnTypeCodeEnum, 0>,
    basic::test::type::Index<TestValueHasMmbrDefnTypeConditionEnum, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncDefaultCode, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncDefaultCodeValue, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncDefaultCondition, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncDefaultConditionValue, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncEquivalent, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncEquivalent, 1>,
    basic::test::type::Index<TestValueHasMmbrFuncMessage, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncMessage, 1>,
    basic::test::type::Index<TestValueHasMmbrFuncMessage, 2>,
    basic::test::type::Index<TestValueHasMmbrFuncMessage, 3>,
    basic::test::type::Index<TestValueHasMmbrFuncName, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncToCodeValue, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncToConditionValue, 0>,
    basic::test::type::Index<TestValueHasMmbrFuncValue, 0>,
    basic::test::type::Index<TestValueHasStMmbrFuncInstance, 0>
    > Case1;

CodeType code1_1{1, TmplCategoryType::GetInstance()};
CodeValueType code_val1_1{1};
ConditionType cond1_1{1, TmplCategoryType::GetInstance()};

CodeType code1_2{1, TmplCategoryType::GetInstance()};
CodeValueType code_val1_2{1};

ConditionValueType cond_val1_2{1};
ConditionType cond1_2{1, TmplCategoryType::GetInstance()};

CodeType code1_3{1, TmplCategoryType::GetInstance()};
ConditionType cond1_3{1, TmplCategoryType::GetInstance()};
int err_code1 = 1;
std::errc err_enum1 = std::errc::operation_not_permitted;

CategoryValueType categ_val{basic::constant::error::sys::system_category};

T1Var1 t1_var1{
    &code1_1, &code_val1_1,
    &cond1_1, &cond1_1,
    &code1_2, &code_val1_2, 
    &cond_val1_2, &cond1_2, 
    true, true, 
    &code1_3, &cond1_3, &err_code1, &err_enum1,
    std::strerror(1), std::strerror(1), std::strerror(1), std::strerror(1),
    std::system_category().name(), categ_val, 
    true, true, 
    false, 
    false, 
    true,
    false,
    true, true, 
    true, true, true, true, 
    true, 
    false, 
    false, 
    true,
    true};

REGISTER_TEST(t1, new TestCategoryDefault<Case1, T1Var1>(t1_var1));

int main()
{
    return RUN_TEST();
}

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

BASIC_TEST_TYPE_NAME("std::errc", std::errc);
BASIC_TEST_TYPE_NAME("basic::error::msg::String", 
    basic::error::msg::String);
BASIC_TEST_TYPE_NAME("basic::error::sys::categ::Default",
    basic::error::sys::categ::Default);
BASIC_TEST_TYPE_NAME("basic::error::sys::Code", 
    basic::error::sys::Code);
BASIC_TEST_TYPE_NAME("basic::error::sys::Condition", 
    basic::error::sys::Condition);

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::defn::type::CodeEnum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::defn::type::CodeEnum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::defn::type::ConditionEnum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::defn::type::ConditionEnum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<
    basic::error::sys::tmpl::Category<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::Category<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<
    basic::error::sys::tmpl::categ::has::mmbr::func::DefaultCode<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::DefaultCode<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size(),
            _format, *tArg1CStr, *tArg2CStr, *tArg3CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::DefaultCodeValue<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::DefaultCodeValue<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct basic::test::type::Name<
    basic::error::sys::tmpl::categ::has::mmbr::func::
        DefaultCondition<TArg1, TArg2, TArg3, TArg4>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "asic::error::sys::tmpl::categ::has::"
            "mmbr::func::DefaultCondition<%s, %s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        basic::test::CString<char> tArg4CStr = 
            std::move(basic::test::type::Name<TArg4>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 12 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size() + 
            tArg4CStr.Size(), _format, *tArg1CStr, *tArg2CStr, *tArg3CStr,
            *tArg4CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::DefaultConditionValue<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::DefaultConditionValue<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<
    basic::error::sys::tmpl::categ::has::mmbr::func::Equivalent<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::Equivalent<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size(),
            _format, *tArg1CStr, *tArg2CStr, *tArg3CStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<
    basic::error::sys::tmpl::categ::has::mmbr::func::Message<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::Message<%s, %s, %s>";
        basic::test::CString<char> tArg1CStr = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArg2CStr = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        basic::test::CString<char> tArg3CStr = 
            std::move(basic::test::type::Name<TArg3>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 9 + 
            tArg1CStr.Size() + tArg2CStr.Size() + tArg3CStr.Size(),
            _format, *tArg1CStr, *tArg2CStr, *tArg3CStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::Name<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::Name<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::ToCodeValue<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::ToCodeValue<%s, %s>";
        basic::test::CString<char> tArgCStr1 = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArgCStr2 = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArgCStr1.Size() + tArgCStr2.Size(), _format, *tArgCStr1, 
            *tArgCStr2);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::ToConditionValue<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::ToConditionValue<%s, %s>";
        basic::test::CString<char> tArgCStr1 = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArgCStr2 = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArgCStr1.Size() + tArgCStr2.Size(), _format, *tArgCStr1, 
            *tArgCStr2);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    mmbr::func::Value<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "mmbr::func::Value<%s, %s>";
        basic::test::CString<char> tArgCStr1 = 
            std::move(basic::test::type::Name<TArg1>::CStr());
        basic::test::CString<char> tArgCStr2 = 
            std::move(basic::test::type::Name<TArg2>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 6 + 
            tArgCStr1.Size() + tArgCStr2.Size(), _format, *tArgCStr1, 
            *tArgCStr2);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::error::sys::tmpl::categ::has::
    st::mmbr::func::Instance<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::error::sys::tmpl::categ::has::"
            "st::mmbr::func::Instance<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<>
struct basic::test::out::Argument<basic::error::sys::Code *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::error::sys::Code * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::error::sys::Code * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::error::sys::Code *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::error::defn::type::sys::code::
    Value *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::error::defn::type::sys::code::
        Value * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(basic::error::defn::type::sys::code::
        Value * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<basic::error::defn::
    type::sys::code::Value *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::error::sys::Condition *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::error::sys::Condition * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::error::sys::Condition * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", cond->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::error::sys::Condition *>::ms_cstr;

struct Void1{};

template<>
struct basic::test::out::Argument<typename std::conditional<
    std::is_same<basic::error::defn::type::sys::cond::Value,
        basic::error::defn::type::sys::code::Value>::value, 
    Void1, basic::error::defn::type::sys::cond::Value *>::type>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::error::defn::type::sys::cond::
        Value * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
    static const char * Value(basic::error::defn::type::sys::cond::
        Value * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<
    typename std::conditional<std::is_same<basic::error::defn::
        type::sys::cond::Value, basic::error::defn::type::sys::
        code::Value>::value, 
    Void1, basic::error::defn::type::sys::cond::Value *>::type>::
        ms_cstr;

struct Void2{};

template<>
struct basic::test::out::Argument<typename std::conditional<
    std::is_same<int, basic::error::defn::type::sys::code::Value>::value ||
    std::is_same<int, basic::error::defn::type::sys::code::Value>::value, 
    Void2, int *>::type>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(int * & val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *val));
        return *ms_cstr;
    }
    static const char * Value(int * && val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *val));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<
    typename std::conditional<std::is_same<int, basic::error::defn::
        type::sys::code::Value>::value || std::is_same<int, basic::error::
        defn::type::sys::code::Value>::value, Void2, int *>::type>::
            ms_cstr;

template<>
struct basic::test::out::Argument<std::errc *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(std::errc * & val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<int>(*val)));
        return *ms_cstr;
    }
    static const char * Value(std::errc * && val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<int>(*val)));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<std::errc *>::
    ms_cstr;
