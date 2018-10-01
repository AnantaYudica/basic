#include "macro/Conditional.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <typeinfo>
#include <type_traits>

struct CaseATTa {}; // case alias type and target
struct CaseAT {}; // case alias type;
struct CaseATTTa {}; // case alias type tmpl and target
struct CaseATT {}; // case alias type tmpl

template<typename TConditional, typename TAliasTarget, 
    typename... TArgs>
using VariableTestConditional = basic::test::Variable<
    TConditional, 
    TAliasTarget,
    basic::test::type::Parameter<TArgs...>>;

    
constexpr std::size_t IConditional = 0;
constexpr std::size_t IAliasTarget = 1;
constexpr std::size_t ITypeParameter = 2;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

typedef basic::test::msg::Argument<CaseATTa, 
    ArgTypeName<IConditional>,
    ArgTypeName<IAliasTarget>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<IConditional>,
    ArgTypeName<IAliasTarget>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATTTa, 
    ArgTypeName<IConditional>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IAliasTarget>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseATT, 
    ArgTypeName<IConditional>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IConditional>, 
    ArgTypeParamName<ITypeParameter>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

template<typename TCases, typename... TVars>
class TestConditional :
    public MsgBaseCaseATTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseATT,
    public basic::test::Message<BASIC_TEST, TestConditional<TCases, TVars...>>,
    public basic::test::Case<TestConditional<TCases, TVars...>, TCases>,
    public basic::test::Base<TestConditional<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestConditional<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestConditional<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestConditional<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseATTa::SetFormat;
    using MsgBaseCaseAT::SetFormat;
    using MsgBaseCaseATTTa::SetFormat;
    using MsgBaseCaseATT::SetFormat;
public:
    using MsgBaseCaseATTa::Format;
    using MsgBaseCaseAT::Format;
    using MsgBaseCaseATTTa::Format;
    using MsgBaseCaseATT::Format;
    using MsgBaseCaseATTa::Argument;
    using MsgBaseCaseAT::Argument;
    using MsgBaseCaseATTTa::Argument;
    using MsgBaseCaseATT::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestConditional(TVars&... vars) :
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
            "%s::type is not same with %s\n");

        CaseAT case_alias_type;
        SetFormat(info, case_alias_type,
            "Test compare between %s::type and %s::Type\n");
        SetFormat(debug, case_alias_type,
            "Test compare between %s::type and %s::Type\n");
        SetFormat(error, case_alias_type,
            "error %s::type is not same with %s::Type\n");

        CaseATTTa case_alias_type_tmpl_and_target;
        SetFormat(info, case_alias_type_tmpl_and_target,
            "Test compare between %s::template type<%s> and %s\n");
        SetFormat(debug, case_alias_type_tmpl_and_target,
            "Test compare between %s::template type<%s> and %s\n");
        SetFormat(error, case_alias_type_tmpl_and_target,
            "error %s::template type<%s> is not same with %s\n");

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

    template<typename TConditional, typename TAliasTarget, typename... TArgs>
    bool Result(const CaseATTa&, VariableTestConditional<TConditional, 
        TAliasTarget, TArgs...>& var)
    {
        return typeid(typename TConditional::type).hash_code() ==
            typeid(TAliasTarget).hash_code();
    }

    template<typename TConditional, typename TAliasTarget, typename... TArgs>
    bool Result(const CaseAT&, VariableTestConditional<TConditional, 
        TAliasTarget, TArgs...>& var)
    {
        return typeid(typename TConditional::type).hash_code() ==
            typeid(typename TConditional::Type).hash_code();
    }

    template<typename TConditional, typename TAliasTarget, typename... TArgs>
    bool Result(const CaseATTTa&, VariableTestConditional<TConditional, 
        TAliasTarget, TArgs...>& var)
    {
        return typeid(typename TConditional::template type<
            TArgs...>).hash_code() == typeid(TAliasTarget).hash_code();
    }

    template<typename TConditional, typename TAliasTarget, typename... TArgs>
    bool Result(const CaseATT&, VariableTestConditional<TConditional, 
        TAliasTarget, TArgs...>& var)
    {
        return typeid(typename TConditional::template type<
            TArgs...>).hash_code() == typeid(typename TConditional::
                template Type<TArgs...>).hash_code();
    }
};

using CaseAliasType = basic::test::type::
    Parameter<CaseATTa, CaseAT>;
using CaseAliasTypeTmpl = basic::test::type::
    Parameter<CaseATTTa, CaseATT>;

template<typename T>
struct A
{
    typedef std::true_type true_type;
    typedef std::false_type false_type;
};

BASIC_TEST_TYPE_NAME("A<void>", A<void>);

template<typename T>
struct B
{};

BASIC_TEST_TYPE_NAME("B<void>", B<void>);

BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);

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
    TrueConditional1;
typedef Conditional1<false, std::true_type, std::false_type>
    FalseConditional1;

BASIC_TEST_TYPE_NAME("Conditional1<true, std::true_type, std::false_type>",
    Conditional1<true, std::true_type, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional1<false, std::true_type, std::false_type>",
    Conditional1<false, std::true_type, std::false_type>);

typedef VariableTestConditional<TrueConditional1, std::true_type> T1Var1;
typedef VariableTestConditional<FalseConditional1, std::false_type> T1Var2;

T1Var1 t1_var1;
T1Var2 t1_var2;

REGISTER_TEST(t1, new TestConditional<CaseAliasType, T1Var1, 
    T1Var2>(t1_var1, t1_var2));

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

typedef Conditional2<true> TrueConditional2;
typedef Conditional2<false> FalseConditional2;

BASIC_TEST_TYPE_NAME("Conditional2<true>", Conditional2<true>);
BASIC_TEST_TYPE_NAME("Conditional2<false>", Conditional2<false>);

typedef VariableTestConditional<TrueConditional2, std::true_type> T2Var1;
typedef VariableTestConditional<FalseConditional2, std::false_type> T2Var2;

T2Var1 t2_var1;
T2Var2 t2_var2;

REGISTER_TEST(t2, new TestConditional<CaseAliasType, T2Var1, 
    T2Var2>(t2_var1, t2_var2));

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

typedef Conditional3<true, std::true_type, A<void>> TrueConditional3;
typedef Conditional3<false, std::true_type, A<void>> FalseConditional3;

BASIC_TEST_TYPE_NAME("Conditional3<true, std::true_type, A<void>>",
    Conditional3<true, std::true_type, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional3<false, std::true_type, A<void>>",
    Conditional3<false, std::true_type, A<void>>);

typedef VariableTestConditional<TrueConditional3, std::true_type> T3Var1;
typedef VariableTestConditional<FalseConditional3, void> T3Var2;

T3Var1 t3_var1;
T3Var2 t3_var2;

REGISTER_TEST(t3, new TestConditional<CaseAliasType, T3Var1, 
    T3Var2>(t3_var1, t3_var2));  


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

typedef Conditional4<true, void> TrueConditional4;
typedef Conditional4<false, void> FalseConditional4;

BASIC_TEST_TYPE_NAME("Conditional4<true, void>", Conditional4<true, void>);
BASIC_TEST_TYPE_NAME("Conditional4<false, void>", Conditional4<false, void>);

typedef VariableTestConditional<TrueConditional4, std::true_type> T4Var1;
typedef VariableTestConditional<FalseConditional4, std::false_type> T4Var2;

T4Var1 t4_var1;
T4Var2 t4_var2;

REGISTER_TEST(t4, new TestConditional<CaseAliasType, T4Var1, 
    T4Var2>(t4_var1, t4_var2));

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

typedef Conditional5<true, A, void> TrueConditional5;
typedef Conditional5<false, A, void> FalseConditional5;

BASIC_TEST_TYPE_NAME("Conditional5<true, A, void>", 
    Conditional5<true, A, void>);
BASIC_TEST_TYPE_NAME("Conditional5<false, A, void>",
    Conditional5<false, A, void>);

typedef VariableTestConditional<TrueConditional5, A<void>> T5Var1;
typedef VariableTestConditional<FalseConditional5, std::false_type> T5Var2;

T5Var1 t5_var1;
T5Var2 t5_var2;

REGISTER_TEST(t5, new TestConditional<CaseAliasType, T5Var1, 
    T5Var2>(t5_var1, t5_var2));

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

typedef Conditional6<true, std::true_type, A, void> TrueConditional6;
typedef Conditional6<false, std::true_type, A, void> FalseConditional6;

BASIC_TEST_TYPE_NAME("Conditional6<true, std::true_type, A, void>",
    Conditional6<true, std::true_type, A, void>);
BASIC_TEST_TYPE_NAME("Conditional6<false, std::true_type, A, void>",
    Conditional6<false, std::true_type, A, void>);

typedef VariableTestConditional<TrueConditional6, std::true_type> T6Var1;
typedef VariableTestConditional<FalseConditional6, A<void>> T6Var2;

T6Var1 t6_var1;
T6Var2 t6_var2;

REGISTER_TEST(t6, new TestConditional<CaseAliasType, T6Var1, 
    T6Var2>(t6_var1, t6_var2));

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

typedef Conditional7<true, A, void, B, void> TrueConditional7;
typedef Conditional7<false, A, void, B, void> FalseConditional7;

BASIC_TEST_TYPE_NAME("Conditional7<true, A, void, B, void>",
    Conditional7<true, A, void, B, void>);
BASIC_TEST_TYPE_NAME("Conditional7<false, A, void, B, void>",
    Conditional7<false, A, void, B, void>);

typedef VariableTestConditional<TrueConditional7, A<void>> T7Var1;
typedef VariableTestConditional<FalseConditional7, B<void>> T7Var2;

T7Var1 t7_var1;
T7Var2 t7_var2;

REGISTER_TEST(t7, new TestConditional<CaseAliasType, T7Var1,
    T7Var2>(t7_var1, t7_var2));

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

typedef Conditional8<true, A<void>, std::false_type> TrueConditional8;
typedef Conditional8<false, A<void>, std::false_type> FalseConditional8;

BASIC_TEST_TYPE_NAME("Conditional8<true, A<void>, std::false_type>",
    Conditional8<true, A<void>, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional8<false, A<void>, std::false_type>",
    Conditional8<false, A<void>, std::false_type>);

typedef VariableTestConditional<TrueConditional8, std::true_type> T8Var1;
typedef VariableTestConditional<FalseConditional8, std::false_type> T8Var2;

T8Var1 t8_var1;
T8Var2 t8_var2;

REGISTER_TEST(t8, new TestConditional<CaseAliasType, T8Var1, 
    T8Var2>(t8_var1, t8_var2));

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

typedef Conditional9<true, std::true_type, A<void>> TrueConditional9;
typedef Conditional9<false, std::true_type, A<void>> FalseConditional9;

BASIC_TEST_TYPE_NAME("Conditional9<true, std::true_type, A<void>>",
    Conditional9<true, std::true_type, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional9<false, std::true_type, A<void>>",
    Conditional9<false, std::true_type, A<void>>);

typedef VariableTestConditional<TrueConditional9, std::true_type> T9Var1;
typedef VariableTestConditional<FalseConditional9, std::false_type> T9Var2;

T9Var1 t9_var1;
T9Var2 t9_var2;

REGISTER_TEST(t9, new TestConditional<CaseAliasType, T9Var1,
    T9Var2>(t9_var1, t9_var2));

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

typedef Conditional10<true, A<void>, A<void>> TrueConditional10;
typedef Conditional10<false, A<void>, A<void>> FalseConditional10;

BASIC_TEST_TYPE_NAME("Conditional10<true, A<void>, A<void>>",
    Conditional10<true, A<void>, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional10<false, A<void>, A<void>>",
    Conditional10<false, A<void>, A<void>>);

typedef VariableTestConditional<TrueConditional10, std::true_type> T10Var1;
typedef VariableTestConditional<FalseConditional10, std::false_type> T10Var2;

T10Var1 t10_var1;
T10Var2 t10_var2;

REGISTER_TEST(t10, new TestConditional<CaseAliasType, T10Var1,
    T10Var2>(t10_var1, t10_var2));

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

typedef Conditional11<true, A<void>> TrueConditional11;
typedef Conditional11<false, A<void>> FalseConditional11;

BASIC_TEST_TYPE_NAME("Conditional11<true, A<void>>",
    Conditional11<true, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional11<false, A<void>>",
    Conditional11<false, A<void>>);

typedef VariableTestConditional<TrueConditional11, std::true_type> T11Var1;
typedef VariableTestConditional<FalseConditional11, std::false_type> T11Var2;

T11Var1 t11_var1;
T11Var2 t11_var2;

REGISTER_TEST(t11, new TestConditional<CaseAliasType, T11Var1,
    T11Var2>(t11_var1, t11_var2));

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

typedef Conditional12<true, std::true_type, A<void>> TrueConditional12;
typedef Conditional12<false, std::true_type, A<void>> FalseConditional12;

BASIC_TEST_TYPE_NAME("Conditional12<true, std::true_type, A<void>>",
    Conditional12<true, std::true_type, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional12<false, std::true_type, A<void>>",
    Conditional12<false, std::true_type, A<void>>);

typedef VariableTestConditional<TrueConditional12, std::true_type> T12Var1;
typedef VariableTestConditional<FalseConditional12, std::false_type> T12Var2;

T12Var1 t12_var1;
T12Var2 t12_var2;

REGISTER_TEST(t12, new TestConditional<CaseAliasType, T12Var1,
    T12Var2>(t12_var1, t12_var2));

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

typedef Conditional13<true, A<void>> TrueConditional13;
typedef Conditional13<false, A<void>> FalseConditional13;

BASIC_TEST_TYPE_NAME("Conditional13<true, A<void>>",
    Conditional13<true, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional13<false, A<void>>",
    Conditional13<false, A<void>>);

typedef VariableTestConditional<TrueConditional13, std::true_type> T13Var1;
typedef VariableTestConditional<FalseConditional13, std::false_type> T13Var2;

T13Var1 t13_var1;
T13Var2 t13_var2;

REGISTER_TEST(t13, new TestConditional<CaseAliasType, T13Var1,
    T13Var2>(t13_var1, t13_var2));

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
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, 
    T_FALSE_NAME_,, T_FALSE_DEFN_TYPE_,, ALIAS_TYPE_FALSE_,);

typedef Conditional14<true, void, A<void>, std::false_type> TrueConditional14;
typedef Conditional14<false, void, A<void>, 
    std::false_type> FalseConditional14;

BASIC_TEST_TYPE_NAME("Conditional14<true, void, A<void>, std::false_type>",
    Conditional14<true, void, A<void>, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional14<false, void, A<void>, std::false_type>",
    Conditional14<false, void, A<void>, std::false_type>);

typedef VariableTestConditional<TrueConditional14, std::true_type> T14Var1;
typedef VariableTestConditional<FalseConditional14, std::false_type> T14Var2;

T14Var1 t14_var1;
T14Var2 t14_var2;

REGISTER_TEST(t14, new TestConditional<CaseAliasType, T14Var1,
    T14Var2>(t14_var1, t14_var2));

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

typedef Conditional15<true, void, std::true_type, A<void>> TrueConditional15;
typedef Conditional15<false, void, std::true_type, A<void>> FalseConditional15;

BASIC_TEST_TYPE_NAME("Conditional15<true, void, std::true_type, A<void>>",
    Conditional15<true, void, std::true_type, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional15<false, void, std::true_type, A<void>>",
    Conditional15<false, void, std::true_type, A<void>>);

typedef VariableTestConditional<TrueConditional15, std::true_type> T15Var1;
typedef VariableTestConditional<FalseConditional15, std::false_type> T15Var2;

T15Var1 t15_var1;
T15Var2 t15_var2;

REGISTER_TEST(t15, new TestConditional<CaseAliasType, T15Var1,
    T15Var2>(t15_var1, t15_var2));

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
    T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, ALIAS_TYPE_TRUE_,, TPLF1, TALF2, 
    T_FALSE_NAME_,, T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional16<true, void, A<void>> TrueConditional16;
typedef Conditional16<false, void, A<void>> FalseConditional16;

BASIC_TEST_TYPE_NAME("Conditional16<true, void, A<void>>",
    Conditional16<true, void, A<void>>);
BASIC_TEST_TYPE_NAME("Conditional16<false, void, A<void>>",
    Conditional16<false, void, A<void>>);

typedef VariableTestConditional<TrueConditional16, std::true_type> T16Var1;
typedef VariableTestConditional<FalseConditional16, std::false_type> T16Var2;

T16Var1 t16_var1;
T16Var2 t16_var2;

REGISTER_TEST(t16, new TestConditional<CaseAliasType, T16Var1,
    T16Var2>(t16_var1, t16_var2));

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

typedef Conditional17<true, A, void> TrueConditional17;
typedef Conditional17<false, A, void> FalseConditional17;

BASIC_TEST_TYPE_NAME("Conditional17<true, A, void>",
    Conditional17<true, A, void>);
BASIC_TEST_TYPE_NAME("Conditional17<false, A, void>",
    Conditional17<false, A, void>);

typedef VariableTestConditional<TrueConditional17, std::true_type> T17Var1;
typedef VariableTestConditional<FalseConditional17, std::false_type> T17Var2;

T17Var1 t17_var1;
T17Var2 t17_var2;

REGISTER_TEST(t17, new TestConditional<CaseAliasType, T17Var1,
    T17Var2>(t17_var1, t17_var2));

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

typedef Conditional18<true, std::true_type, A, void> TrueConditional18;
typedef Conditional18<false, std::true_type, A, void> FalseConditional18;

BASIC_TEST_TYPE_NAME("Conditional18<true, std::true_type, A, void>",
    Conditional18<true, std::true_type, A, void>);
BASIC_TEST_TYPE_NAME("Conditional18<false, std::true_type, A, void>",
    Conditional18<false, std::true_type, A, void>);

typedef VariableTestConditional<TrueConditional18, std::true_type> T18Var1;
typedef VariableTestConditional<FalseConditional18, std::false_type> T18Var2;

T18Var1 t18_var1;
T18Var2 t18_var2;

REGISTER_TEST(t18, new TestConditional<CaseAliasType, T18Var1, 
    T18Var2>(t18_var1, t18_var2));

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

__DEFINE_CONDITIONAL_(Conditional19, BoolTest, Tt, Tf, TPLT5, 
    T_TRUE_NAME_TMPL_, TTNTAL1, T_TRUE_DEFN_TYPE_MMBR_, TTDTMN1, 
    ALIAS_TYPE_TRUE_,, TPLF4, TALF5, T_FALSE_NAME_TMPL_, TFNTAL1, 
    T_FALSE_DEFN_TYPE_MMBR_, TFDTMN1, ALIAS_TYPE_FALSE_,);

typedef Conditional19<true, A, void, A, void> TrueConditional19;
typedef Conditional19<false, A, void, A, void> FalseConditional19;

BASIC_TEST_TYPE_NAME("Conditional19<true, A, void, A, void>",
    Conditional19<true, A, void, A, void>);
BASIC_TEST_TYPE_NAME("Conditional19<false, A, void, A, void>",
    Conditional19<false, A, void, A, void>);

typedef VariableTestConditional<TrueConditional19, std::true_type> T19Var1;
typedef VariableTestConditional<FalseConditional19, std::false_type> T19Var2;

T19Var1 t19_var1;
T19Var2 t19_var2;

REGISTER_TEST(t19, new TestConditional<CaseAliasType, T19Var1,
    T19Var2>(t19_var1, t19_var2));

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

typedef Conditional20<true, std::true_type, std::false_type> TrueConditional20;
typedef Conditional20<false,  std::true_type, std::false_type> 
    FalseConditional20;

BASIC_TEST_TYPE_NAME("Conditional20<true, std::true_type, std::false_type>",
    Conditional20<true, std::true_type, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional20<false,  std::true_type, std::false_type>",
    Conditional20<false,  std::true_type, std::false_type>);

typedef VariableTestConditional<TrueConditional20, std::true_type,
    void> T20Var1;

T20Var1 t20_var1;

REGISTER_TEST(t20, new TestConditional<CaseAliasTypeTmpl, T20Var1>(t20_var1));

typedef VariableTestConditional<FalseConditional20, std::false_type> T21Var1;

T21Var1 t21_var1;

REGISTER_TEST(t21, new TestConditional<CaseAliasType, T21Var1>(t21_var1));

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

typedef Conditional21<true, std::true_type, std::false_type> TrueConditional21;
typedef Conditional21<false,  std::true_type, std::false_type> 
    FalseConditional21;

BASIC_TEST_TYPE_NAME("Conditional21<true, std::true_type, std::false_type>",
    Conditional21<true, std::true_type, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional21<false,  std::true_type, std::false_type>",
    Conditional21<false,  std::true_type, std::false_type>);

typedef VariableTestConditional<TrueConditional21, std::true_type,
    void> T22Var1;

T22Var1 t22_var1;

REGISTER_TEST(t22, new TestConditional<CaseAliasType, T22Var1>(t22_var1));

typedef VariableTestConditional<FalseConditional21, std::false_type,
    void> T23Var1;

T23Var1 t23_var1;

REGISTER_TEST(t23, new TestConditional<CaseAliasTypeTmpl, T23Var1>(t23_var1));

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

typedef Conditional22<true, std::true_type, std::false_type> TrueConditional22;
typedef Conditional22<false,  std::true_type, std::false_type> 
    FalseConditional22;

BASIC_TEST_TYPE_NAME("Conditional22<true, std::true_type, std::false_type>",
    Conditional22<true, std::true_type, std::false_type>);
BASIC_TEST_TYPE_NAME("Conditional22<false,  std::true_type, std::false_type>",
    Conditional22<false,  std::true_type, std::false_type>);

typedef VariableTestConditional<TrueConditional22, std::true_type,
    void> T24Var1;
typedef VariableTestConditional<FalseConditional22, std::false_type,
    void> T24Var2;

T24Var1 t24_var1;
T24Var2 t24_var2;

REGISTER_TEST(t24, new TestConditional<CaseAliasTypeTmpl, T24Var1,
    T24Var2>(t24_var1, t24_var2));

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

typedef Conditional23<true> TrueConditional23;
typedef Conditional23<false> FalseConditional23;

BASIC_TEST_TYPE_NAME("Conditional23<true>", Conditional23<true>);
BASIC_TEST_TYPE_NAME("Conditional23<false>", Conditional23<false>);

typedef VariableTestConditional<TrueConditional23, std::true_type,
    void> T25Var1;

T25Var1 t25_var1;

REGISTER_TEST(t25, new TestConditional<CaseAliasTypeTmpl, T25Var1>(t25_var1));

typedef VariableTestConditional<FalseConditional23, std::false_type> T26Var1;

T26Var1 t26_var1;

REGISTER_TEST(t26, new TestConditional<CaseAliasType, T26Var1>(t26_var1));

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

typedef Conditional24<true> TrueConditional24;
typedef Conditional24<false> FalseConditional24;

BASIC_TEST_TYPE_NAME("Conditional24<true>", Conditional24<true>);
BASIC_TEST_TYPE_NAME("Conditional24<false>", Conditional24<false>);

typedef VariableTestConditional<TrueConditional24, std::true_type> T27Var1;
    
T27Var1 t27_var1;

REGISTER_TEST(t27, new TestConditional<CaseAliasType, T27Var1>(t27_var1));

typedef VariableTestConditional<FalseConditional24, std::false_type,
    void> T28Var1;

T28Var1 t28_var1;

REGISTER_TEST(t28, new TestConditional<CaseAliasTypeTmpl, T28Var1>(t28_var1));

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

typedef Conditional25<true> TrueConditional25;
typedef Conditional25<false> FalseConditional25;

BASIC_TEST_TYPE_NAME("Conditional25<true>", Conditional25<true>);
BASIC_TEST_TYPE_NAME("Conditional25<false>", Conditional25<false>);

typedef VariableTestConditional<TrueConditional25, std::true_type,
    void> T29Var1;
typedef VariableTestConditional<FalseConditional25, std::false_type,
    void> T29Var2;

T29Var1 t29_var1;
T29Var2 t29_var2;

REGISTER_TEST(t29, new TestConditional<CaseAliasTypeTmpl, T29Var1,
    T29Var2>(t29_var1, t29_var2));

int main()
{
    return RUN_TEST();
}
