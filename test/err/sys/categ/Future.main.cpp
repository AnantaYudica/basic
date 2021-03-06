#define USING_BASIC_TEST_MEMORY
#include "Test.h"
#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"
#include "test/var/At.h"
#include "test/out/Argument.h"

#include "err/sys/categ/Future.h"

#include "defn/err/sys/Category.h"

#include "err/sys/Code.h"
#include "err/sys/Condition.h"

#include "err/sys/tmpl/Category.h"

#include "err/sys/tmpl/categ/defn/type/code/set/Value.h"
#include "err/sys/tmpl/categ/defn/type/cond/set/Value.h"

#include "err/sys/tmpl/categ/has/mmbr/defn/type/CodeEnum.h"
#include "err/sys/tmpl/categ/has/mmbr/defn/type/ConditionEnum.h"
#include "err/sys/tmpl/categ/has/mmbr/func/DefaultCode.h"
#include "err/sys/tmpl/categ/has/mmbr/func/DefaultCodeValue.h"
#include "err/sys/tmpl/categ/has/mmbr/func/DefaultCondition.h"
#include "err/sys/tmpl/categ/has/mmbr/func/DefaultConditionValue.h"
#include "err/sys/tmpl/categ/has/mmbr/func/Equivalent.h"
#include "err/sys/tmpl/categ/has/mmbr/func/Message.h"
#include "err/sys/tmpl/categ/has/mmbr/func/Name.h"
#include "err/sys/tmpl/categ/has/mmbr/func/ToCodeValue.h"
#include "err/sys/tmpl/categ/has/mmbr/func/ToConditionValue.h"
#include "err/sys/tmpl/categ/has/mmbr/func/Value.h"

#include "err/sys/tmpl/categ/has/st/mmbr/func/Instance.h"

#include "err/sys/code/has/Enum.h"
#include "err/sys/cond/has/Enum.h"
#include "err/sys/make/Category.h"
#include "err/sys/make/Code.h"
#include "err/sys/make/Condition.h"

#include <system_error>
#include <type_traits>
#include <utility>
#include <cstring>

BASIC_TEST_CONSTRUCT;

#define BUFFER_FORMAT_CSTRING 256

basic::test::CString<char> ConditionToString(basic::err::sys::
    Condition * && cond)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "m_value : %d", cond->Value());
}

basic::test::CString<char> CodeToString(basic::err::sys::
    Code * && code)
{
    return basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
        "m_value : %d", code->Value());
}

const char * BoolToString(bool && b)
{
    return (b ? "true" : "false");
}

char DefnCodeTypeString_1[] = "basic::err::sys::tmpl::"
    "categ::defn::type::code::set::Value<basic::err::sys::categ::"
    "Future>";
char DefnConditionTypeString_1[] = "basic::err::sys::tmpl::"
    "categ::defn::type::cond::set::Value<basic::err::sys::"
    "categ::Future>";

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
struct TestValueCodeHasEnum {};
struct TestValueCondHasEnum {};
struct TestValueMakeCategoryVoid {};
struct TestValueMakeCategoryCodeEnum {};
struct TestValueMakeCategoryConditionEnum {};
struct TestValueMakeCode {};
struct TestValueMakeCondition {};

typedef basic::err::sys::categ::Future CategoryTraitType;
typedef basic::err::sys::tmpl::Category<CategoryTraitType>
    TmplCategoryType;
typedef std::future_errc CodeEnumType;
typedef std::future_errc ConditionEnumType;
typedef basic::err::defn::type::Char CharType;
typedef basic::err::defn::type::sys::categ::Value CategoryValueType;
typedef basic::err::defn::type::sys::code::Value CodeValueType;
typedef basic::err::defn::type::sys::cond::Value ConditionValueType;
typedef basic::err::msg::String MessageStringType;
typedef basic::err::sys::Condition ConditionType;
typedef basic::err::sys::Code CodeType;
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
    std::future_errc> MessageParamTypeType;
typedef basic::test::val::Parameter<
    CodeType *, 
    ConditionType *,
    int *,
    std::future_errc *> MessageParamValueType;
typedef basic::test::val::Sequence<const char *, 4> MessageResultSeqValueType;
typedef basic::test::Value<const char *> NameValueType;
typedef basic::test::Value<CategoryValueType> ValueValueType;
typedef basic::test::type::val::Sequence<const char *, 
    DefnCodeTypeString_1> DefnCodeTypeSeqNameValueType;
typedef basic::test::type::Parameter<std::future_errc> 
    DefnCodeTypeParamTypeType;
typedef basic::test::type::val::Sequence<const char *, 
    DefnConditionTypeString_1> 
        DefnConditionTypeSeqNameValueType;
typedef basic::test::type::Parameter<std::future_errc> 
    DefnConditionTypeParamTypeType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::defn::type::CodeEnum<
        CategoryTraitType>>
            HasMmbrDefnCodeEnumParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrDefnCodeEnumSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::defn::type::
        ConditionEnum<CategoryTraitType>>
            HasMmbrDefnConditionEnumParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrDefnConditionEnumSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::DefaultCode<
        CategoryTraitType, CodeType, TmplCategoryType>>
            HasMmbrFuncDefaultCodeParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrFuncDefaultCodeSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::
        DefaultCodeValue<CategoryTraitType>>
            HasMmbrFuncDefaultCodeValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncDefaultCodeValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::
        DefaultCondition<CategoryTraitType, ConditionType, CodeType, 
        TmplCategoryType>>HasMmbrFuncDefaultConditionParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncDefaultConditionSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::
        DefaultConditionValue<CategoryTraitType>>
            HasMmbrFuncDefaultConditionValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1>
    HasMmbrFuncDefaultConditionValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::Equivalent<
        CategoryTraitType, CodeType, ConditionValueType>,
    basic::err::sys::tmpl::categ::has::mmbr::func::Equivalent<
        CategoryTraitType, CodeValueType, ConditionType>>
            HasMmbrFuncEquivalentParamTypeType;
typedef basic::test::val::Sequence<bool, 2> 
    HasMmbrFuncEquivalentSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, CodeType>,
    basic::err::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, ConditionType>,
    basic::err::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, int>,
    basic::err::sys::tmpl::categ::has::mmbr::func::Message<
        CategoryTraitType, MessageStringType, std::future_errc>>
            HasMmbrFuncMessageParamTypeType;
typedef basic::test::val::Sequence<bool, 4> 
    HasMmbrFuncMessageSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::Name<
        CategoryTraitType>> HasMmbrFuncNameParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncNameSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::ToCodeValue<
        CategoryTraitType, std::future_errc>> 
            HasMmbrFuncToCodeValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncToCodeValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::
        ToConditionValue<CategoryTraitType, std::future_errc>>
            HasMmbrFuncToConditionValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncToConditionValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::mmbr::func::Value<
        CategoryTraitType, CategoryValueType>> HasMmbrFuncValueParamTypeType;
typedef basic::test::val::Sequence<bool, 1> 
    HasMmbrFuncValueSeqValueType;
typedef basic::test::type::Parameter<
    basic::err::sys::tmpl::categ::has::st::mmbr::func::Instance<
        CategoryTraitType>> HasStMmbrFuncInstanceParamTypeType;
typedef basic::test::val::Sequence<bool, 1> HasStMmbrFuncInstanceSeqValueType;

using VariableTestCategoryFuture = basic::test::Variable<
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
    basic::err::sys::code::has::Enum<CodeEnumType>,
    basic::err::sys::cond::has::Enum<ConditionEnumType>,
    basic::test::Value<bool>,
    basic::test::Value<bool>,
    basic::err::sys::make::Category<void>,
    basic::err::sys::make::Category<CodeEnumType>,
    basic::err::sys::make::Category<ConditionEnumType>,
    basic::err::sys::tmpl::Category<CategoryTraitType>,
    basic::test::Value<const basic::err::sys::tmpl::Category<
        CategoryTraitType> *>,
    basic::test::Value<CodeEnumType>,
    basic::test::Value<ConditionEnumType>,
    basic::err::sys::make::Code<CodeEnumType>,
    basic::err::sys::make::Condition<ConditionEnumType>,
    basic::test::Value<CodeValueType>,
    basic::test::Value<ConditionValueType>,
    basic::test::type::Function<basic::test::CString<char>(
        ConditionType * &&), &ConditionToString>,
    basic::test::type::Function<basic::test::CString<char>(
        CodeType * &&), &CodeToString>,
    basic::test::type::Function<const char * (bool && b), &BoolToString>>;

constexpr std::size_t IFutureType = 0;
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
constexpr std::size_t ICodeHasEnumType = 53;
constexpr std::size_t ICondHasEnumType = 54;
constexpr std::size_t ICodeHasEnumValue = 55;
constexpr std::size_t ICondHasEnumValue = 56;
constexpr std::size_t IMakeVoidCategoryType = 57;
constexpr std::size_t IMakeCodeCategoryType = 58;
constexpr std::size_t IMakeConditionCategoryType = 59;
constexpr std::size_t ITmplCategoryType = 60;
constexpr std::size_t IMakeCategoryValue = 61;
constexpr std::size_t ICodeEnumValue = 62;
constexpr std::size_t IConditionEnumValue = 63;
constexpr std::size_t IMakeCodeType = 64;
constexpr std::size_t IMakeConditionType = 65;
constexpr std::size_t IMakeCodeValue = 66;
constexpr std::size_t IMakeConditionValue = 67;
constexpr std::size_t IConditionToStringFunc = 68;
constexpr std::size_t ICodeToStringFunc = 69;
constexpr std::size_t IBoolToStringFunc = 70;

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
template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

typedef basic::test::msg::Argument<TestAliasCodeEnumType,
    ArgTypeName<IFutureType>, ArgTypeName<ICodeEnumType>> 
        ArgTestAliasCodeEnumType;

typedef basic::test::msg::Base<TestAliasCodeEnumType, char, 
    ArgTestAliasCodeEnumType, ArgTestAliasCodeEnumType, 
    ArgTestAliasCodeEnumType> MessageBaseTestAliasCodeEnumType;

typedef basic::test::msg::Argument<TestAliasConditionEnumType,
    ArgTypeName<IFutureType>, ArgTypeName<IConditionEnumType>> 
        ArgTestAliasConditionEnumType;

typedef basic::test::msg::Base<TestAliasConditionEnumType, char, 
    ArgTestAliasConditionEnumType, ArgTestAliasConditionEnumType, 
    ArgTestAliasConditionEnumType> MessageBaseTestAliasConditionEnumType;

typedef basic::test::msg::Argument<TestAliasCharType,
    ArgTypeName<IFutureType>, ArgTypeName<ICharType>> 
        ArgTestAliasCharType;

typedef basic::test::msg::Base<TestAliasCharType, char, 
    ArgTestAliasCharType, ArgTestAliasCharType, 
    ArgTestAliasCharType> MessageBaseTestAliasCharType;

typedef basic::test::msg::Argument<TestAliasCategoryValueType,
    ArgTypeName<IFutureType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasCategoryValueType;

typedef basic::test::msg::Base<TestAliasCategoryValueType, char, 
    ArgTestAliasCategoryValueType, ArgTestAliasCategoryValueType, 
    ArgTestAliasCategoryValueType> MessageBaseTestAliasCategoryValueType;

typedef basic::test::msg::Argument<TestAliasCodeValueType,
    ArgTypeName<IFutureType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasCodeValueType;

typedef basic::test::msg::Base<TestAliasCodeValueType, char, 
    ArgTestAliasCodeValueType, ArgTestAliasCodeValueType, 
    ArgTestAliasCodeValueType> MessageBaseTestAliasCodeValueType;

typedef basic::test::msg::Argument<TestAliasConditionValueType,
    ArgTypeName<IFutureType>, ArgTypeName<ICategoryValueType>> 
        ArgTestAliasConditionValueType;

typedef basic::test::msg::Base<TestAliasConditionValueType, char, 
    ArgTestAliasConditionValueType, ArgTestAliasConditionValueType, 
    ArgTestAliasConditionValueType> MessageBaseTestAliasConditionValueType;

typedef basic::test::msg::Argument<TestAliasStringType,
    ArgTypeName<IFutureType>, ArgTypeName<IStringType>> 
        ArgTestAliasStringType;

typedef basic::test::msg::Base<TestAliasStringType, char, 
    ArgTestAliasStringType, ArgTestAliasStringType, 
    ArgTestAliasStringType> MessageBaseTestAliasStringType;
 
typedef basic::test::msg::Argument<TestValueDefaultCondition,
    ArgTypeName<IFutureType>, 
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
    ArgTypeName<IFutureType>,
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
    ArgTypeName<IFutureType>,
    ArgTypeIndex<IMessageParamType, ArgTypeParamNameAt>,
    ArgTypeIndex<IMessageParamValue, ArgValParamAt>,
    ArgTypeIndex<IMessageResultSeqValue, ArgValSeqAt>> ArgTestValueMessage;

typedef basic::test::msg::Base<TestValueMessage, char, 
    ArgTestValueMessage, ArgTestValueMessage, 
    ArgTestValueMessage> MessageBaseTestValueMessage;

typedef basic::test::msg::Argument<TestValueName,
    ArgTypeName<IFutureType>,
    basic::test::msg::arg::Value<INameValue>> 
        ArgTestValueName;

typedef basic::test::msg::Base<TestValueName, char, 
    ArgTestValueName, ArgTestValueName, 
    ArgTestValueName> MessageBaseTestValueName;

typedef basic::test::msg::Argument<TestValueValue,
    ArgTypeName<IFutureType>,
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

typedef basic::test::msg::Argument<TestValueCodeHasEnum,
    ArgTypeName<ICodeHasEnumType>,
    ArgTypeFunction<IBoolToStringFunc,
        ArgValue<ICodeHasEnumValue>>> ArgTestValueCodeHasEnum;

typedef basic::test::msg::Base<TestValueCodeHasEnum, char,
    ArgTestValueCodeHasEnum, ArgTestValueCodeHasEnum, 
    ArgTestValueCodeHasEnum> MessageBaseTestValueCodeHasEnum;

typedef basic::test::msg::Argument<TestValueCondHasEnum,
    ArgTypeName<ICondHasEnumType>,
    ArgTypeFunction<IBoolToStringFunc,
        ArgValue<ICondHasEnumValue>>> ArgTestValueCondHasEnum;

typedef basic::test::msg::Base<TestValueCondHasEnum, char,
    ArgTestValueCondHasEnum, ArgTestValueCondHasEnum, 
    ArgTestValueCondHasEnum> MessageBaseTestValueCondHasEnum;

typedef basic::test::msg::Argument<TestValueMakeCategoryVoid,
    ArgTypeName<IMakeVoidCategoryType>,
    ArgTypeName<ITmplCategoryType>> ArgTestValueMakeCategoryVoid;

typedef basic::test::msg::Base<TestValueMakeCategoryVoid, char,
    ArgTestValueMakeCategoryVoid, ArgTestValueMakeCategoryVoid, 
    ArgTestValueMakeCategoryVoid> MessageBaseTestValueMakeCategoryVoid;

typedef basic::test::msg::Argument<TestValueMakeCategoryCodeEnum,
    ArgTypeName<IMakeCodeCategoryType>,
    ArgTypeName<ITmplCategoryType>> ArgTestValueMakeCategoryCodeEnum;

typedef basic::test::msg::Base<TestValueMakeCategoryCodeEnum, char,
    ArgTestValueMakeCategoryCodeEnum, ArgTestValueMakeCategoryCodeEnum, 
    ArgTestValueMakeCategoryCodeEnum> MessageBaseTestValueMakeCategoryCodeEnum;

typedef basic::test::msg::Argument<TestValueMakeCategoryConditionEnum,
    ArgTypeName<IMakeConditionCategoryType>,
    ArgTypeName<ITmplCategoryType>> ArgTestValueMakeCategoryConditionEnum;

typedef basic::test::msg::Base<TestValueMakeCategoryConditionEnum, char,
    ArgTestValueMakeCategoryConditionEnum, 
    ArgTestValueMakeCategoryConditionEnum, 
    ArgTestValueMakeCategoryConditionEnum> 
        MessageBaseTestValueMakeCategoryConditionEnum;

typedef basic::test::msg::Argument<TestValueMakeCode,
    ArgTypeName<IMakeCodeType>,
    ArgTypeName<ICodeEnumType>,
    ArgValue<IMakeCodeValue>,
    ArgTypeName<ICodeValueType>> ArgTestValueMakeCode;

typedef basic::test::msg::Base<TestValueMakeCode, char,
    ArgTestValueMakeCode, ArgTestValueMakeCode, 
    ArgTestValueMakeCode> MessageBaseTestValueMakeCode;

typedef basic::test::msg::Argument<TestValueMakeCondition,
    ArgTypeName<IMakeConditionType>,
    ArgTypeName<IConditionEnumType>,
    ArgValue<IMakeConditionValue>,
    ArgTypeName<IConditionValueType>> ArgTestValueMakeCondition;

typedef basic::test::msg::Base<TestValueMakeCondition, char,
    ArgTestValueMakeCondition, ArgTestValueMakeCondition, 
    ArgTestValueMakeCondition> MessageBaseTestValueMakeCondition;

template<typename TCases, typename... TVariables>
struct TestCategoryFuture :
    public basic::test::Message<BASIC_TEST, TestCategoryFuture<TCases, 
        TVariables...>>,
    public basic::test::Case<TestCategoryFuture<TCases, TVariables...>,
        TCases>,
    public basic::test::Base<TestCategoryFuture<TCases, TVariables...>, 
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
    public MessageBaseTestValueHasStMmbrFuncInstance,
    public MessageBaseTestValueCodeHasEnum,
    public MessageBaseTestValueCondHasEnum,
    public MessageBaseTestValueMakeCategoryVoid,
    public MessageBaseTestValueMakeCategoryCodeEnum,
    public MessageBaseTestValueMakeCategoryConditionEnum,
    public MessageBaseTestValueMakeCode,
    public MessageBaseTestValueMakeCondition
{
public:
    using basic::test::Case<TestCategoryFuture<TCases, TVariables...>,
        TCases>::Run;
    using basic::test::Base<TestCategoryFuture<TCases, TVariables...>, 
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
    using MessageBaseTestValueCodeHasEnum::Format;
    using MessageBaseTestValueCodeHasEnum::SetFormat;
    using MessageBaseTestValueCodeHasEnum::Argument;
    using MessageBaseTestValueCondHasEnum::Format;
    using MessageBaseTestValueCondHasEnum::SetFormat;
    using MessageBaseTestValueCondHasEnum::Argument;
    using MessageBaseTestValueMakeCategoryVoid::Format;
    using MessageBaseTestValueMakeCategoryVoid::SetFormat;
    using MessageBaseTestValueMakeCategoryVoid::Argument;
    using MessageBaseTestValueMakeCategoryCodeEnum::Format;
    using MessageBaseTestValueMakeCategoryCodeEnum::SetFormat;
    using MessageBaseTestValueMakeCategoryCodeEnum::Argument;
    using MessageBaseTestValueMakeCategoryConditionEnum::Format;
    using MessageBaseTestValueMakeCategoryConditionEnum::SetFormat;
    using MessageBaseTestValueMakeCategoryConditionEnum::Argument;
    using MessageBaseTestValueMakeCode::Format;
    using MessageBaseTestValueMakeCode::SetFormat;
    using MessageBaseTestValueMakeCode::Argument;
    using MessageBaseTestValueMakeCondition::Format;
    using MessageBaseTestValueMakeCondition::SetFormat;
    using MessageBaseTestValueMakeCondition::Argument;
public:
    TestCategoryFuture(TVariables & ... var) :
        basic::test::Message<BASIC_TEST, TestCategoryFuture<TCases, 
            TVariables...>>(*this),
        basic::test::Case<TestCategoryFuture<TCases, TVariables...>,
            TCases>(*this),
        basic::test::Base<TestCategoryFuture<TCases, TVariables...>, 
            TVariables...>(*this, var...)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;

        TestAliasCodeEnumType testAliasCodeEnumType;
        SetFormat(info, testAliasCodeEnumType, "Test alias type "
            "%s::CodeEnumType is same with %s\n");
        SetFormat(debug, testAliasCodeEnumType, "Test alias type "
            "%s::CodeEnumType is same with %s\n");
        SetFormat(err, testAliasCodeEnumType, "Error alias type "
            "%s::CodeEnumType is not same with %s\n");

        TestAliasConditionEnumType testAliasConditionEnumType;
        SetFormat(info, testAliasConditionEnumType, "Test alias type "
            "%s::ConditionEnumType is same with %s\n");
        SetFormat(debug, testAliasConditionEnumType, "Test alias type "
            "%s::ConditionEnumType is same with %s\n");
        SetFormat(err, testAliasConditionEnumType, "Error alias type "
            "%s::ConditionEnumType is not same with %s\n");

        TestAliasCharType testAliasCharType;
        SetFormat(info, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(debug, testAliasCharType, "Test alias type "
            "%s::CharType is same with %s\n");
        SetFormat(err, testAliasCharType, "Error alias type "
            "%s::CharType is not same with %s\n");
        
        TestAliasCategoryValueType testAliasCategoryValueType;
        SetFormat(info, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(debug, testAliasCategoryValueType, "Test alias type "
            "%s::CategoryValueType is same with %s\n");
        SetFormat(err, testAliasCategoryValueType, "Error alias type "
            "%s::CategoryValueType is not same with %s\n");

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

        TestValueDefaultCondition testValueDefaultCondition;
        SetFormat(info, testValueDefaultCondition, "Test value "
            "%s::DefaultCondition(%s {%s}) is same with %s {%s}\n");
        SetFormat(debug, testValueDefaultCondition, "Test value "
            "%s::DefaultCondition(%s {%s}) is same with %s {%s}\n");
        SetFormat(err, testValueDefaultCondition, "Error value "
            "%s::DefaultCondition(%s {%s}) is not same with %s {%s}\n");
        
        TestValueEquivalent testValueEquivalent;
        SetFormat(info, testValueEquivalent, "Test value "
            "%s::Equivalent(%s {%s}, %s {%s}) is same with %s\n");
        SetFormat(debug, testValueEquivalent, "Test value "
            "%s::Equivalent(%s {%s}, %s {%s}) is same with %s\n");
        SetFormat(err, testValueEquivalent, "Error value "
            "%s::Equivalent(%s {%s}, %s {%s}) is not same with %s\n");

        TestValueMessage testValueMessage;
        SetFormat(info, testValueMessage, "Test value "
            "%s::Message(%s {%s}) is same with \"%s\"\n");
        SetFormat(debug, testValueMessage, "Test value "
            "%s::Message(%s {%s}) is same with \"%s\"\n");
        SetFormat(err, testValueMessage, "Error value "
            "%s::Message(%s {%s}) is not same with \"%s\"\n");

        TestValueName testValueName;
        SetFormat(info, testValueName, "Test value "
            "%s::Name() is same with \"%s\"\n");
        SetFormat(debug, testValueName, "Test value "
            "%s::Name() is same with \"%s\"\n");
        SetFormat(err, testValueName, "Error value "
            "%s::Name() is not same with \"%s\"\n");

        TestValueValue testValueValue;
        SetFormat(info, testValueValue, "Test value "
            "%s::Value() is same with %d\n");
        SetFormat(debug, testValueValue, "Test value "
            "%s::Value() is same with %d\n");
        SetFormat(err, testValueValue, "Error value "
            "%s::Value() is not same with %d\n");

        TestAliasDefnTypeCodeSetValueType testAliasDefnTypeCodeSetValueType;
        SetFormat(info, testAliasDefnTypeCodeSetValueType, "Test alias type "
            "%s is same with %s\n");
        SetFormat(debug, testAliasDefnTypeCodeSetValueType, "Test alias type "
            "%s is same with %s\n");
        SetFormat(err, testAliasDefnTypeCodeSetValueType, "Error alias type "
            "%s is not same with %s\n");
        
        TestAliasDefnTypeConditionSetValueType 
            testAliasDefnTypeConditionSetValueType;
        SetFormat(info, testAliasDefnTypeConditionSetValueType, "Test alias "
            "type %s is same with %s\n");
        SetFormat(debug, testAliasDefnTypeConditionSetValueType, "Test alias "
            "type %s is same with %s\n");
        SetFormat(err, testAliasDefnTypeConditionSetValueType, "Error alias "
            "type %s is not same with %s\n");

        TestValueHasMmbrDefnTypeCodeEnum testValueHasMmbrDefnTypeCodeEnum;
        SetFormat(info, testValueHasMmbrDefnTypeCodeEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrDefnTypeCodeEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrDefnTypeCodeEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrDefnTypeConditionEnum 
            testValueHasMmbrDefnTypeConditionEnum;
        SetFormat(info, testValueHasMmbrDefnTypeConditionEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrDefnTypeConditionEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrDefnTypeConditionEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCode 
            testValueHasMmbrFuncDefaultCode;
        SetFormat(info, testValueHasMmbrFuncDefaultCode, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCode, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncDefaultCode, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCodeValue
            testValueHasMmbrFuncDefaultCodeValue;
        SetFormat(info, testValueHasMmbrFuncDefaultCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncDefaultCodeValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultCondition
            testValueHasMmbrFuncDefaultCondition;
        SetFormat(info, testValueHasMmbrFuncDefaultCondition, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultCondition, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncDefaultCondition, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncDefaultConditionValue
            testValueHasMmbrFuncDefaultConditionValue;
        SetFormat(info, testValueHasMmbrFuncDefaultConditionValue, "Test "
            "value %s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncDefaultConditionValue, "Test "
            "value %s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncDefaultConditionValue, "Error "
            "value %s::Value is not same with %s\n");

        TestValueHasMmbrFuncEquivalent testValueHasMmbrFuncEquivalent;
        SetFormat(info, testValueHasMmbrFuncEquivalent, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncEquivalent, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncEquivalent, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncMessage testValueHasMmbrFuncMessage;
        SetFormat(info, testValueHasMmbrFuncMessage, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncMessage, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncMessage, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncName testValueHasMmbrFuncName;
        SetFormat(info, testValueHasMmbrFuncName, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncName, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncName, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncToCodeValue testValueHasMmbrFuncToCodeValue;
        SetFormat(info, testValueHasMmbrFuncToCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncToCodeValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncToCodeValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncToConditionValue 
            testValueHasMmbrFuncToConditionValue;
        SetFormat(info, testValueHasMmbrFuncToConditionValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncToConditionValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncToConditionValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasMmbrFuncValue testValueHasMmbrFuncValue;
        SetFormat(info, testValueHasMmbrFuncValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasMmbrFuncValue, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasMmbrFuncValue, "Error value "
            "%s::Value is not same with %s\n");

        TestValueHasStMmbrFuncInstance testValueHasStMmbrFuncInstance;
        SetFormat(info, testValueHasStMmbrFuncInstance, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueHasStMmbrFuncInstance, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueHasStMmbrFuncInstance, "Error value "
            "%s::Value is not same with %s\n");

        TestValueCodeHasEnum testValueCodeHasEnum;
        SetFormat(info, testValueCodeHasEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueCodeHasEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueCodeHasEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueCondHasEnum testValueCondHasEnum;
        SetFormat(info, testValueCondHasEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(debug, testValueCondHasEnum, "Test value "
            "%s::Value is same with %s\n");
        SetFormat(err, testValueCondHasEnum, "Error value "
            "%s::Value is not same with %s\n");

        TestValueMakeCategoryVoid testValueMakeCategoryVoid;
        SetFormat(info, testValueMakeCategoryVoid, "Test value "
            "%s::GetInstance() is not same with %s\n");
        SetFormat(debug, testValueMakeCategoryVoid, "Test value "
            "%s::GetInstance() is not same with %s\n");
        SetFormat(err, testValueMakeCategoryVoid, "Error value "
            "%s::GetInstance() is same with %s\n");

        TestValueMakeCategoryCodeEnum testValueMakeCategoryCodeEnum;
        SetFormat(info, testValueMakeCategoryCodeEnum, "Test value "
            "%s::GetInstance() is same with %s\n");
        SetFormat(debug, testValueMakeCategoryCodeEnum, "Test value "
            "%s::GetInstance() is same with %s\n");
        SetFormat(err, testValueMakeCategoryCodeEnum, "Error value "
            "%s::GetInstance() is not same with %s\n");

        TestValueMakeCategoryConditionEnum testValueMakeCategoryConditionEnum;
        SetFormat(info, testValueMakeCategoryConditionEnum, "Test value "
            "%s::GetInstance() is same with %s\n");
        SetFormat(debug, testValueMakeCategoryConditionEnum, "Test value "
            "%s::GetInstance() is same with %s\n");
        SetFormat(err, testValueMakeCategoryConditionEnum, "Error value "
            "%s::GetInstance() is not same with %s\n");

        TestValueMakeCode testValueMakeCode;
        SetFormat(info, testValueMakeCode, "Test value "
            "%s::Value(%s) is same with %d {%s}\n");
        SetFormat(debug, testValueMakeCode, "Test value "
            "%s::Value(%s) is same with %d {%s}\n");
        SetFormat(err, testValueMakeCode, "Error value "
            "%s::Value(%s) is not same with %d {%s}\n");

        TestValueMakeCondition testValueMakeCondition;
        SetFormat(info, testValueMakeCondition, "Test value "
            "%s::Value(%s) is same with %d {%s}\n");
        SetFormat(debug, testValueMakeCondition, "Test value "
            "%s::Value(%s) is same with %d {%s}\n");
        SetFormat(err, testValueMakeCondition, "Error value "
            "%s::Value(%s) is not same with %d {%s}\n");
    }
    bool Result(const TestAliasCodeEnumType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::CodeEnumType).hash_code() == 
            typeid(CodeEnumType).hash_code();
    }
    bool Result(const TestAliasConditionEnumType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::ConditionEnumType).
            hash_code() == typeid(ConditionEnumType).hash_code();
    }
    bool Result(const TestAliasCharType &, VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::CharType).hash_code() == 
            typeid(basic::err::defn::type::Char).hash_code();
    }
    bool Result(const TestAliasCategoryValueType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::CategoryValueType).
            hash_code() == typeid(basic::err::defn::type::sys::
            categ::Value).hash_code();
    }
    bool Result(const TestAliasCodeValueType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::CodeValueType).hash_code() ==
            typeid(basic::err::defn::type::sys::code::Value).hash_code();
    }
    bool Result(const TestAliasConditionValueType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::ConditionValueType).
            hash_code() == typeid(basic::err::defn::type::sys::
            cond::Value).hash_code();
    }
    bool Result(const TestAliasStringType &, 
        VariableTestCategoryFuture & var)
    {
        return typeid(typename CategoryTraitType::StringType).hash_code() == 
            typeid(basic::err::msg::String).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<TestValueDefaultCondition, I> &, 
        VariableTestCategoryFuture & var)
    {
        auto & in_code = *basic::test::var::
            At<IDefaultConditionParamValue>(var).Get().template At<I>();
        auto & in_cond = *basic::test::var::
            At<IDefaultConditionResultParamValue>(var).Get().template At<I>();
        auto cond = CategoryTraitType::Instance().
            template DefaultCondition<basic::err::sys::Condition>(in_code,
            TmplCategoryType::GetInstance());
        return in_cond.Value() == cond.Value();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<TestValueEquivalent, I> &, 
        VariableTestCategoryFuture & var)
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
        VariableTestCategoryFuture & var)
    {
        auto & value = *basic::test::var::
            At<IMessageParamValue>(var).Get().template At<I>();
        auto & result = basic::test::var::
            At<IMessageResultSeqValue>(var).Get().template At<I>();
        return strcmp(CategoryTraitType::Instance().Message(value).Value(), 
            result) == 0;
    }
    bool Result(const TestValueName &, VariableTestCategoryFuture & var)
    {
        auto & result = basic::test::var::At<INameValue>(var).Get().Get();
        return strcmp(CategoryTraitType::Instance().Name(), result) == 0;
    }
    bool Result(const TestValueValue &, VariableTestCategoryFuture & var)
    {
        auto & result = basic::test::var::At<IValueValue>(var).Get().Get();
        return CategoryTraitType::Instance().Value() == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestAliasDefnTypeCodeSetValueType, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IDefnCodeTypeParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        return typeid(typename basic::err::sys::tmpl::categ::defn::
            type::code::set::Value<CategoryTraitType>).
            hash_code() == typeid(ResultType).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestAliasDefnTypeConditionSetValueType, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IDefnConditionTypeParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        return typeid(typename basic::err::sys::tmpl::categ::defn::
            type::cond::set::Value<CategoryTraitType>).hash_code() ==
            typeid(ResultType).hash_code();
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrDefnTypeCodeEnum, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrDefnCodeEnumParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrDefnConditionEnumParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultCodeParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultCodeValueParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultConditionParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncDefaultConditionValueParamType, 
            VariableTestCategoryFuture>::Type ParamType;
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
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncEquivalentParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncEquivalentSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncMessage, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncMessageParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncMessageSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncName, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncNameParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncNameSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncToCodeValue, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncToCodeValueParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncToCodeValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncToConditionValue, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncToConditionValueParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncToConditionValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasMmbrFuncValue, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasMmbrFuncValueParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasMmbrFuncValueSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    template<std::size_t I>
    bool Result(const basic::test::type::Index<
        TestValueHasStMmbrFuncInstance, I> &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<
            IHasStMmbrFuncInstanceParamType, 
            VariableTestCategoryFuture>::Type ParamType;
        typedef typename basic::test::type::param::Element<I, 
            ParamType>::Type ResultType;
        auto & result = basic::test::var::At<
            IHasStMmbrFuncInstanceSeqValue>(var).Get().template At<I>();
        return ResultType::Value == result;
    }
    bool Result(const TestValueCodeHasEnum &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<ICodeHasEnumType,
            VariableTestCategoryFuture>::Type CodeHasEnumType;
        auto & result = basic::test::var::At<ICodeHasEnumValue>(var).Get().
            Get();
        return CodeHasEnumType::Value == result;
    }
    bool Result(const TestValueCondHasEnum &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<ICondHasEnumType,
            VariableTestCategoryFuture>::Type CondHasEnumType;
        auto & result = basic::test::var::At<ICondHasEnumValue>(var).Get().
            Get();
        return CondHasEnumType::Value == result;
    }
    bool Result(const TestValueMakeCategoryVoid &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<IMakeVoidCategoryType,
            VariableTestCategoryFuture>::Type VoidCategoryType;
        auto * result = basic::test::var::At<IMakeCategoryValue>(var).Get().
            Get();
        return VoidCategoryType::GetInstance() != *result;
    }
    bool Result(const TestValueMakeCategoryCodeEnum &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<IMakeCodeCategoryType,
            VariableTestCategoryFuture>::Type CodeCategoryType;
        auto * result = basic::test::var::At<IMakeCategoryValue>(var).Get().
            Get();
        return CodeCategoryType::GetInstance() == *result;
    }
    bool Result(const TestValueMakeCategoryConditionEnum &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<IMakeConditionCategoryType,
            VariableTestCategoryFuture>::Type ConditionCategoryType;
        auto * result = basic::test::var::At<IMakeCategoryValue>(var).Get().
            Get();
        return ConditionCategoryType::GetInstance() == *result;
    }
    bool Result(const TestValueMakeCode &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<IMakeCodeType,
            VariableTestCategoryFuture>::Type CodeType;
        auto & code_enum = basic::test::var::At<ICodeEnumValue>(var).Get().
            Get();
        auto & result = basic::test::var::At<IMakeCodeValue>(var).Get().
            Get();
        return CodeType::Value(code_enum) == result;
    }
    bool Result(const TestValueMakeCondition &, 
        VariableTestCategoryFuture & var)
    {
        typedef typename basic::test::var::Element<IMakeConditionType,
            VariableTestCategoryFuture>::Type ConditionType;
        auto & cond_enum = basic::test::var::At<IConditionEnumValue>(var).
            Get().Get();
        auto & result = basic::test::var::At<IMakeConditionValue>(var).Get().
            Get();
        return ConditionType::Value(cond_enum) == result;
    }
};

typedef VariableTestCategoryFuture T1Var1;

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
    basic::test::type::Index<TestValueHasStMmbrFuncInstance, 0>,
    TestValueCodeHasEnum,
    TestValueCondHasEnum,
    TestValueMakeCategoryVoid,
    TestValueMakeCategoryCodeEnum,
    TestValueMakeCategoryConditionEnum,
    TestValueMakeCode,
    TestValueMakeCondition> Case1;

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
std::future_errc err_enum1 = std::future_errc::future_already_retrieved;
std::string err_msg1 = std::future_category().message(1);

CategoryValueType categ_val{basic::defn::err::sys::future_category};

T1Var1 t1_var1{
    &code1_1, &code_val1_1,
    &cond1_1, &cond1_1,
    &code1_2, &code_val1_2, 
    &cond_val1_2, &cond1_2, 
    true, true, 
    &code1_3, &cond1_3, &err_code1, &err_enum1,
    err_msg1.c_str(), err_msg1.c_str(), err_msg1.c_str(), err_msg1.c_str(),
    std::future_category().name(), categ_val, 
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
    true,
    true,
    true,
    &TmplCategoryType::GetInstance(),
    std::future_errc::future_already_retrieved,
    std::future_errc::promise_already_satisfied,
    static_cast<CodeValueType>(std::future_errc::future_already_retrieved),
    static_cast<ConditionValueType>(
        std::future_errc::promise_already_satisfied)};

REGISTER_TEST(t1, new TestCategoryFuture<Case1, T1Var1>(t1_var1));

int main()
{
    return RUN_TEST();
}

BASIC_TEST_TYPE_NAME("void", void);
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

BASIC_TEST_TYPE_NAME("std::future_errc", std::future_errc);
BASIC_TEST_TYPE_NAME("basic::err::msg::String", 
    basic::err::msg::String);
BASIC_TEST_TYPE_NAME("basic::err::sys::categ::Future",
    basic::err::sys::categ::Future);
BASIC_TEST_TYPE_NAME("basic::err::sys::Code", 
    basic::err::sys::Code);
BASIC_TEST_TYPE_NAME("basic::err::sys::Condition", 
    basic::err::sys::Condition);

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::defn::type::CodeEnum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "mmbr::defn::type::CodeEnum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::defn::type::ConditionEnum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "mmbr::defn::type::ConditionEnum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<
    basic::err::sys::tmpl::Category<TArg>>
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

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<
    basic::err::sys::tmpl::categ::has::mmbr::func::DefaultCode<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::DefaultCodeValue<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "mmbr::func::DefaultCodeValue<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct basic::test::type::Name<
    basic::err::sys::tmpl::categ::has::mmbr::func::
        DefaultCondition<TArg1, TArg2, TArg3, TArg4>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "asic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::DefaultConditionValue<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "mmbr::func::DefaultConditionValue<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2, typename TArg3>
struct basic::test::type::Name<
    basic::err::sys::tmpl::categ::has::mmbr::func::Equivalent<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
    basic::err::sys::tmpl::categ::has::mmbr::func::Message<TArg1,
        TArg2, TArg3>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::Name<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "mmbr::func::Name<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg1, typename TArg2>
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::ToCodeValue<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::ToConditionValue<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    mmbr::func::Value<TArg1, TArg2>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
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
struct basic::test::type::Name<basic::err::sys::tmpl::categ::has::
    st::mmbr::func::Instance<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::tmpl::categ::has::"
            "st::mmbr::func::Instance<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::code::has::Enum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::code::has::Enum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::cond::has::Enum<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::cond::has::Enum<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::make::Category<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::make::Category<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::make::Code<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::make::Code<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<typename TArg>
struct basic::test::type::Name<basic::err::sys::make::Condition<TArg>>
{
    static basic::test::CString<char> CStr()
    {
        static char _format[] = "basic::err::sys::make::Condition<%s>";
        basic::test::CString<char> tArgCStr = 
            std::move(basic::test::type::Name<TArg>::CStr());
        return basic::test::cstr::Format(sizeof(_format) - 3 + tArgCStr.Size(),
            _format, *tArgCStr);
    }
};

template<>
struct basic::test::out::Argument<basic::err::sys::Code *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Code * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", code->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Code * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", code->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Code *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::err::defn::type::sys::code::
    Value *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::defn::type::sys::code::
        Value * & code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
    static const char * Value(basic::err::defn::type::sys::code::
        Value * && code)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *code));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<basic::err::defn::
    type::sys::code::Value *>::ms_cstr;

template<>
struct basic::test::out::Argument<basic::err::sys::Condition *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::sys::Condition * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", cond->Value()));
        return *ms_cstr;
    }
    static const char * Value(basic::err::sys::Condition * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "m_value : %d", cond->Value()));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::
    Argument<basic::err::sys::Condition *>::ms_cstr;

struct Void1{};

template<>
struct basic::test::out::Argument<typename std::conditional<
    std::is_same<basic::err::defn::type::sys::cond::Value,
        basic::err::defn::type::sys::code::Value>::value, 
    Void1, basic::err::defn::type::sys::cond::Value *>::type>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(basic::err::defn::type::sys::cond::
        Value * & cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
    static const char * Value(basic::err::defn::type::sys::cond::
        Value * && cond)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", *cond));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<
    typename std::conditional<std::is_same<basic::err::defn::
        type::sys::cond::Value, basic::err::defn::type::sys::
        code::Value>::value, 
    Void1, basic::err::defn::type::sys::cond::Value *>::type>::
        ms_cstr;

struct Void2{};

template<>
struct basic::test::out::Argument<typename std::conditional<
    std::is_same<int, basic::err::defn::type::sys::code::Value>::value ||
    std::is_same<int, basic::err::defn::type::sys::code::Value>::value, 
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
    typename std::conditional<std::is_same<int, basic::err::defn::
        type::sys::code::Value>::value || std::is_same<int, basic::err::
        defn::type::sys::code::Value>::value, Void2, int *>::type>::
            ms_cstr;

template<>
struct basic::test::out::Argument<std::future_errc *>
{
    static basic::test::CString<char> ms_cstr;
    static const char * Value(std::future_errc * & val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<int>(*val)));
        return *ms_cstr;
    }
    static const char * Value(std::future_errc * && val)
    {
        ms_cstr = std::move(basic::test::cstr::Format(BUFFER_FORMAT_CSTRING, 
            "%d", static_cast<int>(*val)));
        return *ms_cstr;
    }
};

basic::test::CString<char> basic::test::out::Argument<std::future_errc *>::
    ms_cstr;
