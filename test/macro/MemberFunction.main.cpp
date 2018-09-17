#include "macro/MemberFunction.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"

#include <ostream>
#include <sstream>
#include <cstring>
#include <cstddef>

struct CaseATTa {}; // case alias type and target
struct CaseATTTa{}; // case alias type tmpl and target
struct CaseAT{}; // case alias type
struct CaseATT{}; // case alias type tmpl
struct CasePTa{}; // case pointer and target
struct CasePTTa{}; // case pointer tmpl and target
struct CaseP{}; //case pointer
struct CasePT{}; // case pointer tmpl

template<typename Tmf, typename T, typename Tta, typename Ttp, 
    typename... Targs>
using VariableTestMmbrFunc = basic::test::Variable<Tmf, T, Tta,
    basic::test::var::Value<Ttp>,
    basic::test::type::Parameter<Targs...>>;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgVarValue = basic::test::msg::arg::var::Value<I>;

typedef basic::test::msg::Argument<CaseATTa, ArgTypeName<0>, 
    ArgTypeName<2>> ArgCaseATTa;

typedef basic::test::msg::Base<CaseATTa, char, ArgCaseATTa, 
    ArgCaseATTa, ArgCaseATTa> MsgBaseCaseATTa;

typedef basic::test::msg::Argument<CaseATTTa, ArgTypeName<0>,
    ArgTypeParamName<4>, ArgTypeName<2>> ArgCaseATTTa;

typedef basic::test::msg::Base<CaseATTTa, char, ArgCaseATTTa, 
    ArgCaseATTTa, ArgCaseATTTa> MsgBaseCaseATTTa;

typedef basic::test::msg::Argument<CaseAT, ArgTypeName<0>,
    ArgTypeName<0>> ArgCaseAT;

typedef basic::test::msg::Base<CaseAT, char, ArgCaseAT, 
    ArgCaseAT, ArgCaseAT> MsgBaseCaseAT;

typedef basic::test::msg::Argument<CaseATT, ArgTypeName<0>,
    ArgTypeParamName<4>, ArgTypeName<0>, ArgTypeParamName<4>> ArgCaseATT;

typedef basic::test::msg::Base<CaseATT, char, ArgCaseATT, 
    ArgCaseATT, ArgCaseATT> MsgBaseCaseATT;

typedef basic::test::msg::Argument<CasePTa, ArgTypeName<0>,
    ArgVarValue<3>> ArgCasePTa;

typedef basic::test::msg::Base<CasePTa, char, ArgCasePTa, 
    ArgCasePTa, ArgCasePTa> MsgBaseCasePTa;

typedef basic::test::msg::Argument<CasePTTa, ArgTypeName<0>,
    ArgTypeParamName<4>, ArgVarValue<3>> ArgCasePTTa;

typedef basic::test::msg::Base<CasePTTa, char, ArgCasePTTa, 
    ArgCasePTTa, ArgCasePTTa> MsgBaseCasePTTa;

typedef basic::test::msg::Argument<CaseP, ArgTypeName<0>,
    ArgTypeName<0>> ArgCaseP;

typedef basic::test::msg::Base<CaseP, char, ArgCaseP, 
    ArgCaseP, ArgCaseP> MsgBaseCaseP;

typedef basic::test::msg::Argument<CasePT, ArgTypeName<0>,
    ArgTypeParamName<4>, ArgTypeName<0>, ArgTypeParamName<4>> ArgCasePT;

typedef basic::test::msg::Base<CasePT, char, ArgCasePT, 
    ArgCasePT, ArgCasePT> MsgBaseCasePT;

template<typename Tptr>
void* ToVoidPtr(Tptr t)
{
    Tptr * tp = &t;
    void ** vp = reinterpret_cast<void**>(tp);
    return *vp;
} 

template<template<typename> class Tmf, typename TCases, 
    typename... TVar>
class TestMmbrFunc :
    public MsgBaseCaseATTa,
    public MsgBaseCaseATTTa,
    public MsgBaseCaseAT,
    public MsgBaseCaseATT,
    public MsgBaseCasePTa,
    public MsgBaseCasePTTa,
    public MsgBaseCaseP,
    public MsgBaseCasePT,
    public basic::test::Message<BASIC_TEST, TestMmbrFunc<Tmf, 
        TCases, TVar...>>,
    public basic::test::Case<TestMmbrFunc<Tmf, TCases, TVar...>, TCases>,
    public basic::test::Base<TestMmbrFunc<Tmf, TCases, TVar...>, TVar...>
{
public:
    typedef basic::test::Base<TestMmbrFunc<Tmf, TCases, TVar...>, 
        TVar...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, 
        TestMmbrFunc<Tmf, TCases, TVar...>> BaseMessageType;
    typedef basic::test::Case<TestMmbrFunc<Tmf, TCases, TVar...>, 
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
    TestMmbrFunc(TVar&... vars) :
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
    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CaseATTa&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return typeid(typename Tmf<T>::type).hash_code() ==
            typeid(Tta).hash_code();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CaseATTTa&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return typeid(typename Tmf<T>::template type<Targs...>).hash_code() ==
            typeid(Tta).hash_code();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CaseAT&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return typeid(typename Tmf<T>::type).hash_code() ==
            typeid(typename Tmf<T>::Type).hash_code();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CaseATT&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return typeid(typename Tmf<T>::template type<Targs...>).hash_code() ==
            typeid(typename Tmf<T>::template Type<Targs...>).hash_code();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CasePTa&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return ToVoidPtr(Tmf<T>::pointer()) == 
            var.template GetValue<3>();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CasePTTa&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return ToVoidPtr(Tmf<T>::template pointer<Targs...>()) == 
            var.template GetValue<3>();
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CaseP&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return ToVoidPtr(Tmf<T>::pointer()) == ToVoidPtr(Tmf<T>::Pointer());
    }

    template<typename _Tmf, typename T, typename Tta, typename Ttp, 
        typename... Targs>
    bool Result(const CasePT&, VariableTestMmbrFunc<_Tmf, T, Tta, Ttp, 
        Targs...>& var)
    {
        return ToVoidPtr(Tmf<T>::template pointer<Targs...>()) == 
            ToVoidPtr(Tmf<T>::template Pointer<Targs...>());
    }
    
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);


using CaseAliasTypeAndPointer = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTa, CaseP>;
using CaseAliasTypeAndPointerTmpl = basic::test::type::
    Parameter<CaseATTa, CaseAT, CasePTTa, CasePT>;
using CaseAliasTypeTmplAndPointer = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTa, CaseP>;
using CaseAliasTypeTmplAndPointerTmpl = basic::test::type::
    Parameter<CaseATTTa, CaseATT, CasePTTa, CasePT>;;


struct A
{
    void Foo1() {}
    void Foo1() const {}
    void Foo1() volatile {}
    void Foo1() const volatile {}
    void Foo2() & {}
    void Foo2() const & {}
    void Foo2() volatile & {}
    void Foo2() const volatile & {}
    void Foo2() && {}
    void Foo2() const && {}
    void Foo2() volatile && {}
    void Foo2() const volatile && {}
};

BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("void(A::*)()", void(A::*)());
BASIC_TEST_TYPE_NAME("void(A::*)() const", void(A::*)() const);
BASIC_TEST_TYPE_NAME("void(A::*)() volatile", void(A::*)() volatile);
BASIC_TEST_TYPE_NAME("void(A::*)() const volatile", 
    void(A::*)() const volatile);
BASIC_TEST_TYPE_NAME("void(A::*)() &", void(A::*)() &);
BASIC_TEST_TYPE_NAME("void(A::*)() const &", void(A::*)() const &);
BASIC_TEST_TYPE_NAME("void(A::*)() volatile &", void(A::*)() volatile &);
BASIC_TEST_TYPE_NAME("void(A::*)() const volatile &", 
    void(A::*)() const volatile &);
BASIC_TEST_TYPE_NAME("void(A::*)() &&", void(A::*)() &&);
BASIC_TEST_TYPE_NAME("void(A::*)() const &&", void(A::*)() const &&);
BASIC_TEST_TYPE_NAME("void(A::*)() volatile &&", void(A::*)() volatile &&);
BASIC_TEST_TYPE_NAME("void(A::*)() const volatile &&", 
    void(A::*)() const volatile &&);

template<typename>
struct B
{
    void Foo3() {}
};

BASIC_TEST_TYPE_NAME("B<void>", B<void>);
BASIC_TEST_TYPE_NAME("void(B<void>::*)()", void(B<void>::*)());

struct C
{
    template<typename T>
    B<T> Foo4() {}
};

BASIC_TEST_TYPE_NAME("C", C);
BASIC_TEST_TYPE_NAME("B<void>(C::*)()", B<void>(C::*)());

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc1
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...);
 * 	    using type = Tr(T::*)(Targs...);
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

__DEFINE_MMBR_FUNC_(MmbrFunc1, T, Tr, Targs,,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using MmbrFunc1Type = MmbrFunc1<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc1<A, void>", MmbrFunc1<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc1Type<A>, A, 
    void(A::*)(), void*> T1Var1Type;

T1Var1Type t1_var1(ToVoidPtr<void(A::*)()>(&A::Foo1));

REGISTER_TEST(t1, new TestMmbrFunc<MmbrFunc1Type, 
    CaseAliasTypeAndPointer, T1Var1Type>(t1_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc2
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const;
 * 	    using type = Tr(T::*)(Targs...) const;
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

__DEFINE_MMBR_FUNC_(MmbrFunc2, T, Tr, Targs, const,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using MmbrFunc2Type = MmbrFunc2<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc2<A, void>", MmbrFunc2<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc2<A, void>, A, void(A::*)() 
    const, void*> T2Var1Type;

T2Var1Type t2_var1(ToVoidPtr<void(A::*)() const>(&A::Foo1));

REGISTER_TEST(t2, new TestMmbrFunc<MmbrFunc2Type, 
    CaseAliasTypeAndPointer, T2Var1Type>(t2_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc3
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) volatile;
 * 	    using type = Tr(T::*)(Targs...) volatile;
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

__DEFINE_MMBR_FUNC_(MmbrFunc3, T, Tr, Targs, volatile,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using MmbrFunc3Type = MmbrFunc3<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc3<A, void>", MmbrFunc3<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc3<A, void>, A, void(A::*)() volatile, 
    void*> T3Var1Type;

T3Var1Type t3_var1(ToVoidPtr<void(A::*)() volatile>(&A::Foo1));

REGISTER_TEST(t3, new TestMmbrFunc<MmbrFunc3Type, 
    CaseAliasTypeAndPointer, T3Var1Type>(t3_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc4
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const volatile;
 * 	    using type = Tr(T::*)(Targs...) const volatile;
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

__DEFINE_MMBR_FUNC_(MmbrFunc4, T, Tr, Targs, const volatile,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using MmbrFunc4Type = MmbrFunc4<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc4<A, void>", MmbrFunc4<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc4<A, void>, A, 
    void(A::*)() const volatile, void*> T4Var1Type;

T4Var1Type t4_var1(ToVoidPtr<void(A::*)() const volatile>(&A::Foo1));

REGISTER_TEST(t4, new TestMmbrFunc<MmbrFunc4Type, 
    CaseAliasTypeAndPointer, T4Var1Type>(t4_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc5
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) &;
 * 	    using type = Tr(T::*)(Targs...) &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc5, T, Tr, Targs, &,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc5Type = MmbrFunc5<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc5<A, void>", MmbrFunc5<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc5<A, void>, A, 
    void(A::*)() &, void*> T5Var1Type;

T5Var1Type t5_var1(ToVoidPtr<void(A::*)() &>(&A::Foo2));

REGISTER_TEST(t5, new TestMmbrFunc<MmbrFunc5Type, 
    CaseAliasTypeAndPointer, T5Var1Type>(t5_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc6
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const &;
 * 	    using type = Tr(T::*)(Targs...) const &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc6, T, Tr, Targs, const &,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc6Type = MmbrFunc6<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc6<A, void>", MmbrFunc6<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc6<A, void>, A, 
    void(A::*)() const &, void*> T6Var1Type;

T6Var1Type t6_var1(ToVoidPtr<void(A::*)() const &>(&A::Foo2));

REGISTER_TEST(t6, new TestMmbrFunc<MmbrFunc6Type, 
    CaseAliasTypeAndPointer, T6Var1Type>(t6_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc7
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) volatile &;
 * 	    using type = Tr(T::*)(Targs...) volatile &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc7, T, Tr, Targs, volatile &,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc7Type = MmbrFunc7<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc7<A, void>", MmbrFunc7<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc7<A, void>, A, 
    void(A::*)() volatile &, void*> T7Var1Type;

T7Var1Type t7_var1(ToVoidPtr<void(A::*)() volatile &>(&A::Foo2));

REGISTER_TEST(t7, new TestMmbrFunc<MmbrFunc7Type, 
    CaseAliasTypeAndPointer, T7Var1Type>(t7_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc8
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const volatile &;
 * 	    using type = Tr(T::*)(Targs...) const volatile &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc8, T, Tr, Targs, const volatile &,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc8Type = MmbrFunc8<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc8<A, void>", MmbrFunc8<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc8<A, void>, A, 
    void(A::*)() const volatile &, void*> T8Var1Type;

T8Var1Type t8_var1(ToVoidPtr<void(A::*)() const volatile &>(&A::Foo2));

REGISTER_TEST(t8, new TestMmbrFunc<MmbrFunc8Type, 
    CaseAliasTypeAndPointer, T8Var1Type>(t8_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc5
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) &;
 * 	    using type = Tr(T::*)(Targs...) &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc9, T, Tr, Targs, &&,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc9Type = MmbrFunc9<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc9<A, void>", MmbrFunc9<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc9<A, void>, A, 
    void(A::*)() &&, void*> T9Var1Type;

T9Var1Type t9_var1(ToVoidPtr<void(A::*)() &&>(&A::Foo2));

REGISTER_TEST(t9, new TestMmbrFunc<MmbrFunc9Type, 
    CaseAliasTypeAndPointer, T9Var1Type>(t9_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc10
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const &;
 * 	    using type = Tr(T::*)(Targs...) const &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc10, T, Tr, Targs, const &&,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc10Type = MmbrFunc10<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc10<A, void>", MmbrFunc10<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc10<A, void>, A, 
    void(A::*)() const &&, void*> T10Var1Type;

T10Var1Type t10_var1(ToVoidPtr<void(A::*)() const &&>(&A::Foo2));

REGISTER_TEST(t10, new TestMmbrFunc<MmbrFunc10Type, 
    CaseAliasTypeAndPointer, T10Var1Type>(t10_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc11
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) volatile &;
 * 	    using type = Tr(T::*)(Targs...) volatile &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc11, T, Tr, Targs, volatile &&,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc11Type = MmbrFunc11<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc11<A, void>", MmbrFunc11<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc11<A, void>, A, 
    void(A::*)() volatile &&, void*> T11Var1Type;

T11Var1Type t11_var1(ToVoidPtr<void(A::*)() volatile &&>(&A::Foo2));

REGISTER_TEST(t11, new TestMmbrFunc<MmbrFunc11Type, 
    CaseAliasTypeAndPointer, T11Var1Type>(t11_var1));

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct MmbrFunc12
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...) const volatile &;
 * 	    using type = Tr(T::*)(Targs...) const volatile &;
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo2;
 * 	    }
 * 	};
 * */

__DEFINE_MMBR_FUNC_(MmbrFunc12, T, Tr, Targs, const volatile &&,, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo2);

template<typename T>
using MmbrFunc12Type = MmbrFunc12<T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc12<A, void>", MmbrFunc12<A, void>);

typedef VariableTestMmbrFunc<MmbrFunc12<A, void>, A, 
    void(A::*)() const volatile &&, void*> T12Var1Type;

T12Var1Type t12_var1(ToVoidPtr<void(A::*)() const volatile &&>(&A::Foo2));

REGISTER_TEST(t12, new TestMmbrFunc<MmbrFunc12Type, 
    CaseAliasTypeAndPointer, T12Var1Type>(t12_var1));

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct MmbrFunc13
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = Tr(T::*)(Targs...);
 * 	    using type = Tr(T::*)(Targs...);
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

#define __DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_MMBR_FUNC_(MmbrFunc13, T, Tr, Targs,, TPL1, T_NAME_,, 
    T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo1);

template<typename T>
using MmbrFunc13Type = MmbrFunc13<T, void, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc13<A, void, void>", MmbrFunc13<A, void, void>);

typedef VariableTestMmbrFunc<MmbrFunc13<A, void, void>, A, 
    void(A::*)(), void*> T13Var1Type;

T13Var1Type t13_var1(ToVoidPtr<void(A::*)()>(&A::Foo1));

REGISTER_TEST(t13, new TestMmbrFunc<MmbrFunc13Type, 
    CaseAliasTypeAndPointer, T13Var1Type>(t13_var1));

/**
 * 	template<template<typename> class TT, typename T1, 
 *      typename Tr, typename... Targs>
 * 	struct MmbrFunc14
 * 	{
 * 	    static_assert(std::is_same<TT<T1>, 
 *          typename basic::type::trait::Simple<TT<T1>>::type
 * 	        "TT<T> is not simple type");
 * 	    using Type = Tr(TT<T1>::*)(Targs...);
 * 	    using type = Tr(TT<T1>::*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &TT<T1>::Foo3;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &TT<T1>::Foo3;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_MMBR_FUNC_(MmbrFunc14, TT, Tr, Targs,, TPL2, T_NAME_TMPL_,\
    TNTAL1, T_RET_NAME_,, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo3);

template<typename T>
using MmbrFunc14Type = MmbrFunc14<B, T, void>;

BASIC_TEST_TYPE_NAME("MmbrFunc14<B, void, void>", MmbrFunc14<B, void, void>);

typedef VariableTestMmbrFunc<MmbrFunc14<B, void, void>, void, 
    void(B<void>::*)(), void*> T14Var1Type;

T14Var1Type t14_var1(ToVoidPtr<void(B<void>::*)()>(&B<void>::Foo3));

REGISTER_TEST(t14, new TestMmbrFunc<MmbrFunc14Type, 
    CaseAliasTypeAndPointer, T14Var1Type>(t14_var1));

/**
 * 	template<typename T, typename T1, template<typename> class TTr, 
 *      typename... Targs>
 * 	struct MmbrFunc15
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 * 	    using Type = TTr<T1>(T::*)(Targs...);
 * 	    using type = TTr<T1>(T::*)(Targs...);
 * 	    static constexpr Type Pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 * 	    static constexpr type pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_MMBR_FUNC_T_RET_NAME_TMPL_ARG_LIST_TRNTAL1()\
T1

__DEFINE_MMBR_FUNC_(MmbrFunc15, T, TTr, Targs,, TPL3, T_NAME_,, 
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_,, PTR_,, PTR_RET_,, Foo4);

template<typename T>
using MmbrFunc15Type = MmbrFunc15<T, void, B>;

BASIC_TEST_TYPE_NAME("MmbrFunc15<C, void, B>", MmbrFunc15<C, void, B>);

typedef VariableTestMmbrFunc<MmbrFunc15<C, void, B>, C, 
    B<void>(C::*)(), void*> T15Var1Type;

T15Var1Type t15_var1(ToVoidPtr<B<void>(C::*)()>(&C::Foo4));

REGISTER_TEST(t15, new TestMmbrFunc<MmbrFunc15Type, 
    CaseAliasTypeAndPointer, T15Var1Type>(t15_var1));

/**
 * 	template<typename T, template<typename> class TTr, typename... Targs>
 * 	struct MmbrFunc16
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 *      template<typename T1>
 * 	    using Type = TTr<T1>(T::*)(Targs...);
 *      template<typename T1>
 * 	    using type = TTr<T1>(T::*)(Targs...);
 * 	    static constexpr Type<void> Pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 * 	    static constexpr type<void> pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_FUNC_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_MMBR_FUNC_ALIAS_TYPE_TMPL_PARAM_LIST_ATTPL1()\
typename T1

#define __DEFINE_MMBR_FUNC_PTR_RET_TMPL_ARG_LIST_PRTAL1()\
void

__DEFINE_MMBR_FUNC_(MmbrFunc16, T, TTr, Targs,, TPL4, T_NAME_,, 
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_TMPL_, ATTPL1, PTR_,, 
    PTR_RET_TMPL_, PRTAL1, Foo4);

template<typename T>
using MmbrFunc16Type = MmbrFunc16<T, B>;

BASIC_TEST_TYPE_NAME("MmbrFunc16<C, B>", MmbrFunc16<C, B>);

typedef VariableTestMmbrFunc<MmbrFunc16<C, B>, C, 
    B<void>(C::*)(), void*, void> T16Var1Type;

T16Var1Type t16_var1(ToVoidPtr<B<void>(C::*)()>(&C::Foo4));

REGISTER_TEST(t16, new TestMmbrFunc<MmbrFunc16Type, 
    CaseAliasTypeTmplAndPointer, T16Var1Type>(t16_var1));

/**
 * 	template<typename T, template<typename> class TTr, typename... Targs>
 * 	struct MmbrFunc17
 * 	{
 * 	    static_assert(std::is_same<T, typename basic::type::trait::Simple<T>::type
 * 	        "T is not simple type");
 *      template<typename T1>
 * 	    using Type = TTr<T1>(T::*)(Targs...);
 *      template<typename T1>
 * 	    using type = TTr<T1>(T::*)(Targs...);
 *      template<typename T1>
 * 	    static constexpr Type<T1> Pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 *      template<typename T1>
 * 	    static constexpr type<T1> pointer()
 * 	    {
 * 	        return &T::Foo4;
 * 	    }
 * 	};
 * */

#define __DEFINE_MMBR_FUNC_PTR_TMPL_PARAM_LIST_PTPL1()\
typename T1

__DEFINE_MMBR_FUNC_(MmbrFunc17, T, TTr, Targs,, TPL4, T_NAME_,, 
    T_RET_NAME_TMPL_, TRNTAL1, ALIAS_TYPE_TMPL_, ATTPL1,
    PTR_TMPL_, PTPL1, PTR_RET_TMPL_, PRTAL1, Foo4);

template<typename T>
using MmbrFunc17Type = MmbrFunc17<T, B>;

BASIC_TEST_TYPE_NAME("MmbrFunc17<C, B>", MmbrFunc17<C, B>);

typedef VariableTestMmbrFunc<MmbrFunc17<C, B>, C, 
    B<void>(C::*)(), void*, void> T17Var1Type;

T17Var1Type t17_var1(ToVoidPtr<B<void>(C::*)()>(&C::Foo4));

REGISTER_TEST(t17, new TestMmbrFunc<MmbrFunc17Type, 
    CaseAliasTypeTmplAndPointerTmpl, T17Var1Type>(t17_var1));

int main()
{
    return RUN_TEST();
}
