#include "macro/Conditional.h"
#include "Test.h"

BasicTestConstruct;

#include <typeinfo>
#include <type_traits>
#include <string>
#include <vector>

/**
 * struct Helper
 * */
template<typename T>
struct A
{
    typedef std::true_type true_type;
    typedef std::false_type false_type;
};

template<typename T>
struct B
{};

/**
 * struct NameConditional
 * */
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

struct TrueFalseAliasType;
struct TrueAliasTypeTmpl;
struct FalseAliasTypeTmpl;
struct TrueFalseAliasTypeTmpl;

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

template<typename Tc, typename Ttc>
void TestAliasTypeAndTarget()
{
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tc>::Value;
    info_msg += "::type and ";
    info_msg += Name<Ttc>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Tc>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Ttc>::Value;
    if(Assert(error_msg.c_str(), 
        typeid(typename Tc::type).hash_code() ==
            typeid(Ttc).hash_code()))
                Info("Pass\n");
}

template<typename Tc>
void TestAliasType()
{
    std::string error_msg = Name<Tc>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tc>::Value;
    error_msg += "::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tc>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tc>::Value;
    info_msg += "::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tc::type).hash_code() ==
            typeid(typename Tc::Type).hash_code()))
                Info("Pass\n");
}

template<typename Tc, typename Ttc, typename... Targs>
void TestAliasTypeTmplAndTarget()
{
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tc>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Ttc>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Tc>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same with ";
    error_msg += Name<Ttc>::Value;
    if(Assert(error_msg.c_str(), 
        typeid(typename Tc::template type<Targs...>).hash_code() ==
            typeid(Ttc).hash_code()))
                Info("Pass\n");
}

template<typename Tc, typename... Targs>
void TestAliasTypeTmpl()
{
    std::string error_msg = Name<Tc>::Value;
    error_msg += "::template type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += "> is not same error_msg ";
    error_msg += Name<Tc>::Value;
    error_msg += "::template Type<";
    NameParameterTmpl<Targs...>(error_msg);
    error_msg += ">";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tc>::Value;
    info_msg += "::template type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> and ";
    info_msg += Name<Tc>::Value;
    info_msg += "::template Type<";
    NameParameterTmpl<Targs...>(info_msg);
    info_msg += "> : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tc::template type<Targs...>).hash_code() ==
            typeid(typename Tc::template Type<Targs...>).hash_code()))
                Info("Pass\n");
}

/**
 * Definition Parameter name 
 * Tct = True Conditional Type
 * Tcf = False Conditional Type
 * Ttct = True Conditional Target Type
 * Ttcf = False Conditional Target Type
 * Ta = Alias Type
 * Targs = Argumnents Type
 * */

template<typename Tct, typename Tcf, typename Ttct, typename Ttcf,
    typename Ta = TrueFalseAliasType, typename... Targs>
struct TestConditional : basic::test::Base
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tct, Ttct>();
        TestAliasType<Tct>();
        TestAliasTypeAndTarget<Tcf, Ttcf>();
        TestAliasType<Tcf>();
    }
};

template<typename Tct, typename Tcf, typename Ttct, typename Ttcf,
    typename... Targs>
struct TestConditional<Tct, Tcf, Ttct, Ttcf, 
    TrueAliasTypeTmpl, Targs...> : basic::test::Base
{
void Test() 
    {
        TestAliasTypeTmplAndTarget<Tct, Ttct, Targs...>();
        TestAliasTypeTmpl<Tct, Targs...>();
        TestAliasTypeAndTarget<Tcf, Ttcf>();
        TestAliasType<Tcf>();
    }
};

template<typename Tct, typename Tcf, typename Ttct, typename Ttcf,
    typename... Targs>
struct TestConditional<Tct, Tcf, Ttct, Ttcf, 
    FalseAliasTypeTmpl, Targs...> : basic::test::Base
{
void Test() 
    {
        TestAliasTypeAndTarget<Tct, Ttct>();
        TestAliasType<Tct>();
        TestAliasTypeTmplAndTarget<Tcf, Ttcf, Targs...>();
        TestAliasTypeTmpl<Tcf, Targs...>();
    }
};

template<typename Tct, typename Tcf, typename Ttct, typename Ttcf,
    typename... Targs>
struct TestConditional<Tct, Tcf, Ttct, Ttcf, 
    TrueFalseAliasTypeTmpl, Targs...> : basic::test::Base
{
void Test() 
    {
        TestAliasTypeTmplAndTarget<Tct, Ttct, Targs...>();
        TestAliasTypeTmpl<Tct, Targs...>();
        TestAliasTypeTmplAndTarget<Tcf, Ttcf, Targs...>();
        TestAliasTypeTmpl<Tcf, Targs...>();
    }
};


/**
 * template<bool BoolTest, typename Tt, typename Tf>
 * struct Conditional1
 * {
 *      using type = Tt;
 *      using Type = Tt;
 * };
 * template<typename Tt, typename Tf>
 * struct Conditional1<false, Tt, Tf>
 * {
 *      using type = Tf:
 *      using Type = Tf;
 * };
 * */

__DEFINE_CONDITIONAL_(Conditional1, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional1<true, std::true_type, std::false_type>
    TrueConditional1_t;
typedef Conditional1<false, std::true_type, std::false_type>
    FalseConditional1_t;

__DEFINE_NAME_CONDITIONAL_(Conditional1<true, std::true_type, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional1<false, std::true_type, std::false_type>);

RegisterTest(t1, new TestConditional<TrueConditional1_t, 
    FalseConditional1_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt = std::true_type, 
 *      typename Tf = std::false_type>
 *  struct Conditional2
 *  {
 *      using type = Tt;
 *      using Type = Tt;
 *  };
 *  template<template Tt, typename Tf>
 *  struct Conditional2<false, Tt, Tf>
 *  {
 *      using type = Tf;
 *      using Type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT1(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__ = std::true_type,\
    typename __T_FALSE_NAME__ = std::false_type 

__DEFINE_CONDITIONAL_(Conditional2, BoolTest, Tt, Tf, TPLT1, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional2<true> TrueConditional2_t;
typedef Conditional2<false> FalseConditiona2_t;

__DEFINE_NAME_CONDITIONAL_(Conditional2<true>);
__DEFINE_NAME_CONDITIONAL_(Conditional2<false>);

RegisterTest(t2, new TestConditional<TrueConditional2_t, 
    FalseConditiona2_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional3
 *  {
 *      using type = Tt;
 *      using Type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional3<Tt, A<Tf>>
 *  {
 *      using type = Tf;
 *      using Type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_ARG_LIST_FALSE_TALF1(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
__T_TRUE_NAME__, A<__T_FALSE_NAME__>

__DEFINE_CONDITIONAL_(Conditional3, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,, TALF1, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional3<true, std::true_type, A<void>> TrueConditional3_t;
typedef Conditional3<false, std::true_type, A<void>> FalseConditional3_t;

__DEFINE_NAME_CONDITIONAL_(Conditional3<true, std::true_type, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional3<false, std::true_type, B<void>>);

RegisterTest(t3, new TestConditional<TrueConditional3_t,
    FalseConditional3_t, std::true_type, void>());  


/**
 *  template<bool BoolTest, typename T1, typename, Tt = std::true_type,
 *      typename Tf = std::false_type>
 *  struct Conditional3
 *  {
 *      using type = Tt;
 *      using Type = Tt;
 *  };
 *  template<typename T1, typename Tt, typename Tf>
 *  struct Conditional3<false, T1, Tt, Tf>
 *  {
 *      using type = Tf;
 *      using Type = Tf;
 *  };
 * */
#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT2(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename T1, typename __T_TRUE_NAME__ = std::true_type,\
    typename __T_FALSE_NAME__ = std::false_type 

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_FALSE_TPLF1(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename T1, typename __T_TRUE_NAME__, typename __T_FALSE_NAME__ 

#define __DEFINE_CONDITIONAL_TMPL_ARG_LIST_FALSE_TALF2(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
T1, __T_TRUE_NAME__, __T_FALSE_NAME__

__DEFINE_CONDITIONAL_(Conditional4, BoolTest, Tt, Tf, TPLT2, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional4<true, void> TrueConditional4_t;
typedef Conditional4<false, void> FalseConditional4_t;

__DEFINE_NAME_CONDITIONAL_(Conditional4<true, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional4<false, void>);

RegisterTest(t4, new TestConditional<TrueConditional4_t,
    FalseConditional4_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, template<typename> class Tt, typename T1,
 *      typename Tf = std::false_type>
 *  struct Conditional5
 *  {
 *      using type = Tt<T1>;
 *      using Type = Tt<T1>;
 *  };
 *  template<template<typename> class Tt, typename T1,
 *      typename Tf>
 *  struct Conditional5<false, Tt, T1, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */
#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT3(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
template<typename> class __T_TRUE_NAME__, typename T1,\
    typename __T_FALSE_NAME__ = std::false_type 

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_FALSE_TPLF2(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
template<typename> class __T_TRUE_NAME__, typename T1,\
    typename __T_FALSE_NAME__ 

#define __DEFINE_CONDITIONAL_TMPL_ARG_LIST_FALSE_TALF3(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
__T_TRUE_NAME__ , T1, __T_FALSE_NAME__

#define __DEFINE_CONDITIONAL_T_TRUE_NAME_TMPL_ARG_LIST_TTNTAL1()\
T1

__DEFINE_CONDITIONAL_(Conditional5, BoolTest, Tt, Tf, TPLT3, 
    T_TRUE_NAME_TMPL_, TTNTAL1, T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, 
    TPLF2, TALF3, T_FALSE_NAME_,, T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional5<true, A, void> TrueConditional5_t;
typedef Conditional5<false, A, void> FalseConditional5_t;

__DEFINE_NAME_CONDITIONAL_(Conditional5<true, A, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional5<false, A, void>);

RegisterTest(t5, new TestConditional<TrueConditional5_t,
    FalseConditional5_t, A<void>, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, template<typename> class Tf, 
 *      typename T1>
 *  struct Conditional6
 *  {
 *      using type = Tt;
 *      using Type = Tt;
 *  };
 *  template<typename Tt, template<typename> class Tf, typename T1>
 *  struct Conditional6<BoolTest, Tf, Tf, T1>
 *  {
 *      using type = Tf<T1>;
 *      uisng Type = Tf<T1>;
 *  }
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT4(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__, template<typename> class __T_FALSE_NAME__,\
    typename T1

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_FALSE_TPLF3(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__, template<typename> class __T_FALSE_NAME__,\
    typename T1

#define __DEFINE_CONDITIONAL_TMPL_ARG_LIST_FALSE_TALF4(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
__T_TRUE_NAME__ , __T_FALSE_NAME__, T1

#define __DEFINE_CONDITIONAL_T_FALSE_NAME_TMPL_ARG_LIST_TFNTAL1()\
T1

__DEFINE_CONDITIONAL_(Conditional6, BoolTest, Tt, Tf, TPLT4, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, TPLF3, TALF4, T_FALSE_NAME_TMPL_, 
    TFNTAL1, T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional6<true, std::true_type, A, void> TrueConditional6_t;
typedef Conditional6<false, std::true_type, A, void> FalseConditional6_t;

__DEFINE_NAME_CONDITIONAL_(Conditional6<true, std::true_type, A, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional6<false, std::true_type, A, void>);

RegisterTest(t6, new TestConditional<TrueConditional6_t,
    FalseConditional6_t, std::true_type, A<void>>());

/**
 *  template<bool BoolTest, template<typename> class Tt, typename T1,
 *      template<typename> class Tf, typename T2>
 *  struct Conditional7
 *  {
 *      using type = Tt<T1>;
 *      using Type = Tt<T1>;
 *  };
 *  template<template<typename> class Tt, typename T1,
 *      template<typename> class Tf, typename T2>
 *  struct Conditional7<false, Tt, T1, Tf, T2>
 *  {
 *      using type = Tf<T2>;
 *      uisng Type = Tf<T2>;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT5(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
template<typename> class __T_TRUE_NAME__, typename T1,\
    template<typename> class  __T_FALSE_NAME__, typename T2

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_FALSE_TPLF4(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
template<typename> class __T_TRUE_NAME__, typename T1,\
    template<typename> class  __T_FALSE_NAME__, typename T2

#define __DEFINE_CONDITIONAL_TMPL_ARG_LIST_FALSE_TALF5(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
__T_TRUE_NAME__ , T1, __T_FALSE_NAME__, T2

__DEFINE_CONDITIONAL_(Conditional7, BoolTest, Tt, Tf, TPLT5, T_TRUE_NAME_TMPL_,
    TTNTAL1, T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, TPLF4, TALF5, 
    T_FALSE_NAME_TMPL_, TFNTAL1, T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional7<true, A, void, B, void> TrueConditional7_t;
typedef Conditional7<false, A, void, B, void> FalseConditional7_t;

__DEFINE_NAME_CONDITIONAL_(Conditional7<true, A, void, B, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional7<false, A, void, B, void>);

RegisterTest(t7, new TestConditional<TrueConditional7_t,
    FalseConditional7_t, A<void>, B<void>>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional7
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional7<false, Tt, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  }
 * */

#define __DEFINE_CONDITIONAL_T_TRUE_DEFN_TYPE_MMBR_NAME_TTDTMN1()\
true_type

__DEFINE_CONDITIONAL_(Conditional8, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional8<true, A<void>, std::false_type> TrueConditional8_t;
typedef Conditional8<false, A<void>, std::false_type> FalseConditional8_t;

__DEFINE_NAME_CONDITIONAL_(Conditional8<true, A<void>, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional8<false, A<void>, std::false_type>);

RegisterTest(t8, new TestConditional<TrueConditional8_t,
    FalseConditional8_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional9
 *  {
 *      using type = Tt;
 *      using Type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional9<false, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  }
 * */

#define __DEFINE_CONDITIONAL_T_FALSE_DEFN_TYPE_MMBR_NAME_TFDTMN1()\
false_type

__DEFINE_CONDITIONAL_(Conditional9, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional9<true, std::true_type, A<void>> TrueConditional9_t;
typedef Conditional9<false, std::true_type, A<void>> FalseConditional9_t;

__DEFINE_NAME_CONDITIONAL_(Conditional9<true, std::true_type, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional9<false, std::true_type, A<void>>);

RegisterTest(t9, new TestConditional<TrueConditional9_t,
    FalseConditional9_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional10
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional10<false, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  }
 * */

__DEFINE_CONDITIONAL_(Conditional10, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional10<true, A<void>, A<void>> TrueConditional10_t;
typedef Conditional10<false, A<void>, A<void>> FalseConditional10_t;

__DEFINE_NAME_CONDITIONAL_(Conditional10<true, A<void>, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional10<false, A<void>, A<void>>);

RegisterTest(t10, new TestConditional<TrueConditional10_t,
    FalseConditional10_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf = std::false_type>
 *  struct Conditional11
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional11<false, Tt, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT6(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__, typename __T_FALSE_NAME__ = std::false_type

__DEFINE_CONDITIONAL_(Conditional11, BoolTest, Tt, Tf, TPLT6, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional11<true, A<void>> TrueConditional11_t;
typedef Conditional11<false, A<void>> FalseConditional11_t;

__DEFINE_NAME_CONDITIONAL_(Conditional11<true, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional11<false, A<void>>);

RegisterTest(t11, new TestConditional<TrueConditional11_t,
    FalseConditional11_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional12
 *  {
 *      using type = Tt;
 *      uisng Type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional12<false, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT7(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__, typename __T_FALSE_NAME__

__DEFINE_CONDITIONAL_(Conditional12, BoolTest, Tt, Tf, TPLT7, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional12<true, std::true_type, A<void>> TrueConditional12_t;
typedef Conditional12<false, std::true_type, A<void>> FalseConditional12_t;

__DEFINE_NAME_CONDITIONAL_(Conditional12<true, std::true_type, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional12<false, std::true_type, A<void>>);

RegisterTest(t12, new TestConditional<TrueConditional12_t,
    FalseConditional12_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf= Tt>
 *  struct Conditional13
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional13<false, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT8(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename __T_TRUE_NAME__, typename __T_FALSE_NAME__ = __T_TRUE_NAME__

__DEFINE_CONDITIONAL_(Conditional13, BoolTest, Tt, Tf, TPLT8, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional13<true, A<void>> TrueConditional13_t;
typedef Conditional13<false, A<void>> FalseConditional13_t;

__DEFINE_NAME_CONDITIONAL_(Conditional13<true, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional13<false, A<void>>);

RegisterTest(t13, new TestConditional<TrueConditional13_t,
    FalseConditional13_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename T1, typename Tt, typename Tf>
 *  struct Conditional14
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename T1, typename Tt, typename Tf>
 *  struct Conditional14<false, T1, Tt, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT9(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename T1, typename __T_TRUE_NAME__, typename __T_FALSE_NAME__

__DEFINE_CONDITIONAL_(Conditional14, BoolTest, Tt, Tf, TPLT9, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional14<true, void, A<void>, std::false_type> TrueConditional14_t;
typedef Conditional14<false, void, A<void>, std::false_type> FalseConditional14_t;

__DEFINE_NAME_CONDITIONAL_(Conditional14<true, void, A<void>, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional14<false, void, A<void>, std::false_type>);

RegisterTest(t14, new TestConditional<TrueConditional14_t,
    FalseConditional14_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename T1, typename Tt, typename Tf>
 *  struct Conditional15
 *  {
 *      using type = Tt;
 *      uisng Type = Tt;
 *  };
 *  template<typename T1, typename Tt, typename Tf>
 *  struct Condtional14<false, T1, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional15, BoolTest, Tt, Tf, TPLT9, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional15<true, void, std::true_type, A<void>> TrueConditional15_t;
typedef Conditional15<false, void, std::true_type, A<void>> FalseConditional15_t;

__DEFINE_NAME_CONDITIONAL_(Conditional15<true, void, std::true_type, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional15<false, void, std::true_type, A<void>>);

RegisterTest(t15, new TestConditional<TrueConditional15_t,
    FalseConditional15_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename T1, typename Tt, typename Tf = Tt>
 *  struct Conditional16
 *  {
 *      using type = typename Tt::true_type;
 *      using Type = typename Tt::true_type;
 *  };
 *  template<typename T1, typename Tt, typename Tf>
 *  struct Conditional16<T1, Tt, Tf>
 *  {
 *      using type = typename Tf::false_type;
 *      uisng Type = typename Tf::false_type;
 *  };
 * */

#define __DEFINE_CONDITIONAL_TMPL_PARAM_LIST_TRUE_TPLT10(\
    __T_TRUE_NAME__,\
    __T_FALSE_NAME__)\
typename T1, typename __T_TRUE_NAME__,\
    typename __T_FALSE_NAME__ = __T_TRUE_NAME__

__DEFINE_CONDITIONAL_(Conditional16, BoolTest, Tt, Tf, TPLT10, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional16<true, void, A<void>> TrueConditional16_t;
typedef Conditional16<false, void, A<void>> FalseConditional16_t;

__DEFINE_NAME_CONDITIONAL_(Conditional16<true, void, A<void>>);
__DEFINE_NAME_CONDITIONAL_(Conditional16<false, void, A<void>>);

RegisterTest(t16, new TestConditional<TrueConditional16_t,
    FalseConditional16_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, template<typename> class Tt, typename T1, 
 *      typename Tf = std::false_type>
 *  struct Conditional17
 *  {
 *      using type = typename Tt<T1>::true_type;
 *      using Type = typename Tt<T1>::true_type;
 *  };
 *  template<typename T1, template<typename> class Tt, typename T1,
 *      typename Tf>
 *  struct Conditional17<false, Tt, T1, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional17, BoolTest, Tt, Tf, TPLT3, T_TRUE_NAME_TMPL_, 
    TTNTAL1, T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF2, TALF3, 
    T_FALSE_NAME_,, T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional17<true, A, void> TrueConditional17_t;
typedef Conditional17<false, A, void> FalseConditional17_t;

__DEFINE_NAME_CONDITIONAL_(Conditional17<true, A, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional17<false, A, void>);

RegisterTest(t17, new TestConditional<TrueConditional17_t,
    FalseConditional17_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, template<typename> class Tf,
 *      typename T1>
 *  struct Conditional18
 *  {
 *      using type = Tt;
 *      uisng Type = Tt;
 *  };
 *  template<typename Tt, template<typename> class Tf, typename T1>
 *  struct Conditional18<false, Tt, Tf, T1>
 *  {
 *      using type = typename Tf<T1>::false_type;
 *      uisng Type = typename Tf<T1>::false_type;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional18, BoolTest, Tt, Tf, TPLT4, T_TRUE_NAME_,, 
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,, TPLF3, TALF4, T_FALSE_NAME_TMPL_, 
    TFNTAL1, T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional18<true, std::true_type, A, void> TrueConditional18_t;
typedef Conditional18<false, std::true_type, A, void> FalseConditional18_t;

__DEFINE_NAME_CONDITIONAL_(Conditional18<true, std::true_type, A, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional18<false, std::true_type, A, void>);

RegisterTest(t18, new TestConditional<TrueConditional18_t, 
    FalseConditional18_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, template<typename> class Tt, typename T1,
 *      template<typename> class Tf, typename T2>
 *  struct Conditional19
 *  {
 *      using type = typename Tt<T1>::true_type;
 *      using Type = typename Tt<T1>::true_type;
 *  };
 *  template<template<typename> class Tt, typename T1,
 *      template<typename> class Tf, typename T2>
 *  struct Conditional19<false, Tt, T1, Tf, T2>
 *  {
 *      using type = typename Tf<T2>::false_type;
 *      uisng Type = typename Tf<T2>::false_type;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional19, BoolTest, Tt, Tf, TPLT5, T_TRUE_NAME_TMPL_, 
    TTNTAL1, T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF4, TALF5, 
    T_FALSE_NAME_TMPL_, TFNTAL1, T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional19<true, A, void, A, void> TrueConditional19_t;
typedef Conditional19<false, A, void, A, void> FalseConditional19_t;

__DEFINE_NAME_CONDITIONAL_(Conditional19<true, A, void, A, void>);
__DEFINE_NAME_CONDITIONAL_(Conditional19<false, A, void, A, void>);

RegisterTest(t19, new TestConditional<TrueConditional19_t,
    FalseConditional19_t, std::true_type, std::false_type>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional20
 *  {
 *      template<typename T1>
 *      using type = Tt,
 *      template<typename T1>
 *      using type = Tt;
 *  };
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional17<false, Tt, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_ALIAS_TYPE_TMPL_PARAM_LIST_TRUE_ATTPLT1()\
typename T1

__DEFINE_CONDITIONAL_(Conditional20, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_TRUE_, ATTPLT1,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional20<true, std::true_type, std::false_type> TrueConditional20_t;
typedef Conditional20<false,  std::true_type, std::false_type> FalseConditional20_t;

__DEFINE_NAME_CONDITIONAL_(Conditional20<true, std::true_type, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional20<false,  std::true_type, std::false_type>);

RegisterTest(t20, new TestConditional<TrueConditional20_t,
    FalseConditional20_t, std::true_type, std::false_type, TrueAliasTypeTmpl, void>());

/**
 *  template<bool BooTest, typename Tt, typename Tf>
 *  struct Conditional21
 *  {
 *      using type = Tt;
 *      uisng Type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Condtional20
 *  {
 *      template<typename T1>
 *      using type = Tf,
 *      template<typename T1>
 *      using type = Tf;
 *  };
 * */

#define __DEFINE_CONDITIONAL_ALIAS_TYPE_TMPL_PARAM_LIST_FALSE_ATTPLF1()\
typename T1

__DEFINE_CONDITIONAL_(Conditional21, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_FALSE_, ATTPLF1);

typedef Conditional21<true, std::true_type, std::false_type> TrueConditional21_t;
typedef Conditional21<false,  std::true_type, std::false_type> FalseConditional21_t;

__DEFINE_NAME_CONDITIONAL_(Conditional21<true, std::true_type, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional21<false,  std::true_type, std::false_type>);

RegisterTest(t21, new TestConditional<TrueConditional21_t,
    FalseConditional21_t, std::true_type, std::false_type, FalseAliasTypeTmpl, void>());

/**
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional22
 *  {
 *      template<typename T1>
 *      using type = Tt,
 *      template<typename T1>
 *      using type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional22<false, Tt, Tf>
 *  {
 *      template<typename T1>
 *      using type = Tf,
 *      template<typename T1>
 *      using type = Tf;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional22, BoolTest, Tt, Tf,, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_TRUE_, ATTPLT1,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_FALSE_, ATTPLF1);

typedef Conditional22<true, std::true_type, std::false_type> TrueConditional22_t;
typedef Conditional22<false,  std::true_type, std::false_type> FalseConditional22_t;

__DEFINE_NAME_CONDITIONAL_(Conditional22<true, std::true_type, std::false_type>);
__DEFINE_NAME_CONDITIONAL_(Conditional22<false,  std::true_type, std::false_type>);

RegisterTest(t22, new TestConditional<TrueConditional22_t,
    FalseConditional22_t, std::true_type, std::false_type,
    TrueFalseAliasTypeTmpl, void>());

/**
 *  template<bool BoolTest, typename Tt = std::true_type, 
 *      typename Tf = std::false_type>
 *  struct Conditional23
 *  {
 *      template<typename T1>
 *      using type = Tt,
 *      template<typename T1>
 *      using type = Tt;
 *  };
 *  template<bool BoolTest, typename Tt, typename Tf>
 *  struct Conditional23<false, Tt, Tf>
 *  {
 *      using type = Tf;
 *      uisng Type = Tf;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional23, BoolTest, Tt, Tf, TPLT1, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_TRUE_, ATTPLT1,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional23<true> TrueConditional23_t;
typedef Conditional23<false> FalseConditional23_t;

__DEFINE_NAME_CONDITIONAL_(Conditional23<true>);
__DEFINE_NAME_CONDITIONAL_(Conditional23<false>);

RegisterTest(t23, new TestConditional<TrueConditional23_t,
    FalseConditional23_t, std::true_type, std::false_type,
    TrueAliasTypeTmpl, void>());

/**
 *  template<Bool BoolTest, typename Tt = std::true_type,
 *      typename Tf = std::false_type>
 *  struct Conditional24
 *  {
 *      using type = Tt;
 *      uisng Type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional24<false, Tt, Tf>
 *  {
 *      template<typename T1>
 *      using type = Tf,
 *      template<typename T1>
 *      using type = Tf;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional24, BoolTest, Tt, Tf, TPLT1, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TRUE_,,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_FALSE_, ATTPLF1);

typedef Conditional24<true> TrueConditional24_t;
typedef Conditional24<false> FalseConditional24_t;

__DEFINE_NAME_CONDITIONAL_(Conditional24<true>);
__DEFINE_NAME_CONDITIONAL_(Conditional24<false>);

RegisterTest(t24, new TestConditional<TrueConditional24_t,
    FalseConditional24_t, std::true_type, std::false_type,
    FalseAliasTypeTmpl, void>());

/**
 *  template<bool BoolTest, typename Tt = std::true_type, 
 *      typename Tf = std::false_type>
 *  struct Conditional25
 *  {
 *      template<typename T1>
 *      using type = Tt,
 *      template<typename T1>
 *      using type = Tt;
 *  };
 *  template<typename Tt, typename Tf>
 *  struct Conditional25<false, Tt, Tf>
 *  {
 *      template<typename T1>
 *      using type = Tf,
 *      template<typename T1>
 *      using type = Tf;
 *  };
 * */

__DEFINE_CONDITIONAL_(Conditional25, BoolTest, Tt, Tf, TPLT1, T_TRUE_NAME_,,
    T_TRUE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_TRUE_, ATTPLT1,,, T_FALSE_NAME_,,
    T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_TMPL_FALSE_, ATTPLF1);

typedef Conditional25<true> TrueConditional25_t;
typedef Conditional25<false> FalseConditional25_t;

__DEFINE_NAME_CONDITIONAL_(Conditional25<true>);
__DEFINE_NAME_CONDITIONAL_(Conditional25<false>);

RegisterTest(t25, new TestConditional<TrueConditional25_t,
    FalseConditional25_t, std::true_type, std::false_type,
    TrueFalseAliasTypeTmpl, void>());

int main()
{
    return TestRun();
}
