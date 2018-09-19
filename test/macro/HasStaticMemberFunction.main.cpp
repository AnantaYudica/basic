#include "macro/HasStaticMemberFunction.h"
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

struct CaseAVTTa {}; // case alias value type and target
struct CaseAVT {}; // case alias value type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value 

template<typename THasStaticMmbrFunc, typename TAVT, TAVT TAVTValue>
using VariableTestHasStaticMmbrFunc = basic::test::Variable<THasStaticMmbrFunc,
    TAVT,  basic::test::type::Value<TAVT, TAVTValue>,
    basic::test::var::Value<const char*>>;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgVarValue = basic::test::msg::arg::var::Value<I>;

typedef basic::test::msg::Argument<CaseAVTTa, ArgTypeName<0>,
    ArgTypeName<1>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, ArgTypeName<0>,
    ArgTypeName<0>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, ArgTypeName<0>,
    ArgVarValue<3>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, ArgTypeName<0>,
    ArgTypeName<0>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestHasStaticMmbrFunc :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestHasStaticMmbrFunc<TCases,
         TVars...>>,
    public basic::test::Case<TestHasStaticMmbrFunc<TCases, TVars...>, TCases>,
    public basic::test::Base<TestHasStaticMmbrFunc<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestHasStaticMmbrFunc<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestHasStaticMmbrFunc<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestHasStaticMmbrFunc<TCases, TVars...>, 
        TCases> BaseCaseType;
protected:
    using MsgBaseCaseAVTTa::SetFormat;
    using MsgBaseCaseAVT::SetFormat;
    using MsgBaseCaseVTa::SetFormat;
    using MsgBaseCaseV::SetFormat;
public:
    using MsgBaseCaseAVTTa::Format;
    using MsgBaseCaseAVT::Format;
    using MsgBaseCaseVTa::Format;
    using MsgBaseCaseV::Format;
    using MsgBaseCaseAVTTa::Argument;
    using MsgBaseCaseAVT::Argument;
    using MsgBaseCaseVTa::Argument;
    using MsgBaseCaseV::Argument;
public:
    using BaseType::Run;
    using BaseCaseType::Run;
public:
    TestHasStaticMmbrFunc(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error error;
        
        CaseAVTTa case_alias_value_type_and_target;
        SetFormat(info, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(debug, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(error, case_alias_value_type_and_target,
            "error %s::value_type is not same with %s\n");
            
        CaseAVT case_alias_value_type;
        SetFormat(info, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(debug, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(error, case_alias_value_type,
            "error %s::value_type is not same with "
            "%s::ValueType\n");

        CaseVTa case_value_and_target;
        SetFormat(info, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(debug, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(error, case_value_and_target,
            "error %s::value is not same with %s\n");

        CaseV case_value;
        SetFormat(info, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(debug, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(error, case_value,
            "error %s::value is not same with "
            "%s::Value\n");
    }
    
    template<typename THasStaticMmbrFunc, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseAVTTa&, VariableTestHasStaticMmbrFunc<
        THasStaticMmbrFunc, TAVT, TAVTValue>& var)
    {
        return typeid(typename THasStaticMmbrFunc::value_type).hash_code() ==
            typeid(TAVT).hash_code();
    }
    
    template<typename THasStaticMmbrFunc, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseAVT&, VariableTestHasStaticMmbrFunc<
        THasStaticMmbrFunc, TAVT, TAVTValue>& var)
    {
        return typeid(typename THasStaticMmbrFunc::value_type).hash_code() ==
            typeid(typename THasStaticMmbrFunc::ValueType).hash_code();
    }
    
    template<typename THasStaticMmbrFunc, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseVTa&, VariableTestHasStaticMmbrFunc<
        THasStaticMmbrFunc, TAVT, TAVTValue>& var)
    {
        return TAVTValue == THasStaticMmbrFunc::value;
    }
    
    template<typename THasStaticMmbrFunc, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseV&, VariableTestHasStaticMmbrFunc<
        THasStaticMmbrFunc, TAVT, TAVTValue>& var)
    {
        return THasStaticMmbrFunc::value == THasStaticMmbrFunc::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{
    static void Foo1() {}
    template<typename>
    static void Foo2() {}
};

struct B
{};

template<typename>
struct C
{
    static void Foo1() {}
};

template<>
struct C<std::false_type>
{};

struct D
{
    template<typename T>
    static C<T> Foo3() {return C<T>();}
};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("B", B);
BASIC_TEST_TYPE_NAME("C<std::true_type>", C<std::true_type>);
BASIC_TEST_TYPE_NAME("C<std::false_type>", C<std::false_type>);

const char* true_cstr = "true";
const char* false_cstr = "false";

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc1(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc1<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc1<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc1, _HasStaticMmbrFunc1, T, Tr, 
    Targs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasStaticMmbrFunc1 = HasStaticMmbrFunc1<T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc1<A, void>",
    HasStaticMmbrFunc1<A, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc1<B, void>",
    HasStaticMmbrFunc1<B, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc1<A>, bool, 
    true> T1Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc1<B>, bool, 
    false> T1Var2;

T1Var1 t1_var1(true_cstr);
T1Var2 t1_var2(false_cstr);

REGISTER_TEST(t1, new TestHasStaticMmbrFunc<Cases, T1Var1,
    T1Var2>(t1_var1, t1_var2));

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc2(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc2(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc2<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc2<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc2, _HasStaticMmbrFunc2, T, Tr, 
    Targs, TPL1, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Foo1);

template<typename T>
using THasStaticMmbrFunc2 = HasStaticMmbrFunc2<T, void, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc2<A, void, void>",
    HasStaticMmbrFunc2<A, void, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc2<B, void, void>",
    HasStaticMmbrFunc2<B, void, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc2<A>, bool, 
    true> T2Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc2<B>, bool, 
    false> T2Var2;

T2Var1 t2_var1(true_cstr);
T2Var2 t2_var2(false_cstr);

REGISTER_TEST(t2, new TestHasStaticMmbrFunc<Cases, T2Var1, 
    T2Var2>(t2_var1, t2_var2));

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc3(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc3(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *          typename basic::type::trait::Simple<T<T1>>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *          typename basic::type::trait::Simple<T<T1>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc3, _HasStaticMmbrFunc3, T, Tr, 
    Targs, TPL2, T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasStaticMmbrFunc3 = HasStaticMmbrFunc3<C, T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc3<C, std::true_type, void>",
    HasStaticMmbrFunc3<C, std::true_type, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc3<C, std::false_type, void>",
    HasStaticMmbrFunc3<C, std::false_type, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc3<std::true_type>, 
    bool, true> T3Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc3<std::false_type>, 
    bool, false> T3Var2;

T3Var1 t3_var1(true_cstr);
T3Var2 t3_var2(false_cstr);

REGISTER_TEST(t3, new TestHasStaticMmbrFunc<Cases, T3Var1,
    T3Var2>(t3_var1, t3_var2));

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc4(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME_SIMPLE_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc4, _HasStaticMmbrFunc4, T, Tr, 
    Targs, TPL1, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasStaticMmbrFunc4 = HasStaticMmbrFunc4<T, void, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc4<A, void, void>",
    HasStaticMmbrFunc4<A, void, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc4<B, void, void>",
    HasStaticMmbrFunc4<B, void, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc4<A>, bool, 
    true> T4Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc4<B>, bool, 
    false> T4Var2;

T4Var1 t4_var1(true_cstr);
T4Var2 t4_var2(false_cstr);

REGISTER_TEST(t4, new TestHasStaticMmbrFunc<Cases, T4Var1,
    T4Var2>(t4_var1, t4_var2));

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(t.template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc5(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, void, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, void, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME_SIMPLE_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc5, _HasStaticMmbrFunc5, T, Tr, 
    Targs,, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL2, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, template Foo2<T1>);

template<typename T>
using THasStaticMmbrFunc5 = HasStaticMmbrFunc5<T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc5<A, void>",
    HasStaticMmbrFunc5<A, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc5<B, void>",
    HasStaticMmbrFunc5<B, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc5<A>, bool, 
    true> T5Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc5<B>, bool, 
    false> T5Var2;

T5Var1 t5_var1(true_cstr);
T5Var2 t5_var2(false_cstr);

REGISTER_TEST(t5, new TestHasStaticMmbrFunc<Cases, T5Var1,
    T5Var2>(t5_var1, t5_var2));

/**
 *  template<typename T1, typename Tr, typename... Targs,
 *      template<typename> class T = C>
 *  constexpr auto _HasStaticMmbrFunc6(int, Targs... args) ->
 *      decltype(Tr(T<T1>::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc6(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc6<
 *                  T, Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc6<
 *              T, Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 typename T1, typename __T_RET_NAME__, typename... __T_ARGS_NAME__,\
    template<typename> class __T_NAME__ = C

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_FTNTAL1()\
T1

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc6, _HasStaticMmbrFunc6, T, Tr, 
    Targs,, T_NAME_,, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, FTNTAL1,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using THasStaticMmbrFunc6 = HasStaticMmbrFunc6<T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc6<std::true_type, void>",
    HasStaticMmbrFunc6<std::true_type, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc6<std::false_type, void>",
    HasStaticMmbrFunc6<std::false_type, void>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc6<std::true_type>, 
    bool, true> T6Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc6<std::false_type>, 
    bool, false> T6Var2;

T6Var1 t6_var1(true_cstr);
T6Var2 t6_var2(false_cstr);

REGISTER_TEST(t6, new TestHasStaticMmbrFunc<Cases, T6Var1,
    T6Var2>(t6_var1, t6_var2));

/**
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc7(int, Targs... args) ->
 *      decltype(Tr<T1>(T::template Foo3<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc7(...);
 *  template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 *  struct HasStaticMmbrFunc7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc7<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc7<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNRAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc7, _HasStaticMmbrFunc7, T, Tr, 
    Targs, TPL3, T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNRAL1, template Foo3<T1>);

template<typename T>
using THasStaticMmbrFunc7 = HasStaticMmbrFunc7<T, void, C>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc7<D, void, C>",
    HasStaticMmbrFunc7<D, void, C>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrFunc7<B, void, C>",
    HasStaticMmbrFunc7<B, void, C>);

typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc7<D>, bool, 
    true> T7Var1;
typedef VariableTestHasStaticMmbrFunc<THasStaticMmbrFunc7<B>, bool, 
    false> T7Var2;

T7Var1 t7_var1(true_cstr);
T7Var2 t7_var2(false_cstr);

REGISTER_TEST(t7, new TestHasStaticMmbrFunc<Cases, T7Var1,
    T7Var2>(t7_var1, t7_var2));

int main()
{
    return RUN_TEST();
}
