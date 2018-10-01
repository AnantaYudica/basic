#include "macro/HasMemberObject.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>
#include <typeinfo>

struct CaseAVTTa {}; // case alias value type and target
struct CaseAVT {}; // case alias value type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value 

template<typename THasMmbrObj, typename TAliasVal, TAliasVal AliasValue>
using VariableTestHasMmbrObj = basic::test::Variable<
    THasMmbrObj,
    TAliasVal,  
    basic::test::type::Value<TAliasVal, AliasValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IHasMmbrObj = 0;
constexpr std::size_t IAliasVal = 1;
constexpr std::size_t ITypeValAliasValue = 2;
constexpr std::size_t IValFuncBoolToCString = 3;

template<std::size_t I>
using ArgTypeName = basic::test::msg::arg::type::Name<I>;

template<std::size_t I>
using ArgTypeValue = basic::test::msg::arg::type::Value<I>;

template<std::size_t I>
using ArgTypeParamName = basic::test::msg::arg::type::param::Name<I>;

template<std::size_t I>
using ArgValue = basic::test::msg::arg::Value<I>;

template<std::size_t I, typename... TArgArgs>
using ArgValFunction = basic::test::msg::arg::val::Function<I, TArgArgs...>;

typedef basic::test::msg::Argument<CaseAVTTa, 
    ArgTypeName<IHasMmbrObj>,
    ArgTypeName<IAliasVal>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, 
    ArgTypeName<IHasMmbrObj>,
    ArgTypeName<IHasMmbrObj>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IHasMmbrObj>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValAliasValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IHasMmbrObj>,
    ArgTypeName<IHasMmbrObj>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestHasMmbrObj :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestHasMmbrObj<TCases, TVars...>>,
    public basic::test::Case<TestHasMmbrObj<TCases, TVars...>, TCases>,
    public basic::test::Base<TestHasMmbrObj<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestHasMmbrObj<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestHasMmbrObj<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestHasMmbrObj<TCases, TVars...>, 
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
    TestHasMmbrObj(TVars&... vars) :
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
    
    template<typename THasMmbrObj, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVTTa&, VariableTestHasMmbrObj<THasMmbrObj, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrObj::value_type).hash_code() ==
            typeid(TAliasVal).hash_code();
    }
    
    template<typename THasMmbrObj, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVT&, VariableTestHasMmbrObj<THasMmbrObj, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrObj::value_type).hash_code() ==
            typeid(typename THasMmbrObj::ValueType).hash_code();
    }
    
    template<typename THasMmbrObj, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseVTa&, VariableTestHasMmbrObj<THasMmbrObj, 
        TAliasVal, AliasValue>& var)
    {
        return AliasValue == THasMmbrObj::value;
    }
    
    template<typename THasMmbrObj, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseV&, VariableTestHasMmbrObj<THasMmbrObj, 
        TAliasVal, AliasValue>& var)
    {
        return THasMmbrObj::value == THasMmbrObj::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{
    int Obj1;
};

struct B
{};

template<typename>
struct C
{
    int Obj2;
};

template<>
struct C<std::false_type>
{};

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);
BASIC_TEST_TYPE_NAME("A", A);
BASIC_TEST_TYPE_NAME("B", B);

const char* true_cstr = "true";
const char* false_cstr = "false";

const char* BoolToString(bool&& b)
{
    return b ? true_cstr : false_cstr;
}

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj1(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj1(...);
 *  template<typename T>
 *  struct HasMmbrObj1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj1, _HasMmbrObj1, T,, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasMmbrObj1 = HasMmbrObj1<T>;

BASIC_TEST_TYPE_NAME("HasMmbrObj1<A>", HasMmbrObj1<A>);
BASIC_TEST_TYPE_NAME("HasMmbrObj1<B>", HasMmbrObj1<B>);

typedef VariableTestHasMmbrObj<THasMmbrObj1<A>, bool, true> T1Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj1<B>, bool, false> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);

REGISTER_TEST(t1, new TestHasMmbrObj<Cases, T1Var1, 
    T1Var2>(t1_var1, t1_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj2(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj2(...);
 *  template<typename T, typename T1>
 *  struct HasMmbrObj2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj2, _HasMmbrObj2, T, TPL1, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasMmbrObj2 = HasMmbrObj2<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrObj2<A, void>", HasMmbrObj2<A, void>);
BASIC_TEST_TYPE_NAME("HasMmbrObj2<B, void>", HasMmbrObj2<B, void>);

typedef VariableTestHasMmbrObj<THasMmbrObj2<A>, bool, true> T2Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj2<B>, bool, false> T2Var2;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);

REGISTER_TEST(t2, new TestHasMmbrObj<Cases, T2Var1,
    T2Var2>(t2_var1, t2_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrObj3(T t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj3(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasMmbrObj3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj3, _HasMmbrObj3, T, TPL2, T_NAME_TMPL_, 
    TNTAL1,,,, PROTO_FUNC_T_NAME_,, Obj2);

template<typename T>
using THasMmbrObj3 = HasMmbrObj3<C, T>;

BASIC_TEST_TYPE_NAME("HasMmbrObj3<C, std::true_type>",
    HasMmbrObj3<C, std::true_type>);
BASIC_TEST_TYPE_NAME("HasMmbrObj3<C, std::false_type",
    HasMmbrObj3<C, std::false_type>);

typedef VariableTestHasMmbrObj<THasMmbrObj3<std::true_type>, bool, 
    true> T3Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj3<std::false_type>, bool,
    false> T3Var2;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);

REGISTER_TEST(t3, new TestHasMmbrObj<Cases, T3Var1, 
    T3Var2>(t3_var1, t3_var2));

/**
 *  template<typename T, typename T1 = void>
 *  constexpr auto _HasMmbrObj4(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrObj4(...);
 *  template<typename T>
 *  struct HasMmbrObj4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1 = void

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj4, _HasMmbrObj4, T,, T_NAME_,,
    PFTTPL1,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasMmbrObj4 = HasMmbrObj4<T>;

BASIC_TEST_TYPE_NAME("HasMmbrObj4<A>", HasMmbrObj4<A>);
BASIC_TEST_TYPE_NAME("HasMmbrObj4<B>", HasMmbrObj4<B>);

typedef VariableTestHasMmbrObj<THasMmbrObj4<A>, bool, true> T4Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj4<B>, bool, false> T4Var2;

T4Var1 t4_var1(&BoolToString);
T4Var2 t4_var2(&BoolToString);

REGISTER_TEST(t4, new TestHasMmbrObj<Cases, T4Var1,
    T4Var2>(t4_var1, t4_var2));

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasMmbrObj5(T t) -> 
 *      decltype(t.Obj1, std::true_type());
 *  template<typename T, typename T1>
 *  constexpr std::false _HasMmbrObj5(...);
 *  template<typename T, typename T1>
 *  struct HasMmbrObj5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type, T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type, T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__,...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj5, _HasMmbrObj5, T, TPL1, T_NAME_,,
    PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasMmbrObj5 = HasMmbrObj5<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrObj5<A, void>", HasMmbrObj5<A, void>);
BASIC_TEST_TYPE_NAME("HasMmbrObj5<B, void>", HasMmbrObj5<B, void>);

typedef VariableTestHasMmbrObj<THasMmbrObj5<A>, bool, true> T5Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj5<B>, bool, false> T5Var2;

T5Var1 t5_var1(&BoolToString);
T5Var2 t5_var2(&BoolToString);

REGISTER_TEST(t5, new TestHasMmbrObj<Cases, T5Var1, 
    T5Var2>(t5_var1, t5_var2));

/**
 *  template<template<typename> class T, typename T1>
 *  constexpr auto _HasMmbrObj6(T<T1> t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<template<typename> class T>
 *  constexpr std::false _HasMmbrObj6(...);
 *  template<typename T, template<typename> class T1>
 *  struct HasMmbrObj6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrObj6<T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_HasMmbrObj6<T1>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>()))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_OBJ_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__)\
typename __T_NAME__, template<typename> class T1 

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__,...)\
T1

#define __DEFINE_HAS_MMBR_OBJ_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

__DEFINE_HAS_MMBR_OBJ_(HasMmbrObj6, _HasMmbrObj6, T, TPL3, T_NAME_,,
    PFTTPL3, PFFTPL2, PFTAL2, PROTO_FUNC_T_NAME_TMPL_, PFTNTAL1, Obj2);

template<typename T>
using THasMmbrObj6 = HasMmbrObj6<C<T>, C>;

BASIC_TEST_TYPE_NAME("HasMmbrObj6<C<std::true_type>, C>",
    HasMmbrObj6<C<std::true_type>, C>);
BASIC_TEST_TYPE_NAME("HasMmbrObj6<C<std::false_type>, C>",
    HasMmbrObj6<C<std::false_type>, C>);

typedef VariableTestHasMmbrObj<THasMmbrObj6<std::true_type>, bool, 
    true> T6Var1;
typedef VariableTestHasMmbrObj<THasMmbrObj6<std::false_type>, bool,
    false> T6Var2;

T6Var1 t6_var1(&BoolToString);
T6Var2 t6_var2(&BoolToString);

REGISTER_TEST(t6, new TestHasMmbrObj<Cases, T6Var1, 
    T6Var2>(t6_var1, t6_var2));

int main()
{
    return RUN_TEST();
}
