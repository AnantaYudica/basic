#include "macro/StaticMemberObject.h"
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

template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
    typename... TArgs>
using VariableTestStaticMmbrObj = basic::test::Variable<
    TStaticMmbrObj, 
    TAlias,
    basic::test::Value<TPointer>,
    basic::test::type::Parameter<TArgs...>>;

constexpr std::size_t IStaticMmbrObj = 0;
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
    ArgTypeName<IStaticMmbrObj>, 
    ArgTypeName<IAliasType>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IAliasType>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseAT, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeName<IStaticMmbrObj>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IStaticMmbrObj>, 
    ArgTypeParamName<ITypeParameter>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

typedef basic::test::msg::Argument<CasePTa, 
    ArgTypeName<IStaticMmbrObj>,
    ArgValue<IValPointer>> ArgCasePTa;

typedef basic::test::msg::Base<CasePTa, char, ArgCasePTa, 
    ArgCasePTa, ArgCasePTa> MsgBaseCasePTa;

typedef basic::test::msg::Argument<CasePTTa, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgValue<IValPointer>> ArgCasePTTa;

typedef basic::test::msg::Base<CasePTTa, char, ArgCasePTTa, 
    ArgCasePTTa, ArgCasePTTa> MsgBaseCasePTTa;

typedef basic::test::msg::Argument<CaseP, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeName<IStaticMmbrObj>> ArgCaseP;

typedef basic::test::msg::Base<CaseP, char, ArgCaseP, 
    ArgCaseP, ArgCaseP> MsgBaseCaseP;

typedef basic::test::msg::Argument<CasePT, 
    ArgTypeName<IStaticMmbrObj>,
    ArgTypeParamName<ITypeParameter>, 
    ArgTypeName<IStaticMmbrObj>, 
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
class TestStaticMmbrObj :
    public MsgBaseCaseATTa,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public MsgBaseCasePTa,
    public MsgBaseCasePTTa,
    public MsgBaseCaseP,
    public MsgBaseCasePT,
    public basic::test::Message<BASIC_TEST, TestStaticMmbrObj<TCases, TVars...>>,
    public basic::test::Case<TestStaticMmbrObj<TCases, TVars...>, TCases>,
    public basic::test::Base<TestStaticMmbrObj<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestStaticMmbrObj<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestStaticMmbrObj<TCases, TVars...>> BaseMessageType;
    typedef basic::test::Case<TestStaticMmbrObj<TCases, TVars...>, 
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
    TestStaticMmbrObj(TVars&... vars) :
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
    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATTa&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrObj::type).hash_code() ==
            typeid(TAlias).hash_code();
    }
  
    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATTTa&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrObj::template type<
            TArgs...>).hash_code() == typeid(TAlias).hash_code();
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseAT&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrObj::type).hash_code() ==
            typeid(typename TStaticMmbrObj::Type).hash_code();
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseATT&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return typeid(typename TStaticMmbrObj::template type<
            TArgs...>).hash_code() == typeid(typename TStaticMmbrObj::
            template Type<TArgs...>).hash_code();
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePTa&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrObj::pointer()) == 
            basic::test::var::At<IValPointer>(var).Get().Get();
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePTTa&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrObj::template pointer<TArgs...>()) == 
            basic::test::var::At<IValPointer>(var).Get().Get();
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CaseP&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrObj::pointer()) == 
            ToVoidPtr(TStaticMmbrObj::Pointer());
    }

    template<typename TStaticMmbrObj, typename TAlias, typename TPointer, 
        typename... TArgs>
    bool Result(const CasePT&, VariableTestStaticMmbrObj<TStaticMmbrObj, 
        TAlias, TPointer, TArgs...>& var)
    {
        return ToVoidPtr(TStaticMmbrObj::template pointer<TArgs...>()) == 
            ToVoidPtr(TStaticMmbrObj::template Pointer<TArgs...>());
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
    static int Obj1;
};

int A::Obj1;

template<typename T>
struct B
{
    static int Obj2;
};

template<typename T>
int B<T>::Obj2;

struct C
{
    static B<void> Obj3;
};

B<void> C::Obj3;

template<typename T, T TVal>
struct ValueName
{
    static constexpr const char * Value = "undefined"; 
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("int", int);
BASIC_TEST_TYPE_NAME("B<void>", B<void>);

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj1
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj1, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using TStaticMmbrObj1 = StaticMmbrObj1<T, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj1<A, int>", StaticMmbrObj1<A, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj1<A>, int, void*> T1Var1;

T1Var1 t1_var1(ToVoidPtr<int*>(&A::Obj1));

REGISTER_TEST(t1, new TestStaticMmbrObj<CasesAliasTypeAndPointer,
    T1Var1>(t1_var1));

/**
 * 	template<typename T, typename T1, typename To>
 * 	struct StaticMmbrObj2
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename T1, typename __T_OBJ_NAME__

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj2, T, To, TPL1, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj1);

template<typename T>
using TStaticMmbrObj2 = StaticMmbrObj2<T, void, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj2<A, void, int>", 
    StaticMmbrObj2<A, void, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj2<A>, int, void*> T2Var1;

T2Var1 t2_var1(ToVoidPtr<int*>(&A::Obj1));

REGISTER_TEST(t2, new TestStaticMmbrObj<CasesAliasTypeAndPointer,
    T2Var1>(t2_var1));

/**
 * 	template<template<typename> class T, typename T1, typename To>
 * 	struct StaticMmbrObj3
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T<T1>::Obj2;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL()\
T1

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj3, T, To, TPL2, T_NAME_TMPL_, TNTAL, 
    T_OBJ_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj2);

template<typename T>
using TStaticMmbrObj3 = StaticMmbrObj3<B, T, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj3<B, void, int>",
    StaticMmbrObj3<B, void, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj3<void>, int, void*> T3Var1;

T3Var1 t3_var1(ToVoidPtr<int*>(&B<void>::Obj2));

REGISTER_TEST(t3, new TestStaticMmbrObj<CasesAliasTypeAndPointer,
    T3Var1>(t3_var1));

/**
 * 	template<typename T, typename T1, template<typename> class To>
 * 	struct StaticMmbrObj4
 * 	{
 * 	    using Type = To<T1>;
 * 	    using type = To<T1>;
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj4, T, To, TPL3, T_NAME_,, 
    T_OBJ_NAME_TMPL_, TONTAL1, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Obj3);

template<typename T>
using TStaticMmbrObj4 = StaticMmbrObj4<T, void, B>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj4<C, void, B>",
    StaticMmbrObj4<C, void, B>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj4<C>, B<void>, void*> T4Var1;

T4Var1 t4_var1(ToVoidPtr<B<void>*>(&C::Obj3));

REGISTER_TEST(t4_1, new TestStaticMmbrObj<CasesAliasTypeAndPointer,
    T4Var1>(t4_var1));

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj5
 * 	{
 *      template<typename = void>
 * 	    using Type = To;
 *      template<typename = void>
 * 	    using type = To;
 * 	    static constexpr Type<>* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type<>* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename = void

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL1()

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj5, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, PTR_RET_TMPL_, PRTAL1, Obj1);

template<typename T>
using TStaticMmbrObj5 = StaticMmbrObj5<T, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj5<A, int>",
    StaticMmbrObj5<A, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj5<A>, int, void*> T5Var1;

T5Var1 t5_var1(ToVoidPtr<int*>(&A::Obj1));

REGISTER_TEST(t5, new TestStaticMmbrObj<CasesAliasTypeTmplAndPointer,
    T5Var1>(t5_var1));

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj6
 * 	{
 * 	    using Type = To;
 * 	    using type = To;
 *      template<typename = void>
 * 	    static constexpr Type* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 *      template<typename = void>
 * 	    static constexpr type* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL1()\
typename = void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj6, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_,, PTR_TMPL_, PTPL1, PTR_RET_,, Obj1);

template<typename T>
using TStaticMmbrObj6 = StaticMmbrObj6<T, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj6<A, int>", StaticMmbrObj6<A, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj6<A>, int, void*> T6Var1;

T6Var1 t6_var1(ToVoidPtr<int*>(&A::Obj1));

REGISTER_TEST(t6, new TestStaticMmbrObj<CasesAliasTypeAndPointerTmpl,
    T6Var1>(t6_var1));

/**
 * 	template<typename T, typename To>
 * 	struct StaticMmbrObj7
 * 	{
 *      template<typename T1>
 * 	    using Type = To;
 *      template<typename T1>
 * 	    using type = To;
 * 	    static constexpr Type<void>* Pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	    static constexpr type<void>* pointer()
 * 	    {
 * 	        return &T::Obj1;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL2()\
void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj7, T, To,, T_NAME_,, T_OBJ_NAME_,,
    ALIAS_TYPE_TMPL_, ATTPL2, PTR_,, PTR_RET_TMPL_, PRTAL2, Obj1);

template<typename T>
using TStaticMmbrObj7 = StaticMmbrObj7<T, int>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj7<A, int>", StaticMmbrObj7<A, int>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj7<A>, int, void*,
    void> T7Var1;

T7Var1 t7_var1(ToVoidPtr<int*>(&A::Obj1));

REGISTER_TEST(t7, new TestStaticMmbrObj<CasesAliasTypeTmplAndPointer,
    T7Var1>(t7_var1));

/**
 * 	template<typename T, template<typename> class To>
 * 	struct StaticMmbrObj8
 * 	{
 *      template<typename T1>
 * 	    using Type = To<T1>;
 *      template<typename T1>
 * 	    using type = To<T1>;
 *      template<typename T1>
 * 	    static constexpr Type<T1>* Pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type<T1>* pointer()
 * 	    {
 * 	        return &T::Obj3;
 * 	    }
 * 	};
 * */

#define __DEFINE_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_OBJ_NAME__)\
typename __T_NAME__, template<typename> class __T_OBJ_NAME__

#define __DEFINE_STATIC_MMBR_OBJ_T_OBJ_NAME_TMPL_ARG_LIST_TONTAL1()\
T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_TMPL_PARAM_LIST_PTPL2()\
typename T1

#define __DEFINE_STATIC_MMBR_OBJ_PTR_RET_TMPL_ARG_LIST_PRTAL3()\
void

__DEFINE_STATIC_MMBR_OBJ_(StaticMmbrObj8, T, To, TPL4, T_NAME_,, 
    T_OBJ_NAME_TMPL_, TONTAL1, ALIAS_TYPE_TMPL_, ATTPL2, 
    PTR_TMPL_, PTPL2, PTR_RET_TMPL_, PRTAL3, Obj3);

template<typename T>
using TStaticMmbrObj8 = StaticMmbrObj8<T, B>;

BASIC_TEST_TYPE_NAME("StaticMmbrObj8<C, B>", StaticMmbrObj8<C, B>);

typedef VariableTestStaticMmbrObj<TStaticMmbrObj8<C>, B<void>, void*,
    void> T8Var1;

T8Var1 t8_var1(ToVoidPtr<B<void>*>(&C::Obj3));

REGISTER_TEST(t8, new TestStaticMmbrObj<CasesAliasTypeTmplAndPointerTmpl,
    T8Var1>(t8_var1));


int main()
{
    return RUN_TEST();
}
