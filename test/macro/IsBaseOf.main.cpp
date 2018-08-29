#include "macro/IsBaseOf.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <typeinfo>

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

template<typename T, T TVal>
struct ValueName
{
    static constexpr const char * Value = "undefined"; 
};

#define __DEFINE_VALUE_NAME_(NAME, ...)\
template<>\
struct ValueName<__VA_ARGS__>\
{\
    static constexpr const char * Value = NAME;\
}

template<typename T>
struct Name
{
    static const char * Value;
};

template<typename T>
const char* Name<T>::Value = "undefined"; 

template<typename T, T TVal>
struct Name<ValueName<T, TVal>>
{
    static constexpr const char * Value = ValueName<T, TVal>::Value;
};

#define __DEFINE_NAME_(...)\
template<>\
struct Name<__VA_ARGS__>\
{\
    static constexpr const char * Value = #__VA_ARGS__;\
}

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);

__DEFINE_NAME_(std::true_type);
__DEFINE_NAME_(std::false_type);
__DEFINE_NAME_(void);
__DEFINE_NAME_(bool);

struct BaseTest
{
    virtual ~BaseTest() {};
    virtual void Test() = 0;
};

struct TestRegister
{
    static std::vector<BaseTest*> List;
    BaseTest* m_ptr;
    TestRegister(BaseTest* ptr) :
        m_ptr(ptr)
    {
        List.push_back(m_ptr);
    }
    ~TestRegister()
    {
        delete m_ptr;
    }
};

std::vector<BaseTest*> TestRegister::List;

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Tibo, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Tibo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tibo<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tibo, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Tibo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tibo<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tibo<T>::value_type).hash_code() ==
            typeid(typename Tibo<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tibo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Tibo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Tibo<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Tibo, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Tibo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Tibo<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Tibo<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Tibo<T>::value, Tibo<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Tibo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestIsBaseOf : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tibo, T, Ttavt>();
        TestAliasType<Tibo, T>();
        TestValueAndTargetValue<Tibo, T, Ttavt, TtavtValue, Compare>();
        TestValue<Tibo, T, Ttavt, Compare>();
    };
};

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
using IsBaseOf1_t = IsBaseOf1<T>;

__DEFINE_NAME_(IsBaseOf1<A>);
__DEFINE_NAME_(IsBaseOf1<AA>);
__DEFINE_NAME_(IsBaseOf1<B>);
__DEFINE_NAME_(IsBaseOf1<BB>);

TestRegister t1(new TestIsBaseOf<IsBaseOf1_t, A, bool, false, 
    &BoolCompare>());
TestRegister t2(new TestIsBaseOf<IsBaseOf1_t, AA, bool, true,
    &BoolCompare>());
TestRegister t3(new TestIsBaseOf<IsBaseOf1_t, B, bool, false,
    &BoolCompare>());
TestRegister t4(new TestIsBaseOf<IsBaseOf1_t, BB, bool, false,
    &BoolCompare>());

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
using IsBaseOf2_t = IsBaseOf2<T, void>;

__DEFINE_NAME_(IsBaseOf2<A, void>);
__DEFINE_NAME_(IsBaseOf2<AA, void>);
__DEFINE_NAME_(IsBaseOf2<B, void>);
__DEFINE_NAME_(IsBaseOf2<BB, void>);

TestRegister t5(new TestIsBaseOf<IsBaseOf2_t, A, bool, false, 
    &BoolCompare>());
TestRegister t6(new TestIsBaseOf<IsBaseOf2_t, AA, bool, true,
    &BoolCompare>());
TestRegister t7(new TestIsBaseOf<IsBaseOf2_t, B, bool, false, 
    &BoolCompare>());
TestRegister t8(new TestIsBaseOf<IsBaseOf2_t, BB, bool, false, 
    &BoolCompare>());

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
using IsBaseOf3_t = IsBaseOf3<C, T>;

__DEFINE_NAME_(IsBaseOf3<C, std::true_type>);
__DEFINE_NAME_(IsBaseOf3<C, std::false_type>);

TestRegister t9(new TestIsBaseOf<IsBaseOf3_t, std::true_type, bool, true, 
    &BoolCompare>());
TestRegister t10(new TestIsBaseOf<IsBaseOf3_t, std::false_type, bool, false,
    &BoolCompare>());

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
using IsBaseOf4_t = IsBaseOf4<T>;

__DEFINE_NAME_(IsBaseOf4<A>);
__DEFINE_NAME_(IsBaseOf4<AA>);
__DEFINE_NAME_(IsBaseOf4<B>);
__DEFINE_NAME_(IsBaseOf4<BB>);

TestRegister t11(new TestIsBaseOf<IsBaseOf4_t, A, bool, false, 
    &BoolCompare>());
TestRegister t12(new TestIsBaseOf<IsBaseOf4_t, AA, bool, true,
    &BoolCompare>());
TestRegister t13(new TestIsBaseOf<IsBaseOf4_t, B, bool, false, 
    &BoolCompare>());
TestRegister t14(new TestIsBaseOf<IsBaseOf4_t, BB, bool, false, 
    &BoolCompare>());

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
using IsBaseOf5_t = IsBaseOf5<T, void>;

__DEFINE_NAME_(IsBaseOf5<A, void>);
__DEFINE_NAME_(IsBaseOf5<AA, void>);
__DEFINE_NAME_(IsBaseOf5<B, void>);
__DEFINE_NAME_(IsBaseOf5<BB, void>);

TestRegister t15(new TestIsBaseOf<IsBaseOf5_t, A, bool, false, 
    &BoolCompare>());
TestRegister t16(new TestIsBaseOf<IsBaseOf5_t, AA, bool, true,
    &BoolCompare>());
TestRegister t17(new TestIsBaseOf<IsBaseOf5_t, B, bool, false, 
    &BoolCompare>());
TestRegister t18(new TestIsBaseOf<IsBaseOf5_t, BB, bool, false, 
    &BoolCompare>());

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
using IsBaseOf6_1_t = IsBaseOf6<D, T>;
template<typename T>
using IsBaseOf6_2_t = IsBaseOf6<DD, T>;
template<typename T>
using IsBaseOf6_3_t = IsBaseOf6<C, T>;

__DEFINE_NAME_(IsBaseOf6<D, void>);
__DEFINE_NAME_(IsBaseOf6<DD, std::true_type>);
__DEFINE_NAME_(IsBaseOf6<DD, std::false_type>);
__DEFINE_NAME_(IsBaseOf6<C, void>);

TestRegister t19(new TestIsBaseOf<IsBaseOf6_1_t, void, bool, false,
    &BoolCompare>());
TestRegister t20(new TestIsBaseOf<IsBaseOf6_2_t, std::true_type, bool, true,
    &BoolCompare>());
TestRegister t21(new TestIsBaseOf<IsBaseOf6_2_t, std::false_type, bool, false,
    &BoolCompare>());
TestRegister t22(new TestIsBaseOf<IsBaseOf6_3_t, void, bool, false,
    &BoolCompare>());

int main()
{
    Info("BeginTest:\n");
    
    for (auto t : TestRegister::List)
    {
        t->Test();
    }
    Info("EndTest:");
    return  ResultStatus;
}
