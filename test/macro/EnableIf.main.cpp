#include "macro/EnableIf.h"
#include "Test.h"

BasicTestConstruct;

#include <type_traits>
#include <vector>
#include <typeinfo>
#include <string>

template<typename T>
struct A
{};

template<typename Tc>
struct Name
{
    static const char * Value;
};
template<typename Tc>
const char* Name<Tc>::Value = "undefined"; 

#define __DEFINE_NAME_CONDITIONAL_(...)\
template<>\
struct Name<__VA_ARGS__>\
{\
    static constexpr const char * Value = #__VA_ARGS__;\
}

__DEFINE_NAME_CONDITIONAL_(std::true_type);
__DEFINE_NAME_CONDITIONAL_(std::false_type);
__DEFINE_NAME_CONDITIONAL_(void);
__DEFINE_NAME_CONDITIONAL_(A<void>);

template<typename T, typename... Targs>
typename std::enable_if<sizeof...(Targs) != 0>::type 
    NameParameterTmpl(std::string& str, bool first = true)
{
    if (!first)
        str += ", ";
    str += Name<T>::Value;
    NameParameterTmpl<Targs...>(str, false);
}

template<typename T, typename... Targs>
typename std::enable_if<sizeof...(Targs) == 0>::type 
    NameParameterTmpl(std::string& str, bool first = true)
{
     if (!first)
        str += ", ";
    str += Name<T>::Value;
}

template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf>
static auto CallFoo(int) ->
    decltype(std::declval<typename Te<BoolTest, Ttt>::type>());
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf>
static Ttf CallFoo(...);
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf>
static auto CallFoo1(int) ->
    decltype(std::declval<typename Te<BoolTest, Ttt>::Type>());
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf>
static Ttf CallFoo1(...);
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
static auto CallFoo2(int) ->
    decltype(std::declval<typename Te<BoolTest, Ttt>::
        template type<Targs...>>());
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
static Ttf CallFoo2(...);
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
static auto CallFoo3(int) ->
    decltype(std::declval<typename Te<BoolTest, Ttt>::
        template Type<Targs...>>());
template<bool BoolTest, template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
static Ttf CallFoo3(...);

template<template<bool, typename> class Te, typename Ttt,
    typename Ttf>
void TestAliasTypeAndTarget()
{
    typedef decltype(CallFoo<true, Te, Ttt, Ttf>(0)) TrueCallFooType;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Ttt>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Te<true, Ttt>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Ttt>::Value;
    if (Assert(error_msg.c_str(), typeid(TrueCallFooType).hash_code() ==
        typeid(Ttt).hash_code()))
            Info("Pass\n");
}

template<template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
void TestAliasTypeTmplAndTarget()
{
    typedef decltype(CallFoo2<true, Te, Ttt, 
        Ttf, Targs...>(0)) TrueCallFoo2Type;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Ttt>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Te<true, Ttt>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Ttt>::Value;
    if (Assert(error_msg.c_str(), typeid(TrueCallFoo2Type).hash_code() ==
        typeid(Ttt).hash_code()))
            Info("Pass\n");
}

template<template<bool, typename> class Te, typename Ttt,
    typename Ttf>
void TestNoHasAliasType()
{
    typedef decltype(CallFoo<false, Te, Ttt, Ttf>(0)) FalseCallFooType;
    std::string info_msg = "Test not has member alias type to ";
    info_msg += Name<Te<false, Ttt>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Te<false, Ttt>>::Value;
    error_msg = " has alias type";
    if (Assert(error_msg.c_str(), typeid(FalseCallFooType).hash_code() ==
        typeid(Ttf).hash_code()))
            Info("Pass\n");
}
template<template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
void TestNoHasAliasTypeTmpl()
{
    typedef decltype(CallFoo2<false, Te, Ttt, 
        Ttf, Targs...>(0)) FalseCallFoo2Type;
    std::string info_msg = "Test not has member alias type template to ";
    info_msg += Name<Te<false, Ttt>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Te<false, Ttt>>::Value;
    error_msg = " has alias type";
    if (Assert(error_msg.c_str(), typeid(FalseCallFoo2Type).hash_code() ==
        typeid(Ttf).hash_code()))
            Info("Pass\n");
}

template<template<bool, typename> class Te, typename Ttt,
    typename Ttf>
void TestAliasType()
{
    typedef decltype(CallFoo<true, Te, Ttt, Ttf>(0)) TrueCallFooType;
    typedef decltype(CallFoo1<true, Te, Ttt, Ttf>(0)) TrueCallFoo1Type;
    std::string error_msg = Name<Te<true, Ttt>>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Te<true, Ttt>>::Value;
    error_msg += "::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::type and ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(TrueCallFooType).hash_code() ==
            typeid(TrueCallFoo1Type).hash_code()))
                Info("Pass\n");
}

template<template<bool, typename> class Te, typename Ttt,
    typename Ttf, typename... Targs>
void TestAliasTypeTmpl()
{
    typedef decltype(CallFoo2<true, Te, Ttt,
        Ttf, Targs...>(0)) TrueCallFoo2Type;
    typedef decltype(CallFoo3<true, Te,Ttt,
        Ttf, Targs...>(0)) TrueCallFoo3Type;
    std::string error_msg = Name<Te<true, Ttt>>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Te<true, Ttt>>::Value;
    error_msg += "::template Type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Te<true, Ttt>>::Value;
    info_msg += "::template Type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(TrueCallFoo2Type).hash_code() ==
            typeid(TrueCallFoo3Type).hash_code()))
                Info("Pass\n");
}

struct TestOutputType;
struct TestOutputTypeTmpl;

template<template<bool, typename> class Te, typename Ttt, typename Ttf,
    typename = TestOutputType, typename... Targs>
struct TestEnableIf : basic::test::Base
{
    void Test()
    {
        TestAliasTypeAndTarget<Te, Ttt, Ttf>();
        TestNoHasAliasType<Te, Ttt, Ttf>();
        TestAliasType<Te, Ttt, Ttf>();
    }
};

template<template<bool, typename To> class Te, typename Ttt, typename Ttf,
    typename... Targs>
struct TestEnableIf<Te, Ttt, Ttf, TestOutputTypeTmpl, Targs...> : 
    basic::test::Base
{
    void Test()
    {
        TestAliasTypeTmplAndTarget<Te, Ttt, Ttf, Targs...>();
        TestNoHasAliasTypeTmpl<Te, Ttt, Ttf, Targs...>();
        TestAliasTypeTmpl<Te, Ttt, Ttf, Targs...>();
    }
};

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
using EnableIf1_t = EnableIf1<BoolTest, void, To>;

__DEFINE_NAME_CONDITIONAL_(EnableIf1<true, void, std::true_type>);
__DEFINE_NAME_CONDITIONAL_(EnableIf1<false, void, std::true_type>);

RegisterTest(t1, new TestEnableIf<EnableIf1_t, std::true_type, std::false_type>());

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
using EnableIf2_t = EnableIf2<BoolTest, void, To>;

__DEFINE_NAME_CONDITIONAL_(EnableIf2<true>);
__DEFINE_NAME_CONDITIONAL_(EnableIf2<false>);

RegisterTest(t2, new TestEnableIf<EnableIf2_t, std::true_type, std::false_type>());

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
using EnableIf3_t = EnableIf3<BoolTest, A<void>, To>;

__DEFINE_NAME_CONDITIONAL_(EnableIf3<true, A<void>, std::true_type>);
__DEFINE_NAME_CONDITIONAL_(EnableIf3<false, A<void>, std::true_type>);

RegisterTest(t3, new TestEnableIf<EnableIf3_t, std::true_type, std::false_type>());

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
using EnableIf4_t = EnableIf4<BoolTest, void, void, To>;

__DEFINE_NAME_CONDITIONAL_(EnableIf4<true, void, void, std::true_type>);
__DEFINE_NAME_CONDITIONAL_(EnableIf4<false, void, void, std::true_type>);

RegisterTest(t4, new TestEnableIf<EnableIf4_t, std::true_type, std::false_type>());

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
using EnableIf5_t = EnableIf5<BoolTest, void, A>;

__DEFINE_NAME_CONDITIONAL_(EnableIf5<true, void, A>);
__DEFINE_NAME_CONDITIONAL_(EnableIf5<false, void, A>);

RegisterTest(t5, new TestEnableIf<EnableIf5_t, A<void>, std::false_type>());

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
using EnableIf6_t = EnableIf6<BoolTest, void, A>;

__DEFINE_NAME_CONDITIONAL_(EnableIf6<true, void, A>);
__DEFINE_NAME_CONDITIONAL_(EnableIf6<false, void, A>);

RegisterTest(t6, new TestEnableIf<EnableIf6_t, A<void>, std::false_type,
    TestOutputTypeTmpl, void>());

int main()
{
    return TestRun();
}
