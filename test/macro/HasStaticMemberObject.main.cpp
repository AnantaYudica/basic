#include "macro/HasStaticMemberObject.h"
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

template<typename THasStaticMmbrObj, typename TAliasVal, TAliasVal AliasValue>
using VariableTestHasStaticMmbrObj = basic::test::Variable<
    THasStaticMmbrObj,
    TAliasVal,  
    basic::test::type::Value<TAliasVal, AliasValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IHasStaticMmbrObj = 0;
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
    ArgTypeName<IHasStaticMmbrObj>,
    ArgTypeName<IAliasVal>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, 
    ArgTypeName<IHasStaticMmbrObj>,
    ArgTypeName<IHasStaticMmbrObj>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IHasStaticMmbrObj>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValAliasValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV, 
    ArgTypeName<IHasStaticMmbrObj>,
    ArgTypeName<IHasStaticMmbrObj>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
class TestHasStaticMmbrObj :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestHasStaticMmbrObj<TCases,
         TVars...>>,
    public basic::test::Case<TestHasStaticMmbrObj<TCases, TVars...>, TCases>,
    public basic::test::Base<TestHasStaticMmbrObj<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestHasStaticMmbrObj<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestHasStaticMmbrObj<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestHasStaticMmbrObj<TCases, TVars...>, 
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
    TestHasStaticMmbrObj(TVars&... vars) :
        BaseType(*this, vars...),
        BaseMessageType(*this),
        BaseCaseType(*this)
    {
        basic::test::msg::base::Info info;
        basic::test::msg::base::Debug debug;
        basic::test::msg::base::Error err;
        
        CaseAVTTa case_alias_value_type_and_target;
        SetFormat(info, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(debug, case_alias_value_type_and_target,
            "Test compare between %s::value_type and %s\n");
        SetFormat(err, case_alias_value_type_and_target,
            "error %s::value_type is not same with %s\n");
            
        CaseAVT case_alias_value_type;
        SetFormat(info, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(debug, case_alias_value_type,
            "Test compare between %s::value_type and "
            "%s::ValueType\n");
        SetFormat(err, case_alias_value_type,
            "error %s::value_type is not same with "
            "%s::ValueType\n");

        CaseVTa case_value_and_target;
        SetFormat(info, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(debug, case_value_and_target,
            "Test compare between %s::value and %s\n");
        SetFormat(err, case_value_and_target,
            "error %s::value is not same with %s\n");

        CaseV case_value;
        SetFormat(info, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(debug, case_value,
            "Test compare between %s::value and "
            "%s::Value\n");
        SetFormat(err, case_value,
            "error %s::value is not same with "
            "%s::Value\n");
    }
    
    template<typename THasStaticMmbrObj, typename TAliasVal, 
        TAliasVal AliasValue>
    bool Result(const CaseAVTTa&, VariableTestHasStaticMmbrObj<
        THasStaticMmbrObj, TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasStaticMmbrObj::value_type).hash_code() ==
            typeid(TAliasVal).hash_code();
    }
    
    template<typename THasStaticMmbrObj, typename TAliasVal, 
        TAliasVal AliasValue>
    bool Result(const CaseAVT&, VariableTestHasStaticMmbrObj<
        THasStaticMmbrObj, TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasStaticMmbrObj::value_type).hash_code() ==
            typeid(typename THasStaticMmbrObj::ValueType).hash_code();
    }
    
    template<typename THasStaticMmbrObj, typename TAliasVal, 
        TAliasVal AliasValue>
    bool Result(const CaseVTa&, VariableTestHasStaticMmbrObj<
        THasStaticMmbrObj, TAliasVal, AliasValue>& var)
    {
        return AliasValue == THasStaticMmbrObj::value;
    }
    
    template<typename THasStaticMmbrObj, typename TAliasVal, 
        TAliasVal AliasValue>
    bool Result(const CaseV&, VariableTestHasStaticMmbrObj<
        THasStaticMmbrObj, TAliasVal, AliasValue>& var)
    {
        return THasStaticMmbrObj::value == THasStaticMmbrObj::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{
    static int Obj1;
};

int A::Obj1;

struct B
{};

template<typename>
struct C
{
    static int Obj2;
};

template<typename T>
int C<T>::Obj2;

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
 *  constexpr auto _HasStaticMmbrObj1(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj1(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj1, _HasStaticMmbrObj1, T,, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasStaticMmbrObj1 = HasStaticMmbrObj1<T>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj1<A>", HasStaticMmbrObj1<A>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj1<B>", HasStaticMmbrObj1<B>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj1<A>, bool, 
    true> T1Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj1<B>, bool, 
    false> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);

REGISTER_TEST(t1, new TestHasStaticMmbrObj<Cases, T1Var1,
    T1Var2>(t1_var1, t1_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasStaticMmbrObj2(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj2(...);
 *  template<typename T, typename T1>
 *  struct HasStaticMmbrObj2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj2, _HasStaticMmbrObj2, T, TPL1, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasStaticMmbrObj2 = HasStaticMmbrObj2<T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj2<A, void>", HasStaticMmbrObj2<A, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj2<B, void>", HasStaticMmbrObj2<B, void>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj2<A>, bool, 
    true> T2Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj2<B>, bool, 
    false> T2Var2;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);

REGISTER_TEST(t2, new TestHasStaticMmbrObj<Cases, T2Var1,
    T2Var2>(t2_var1, t2_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasStaticMmbrObj3(T t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj3(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasStaticMmbrObj3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj3<
 *          typename basic::type::trait::Simple<T<T1>>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj3<
 *          typename basic::type::trait::Simple<T<T1>>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj3, _HasStaticMmbrObj3, T, TPL2,
    T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,, Obj2);

template<typename T>
using THasStaticMmbrObj3 = HasStaticMmbrObj3<C, T>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj3<C, std::true_type>",
    HasStaticMmbrObj3<C, std::true_type>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj3<C, std::false_type>",
    HasStaticMmbrObj3<C, std::false_type>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj3<std::true_type>, bool,
    true> T3Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj3<std::false_type>, bool,
    false> T3Var2;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);

REGISTER_TEST(t3, new TestHasStaticMmbrObj<Cases, T3Var1,
    T3Var2>(t3_var1, t3_var2));

/**
 *  template<typename T, typename T1 = void>
 *  constexpr auto _HasStaticMmbrObj4(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj4(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1 = void

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj4, _HasStaticMmbrObj4, T,,
    T_NAME_,, PFTTPL1,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasStaticMmbrObj4 = HasStaticMmbrObj4<T>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj4<A>", HasStaticMmbrObj4<A>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj4<B>", HasStaticMmbrObj4<B>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj4<A>, bool,
    true> T4Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj4<B>, bool,
    false> T4Var2;

T4Var1 t4_var1(&BoolToString);
T4Var2 t4_var2(&BoolToString);

REGISTER_TEST(t4, new TestHasStaticMmbrObj<Cases, T4Var1,
    T4Var2>(t4_var1, t4_var2));

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasStaticMmbrObj5(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T, typename T1>
 *  constexpr std::false _HasStaticMmbrObj5(...);
 *  template<typename T, typename T1>
 *  struct HasStaticMmbrObj5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj5<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj5<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_NAME_SIMPLE_TYPE__)\
__T_NAME_SIMPLE_TYPE__, T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj5, _HasStaticMmbrObj5, T, TPL1,
    T_NAME_,, PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using THasStaticMmbrObj5 = HasStaticMmbrObj5<T, void>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj5<A, void>", HasStaticMmbrObj5<A, void>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj5<B, void>", HasStaticMmbrObj5<B, void>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj5<A>, bool,
    true> T5Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj5<B>, bool,
    false> T5Var2;

T5Var1 t5_var1(&BoolToString);
T5Var2 t5_var2(&BoolToString);

REGISTER_TEST(t5, new TestHasStaticMmbrObj<Cases, T5Var1,
    T5Var2>(t5_var1, t5_var2));

/**
 *  template<typename T1, template<typename> class T = C>
 *  constexpr auto _HasStaticMmbrObj6(int) -> 
 *      decltype(T<T1>::Obj2, std::true_type());
 *  template<typename T1>
 *  constexpr std::false _HasStaticMmbrObj6(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj6<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj6<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
typename T1, template<typename> class __T_NAME__ = C

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj6, _HasStaticMmbrObj6, T,,
    T_NAME_,, PFTTPL3, PFFTPL2,, PROTO_FUNC_T_NAME_TMPL_, PFTNTAL1,
    Obj2);

template<typename T>
using THasStaticMmbrObj6 = HasStaticMmbrObj6<T>;

BASIC_TEST_TYPE_NAME("HasStaticMmbrObj6<std::true_type>",
    HasStaticMmbrObj6<std::true_type>);
BASIC_TEST_TYPE_NAME("HasStaticMmbrObj6<std::false_type>",
    HasStaticMmbrObj6<std::false_type>);

typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj6<std::true_type>, bool,
    true> T6Var1;
typedef VariableTestHasStaticMmbrObj<THasStaticMmbrObj6<std::false_type>, bool,
    false> T6Var2;

T6Var1 t6_var1(&BoolToString);
T6Var2 t6_var2(&BoolToString);

REGISTER_TEST(t6, new TestHasStaticMmbrObj<Cases, T6Var1,
    T6Var2>(t6_var1, t6_var2));

int main()
{
    return RUN_TEST();
}
