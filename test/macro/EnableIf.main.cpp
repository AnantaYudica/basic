#include "macro/EnableIf.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"

#include <type_traits>
#include <vector>
#include <typeinfo>
#include <string>

struct CaseATTa {}; // case alias type and target
struct CaseATTTa {}; // case alias type tmpl and target
struct CaseNAT {}; // case no alias type
struct CaseNATT {}; // case no alias type tmpl
struct CaseAT {}; // case alias type
struct CaseATT {}; // case alias type tmpl

template<typename TEITrue, typename TTrue, 
    typename TEIFalse, typename TFalse, typename... Targs>
using VariableTestEnableIf = basic::test::Variable<TEITrue, TTrue,
    TEIFalse, TFalse, basic::test::type::Parameter<Targs...>>;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgVarValue = basic::test::msg::arg::var::Value<I>;

typedef basic::test::msg::Argument<CaseATTa, ArgTypeName<0>,
    ArgTypeName<1>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, ArgTypeName<0>,
    ArgTypeName<1>, ArgTypeParamName<4>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseNAT, ArgTypeName<2>> ArgCaseNAT;

typedef basic::test::msg::Base<CaseNAT, char, ArgCaseNAT, 
    ArgCaseNAT, ArgCaseNAT> MsgBaseCaseNAT;

typedef basic::test::msg::Argument<CaseNATT, ArgTypeName<2>> ArgCaseNATT;

typedef basic::test::msg::Base<CaseNATT, char, ArgCaseNATT, 
    ArgCaseNATT, ArgCaseNATT> MsgBaseCaseNATT;

typedef basic::test::msg::Argument<CaseAT, ArgTypeName<0>,
    ArgTypeName<0>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, ArgTypeName<0>,
    ArgTypeParamName<4>, ArgTypeName<0>, ArgTypeParamName<4>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

template<template<bool, typename> class TTEI, typename TFalse, 
    bool BoolTest, typename TTrue>
static auto GetTypeAlias1(const TTEI<BoolTest, TTrue>&) ->
    decltype(std::declval<typename TTEI<BoolTest, TTrue>::type>());
template<template<bool, typename> class TTEI, typename TFalse>
static TFalse GetTypeAlias1(...);

template<template<bool, typename> class TTEI, typename TFalse, 
    bool BoolTest, typename TTrue>
static auto GetTypeAlias2(const TTEI<BoolTest, TTrue>&) ->
    decltype(std::declval<typename TTEI<BoolTest, TTrue>::Type>());
template<template<bool, typename> class TTEI, typename TFalse>
static TFalse GetTypeAlias2(...);

template<template<bool, typename> class TTEI, typename TFalse, 
    typename... Targs, bool BoolTest, typename TTrue>
static auto GetTypeAliasTmpl1(const TTEI<BoolTest, TTrue>&) ->
    decltype(std::declval<typename TTEI<BoolTest, TTrue>::
        template type<Targs...>>());
template<template<bool, typename> class TTEI, typename TFalse, 
    typename... Targs>
static TFalse GetTypeAliasTmpl1(...);

template<template<bool, typename> class TTEI, typename TFalse, 
    typename... Targs, bool BoolTest, typename TTrue>
static auto GetTypeAliasTmpl2(const TTEI<BoolTest, TTrue>&) ->
    decltype(std::declval<typename TTEI<BoolTest, TTrue>::
        template Type<Targs...>>());
template<template<bool, typename> class TTEI, typename TFalse, 
    typename... Targs>
static TFalse GetTypeAliasTmpl2(...);


template<template <bool, typename> class TTEI, typename TCases, 
    typename... TVars>
class TestEnableIf :
    public MsgBaseCaseATTa, 
    public MsgBaseCaseATTTa,
    public MsgBaseCaseNAT,
    public MsgBaseCaseNATT,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public basic::test::Message<BASIC_TEST, TestEnableIf<TTEI, TCases, 
        TVars...>>,
    public basic::test::Case<TestEnableIf<TTEI, TCases, TVars...>, TCases>,
    public basic::test::Base<TestEnableIf<TTEI, TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestEnableIf<TTEI, TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestEnableIf<TTEI, TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestEnableIf<TTEI, TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseATTa::SetFormat;
    using MsgBaseCaseATTTa::SetFormat;
    using MsgBaseCaseNAT::SetFormat;
    using MsgBaseCaseNATT::SetFormat;
    using MsgBaseCaseAT::SetFormat;
    using MsgBaseCaseATT::SetFormat;
public:
    using MsgBaseCaseATTa::Format;
    using MsgBaseCaseATTTa::Format;
    using MsgBaseCaseNAT::Format;
    using MsgBaseCaseNATT::Format;
    using MsgBaseCaseAT::Format;
    using MsgBaseCaseATT::Format;
    using MsgBaseCaseATTa::Argument;
    using MsgBaseCaseATTTa::Argument;
    using MsgBaseCaseNAT::Argument;
    using MsgBaseCaseNATT::Argument;
    using MsgBaseCaseAT::Argument;
    using MsgBaseCaseATT::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestEnableIf(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        CaseATTa case_alias_type_and_target;
        SetFormat(info, case_alias_type_and_target,
            "Test compare between %s::type and %s\n");
        SetFormat(debug, case_alias_type_and_target,
            "Test compare between %s::type and %s\n");
        SetFormat(error, case_alias_type_and_target,
            "error %s::type is not same with %s\n");

        CaseATTTa case_alias_type_tmpl_and_target;
        SetFormat(info, case_alias_type_tmpl_and_target,
            "Test compare between %s::template type<%s> and %s\n");
        SetFormat(debug, case_alias_type_tmpl_and_target,
            "Test compare between %s::template type<%s> and %s\n");
        SetFormat(error, case_alias_type_tmpl_and_target,
            "error %s::template type<%s> is not same with %s\n");
        
        CaseNAT case_no_alias_type;
        SetFormat(info, case_no_alias_type,
            "test there is no type alias member of %s\n");
        SetFormat(debug, case_no_alias_type,
            "test there is no type alias member of %s\n");
        SetFormat(error, case_no_alias_type,
            "error %s has type alias member\n");

        CaseNATT case_no_alias_type_tmpl;
        SetFormat(info, case_no_alias_type_tmpl,
            "test there is no type template alias member of %s\n");
        SetFormat(debug, case_no_alias_type_tmpl,
            "test there is no type template alias member of %s\n");
        SetFormat(error, case_no_alias_type_tmpl,
            "error %s has type template alias member\n");

        CaseAT case_alias_type;
        SetFormat(info, case_alias_type,
            "Test compare between %s::type and %s::Type\n");
        SetFormat(debug, case_alias_type,
            "Test compare between %s::type and %s::Type\n");
        SetFormat(error, case_alias_type,
            "error %s::type is not same with %s::Type\n");

        CaseATT case_alias_type_tmpl;
        SetFormat(info, case_alias_type_tmpl,
            "Test compare between %s::template type<%s> and "
            "%s::template Type<%s>\n");
        SetFormat(debug, case_alias_type_tmpl,
            "Test compare between %s::template type<%s> and "
            "%s::template Type<%s>\n");
        SetFormat(error, case_alias_type_tmpl,
            "error %s::template type<%s> is not same with "
            "%s::template Type<%s>\n");
    }

    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseATTa&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAlias1<TTEI, TFalse>(std::declval<
            TEITrue>()))).hash_code() == typeid(TTrue).hash_code();
    }

    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseATTTa&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAliasTmpl1<TTEI, TFalse, 
            Targs...>(std::declval<TEITrue>()))).hash_code() == 
            typeid(TTrue).hash_code();
    }
    
    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseNAT&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAlias1<TTEI, TFalse>(std::declval<
            TEIFalse>()))).hash_code() == typeid(TFalse).hash_code();
    }
    
    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseNATT&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAliasTmpl1<TTEI, TFalse, 
            Targs...>(std::declval<TEIFalse>()))).hash_code() == 
            typeid(TFalse).hash_code();
    }
    
    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseAT&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAlias1<TTEI, TFalse>(std::declval<
            TEITrue>()))).hash_code() == typeid(decltype(GetTypeAlias2<TTEI, 
            TFalse>(std::declval<TEITrue>()))).hash_code();
    }
    
    template<typename TEITrue, typename TTrue, 
        typename TEIFalse, typename TFalse, typename... Targs>
    bool Result(const CaseATT&, VariableTestEnableIf<TEITrue, TTrue,
        TEIFalse, TFalse, Targs...>& var)
    {
        return typeid(decltype(GetTypeAliasTmpl1<TTEI, TFalse, 
            Targs...>(std::declval<TEITrue>()))).hash_code() == 
            typeid(decltype(GetTypeAliasTmpl2<TTEI, TFalse, 
            Targs...>(std::declval<TEITrue>()))).hash_code();
    }
};


using CaseAliasType = basic::test::type::
    Parameter<CaseATTa, CaseNAT, CaseAT>;
using CaseAliasTypeTmpl = basic::test::type::
    Parameter<CaseATTTa, CaseNATT, CaseATT>;


template<typename T>
struct A
{};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("A<void>", A<void>);


/**
 *  template<bool BoolTest, typename T, typename To = void, bool = true>
 *  struct EnableIf1
 *  {
 *      using type = To;
 *      using Type = To;
 *  };
 *  template<typename T, typename To>
 *  struct EnableIf1<true, T, To, false>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf1<false, T, To, true>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf1<false, T, To, false>
 *  {};
 * */

__DEFINE_ENABLE_IF_(EnableIf1, BoolTest, T, To,,,, T_OUT_NAME_,,
    ALIAS_TYPE_,, true);

template<bool BoolTest, typename To>
using BoolToEnableIf1 = EnableIf1<BoolTest, void, To>;

BASIC_TEST_TYPE_NAME("EnableIf1<true, void, std::true_type>",
    EnableIf1<true, void, std::true_type>);
BASIC_TEST_TYPE_NAME("EnableIf1<false, void, std::true_type>",
    EnableIf1<false, void, std::true_type>);

typedef VariableTestEnableIf<BoolToEnableIf1<true, std::true_type>, 
    std::true_type, BoolToEnableIf1<false, std::true_type>,
    std::false_type> T1Var1;

T1Var1 t1_var1;

REGISTER_TEST(t1, new TestEnableIf<BoolToEnableIf1, CaseAliasType,
    T1Var1>(t1_var1));

/**
 *  template<bool BoolTest, typename T = void, typename To = std::true_type, 
 *      bool = true>
 *  struct EnableIf2
 *  {
 *      using type = To;
 *      using Type = To;
 *  };
 *  template<typename T, typename To>
 *  struct EnableIf2<true, T, To, false>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf2<false, T, To, true>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf2<false, T, To, false
 *  {};
 * */

#define __DEFINE_ENABLE_IF_TMPL_PARAM_LIST_PRIMARY_TPLP1(\
    __T_NAME__,\
    __T_OUT_NAME__)\
typename __T_NAME__ = void, typename __T_OUT_NAME__ = std::true_type

__DEFINE_ENABLE_IF_(EnableIf2, BoolTest, T, To, TPLP1,,, T_OUT_NAME_,,
    ALIAS_TYPE_,, true);

template<bool BoolTest, typename To>
using BoolToEnableIf2 = EnableIf2<BoolTest, void, To>;

BASIC_TEST_TYPE_NAME("EnableIf2<true>", EnableIf2<true>);
BASIC_TEST_TYPE_NAME("EnableIf2<false>", EnableIf2<false>);

typedef VariableTestEnableIf<BoolToEnableIf2<true, std::true_type>, 
    std::true_type, BoolToEnableIf2<false, std::true_type>,
    std::false_type> T2Var1;

T2Var1 t2_var1;

REGISTER_TEST(t2, new TestEnableIf<BoolToEnableIf2, CaseAliasType,
    T2Var1>(t2_var1));

/**
 *  template<bool BoolTest, typename T, typename To = void, bool = true>
 *  struct EnableIf3
 *  {
 *      using type = To;
 *      using Type = To;
 *  };
 *  template<typename T, typename To>
 *  struct EnableIf3<true, A<T>, To, false>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf3<false, A<T>, To, true>
 *  {};
 *  template<typename T, typename To>
 *  struct EnableIf3<false, A<T>, To, false>
 *  {};
 * */

#define __DEFINE_ENABLE_IF_TMPL_ARG_LIST_TAL1(\
    __T_NAME__,\
    __T_OUT_NAME__)\
A<__T_NAME__>, __T_OUT_NAME__

__DEFINE_ENABLE_IF_(EnableIf3, BoolTest, T, To,,, TAL1, T_OUT_NAME_,,
    ALIAS_TYPE_,, true);

template<bool BoolTest, typename To>
using BoolToEnableIf3 = EnableIf3<BoolTest, A<void>, To>;

BASIC_TEST_TYPE_NAME("EnableIf3<true, A<void>, std::true_type>",
    EnableIf3<true, A<void>, std::true_type>);
BASIC_TEST_TYPE_NAME("EnableIf3<false, A<void>, std::true_type>",
    EnableIf3<false, A<void>, std::true_type>);

typedef VariableTestEnableIf<BoolToEnableIf3<true, std::true_type>, 
    std::true_type, BoolToEnableIf3<false, std::true_type>,
    std::false_type> T3Var1;

T3Var1 t3_var1;

REGISTER_TEST(t3, new TestEnableIf<BoolToEnableIf3, CaseAliasType,
    T3Var1>(t3_var1));

/**
 *  template<bool BoolTest, typename T1, typename T2, typename To, bool = true>
 *  struct EnableIf4
 *  {
 *      using type = To;
 *      using Type = To;
 *  };
 *  template<typename T1, typename T2, typename To>
 *  struct EnableIf4<true, T1, T2, To, false>
 *  {};
 *  template<typename T1, typename T2, typename To>
 *  struct EnableIf4<false, T1, T2, To, true>
 *  {};
 *  template<typename T1, typename T2, typename To>
 *  struct EnableIf4<false, T1, T2, To, false>
 *  {};
 * */

#define __DEFINE_ENABLE_IF_TMPL_PARAM_LIST_PRIMARY_TPLP2(\
    __T_NAME__,\
    __T_OUT_NAME__)\
typename __T_NAME__, typename T2, typename __T_OUT_NAME__ = void

#define __DEFINE_ENABLE_IF_TMPL_PARAM_LIST_SPECIALIZED_TPLS1(\
    __T_NAME__,\
    __T_OUT_NAME__)\
typename __T_NAME__, typename T2, typename __T_OUT_NAME__

#define __DEFINE_ENABLE_IF_TMPL_ARG_LIST_TAL2(\
    __T_NAME__,\
    __T_OUT_NAME__)\
__T_NAME__, T2, __T_OUT_NAME__

__DEFINE_ENABLE_IF_(EnableIf4, BoolTest, T1, To, TPLP2, TPLS1,
    TAL2, T_OUT_NAME_,, ALIAS_TYPE_,, true);

template<bool BoolTest, typename To>
using BoolToEnableIf4 = EnableIf4<BoolTest, void, void, To>;

BASIC_TEST_TYPE_NAME("EnableIf4<true, void, void, std::true_type>",
    EnableIf4<true, void, void, std::true_type>);
BASIC_TEST_TYPE_NAME("EnableIf4<false, void, void, std::true_type>",
    EnableIf4<false, void, void, std::true_type>);

typedef VariableTestEnableIf<BoolToEnableIf4<true, std::true_type>, 
    std::true_type, BoolToEnableIf4<false, std::true_type>,
    std::false_type> T4Var1;

T4Var1 t4_var1;

REGISTER_TEST(t4, new TestEnableIf<BoolToEnableIf4, CaseAliasType,
    T4Var1>(t4_var1));

/**
 *  template<bool BoolTest, typename T,  
 *      template<typename> class To, bool = true>
 *  struct EnableIf5
 *  {
 *      using type = To<T>;
 *      using Type = To<T>;
 *  };
 *  template<typename T, template<typename> class To>
 *  struct EnableIf5<true, T, To, false>
 *  {};
 *  template<typename T, typename<typename> class To>
 *  struct EnableIf5<false, T, To, true>
 *  {};
 *  template<typename T, typename<typename> class To>
 *  struct EnableIf5<false, T, To, false>
 *  {};
 * */

#define __DEFINE_ENABLE_IF_TMPL_PARAM_LIST_PRIMARY_TPLP3(\
    __T_NAME__,\
    __T_OUT_NAME__)\
typename __T_NAME__, template<typename> class __T_OUT_NAME__

#define __DEFINE_ENABLE_IF_TMPL_PARAM_LIST_SPECIALIZED_TPLS2(\
    __T_NAME__,\
    __T_OUT_NAME__)\
typename __T_NAME__, template<typename> class __T_OUT_NAME__

#define __DEFINE_ENABLE_IF_T_OUT_NAME_TMPL_ARG_LIST_TONTAL1()\
T

__DEFINE_ENABLE_IF_(EnableIf5, BoolTest, T, To, TPLP3, TPLS2,,
    T_OUT_NAME_TMPL_, TONTAL1, ALIAS_TYPE_,, true);

template<bool BoolTest, typename To>
using BoolToEnableIf5 = EnableIf5<BoolTest, To, A>;

BASIC_TEST_TYPE_NAME("EnableIf5<true, void, A>",
    EnableIf5<true, void, A>);
BASIC_TEST_TYPE_NAME("EnableIf5<false, void, A>",
    EnableIf5<false, void, A>);

typedef VariableTestEnableIf<BoolToEnableIf5<true, void>, 
    A<void>, BoolToEnableIf5<false, void>, 
    std::false_type> T5Var1;

T5Var1 t5_var1;

REGISTER_TEST(t5, new TestEnableIf<BoolToEnableIf5, CaseAliasType,
    T5Var1>(t5_var1));

/**
 *  template<bool BoolTest, typename T, template<typename> To,
 *      bool = true>
 *  struct EnableIf6
 *  {
 *      template<typename T1>
 *      using type = To<T1>;
 *      template<typename T1>
 *      using Type = To<T1>;
 *  };
 *  template<typename T, template<typename> To>
 *  struct EnableIf6<true, T, To, false>
 *  {};
 *  template<typename T, template<typename> To>
 *  struct EnableIf6<false, T, To, true>
 *  {};
 *  template<typename T, template<typename> To>
 *  struct EnableIf6<false, T, To, false>
 *  {};
 * */

#define __DEFINE_ENABLE_IF_T_OUT_NAME_TMPL_ARG_LIST_TONTAL2()\
T1

#define __DEFINE_ENABLE_IF_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1

__DEFINE_ENABLE_IF_(EnableIf6, BoolTest, T, To, TPLP3, TPLS2,,
    T_OUT_NAME_TMPL_, TONTAL2, ALIAS_TYPE_TMPL_, ATTPL1, true);

template<bool BoolTest, typename To>
using BoolToEnableIf6 = EnableIf6<BoolTest, To, A>;

BASIC_TEST_TYPE_NAME("EnableIf6<true, void, A>",
    EnableIf6<true, void, A>);
BASIC_TEST_TYPE_NAME("EnableIf6<false, void, A>",
    EnableIf6<false, void, A>);

typedef VariableTestEnableIf<BoolToEnableIf6<true, void>, 
    A<void>, BoolToEnableIf6<false, void>, 
    std::false_type, void> T6Var1;

T6Var1 t6_var1;

REGISTER_TEST(t6, new TestEnableIf<BoolToEnableIf6, CaseAliasTypeTmpl,
    T6Var1>(t6_var1));

int main()
{
    return RUN_TEST();
}
