#include "macro/IsBaseOf.h"
#define USING_BASIC_TEST_MEMORY
#define EXPERIMENTAL
#include "Test.h"
BASIC_TEST_CONSTRUCT;

#include "test/Message.h"
#include "test/Variable.h"
#include "test/Case.h"

#include <vector>
#include <type_traits>
#include <typeinfo>

struct CaseAVTTa {}; // case alias value type and target
struct CaseAVT {}; // case alias value type
struct CaseVTa {}; // case value and target
struct CaseV {}; // case value 

template<typename TIsBaseOf, typename TAVT, TAVT TAVTValue>
using VariableTestIsBaseOf = basic::test::Variable<TIsBaseOf,
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
class TestIsBaseOf :
    public MsgBaseCaseAVTTa,
    public MsgBaseCaseAVT,
    public MsgBaseCaseVTa,
    public MsgBaseCaseV,
    public basic::test::Message<BASIC_TEST, TestIsBaseOf<TCases,
         TVars...>>,
    public basic::test::Case<TestIsBaseOf<TCases, TVars...>, TCases>,
    public basic::test::Base<TestIsBaseOf<TCases, TVars...>, TVars...>
{
public:
    typedef basic::test::Base<TestIsBaseOf<TCases, TVars...>, 
        TVars...> BaseType; 
    typedef basic::test::Message<BASIC_TEST, TestIsBaseOf<TCases, 
        TVars...>> BaseMessageType;
    typedef basic::test::Case<TestIsBaseOf<TCases, TVars...>, 
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
    TestIsBaseOf(TVars&... vars) :
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
    
    template<typename TIsBaseOf, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseAVTTa&, VariableTestIsBaseOf<
        TIsBaseOf, TAVT, TAVTValue>& var)
    {
        return typeid(typename TIsBaseOf::value_type).hash_code() ==
            typeid(TAVT).hash_code();
    }
    
    template<typename TIsBaseOf, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseAVT&, VariableTestIsBaseOf<
        TIsBaseOf, TAVT, TAVTValue>& var)
    {
        return typeid(typename TIsBaseOf::value_type).hash_code() ==
            typeid(typename TIsBaseOf::ValueType).hash_code();
    }
    
    template<typename TIsBaseOf, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseVTa&, VariableTestIsBaseOf<
        TIsBaseOf, TAVT, TAVTValue>& var)
    {
        return TAVTValue == TIsBaseOf::value;
    }
    
    template<typename TIsBaseOf, typename TAVT, TAVT TAVTValue>
    bool Result(const CaseV&, VariableTestIsBaseOf<
        TIsBaseOf, TAVT, TAVTValue>& var)
    {
        return TIsBaseOf::value == TIsBaseOf::Value;
    }
};

typedef basic::test::type::Parameter<CaseAVTTa, CaseAVT, 
    CaseVTa, CaseV> Cases;

struct A
{};

struct AA : A {};

struct B {};

struct BB : B {};

template<typename T>
struct C : A {};

template<>
struct C<std::false_type> : B {};

template<typename T>
struct D {};

template<typename>
struct DD : D<std::true_type> {};

template<>
struct DD<std::false_type> : C<std::false_type> {}; 

BASIC_TEST_TYPE_NAME("std::true_type", std::true_type);
BASIC_TEST_TYPE_NAME("std::false_type", std::false_type);
BASIC_TEST_TYPE_NAME("void", void);
BASIC_TEST_TYPE_NAME("bool", bool);

const char* true_cstr = "true";
const char* false_cstr = "false";

/**
 *  template<typename T>
 *  constexpr auto _IsBaseOf1(const A&) ->
 *      std::integral_constant<bool, !std::is_same<T, A>::value>;
 *  template<typename T>
 *  constexpr std::false_type _IsBaseOf1(...);
 *  template<typename T>
 *  struct IsBaseOf1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf1<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf1<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *  };
 * */

__DEFINE_IS_BASE_OF_(IsBaseOf1, _IsBaseOf1, T,, T_NAME_,,,,,
    PROTO_FUNC_T_NAME_,, A);

template<typename T>
using TIsBaseOf1 = IsBaseOf1<T>;

BASIC_TEST_TYPE_NAME("IsBaseOf1<A>", IsBaseOf1<A>);
BASIC_TEST_TYPE_NAME("IsBaseOf1<AA>", IsBaseOf1<AA>);
BASIC_TEST_TYPE_NAME("IsBaseOf1<B>", IsBaseOf1<B>);
BASIC_TEST_TYPE_NAME("IsBaseOf1<BB>", IsBaseOf1<BB>);

typedef VariableTestIsBaseOf<TIsBaseOf1<A>, bool, false> T1Var1;
typedef VariableTestIsBaseOf<TIsBaseOf1<AA>, bool, true> T1Var2;
typedef VariableTestIsBaseOf<TIsBaseOf1<B>, bool, false> T1Var3;
typedef VariableTestIsBaseOf<TIsBaseOf1<BB>, bool, false> T1Var4;

T1Var1 t1_var1(false_cstr);
T1Var2 t1_var2(true_cstr);
T1Var3 t1_var3(false_cstr);
T1Var4 t1_var4(false_cstr);

REGISTER_TEST(t1, new TestIsBaseOf<Cases, T1Var1, T1Var2, T1Var3,
    T1Var4>(t1_var1, t1_var2, t1_var3, t1_var4));

/**
 *  template<typename T>
 *  constexpr auto _IsBaseOf2(const A&) ->
 *      std::integral_constant<bool, !std::is_same<T, A>::value>;
 *  template<typename T>
 *  constexpr std::false_type _IsBaseOf2(...);
 *  template<typename T, typename T1>
 *  struct IsBaseOf2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf2<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf2<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *  };
 * */

#define __DEFINE_IS_BASE_OF_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_IS_BASE_OF_(IsBaseOf2, _IsBaseOf2, T, TPL1, T_NAME_,,,,, 
    PROTO_FUNC_T_NAME_,, A);

template<typename T>
using TIsBaseOf2 = IsBaseOf2<T, void>;

BASIC_TEST_TYPE_NAME("IsBaseOf2<A, void>", IsBaseOf2<A, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf2<AA, void>", IsBaseOf2<AA, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf2<B, void>", IsBaseOf2<B, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf2<BB, void>", IsBaseOf2<BB, void>);

typedef VariableTestIsBaseOf<TIsBaseOf2<A>, bool, false> T2Var1;
typedef VariableTestIsBaseOf<TIsBaseOf2<AA>, bool, true> T2Var2;
typedef VariableTestIsBaseOf<TIsBaseOf2<B>, bool, false> T2Var3;
typedef VariableTestIsBaseOf<TIsBaseOf2<BB>, bool, false> T2Var4;

T2Var1 t2_var1(false_cstr);
T2Var2 t2_var2(true_cstr);
T2Var3 t2_var3(false_cstr);
T2Var4 t2_var4(false_cstr);

REGISTER_TEST(t2, new TestIsBaseOf<Cases, T2Var1, T2Var2, T2Var3,
    T2Var4>(t2_var1, t2_var2, t2_var3, t2_var4));

/**
 *  template<typename T>
 *  constexpr auto _IsBaseOf3(const A&) ->
 *      std::integral_constant<bool, !std::is_same<T, A>::value>;
 *  template<typename T>
 *  constexpr std::false_type _IsBaseOf3(...);
 *  template<template<typename> class T, typename T1>
 *  struct IsBaseOf3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf3<T<T1>>(
 *          std::declval<typename std::remove_cv<T<T1>>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf3<T<T1>>(
 *          std::declval<typename std::remove_cv<T<T1>>::type>()))::value;
 *  };
 * */

#define __DEFINE_IS_BASE_OF_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_IS_BASE_OF_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_IS_BASE_OF_(IsBaseOf3, _IsBaseOf3, T, TPL2, T_NAME_TMPL_, 
    TNTAL1,,,, PROTO_FUNC_T_NAME_,, A);

template<typename T>
using TIsBaseOf3 = IsBaseOf3<C, T>;

BASIC_TEST_TYPE_NAME("IsBaseOf3<C, std::true_type>", 
    IsBaseOf3<C, std::true_type>);
BASIC_TEST_TYPE_NAME("IsBaseOf3<C, std::false_type>",
    IsBaseOf3<C, std::false_type>);

typedef VariableTestIsBaseOf<TIsBaseOf3<std::true_type>, bool, true> T3Var1;
typedef VariableTestIsBaseOf<TIsBaseOf3<std::false_type>, bool, false> T3Var2;

T3Var1 t3_var1(true_cstr);
T3Var2 t3_var2(false_cstr);

REGISTER_TEST(t3, new TestIsBaseOf<Cases, T3Var1, 
    T3Var2>(t3_var1, t3_var2));

/**
 *  template<typename T, typename = void>
 *  constexpr auto _IsBaseOf4(const A&) ->
 *      std::integral_constant<bool, !std::is_same<T, A>::value>;
 *  template<typename T>
 *  constexpr std::false_type _IsBaseOf4(...);
 *  template<typename T>
 *  struct IsBaseOf4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf4<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf4<T>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *  };
 * */

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename = void

__DEFINE_IS_BASE_OF_(IsBaseOf4, _IsBaseOf4, T,, T_NAME_,, PFTTPL1,,,
    PROTO_FUNC_T_NAME_,, A);

template<typename T>
using TIsBaseOf4 = IsBaseOf4<T>;

BASIC_TEST_TYPE_NAME("IsBaseOf4<A>", IsBaseOf4<A>);
BASIC_TEST_TYPE_NAME("IsBaseOf4<AA>", IsBaseOf4<AA>);
BASIC_TEST_TYPE_NAME("IsBaseOf4<B>", IsBaseOf4<B>);
BASIC_TEST_TYPE_NAME("IsBaseOf4<BB>", IsBaseOf4<BB>);

typedef VariableTestIsBaseOf<TIsBaseOf4<A>, bool, false> T4Var1;
typedef VariableTestIsBaseOf<TIsBaseOf4<AA>, bool, true> T4Var2;
typedef VariableTestIsBaseOf<TIsBaseOf4<B>, bool, false> T4Var3;
typedef VariableTestIsBaseOf<TIsBaseOf4<BB>, bool, false> T4Var4;

T4Var1 t4_var1(false_cstr);
T4Var2 t4_var2(true_cstr);
T4Var3 t4_var3(false_cstr);
T4Var4 t4_var4(false_cstr);

REGISTER_TEST(t4, new TestIsBaseOf<Cases, T4Var1, T4Var2, T4Var3,
    T4Var4>(t4_var1, t4_var2, t4_var3, t4_var4));

/**
 *  template<typename T, typename T1>
 *  constexpr auto _IsBaseOf5(const A&) ->
 *      std::integral_constant<bool, !std::is_same<T, A>::value>;
 *  template<typename T, typename T1>
 *  constexpr std::false_type _IsBaseOf5(...);
 *  template<typename T>
 *  struct IsBaseOf5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf5<T, T1>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf5<T, T1>(
 *          std::declval<typename std::remove_cv<T>::type>()))::value;
 *  };
 * */

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_TYPE__, ...)\
__T_TYPE__,##__VA_ARGS__, T1

__DEFINE_IS_BASE_OF_(IsBaseOf5, _IsBaseOf5, T, TPL1, T_NAME_,, 
    PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, A);

template<typename T>
using TIsBaseOf5 = IsBaseOf5<T, void>;

BASIC_TEST_TYPE_NAME("IsBaseOf5<A, void>", IsBaseOf5<A, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf5<AA, void>", IsBaseOf5<AA, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf5<B, void>", IsBaseOf5<B, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf5<BB, void>", IsBaseOf5<BB, void>);

typedef VariableTestIsBaseOf<TIsBaseOf5<A>, bool, false> T5Var1;
typedef VariableTestIsBaseOf<TIsBaseOf5<AA>, bool, true> T5Var2;
typedef VariableTestIsBaseOf<TIsBaseOf5<B>, bool, false> T5Var3;
typedef VariableTestIsBaseOf<TIsBaseOf5<BB>, bool, false> T5Var4;

T5Var1 t5_var1(false_cstr);
T5Var2 t5_var2(true_cstr);
T5Var3 t5_var3(false_cstr);
T5Var4 t5_var4(false_cstr);

REGISTER_TEST(t5, new TestIsBaseOf<Cases, T5Var1, T5Var2, T5Var3,
    T5Var4>(t5_var1, t5_var2, t5_var3, t5_var4));

/**
 *  template<template<typename> class T, typename T1, typename T2>
 *  constexpr auto _IsBaseOf6(const D<T2>&) ->
 *      std::integral_constant<bool, !std::is_same<T<T1>, D<T2>>::value>;
 *  template<template<typename> class T, typename T1>
 *  constexpr std::false_type _IsBaseOf6(...);
 *  template<template<typename> class T, typename T1>
 *  struct IsBaseOf6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_IsBaseOf6<T, T1>(
 *          std::declval<typename std::remove_cv<T<T1>>::type>()))::value;
 *      static constexpr ValueType Value = decltype(_IsBaseOf6<T, T1>(
 *          std::declval<typename std::remove_cv<T<T1>>::type>()))::value;
 *  };
 * */

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1, typename T2

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __T_TYPE__, ...)\
__T_NAME__, T1

#define __DEFINE_IS_BASE_OF_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTL1()\
T1

__DEFINE_IS_BASE_OF_(IsBaseOf6, _IsBaseOf6, T, TPL2, T_NAME_TMPL_, TNTAL1, 
    PFTTPL3, PFFTPL2, PFTAL2, PROTO_FUNC_T_NAME_TMPL_, PFTNTL1, D<T2>);

template<typename T>
using TIsBaseOf6_1 = IsBaseOf6<D, T>;
template<typename T>
using TIsBaseOf6_2 = IsBaseOf6<DD, T>;
template<typename T>
using TIsBaseOf6_3 = IsBaseOf6<C, T>;

BASIC_TEST_TYPE_NAME("IsBaseOf6<D, void>", IsBaseOf6<D, void>);
BASIC_TEST_TYPE_NAME("IsBaseOf6<DD, std::true_type>", 
    IsBaseOf6<DD, std::true_type>);
BASIC_TEST_TYPE_NAME("IsBaseOf6<DD, std::false_type>", 
    IsBaseOf6<DD, std::false_type>);
BASIC_TEST_TYPE_NAME("IsBaseOf6<C, void>", IsBaseOf6<C, void>);

typedef VariableTestIsBaseOf<TIsBaseOf6_1<void>, bool, false> T6Var1;
typedef VariableTestIsBaseOf<TIsBaseOf6_2<std::true_type>, bool, true> T6Var2;
typedef VariableTestIsBaseOf<TIsBaseOf6_2<std::false_type>, bool, 
    false> T6Var3;
typedef VariableTestIsBaseOf<TIsBaseOf6_3<void>, bool, false> T6Var4;

T6Var1 t6_var1(false_cstr);
T6Var2 t6_var2(true_cstr);
T6Var3 t6_var3(false_cstr);
T6Var4 t6_var4(false_cstr);

REGISTER_TEST(t6, new TestIsBaseOf<Cases, T6Var1, T6Var2, T6Var3,
    T6Var4>(t6_var1, t6_var2, t6_var3, t6_var4));

int main()
{
    return RUN_TEST();
}
