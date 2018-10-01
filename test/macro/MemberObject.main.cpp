#include "macro/MemberObject.h"
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
struct CasePTa{}; // case pointer and target
struct CasePTTa{}; // case pointer tmpl and target
struct CaseP{}; //case pointer
struct CasePT{}; // case pointer tmpl

template<typename TMmbrObj, typename TObject, typename TAliasType, 
    typename TPointer, typename... TArgs>
using VariableTestMmbrObj = basic::test::Variable<
    TMmbrObj, 
    TObject,
    basic::test::Value<TObject*>, 
    TAliasType,
    basic::test::Value<TPointer>,
    basic::test::type::Parameter<TArgs...>>;

constexpr std::size_t IMmbrObj = 0;
constexpr std::size_t IObject = 1;
constexpr std::size_t IValPtrObject = 2;
constexpr std::size_t IAliasType = 3;
constexpr std::size_t IValPointer = 4;
constexpr std::size_t ITypeParameter = 5;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

typedef basic::test::msg::Argument<CaseATTa, 
    ArgTypeName<IMmbrObj>, 
    ArgTypeName<IAliasType>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, 
    ArgTypeName<IMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IAliasType>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<IMmbrObj>,
    ArgTypeName<IMmbrObj>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, 
    ArgTypeName<IMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IMmbrObj>, 
    ArgTypeParamName<ITypeParameter>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

typedef basic::test::msg::Argument<CasePTa, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>, 
    ArgTypeName<IMmbrObj>, 
    ArgValue<IValPointer>> ArgCasePTa;

typedef basic::test::msg::Base<CasePTa, char, ArgCasePTa, 
    ArgCasePTa, ArgCasePTa> MsgBaseCasePTa;

typedef basic::test::msg::Argument<CasePTTa, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>,
    ArgTypeName<IMmbrObj>, 
    ArgTypeParamName<ITypeParameter>,
    ArgValue<IValPointer>> ArgCasePTTa;

typedef basic::test::msg::Base<CasePTTa, char, ArgCasePTTa, 
    ArgCasePTTa, ArgCasePTTa> MsgBaseCasePTTa;

typedef basic::test::msg::Argument<CaseP, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>, 
    ArgTypeName<IMmbrObj>, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>, 
    ArgTypeName<IMmbrObj>> ArgCaseP;

typedef basic::test::msg::Base<CaseP, char, ArgCaseP, 
    ArgCaseP, ArgCaseP> MsgBaseCaseP;

typedef basic::test::msg::Argument<CasePT, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>, 
    ArgTypeName<IMmbrObj>, 
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IObject>,
    ArgValue<IValPtrObject>, 
    ArgTypeName<IMmbrObj>, 
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
class TestMmbrObj :
    public MsgBaseCaseATTa,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public MsgBaseCasePTa,
    public MsgBaseCasePTTa,
    public MsgBaseCaseP,
    public MsgBaseCasePT,
    public basic::test::Message<BASIC_TEST, TestMmbrObj<TCases, TVars...>>,
    public basic::test::Case<TestMmbrObj<TCases, TVars...>, TCases>,
    public basic::test::Base<TestMmbrObj<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestMmbrObj<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestMmbrObj<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestMmbrObj<TCases, TVars...>, 
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
    TestMmbrObj(TVars&... vars) :
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
            "test compare between %s{%p}->%s::pointer() and %p\n");
        SetFormat(debug, case_pointer_and_target,
            "test compare between %s{%p}->%s::pointer() and %p\n");
        SetFormat(error, case_pointer_and_target,
            "error %s{%p}->%s::pointer() is not same with %p\n");

        CasePTTa case_pointer_tmpl_and_target;
        SetFormat(info, case_pointer_tmpl_and_target, 
            "test compare between %s{%p}->%s::template pointer<%s>() and %p\n");
        SetFormat(debug, case_pointer_tmpl_and_target,
            "test compare between %s{%p}->%s::template pointer<%s>() and %p\n");
        SetFormat(error, case_pointer_tmpl_and_target,
            "error %s{%p}->%s::template pointer<%s>() is not same with %p\n");

        CaseP case_pointer;
        SetFormat(info, case_pointer, 
            "test compare between %s{%p}->%s::pointer() and "
            "%s{%p}->%s::Pointer()\n");
        SetFormat(debug, case_pointer,
            "test compare between %s{%p}->%s::pointer() and "
            "%s{%p}->%s::Pointer()\n");
        SetFormat(error, case_pointer,
            "error %s{%p}->%s::pointer() is not same with "
            "%s{%p}->%s::Pointer()\n");

        CasePT case_pointer_tmpl;
        SetFormat(info, case_pointer_tmpl, 
            "test compare between %s{%p}->%s::template pointer<%s>() "
            "and %s{%p}->%s::template Pointer<%s>()\n");
        SetFormat(debug, case_pointer_tmpl,
            "test compare between %s{%p}->%s::template pointer<%s>() "
            "and %s{%p}->%s::template Pointer<%s>()\n");
        SetFormat(error, case_pointer_tmpl,
            "error %s{%p}->%s::template pointer<%s>() is "
            "not same with %s{%p}->%s::template Pointer<%s>()\n");

    }
public:
    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CaseATTa&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TMmbrObj::type).hash_code() ==
            typeid(TAliasType).hash_code();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CaseATTTa&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TMmbrObj::template type<TArgs...>).hash_code() ==
            typeid(TAliasType).hash_code();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CaseAT&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TMmbrObj::type).hash_code() ==
            typeid(typename TMmbrObj::Type).hash_code();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CaseATT&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return typeid(typename TMmbrObj::template type<TArgs...>).hash_code() ==
            typeid(typename TMmbrObj::template Type<TArgs...>).hash_code();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CasePTa&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(&(basic::test::var::At<
            IValPtrObject>(var).Get().Get()->*TMmbrObj::pointer())) == 
                basic::test::var::At<IValPointer>(var).Get().Get();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CasePTTa&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(&(basic::test::var::At<
            IValPtrObject>(var).Get().Get()->*TMmbrObj::template pointer<
                TArgs...>())) == basic::test::var::At<
                    IValPtrObject>(var).Get().Get();
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CaseP&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(&(basic::test::var::At<
            IValPtrObject>(var).Get().Get()->*TMmbrObj::pointer())) == 
            ToVoidPtr(&(basic::test::var::At<IValPtrObject>(var).Get().Get()->*
                TMmbrObj::Pointer()));
    }

    template<typename TMmbrObj, typename TObject, typename TAliasType, 
        typename TPointer, typename... TArgs>
    bool Result(const CasePT&, VariableTestMmbrObj<TMmbrObj, TObject, 
        TAliasType, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(&(basic::test::var::At<
            IValPtrObject>(var).Get().Get()->*TMmbrObj::template pointer<
                TArgs...>())) == ToVoidPtr(&(basic::test::var::At<
                    IValPtrObject>(var).Get().Get()->*TMmbrObj::
                    template Pointer<TArgs...>()));
    }
};

struct A
{
    int Obj1;
};

template<typename>
struct B
{
    int Obj2;
};

struct C
{
    B<void> Obj3;
};

using CasesAliasTypeAndPointer = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTa, CaseP>;
using CasesAliasTypeAndPointerTmpl = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTTa, CasePT>;
using CasesAliasTypeTmplAndPointer = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTa, CaseP>;
using CasesAliasTypeTmplAndPointerTmpl = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTTa, CasePT>;;

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("int A::*", int A::*);
BASIC_TEST_TYPE_NAME("B<void>", B<void>);
BASIC_TEST_TYPE_NAME("int B<void>::*", int B<void>::*);
BASIC_TEST_TYPE_NAME("C", C);
BASIC_TEST_TYPE_NAME("B<void> C::*", B<void> C::*);

A a;
B<void> b_void;
C c;

/**
 * 	template<typename T, typename To>
 * 	struct MmbrObj1
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_OBJ_(MmbrObj1, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using TMmbrObj1 = MmbrObj1<T, int>;

BASIC_TEST_TYPE_NAME("MmbrObj1<A, int>", MmbrObj1<A, int>);

typedef VariableTestMmbrObj<TMmbrObj1<A>, A, int A::*, 
    void*> T1Var1;

T1Var1 t1_var1(&a, ToVoidPtr<int*>(&a.Obj1));

REGISTER_TEST(t1, new TestMmbrObj<CasesAliasTypeAndPointer,
    T1Var1>(t1_var1));

/**
 * 	template<typename T, typename To, typename T1>
 * 	struct MmbrObj2
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename __T_OBJ_NAME__, typename T1

__DEFINE_MMBR_OBJ_(MmbrObj2, T, To, TPL1, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using TMmbrObj2 = MmbrObj2<T, int, void>;

BASIC_TEST_TYPE_NAME("MmbrObj2<A, int, void>", MmbrObj2<A, int, void>);

typedef VariableTestMmbrObj<TMmbrObj2<A>, A, int A::*, 
    void*> T2Var1;

T2Var1 t2_var1(&a, ToVoidPtr<int*>(&a.Obj1));

REGISTER_TEST(t2, new TestMmbrObj<CasesAliasTypeAndPointer,
    T2Var1>(t2_var1));

/**
 * 	template<template<typename> class T, typename To, typename T1>
 * 	struct MmbrObj3
 * 	{
 * 	    using type = To T<T1>::*;
 * 	    using Type = To T<T1>::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
template<typename>class __T_NAME__, typename __T_OBJ_NAME__, typename T1

#define __DEFINE_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj3, T, To, TPL2, T_NAME_TMPL_, TNTAL1, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj2);

template<typename T>
using TMmbrObj3 = MmbrObj3<B, int, T>;

BASIC_TEST_TYPE_NAME("MmbrObj3<B, int, void>", MmbrObj3<B, int, void>);

typedef VariableTestMmbrObj<TMmbrObj3<void>, B<void>, int B<void>::*, 
    void*> T3Var1;

T3Var1 t3_var1(&b_void, ToVoidPtr<int*>(&b_void.Obj2));

REGISTER_TEST(t3, new TestMmbrObj<CasesAliasTypeAndPointer,
    T3Var1>(t3_var1));

/**
 * 	template<typename T, template<typename> class To, typename T1>
 * 	struct MmbrObj4
 * 	{
 * 	    using type = To<T1> T::*;
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename>class __T_OBJ_NAME__, typename T1

#define __DEFINE_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj4, T, To, TPL3, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj3);

template<typename T>
using TMmbrObj4 = MmbrObj4<T, B, void>;

BASIC_TEST_TYPE_NAME("MmbrObj4<C, B, void>", MmbrObj4<C, B, void>);

typedef VariableTestMmbrObj<TMmbrObj4<C>, C, B<void> C::*, 
    void*> T4Var1;

T4Var1 t4_var1(&c, ToVoidPtr<B<void>*>(&c.Obj3));

REGISTER_TEST(t4, new TestMmbrObj<CasesAliasTypeAndPointer,
    T4Var1>(t4_var1));

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj5
 * 	{
 *      template<typenane T1 = void>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1 = void>
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type<> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type<> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename>class __T_OBJ_NAME__

#define __DEFINE_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1 = void

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_MMBR_OBJ_(MmbrObj5, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Obj3);

template<typename T>
using TMmbrObj5 = MmbrObj5<T, B>;

BASIC_TEST_TYPE_NAME("MmbrObj5<C, B>", MmbrObj5<C, B>);

typedef VariableTestMmbrObj<TMmbrObj5<C>, C, B<void> C::*, 
    void*, void> T5Var1;

T5Var1 t5_var1(&c, ToVoidPtr<B<void>*>(&c.Obj3));

REGISTER_TEST(t5, new TestMmbrObj<CasesAliasTypeTmplAndPointer,
    T5Var1>(t5_var1));

/**
 * 	template<typename T, typename To>
 * 	struct MmbrObj6
 * 	{
 * 	    using type = To T::*;
 * 	    using Type = To T::*;
 *      template<typename T1>
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL1()\
typename T1

__DEFINE_MMBR_OBJ_(MmbrObj6, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Obj1);

template<typename T>
using TMmbrObj6 = MmbrObj6<T, int>;

BASIC_TEST_TYPE_NAME("MmbrObj6<A, int>", MmbrObj6<A, int>);

typedef VariableTestMmbrObj<TMmbrObj6<A>, A, int A::*, 
    void*, void> T6Var1;

T6Var1 t6_var1(&a, ToVoidPtr<int*>(&a.Obj1));

REGISTER_TEST(t6_1, new TestMmbrObj<CasesAliasTypeAndPointerTmpl,
    T6Var1>(t6_var1));

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj7
 * 	{
 *      template<typenane T1>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1>
 * 	    using Type = To<T1> T::*;
 * 	    static constexpr type<void> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr Type<void> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_MMBR_OBJ_(MmbrObj7, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Obj3);

template<typename T>
using TMmbrObj7 = MmbrObj7<T, B>;

BASIC_TEST_TYPE_NAME("MmbrObj7<C, B>", MmbrObj7<C, B>);

typedef VariableTestMmbrObj<TMmbrObj7<C>, C, B<void> C::*, 
    void*, void> T7Var1;

T7Var1 t7_var1(&c, ToVoidPtr<B<void>*>(&c.Obj3));

REGISTER_TEST(t7, new TestMmbrObj<CasesAliasTypeTmplAndPointer,
    T7Var1>(t7_var1));

/**
 * 	template<typename T, template<typename> class To>
 * 	struct MmbrObj8
 * 	{
 *      template<typenane T1>
 * 	    using type = To<T1> T::*;
 *      template<typenane T1>
 * 	    using Type = To<T1> T::*;
 *      template<typename T1>
 * 	    static constexpr type<T1> pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr Type<T1> Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
T1

__DEFINE_MMBR_OBJ_(MmbrObj8, T, To, TPL4, T_NAME_,, T_OBJ_NAME_TMPL_, TONTAL1,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_TMPL_, PTPL1, PTR_RET_TMPL_, PRTAL3, Obj3);

template<typename T>
using TMmbrObj8 = MmbrObj8<T, B>;

BASIC_TEST_TYPE_NAME("MmbrObj8<C, B>", MmbrObj8<C, B>);

typedef VariableTestMmbrObj<TMmbrObj8<C>, C, B<void> C::*, 
    void*, void> T8Var1;

T8Var1 t8_var1(&c, ToVoidPtr<B<void>*>(&c.Obj3));

REGISTER_TEST(t8, new TestMmbrObj<CasesAliasTypeTmplAndPointerTmpl,
    T8Var1>(t8_var1));

int main()
{
    return RUN_TEST();
}
