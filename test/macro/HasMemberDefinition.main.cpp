#include "macro/HasMemberDefinition.h"
#define USING_BASIC_TEST_MEMORY
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Base.h"
#include "test/Case.h"
#include "test/Message.h"
#include "test/Variable.h"

#include "test/var/At.h"

#include <type_traits>

struct CaseAVTTa {}; // case alias value type and target
struct CaseAVT {}; // case alias value type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value

template<typename THasMmbrDefn, typename TAliasVal, TAliasVal AliasValue>
using VariableTestHasMmbrDefn = basic::test::Variable<
    THasMmbrDefn,
    TAliasVal,  
    basic::test::type::Value<TAliasVal, AliasValue>,
    basic::test::val::Function<const char*(bool&&)>>;

constexpr std::size_t IHasMmbrDefn = 0;
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
    ArgTypeName<IHasMmbrDefn>,
    ArgTypeName<IAliasVal>> ArgCaseAVTTa;

typedef basic::test::msg::Base<CaseAVTTa, char, ArgCaseAVTTa, 
    ArgCaseAVTTa, ArgCaseAVTTa> MsgBaseCaseAVTTa;

typedef basic::test::msg::Argument<CaseAVT, 
    ArgTypeName<IHasMmbrDefn>,
    ArgTypeName<IHasMmbrDefn>> ArgCaseAVT;

typedef basic::test::msg::Base<CaseAVT, char, ArgCaseAVT, 
    ArgCaseAVT, ArgCaseAVT> MsgBaseCaseAVT;

typedef basic::test::msg::Argument<CaseVTa, 
    ArgTypeName<IHasMmbrDefn>,
    ArgValFunction<IValFuncBoolToCString,
        ArgTypeValue<ITypeValAliasValue>>> ArgCaseVTa;

typedef basic::test::msg::Base<CaseVTa, char, ArgCaseVTa, 
    ArgCaseVTa, ArgCaseVTa> MsgBaseCaseVTa;

typedef basic::test::msg::Argument<CaseV,
    ArgTypeName<IHasMmbrDefn>,
    ArgTypeName<IHasMmbrDefn>> ArgCaseV;

typedef basic::test::msg::Base<CaseV, char, ArgCaseV, 
    ArgCaseV, ArgCaseV> MsgBaseCaseV;

template<typename TCases, typename... TVars>
struct TestHasMmbrDefn :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestHasMmbrDefn<TCases, TVars...>>,
    public basic::test::Case<TestHasMmbrDefn<TCases, TVars...>, TCases>,
    public basic::test::Base<TestHasMmbrDefn<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestHasMmbrDefn<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestHasMmbrDefn<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestHasMmbrDefn<TCases, TVars...>, 
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
    TestHasMmbrDefn(TVars&... vars) :
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

    template<typename THasMmbrDefn, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVTTa&, VariableTestHasMmbrDefn<THasMmbrDefn, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrDefn::value_type).hash_code() ==
            typeid(TAliasVal).hash_code();
    }

    template<typename THasMmbrDefn, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseAVT&, VariableTestHasMmbrDefn<THasMmbrDefn, 
        TAliasVal, AliasValue>& var)
    {
        return typeid(typename THasMmbrDefn::value_type).hash_code() ==
            typeid(typename THasMmbrDefn::ValueType).hash_code();
    }

    template<typename THasMmbrDefn, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseVTa&, VariableTestHasMmbrDefn<THasMmbrDefn, 
        TAliasVal, AliasValue>& var)
    {
        return AliasValue == THasMmbrDefn::value;
    }
    
    template<typename THasMmbrDefn, typename TAliasVal, TAliasVal AliasValue>
    bool Result(const CaseV&, VariableTestHasMmbrDefn<THasMmbrDefn, 
        TAliasVal, AliasValue>& var)
    {
        return THasMmbrDefn::value == THasMmbrDefn::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{
    typedef void Type1;
};

struct B
{};

template<typename>
struct C
{
    typedef void Type2;
};

template<>
struct C<std::false_type>
{};

struct D
{
    template<typename T>
    using Type3 = C<T>;
};


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
 *  constexpr auto _HasMmbrDefn1(int) -> 
 *      decltype(std::declval<typename T::Type1>(), std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrDefn1(...);
 *  template<typename T>
 *  struct HasMmbrDefn1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn1, _HasMmbrDefn1, T,, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Type1);

template<typename T>
using THasMmbrDefn1 = HasMmbrDefn1<T>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn1<A>", HasMmbrDefn1<A>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn1<B>", HasMmbrDefn1<B>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn1<A>, bool, true> T1Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn1<B>, bool, false> T1Var2;

T1Var1 t1_var1(&BoolToString);
T1Var2 t1_var2(&BoolToString);

REGISTER_TEST(t1, new TestHasMmbrDefn<Cases, T1Var1, 
    T1Var2>(t1_var1, t1_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrDefn2(int) -> 
 *      decltype(std::declval<typename T::Type1>(), std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrDefn2(...);
 *  template<typename T, typename>
 *  struct HasMmbrDefn2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn2, _HasMmbrDefn2, T, TPL1, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Type1);

template<typename T>
using THasMmbrDefn2 = HasMmbrDefn2<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn2<A, void>", HasMmbrDefn2<A, void>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn2<B, void>", HasMmbrDefn2<B, void>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn2<A>, bool, true> T2Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn2<B>, bool, false> T2Var2;

T2Var1 t2_var1(&BoolToString);
T2Var2 t2_var2(&BoolToString);

REGISTER_TEST(t2, new TestHasMmbrDefn<Cases, T2Var1, 
    T2Var2>(t2_var1, t2_var2));

/**
 *  template<typename T>
 *  constexpr auto _HasMmbrDefn3(int) -> 
 *      decltype(std::declval<typename T::Type1>(), std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrDefn3(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasMmbrDefn3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn3<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn3<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_T_NAME_TMPL_ARG_LIST_TNTAL()\
T1

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn3, _HasMmbrDefn3, T, TPL2, 
    T_NAME_TMPL_, TNTAL,,,, PROTO_FUNC_T_NAME_,, Type2);

template<typename T>
using THasMmbrDefn3 = HasMmbrDefn3<C, T>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn3<C, std::true_type>",
    HasMmbrDefn3<C, std::true_type>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn3<C, std::false_type>",
    HasMmbrDefn3<C, std::false_type>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn3<std::true_type>, 
    bool, true> T3Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn3<std::false_type>,
    bool, false> T3Var2;

T3Var1 t3_var1(&BoolToString);
T3Var2 t3_var2(&BoolToString);

REGISTER_TEST(t3, new TestHasMmbrDefn<Cases, T3Var1,
    T3Var2>(t3_var1, t3_var2));

/**
 *  template<typename T, typename T1 = void>
 *  constexpr auto _HasMmbrDefn4(int) -> 
 *      decltype(std::declval<typename T::Type1>(), std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasMmbrDefn4(...);
 *  template<typename T>
 *  struct HasMmbrDefn4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename = void

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn4, _HasMmbrDefn4, T,, 
    T_NAME_,, PFTTPL1,,, PROTO_FUNC_T_NAME_,, Type1);

template<typename T>
using THasMmbrDefn4 = HasMmbrDefn4<T>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn4<A>", HasMmbrDefn4<A>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn4<B>", HasMmbrDefn4<B>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn4<A>, bool, true> T4Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn4<B>, bool, false> T4Var2;

T4Var1 t4_var1(&BoolToString);
T4Var2 t4_var2(&BoolToString);

REGISTER_TEST(t4, new TestHasMmbrDefn<Cases, T4Var1, 
    T4Var2>(t4_var1, t4_var2));

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasMmbrDefn5(int) -> 
 *      decltype(std::declval<typename T::Type1>(), std::true_type());
 *  template<typename T, typename T1>
 *  constexpr std::false _HasMmbrDefn5(...);
 *  template<typename T>
 *  struct HasMmbrDefn5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn5<
 *          typename basic::type::trait::Simple<T>::type, void>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn5<
 *          typename basic::type::trait::Simple<T>::type, void>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __SIMPLE_T_TYPE__, ...)\
__SIMPLE_T_TYPE__,##__VA_ARGS__, void

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn5, _HasMmbrDefn5, T,, 
    T_NAME_,, PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, Type1);

template<typename T>
using THasMmbrDefn5 = HasMmbrDefn5<T>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn5<A>", HasMmbrDefn5<A>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn5<B>", HasMmbrDefn5<B>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn5<A>, bool, true> T5Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn5<B>, bool, false> T5Var2;

T5Var1 t5_var1(&BoolToString);
T5Var2 t5_var2(&BoolToString);

REGISTER_TEST(t5, new TestHasMmbrDefn<Cases, T5Var1,
    T5Var2>(t5_var1, t5_var2));

/**
 *  template<template<typename> class T, typename T1>
 *  constexpr auto _HasMmbrDefn6(int) -> 
 *      decltype(std::declval<typename T<T1>::Type2>(), std::true_type());
 *  template<template<typename> class T, typename T1>
 *  constexpr std::false _HasMmbrDefn6(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasMmbrDefn6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn6<
 *          T, T1>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn6<
 *          T, T1>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __SIMPLE_T_TYPE__, ...)\
__T_NAME__, T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn6, _HasMmbrDefn6, T, TPL2, 
    T_NAME_,, PFTTPL3, PFFTPL2, PFTAL2, PROTO_FUNC_T_NAME_TMPL_, 
    PFTNTAL1, Type2);

template<typename T>
using THasMmbrDefn6 = HasMmbrDefn6<C, T>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn6<C, std::true_type>",
    HasMmbrDefn6<C, std::true_type>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn6<C, std::false_type>",
    HasMmbrDefn6<C, std::false_type>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn6<std::true_type>, 
    bool, true> T6Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn6<std::false_type>, 
    bool, false> T6Var2;

T6Var1 t6_var1(&BoolToString);
T6Var2 t6_var2(&BoolToString);

REGISTER_TEST(t6, new TestHasMmbrDefn<Cases, T6Var1, 
    T6Var2>(t6_var1, t6_var2));

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasMmbrDefn7(int) -> 
 *      decltype(std::declval<typename T::template Type3<T1>>(), std::true_type());
 *  template<typename  T, typename T1>
 *  constexpr std::false _HasMmbrDefn7(...);
 *  template<typename T, typename T1>
 *  struct HasMmbrDefn7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasMmbrDefn7<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *      static constexpr ValueType Value =  decltype(_HasMmbrDefn7<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_DEFN_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_MMBR_DEFN_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__,\
    __SIMPLE_T_TYPE__, ...)\
__SIMPLE_T_TYPE__,##__VA_ARGS__, T1

__DEFINE_HAS_MMBR_DEFN_(HasMmbrDefn7, _HasMmbrDefn7, T, TPL3, 
    T_NAME_,, PFTTPL2, PFFTPL1, PFTAL2, PROTO_FUNC_T_NAME_,, template Type3<T1>);

template<typename T>
using THasMmbrDefn7 = HasMmbrDefn7<T, void>;

BASIC_TEST_TYPE_NAME("HasMmbrDefn7<D, void>", HasMmbrDefn7<D, void>);
BASIC_TEST_TYPE_NAME("HasMmbrDefn7<B, void>", HasMmbrDefn7<B, void>);

typedef VariableTestHasMmbrDefn<THasMmbrDefn7<D>, bool, true> T7Var1;
typedef VariableTestHasMmbrDefn<THasMmbrDefn7<B>, bool, false> T7Var2;

T7Var1 t7_var1(&BoolToString);
T7Var2 t7_var2(&BoolToString);

REGISTER_TEST(t7, new TestHasMmbrDefn<Cases, T7Var1, 
    T7Var2>(t7_var1, t7_var2));

int main()
{
    return RUN_TEST();
}
