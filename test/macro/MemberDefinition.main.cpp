#include "macro/MemberDefinition.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>

struct CaseATTa {}; // case alias type and target
struct CaseATTTa{}; // case alias type tmpl and target
struct CaseAT{}; // case alias type
struct CaseATT{}; // case alias type tmpl

template<typename TMmbrDefn, typename TAliasType, typename... TArgs>
using VariableTestMmbrDefn = basic::test::Variable<
    TMmbrDefn, 
    TAliasType,
    basic::test::type::Parameter<TArgs...>>;

constexpr std::size_t IMmbrDefn = 0;
constexpr std::size_t IAliasType = 1;
constexpr std::size_t ITypeParameter = 2;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

typedef basic::test::msg::Argument<CaseATTa, 
    ArgTypeName<IMmbrDefn>, 
    ArgTypeName<IAliasType>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, 
    ArgTypeName<IMmbrDefn>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IAliasType>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<IMmbrDefn>,
    ArgTypeName<IMmbrDefn>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, 
    ArgTypeName<IMmbrDefn>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IMmbrDefn>, 
    ArgTypeParamName<ITypeParameter>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

template<typename TCases, typename... TVar>
class TestMmbrDefn :
    public MsgBaseCaseATTa,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public basic::test::Message<BASIC_TEST, TestMmbrDefn<TCases, TVar...>>,
    public basic::test::Case<TestMmbrDefn<TCases, TVar...>, TCases>,
    public basic::test::Base<TestMmbrDefn<TCases, TVar...>, TVar...>
{
public:
    typedef basic::test::Base<TestMmbrDefn<TCases, TVar...>, TVar...> BaseType;
    typedef basic::test::Message<BASIC_TEST, TestMmbrDefn<TCases, 
        TVar...>> BaseMessageType;
    typedef basic::test::Case<TestMmbrDefn<TCases, TVar...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseATTa::SetFormat;
    using MsgBaseCaseATTTa::SetFormat;
    using MsgBaseCaseAT::SetFormat;
    using MsgBaseCaseATT::SetFormat;
public:
    using MsgBaseCaseATTa::Format;
    using MsgBaseCaseATTTa::Format;
    using MsgBaseCaseAT::Format;
    using MsgBaseCaseATT::Format;
    using MsgBaseCaseATTa::Argument;
    using MsgBaseCaseATTTa::Argument;
    using MsgBaseCaseAT::Argument;
    using MsgBaseCaseATT::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestMmbrDefn(TVar&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;

        CaseATTa case_alias_type_and_target;
        SetFormat(info, case_alias_type_and_target, 
            "test compare between %s::type and %s\n");
        SetFormat(debug, case_alias_type_and_target,
            "test compare between %s::type and %s\n");
        SetFormat(error, case_alias_type_and_target,
            "error %s::type is not same with %s\n");

        CaseATTTa case_alias_type_tmpl_and_target;
        SetFormat(info, case_alias_type_tmpl_and_target, 
            "test compare between %s::template type<%s> and %s\n");
        SetFormat(debug, case_alias_type_tmpl_and_target,
            "test compare between %s::template type<%s> and %s\n");
        SetFormat(error, case_alias_type_tmpl_and_target,
            "error %s::template type<%s> is not same with %s\n");

        CaseAT case_alias_type;
        SetFormat(info, case_alias_type, 
            "test compare between %s::type and %s::Type\n");
        SetFormat(debug, case_alias_type,
            "test compare between %s::type and %s::Type\n");
        SetFormat(error, case_alias_type,
            "error %s::type is not same with %s::Type\n");

        CaseATT case_alias_tmpl_type;
        SetFormat(info, case_alias_tmpl_type, 
            "test compare between %s::template type<%s> "
            "and %s::template type<%s>\n");
        SetFormat(debug, case_alias_tmpl_type,
            "test compare between %s::template type<%s> "
            "and %s::template type<%s>\n");
        SetFormat(error, case_alias_tmpl_type,
            "error %s::template type<%s> is not same "
            "with %s::template type<%s>\n");
    }
public:
    template<typename TMmbrDefn, typename TAliasType, typename... TArgs>
    bool Result(const CaseATTa&, VariableTestMmbrDefn<TMmbrDefn, TAliasType, 
        TArgs...>& var)
    {
        return typeid(typename TMmbrDefn::type).hash_code() ==
            typeid(TAliasType).hash_code();
    }

    template<typename TMmbrDefn, typename TAliasType, typename... TArgs>
    bool Result(const CaseATTTa&, VariableTestMmbrDefn<TMmbrDefn, TAliasType,  
        TArgs...>& var)
    {
        return typeid(typename TMmbrDefn::template type<
            TArgs...>).hash_code() == typeid(TAliasType).hash_code();
    }

    template<typename TMmbrDefn, typename TAliasType, typename... TArgs>
    bool Result(const CaseAT&, VariableTestMmbrDefn<TMmbrDefn, TAliasType, 
        TArgs...>& var)
    {
        return typeid(typename TMmbrDefn::type).hash_code() ==
            typeid(typename TMmbrDefn::Type).hash_code();
    }

    template<typename TMmbrDefn, typename TAliasType, typename... TArgs>
    bool Result(const CaseATT&, VariableTestMmbrDefn<TMmbrDefn, TAliasType, 
        TArgs...>& var)
    {
        return typeid(typename TMmbrDefn::template type<
            TArgs...>).hash_code() == typeid(typename TMmbrDefn::template Type<
            TArgs...>).hash_code();
    }
};

using CasesAliasType = basic::test::type::Parameter<CaseATTa, CaseAT>;
using CasesAliasTypeTmp = basic::test::type::Parameter<CaseATTTa, CaseATT>;

struct A
{
    typedef void Type1;
};

template<typename>
struct B
{
    typedef void Type2;
};

template<>
struct B<std::false_type>
{};

struct C
{
    template<typename T>
    using Type3 = B<T>;
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("B<void", B<void>);

/**
 *  template<typename T>
 *  struct MemberDefn1
 *  {
 *      using type = typename T::Type1;
 *      using Type = typename T::Type1;
 *  }
 * */

__DEFINE_MMBR_DEFN_(MmbrDefn1, T,, T_NAME_,, ALIAS_TYPE_,, Type1);

template<typename T>
using TMmbrDefn1 = MmbrDefn1<T>;

BASIC_TEST_TYPE_NAME("MmbrDefn1<A>", MmbrDefn1<A>);

typedef VariableTestMmbrDefn<TMmbrDefn1<A>, typename A::Type1> T1Var1;

T1Var1 t1_var1;

REGISTER_TEST(t1, new TestMmbrDefn<CasesAliasType, T1Var1>(t1_var1));

/**
 *  template<typename T, typename T1>
 *  struct MemberDefn2
 *  {
 *      using type = typename T::Type1;
 *      using Type = typename T::Type1;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_MMBR_DEFN_(MmbrDefn2, T, TPL1, T_NAME_,, ALIAS_TYPE_,, Type1);

template<typename T>
using TMmbrDefn2 = MmbrDefn2<T, void>;

BASIC_TEST_TYPE_NAME("MmbrDefn2<A, void>", MmbrDefn2<A, void>);

typedef VariableTestMmbrDefn<TMmbrDefn2<A>, typename A::Type1> T2Var1;

T2Var1 t2_var1;

REGISTER_TEST(t2, new TestMmbrDefn<CasesAliasType, T2Var1>(t2_var1));

/**
 *  template<template<typename> class T, typename T1>
 *  struct MemberDefn3
 *  {
 *      using type = typename T<T1>::Type2;
 *      using Type = typename T<T1>::Type2;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_MMBR_DEFN_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_MMBR_DEFN_(MmbrDefn3, T, TPL2, T_NAME_TMPL_, 
    TNTAL1, ALIAS_TYPE_,, Type2);

template<typename T>
using TMmbrDefn3 = MmbrDefn3<B, T>;

BASIC_TEST_TYPE_NAME("MmbrDefn3<B, void>", MmbrDefn3<B, void>);

typedef VariableTestMmbrDefn<TMmbrDefn3<void>, typename B<void>::Type2> T3Var1;

T3Var1 t3_var1;

REGISTER_TEST(t3, new TestMmbrDefn<CasesAliasType, T3Var1>(t3_var1));

/**
 *  template<typename T>
 *  struct MemberDefn3
 *  {
 *      template<typename T1>
 *      using type = typename T::template Type3<T1>;
 *      template<typename T1>
 *      using Type = typename T::template Type1<T1>;
 *  }
 * */

#define __DEFINE_MMBR_DEFN_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1

__DEFINE_MMBR_DEFN_(MmbrDefn4, T,, T_NAME_,, ALIAS_TYPE_TMPL_, ATTPL1, 
    template Type3<T1>);

template<typename T>
using TMmbrDefn4 = MmbrDefn4<T>;

BASIC_TEST_TYPE_NAME("MmbrDefn4<C>", MmbrDefn4<C>);

typedef VariableTestMmbrDefn<TMmbrDefn4<C>, 
    typename C::template Type3<void>, void> T4Var1;

T4Var1 t4_var1;

REGISTER_TEST(t4, new TestMmbrDefn<CasesAliasTypeTmp, T4Var1>(t4_var1));


int main()
{
    return RUN_TEST();
}
