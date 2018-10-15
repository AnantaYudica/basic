#include "macro/StaticMemberFunction.h"
#define USING_BASIC_TEST_MEMORY
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
struct CasePTa{}; // case pointer and target
struct CasePTTa{}; // case pointer tmpl and target
struct CaseP{}; //case pointer
struct CasePT{}; // case pointer tmpl

template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
    typename... TArgs>
using VariableTestStaticMmbrFunc = basic::test::Variable<
    TStaticMmbrFunc, 
    TAliasType,
    basic::test::Value<TPointer>,
    basic::test::type::Parameter<TArgs...>>;

constexpr std::size_t IStaticMmbrFunc = 0;
constexpr std::size_t IAliasType = 1;
constexpr std::size_t IValPointer = 2;
constexpr std::size_t ITypeParameter = 3;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

typedef basic::test::msg::Argument<CaseATTa, 
    ArgTypeName<IStaticMmbrFunc>, 
    ArgTypeName<IAliasType>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IAliasType>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeName<IStaticMmbrFunc>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IStaticMmbrFunc>, 
    ArgTypeParamName<ITypeParameter>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

typedef basic::test::msg::Argument<CasePTa, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgValue<IValPointer>> ArgCasePTa;

typedef basic::test::msg::Base<CasePTa, char, ArgCasePTa, 
    ArgCasePTa, ArgCasePTa> MsgBaseCasePTa;

typedef basic::test::msg::Argument<CasePTTa, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeParamName<ITypeParameter>, 
    ArgValue<IValPointer>> ArgCasePTTa;

typedef basic::test::msg::Base<CasePTTa, char, ArgCasePTTa, 
    ArgCasePTTa, ArgCasePTTa> MsgBaseCasePTTa;

typedef basic::test::msg::Argument<CaseP, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeName<IStaticMmbrFunc>> ArgCaseP;

typedef basic::test::msg::Base<CaseP, char, ArgCaseP, 
    ArgCaseP, ArgCaseP> MsgBaseCaseP;

typedef basic::test::msg::Argument<CasePT, 
    ArgTypeName<IStaticMmbrFunc>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IStaticMmbrFunc>, 
    ArgTypeParamName<ITypeParameter>> ArgCasePT;

typedef basic::test::msg::Base<CasePT, char, ArgCasePT, 
    ArgCasePT, ArgCasePT> MsgBaseCasePT;

template<typename Tptr>
void* ToVoidPtr(Tptr t)
{
    Tptr * tp = &t;
    void ** vp = reinterpret_cast<void**>(tp);
    return *vp;
} 

template<typename TCases, typename... TVars>
class TestStaticMmbrFunc :
    public MsgBaseCaseATTa,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public MsgBaseCasePTa,
    public MsgBaseCasePTTa,
    public MsgBaseCaseP,
    public MsgBaseCasePT,
    public basic::test::Message<BASIC_TEST, TestStaticMmbrFunc<TCases, TVars...>>,
    public basic::test::Case<TestStaticMmbrFunc<TCases, TVars...>, TCases>,
    public basic::test::Base<TestStaticMmbrFunc<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestStaticMmbrFunc<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestStaticMmbrFunc<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestStaticMmbrFunc<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseATTa::SetFormat;
    using MsgBaseCaseATTTa::SetFormat;
    using MsgBaseCaseAT::SetFormat;
    using MsgBaseCaseATT::SetFormat;
    using MsgBaseCasePTa::SetFormat;
    using MsgBaseCasePTTa::SetFormat;
    using MsgBaseCaseP::SetFormat;
    using MsgBaseCasePT::SetFormat;
public:
    using MsgBaseCaseATTa::Format;
    using MsgBaseCaseATTTa::Format;
    using MsgBaseCaseAT::Format;
    using MsgBaseCaseATT::Format;
    using MsgBaseCasePTa::Format;
    using MsgBaseCasePTTa::Format;
    using MsgBaseCaseP::Format;
    using MsgBaseCasePT::Format;
    using MsgBaseCaseATTa::Argument;
    using MsgBaseCaseATTTa::Argument;
    using MsgBaseCaseAT::Argument;
    using MsgBaseCaseATT::Argument;
    using MsgBaseCasePTa::Argument;
    using MsgBaseCasePTTa::Argument;
    using MsgBaseCaseP::Argument;
    using MsgBaseCasePT::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestStaticMmbrFunc(TVars&... vars) :
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

        CasePTa case_pointer_and_target;
        SetFormat(info, case_pointer_and_target, 
            "test compare between %s::pointer() and %p\n");
        SetFormat(debug, case_pointer_and_target,
            "test compare between %s::pointer() and %p\n");
        SetFormat(error, case_pointer_and_target,
            "error %s::pointer() is not same with %p\n");

        CasePTTa case_pointer_tmpl_and_target;
        SetFormat(info, case_pointer_tmpl_and_target, 
            "test compare between %s::template pointer<%s>() and %p\n");
        SetFormat(debug, case_pointer_tmpl_and_target,
            "test compare between %s::template pointer<%s>() and %p\n");
        SetFormat(error, case_pointer_tmpl_and_target,
            "error %s::template pointer<%s>() is not same with %p\n");

        CaseP case_pointer;
        SetFormat(info, case_pointer, 
            "test compare between %s::pointer() and %s::Pointer()\n");
        SetFormat(debug, case_pointer,
            "test compare between %s::pointer() and %s::Pointer()\n");
        SetFormat(error, case_pointer,
            "error %s::pointer() is not same with %s::Pointer()\n");

        CasePT case_pointer_tmpl;
        SetFormat(info, case_pointer_tmpl, 
            "test compare between %s::template pointer<%s>() "
            "and %s::template Pointer<%s>()\n");
        SetFormat(debug, case_pointer_tmpl,
            "test compare between %s::template pointer<%s>() "
            "and %s::template Pointer<%s>()\n");
        SetFormat(error, case_pointer_tmpl,
            "error %s::template pointer<%s>() is "
            "not same with %s::template Pointer<%s>()\n");

    }
public:
    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATTa&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrFunc::type).hash_code() ==
            typeid(TAliasType).hash_code();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATTTa&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrFunc::template type<
            TArgs...>).hash_code() == typeid(TAliasType).hash_code();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseAT&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrFunc::type).hash_code() ==
            typeid(typename TStaticMmbrFunc::Type).hash_code();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATT&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrFunc::template type<
            TArgs...>).hash_code() == typeid(typename TStaticMmbrFunc::
            template Type<TArgs...>).hash_code();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePTa&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrFunc::pointer()) == 
            basic::test::var::At<IValPointer>(var).Get().Get();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePTTa&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrFunc::template pointer<TArgs...>()) == 
            basic::test::var::At<IValPointer>(var).Get().Get();
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseP&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrFunc::pointer()) == 
            ToVoidPtr(TStaticMmbrFunc::Pointer());
    }

    template<typename TStaticMmbrFunc, typename TAliasType, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePT&, VariableTestStaticMmbrFunc<TStaticMmbrFunc, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrFunc::template pointer<TArgs...>()) == 
            ToVoidPtr(TStaticMmbrFunc::template Pointer<TArgs...>());
    }
};

using CasesAliasTypeAndPointer = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTa, CaseP>;
using CasesAliasTypeAndPointerTmpl = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTTa, CasePT>;
using CasesAliasTypeTmplAndPointer = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTa, CaseP>;
using CasesAliasTypeTmplAndPointerTmpl = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTTa, CasePT>;;

struct A
{
    static void Foo1() {}
};

template<typename T>
struct B
{
    static void Foo2() {}
};

struct C
{
    template<typename T>
    static B<T> Foo3() { return {}; }
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("B<void>", B<void>);
BASIC_TEST_TYPE_NAME("void(*)()", void(*)());
BASIC_TEST_TYPE_NAME("B<void> (*)()", B<void> (*)());


/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc1
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc1, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using TStaticMmbrFunc1 = StaticMmbrFunc1<T, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc1<A, void>", StaticMmbrFunc1<A, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc1<A>, void (*)(), 
    void*> T1Var1;

T1Var1 t1_var1(ToVoidPtr<void (*)()>(&A::Foo1));

REGISTER_TEST(t1, new TestStaticMmbrFunc<CasesAliasTypeAndPointer, 
    T1Var1>(t1_var1));

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc2
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc2, T, Tr, Targs, TPL1, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using TStaticMmbrFunc2 = StaticMmbrFunc2<T, void, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc2<A, void, void>", 
    StaticMmbrFunc2<A, void, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc2<A>, void (*)(), 
    void*> T2Var1;

T2Var1 t2_var1(ToVoidPtr<void (*)()>(&A::Foo1));

REGISTER_TEST(t2, new TestStaticMmbrFunc<CasesAliasTypeAndPointer,
    T2Var1>(t2_var1));

/**
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct StaticMmbrFunc3
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T<T1>::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T<T1>::Foo2;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename>class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc3, T, Tr, Targs, TPL2, 
    T_NAME_TMPL_, TNTAL1, T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using TStaticMmbrFunc3 = StaticMmbrFunc3<B, T, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc3<B, void, void>",
    StaticMmbrFunc3<B, void, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc3<void>, void (*)(), 
    void*> T3Var1;

T3Var1 t3_var1(ToVoidPtr<void (*)()>(&B<void>::Foo2));

REGISTER_TEST(t3, new TestStaticMmbrFunc<CasesAliasTypeAndPointer,
    T3Var1>(t3_var1));

/**
 * 	template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 * 	struct StaticMmbrFunc4
 * 	{
 * 	    using Type = Tr<T1> (*)(Targs...);
 * 	    using type = Tr<T1> (*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo3;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_T_RET_NAME_TMPL_ARG_LIST_TRNTAL1()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc4, T, Tr, Targs, TPL3, T_NAME_,,
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo3);

template<typename T>
using TStaticMmbrFunc4 = StaticMmbrFunc4<T, void, B>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc4<C, void, B>", 
    StaticMmbrFunc4<C, void, B>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc4<C>, B<void> (*)(), 
    void*> T4Var1;

T4Var1 t4_var1(ToVoidPtr<B<void> (*)()>(&C::Foo3));

REGISTER_TEST(t4, new TestStaticMmbrFunc<CasesAliasTypeAndPointer,
    T4Var1>(t4_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc5
 * 	{
 *      template<typename T1 = void>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1 = void>
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type<> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type<> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1 = void

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc5, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Foo1);

template<typename T>
using TStaticMmbrFunc5 = StaticMmbrFunc5<T, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc5<A, void>", StaticMmbrFunc5<A, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc5<A>, void (*)(), 
    void*> T5Var1;

T5Var1 t5_var1(ToVoidPtr<void (*)()>(&A::Foo1));

REGISTER_TEST(t5, new TestStaticMmbrFunc<CasesAliasTypeTmplAndPointer,
    T5Var1>(t5_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc6
 * 	{
 * 	    using Type = Tr (*)(Targs...);
 * 	    using type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_PTR_TMPL_PARAM_LIST_PTPL1()\
typename T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc6, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Foo1);

template<typename T>
using TStaticMmbrFunc6 = StaticMmbrFunc6<T, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc6<A, void>", StaticMmbrFunc6<A, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc6<A>, void (*)(), 
    void*, void> T6Var1;

T6Var1 t6_var1(ToVoidPtr<void (*)()>(&A::Foo1));

REGISTER_TEST(t6, new TestStaticMmbrFunc<CasesAliasTypeAndPointerTmpl,
    T6Var1>(t6_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc7
 * 	{
 *      template<typename T1>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    using type = Tr (*)(Targs...);
 * 	    static constexpr Type<void> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	    static constexpr type<void> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc7, T, Tr, Targs,, T_NAME_,,
    T_RET_NAME_,, ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Foo1);

template<typename T>
using TStaticMmbrFunc7 = StaticMmbrFunc7<T, void>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc7<A, void>", StaticMmbrFunc7<A, void>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc7<A>, void (*)(), 
    void*, void> T7Var1;

T7Var1 t7var1(ToVoidPtr<void (*)()>(&A::Foo1));

REGISTER_TEST(t7, new TestStaticMmbrFunc<CasesAliasTypeTmplAndPointer,
    T7Var1>(t7var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct StaticMmbrFunc8
 * 	{
 *      template<typename T1>
 * 	    using Type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    using type = Tr (*)(Targs...);
 *      template<typename T1>
 * 	    static constexpr Type<T1> Pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type<T1> pointer()
 * 	    {
 * 	        return &T::Foo1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_STATIC_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
T1

__DEFINE_STATIC_MMBR_FUNC_(StaticMmbrFunc8, T, Tr, Targs, TPL4, T_NAME_,,
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_TMPL_, ATTPL2, PTR_TMPL_, PTPL1, 
    PTR_RET_TMPL_, PRTAL3, Foo3);

template<typename T>
using TStaticMmbrFunc8 = StaticMmbrFunc8<T, B>;

BASIC_TEST_TYPE_NAME("StaticMmbrFunc8<C, B>", StaticMmbrFunc8<C, B>);

typedef VariableTestStaticMmbrFunc<TStaticMmbrFunc8<C>, B<void> (*)(), 
    void*, void> T8Var1;

T8Var1 t8var1(ToVoidPtr<B<void> (*)()>(&C::Foo3));

REGISTER_TEST(t8, new TestStaticMmbrFunc<CasesAliasTypeTmplAndPointerTmpl,
    T8Var1>(t8var1));

int main()
{
    return RUN_TEST();
}
