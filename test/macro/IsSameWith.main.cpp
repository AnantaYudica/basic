#include "macro/IsSameWith.h"
#include "Test.h"

BasicTestConstruct;

#include <vector>
#include <type_traits>
#include <typeinfo>

struct A
{};

struct B
{};

template<typename>
struct C
{};

template<typename>
struct D
{};

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

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Tis, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Tis<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tis<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tis, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Tis<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tis<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Tis<T>::value_type).hash_code() ==
            typeid(typename Tis<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Tis, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Tis<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Tis<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Tis, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Tis<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Tis<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Tis<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Tis<T>::value, Tis<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Tis, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestIsSame : basic::test::Base
{
    void Test() 
    {
        TestAliasTypeAndTarget<Tis, T, Ttavt>();
        TestAliasType<Tis, T>();
        TestValueAndTargetValue<Tis, T, Ttavt, TtavtValue, Compare>();
        TestValue<Tis, T, Ttavt, Compare>();
    };
};

/**
 *  template<T> 
 *  struct IsSame1
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<>
 *  struct IsSame1<A>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

__DEFINE_IS_SAME_WITH_(IsSame1, T,,, A);

template<typename T>
using IsSame1_t = IsSame1<T>;

__DEFINE_NAME_(IsSame1<A>);
__DEFINE_NAME_(IsSame1<B>);

RegisterTest(t1, new TestIsSame<IsSame1_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t2, new TestIsSame<IsSame1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename = void> 
 *  struct IsSame2
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<>
 *  struct IsSame2<A>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

#define __DEFINE_IS_SAME_WITH_TMPL_PARAM_LIST_PRIMARY_TPLP1(\
    __T_NAME__)\
typename __T_NAME__, typename = void

__DEFINE_IS_SAME_WITH_(IsSame2, T, TPLP1,, A);

template<typename T>
using IsSame2_t = IsSame2<T>;

__DEFINE_NAME_(IsSame2<A>);
__DEFINE_NAME_(IsSame2<B>);

RegisterTest(t3, new TestIsSame<IsSame2_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t4, new TestIsSame<IsSame2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T> 
 *  struct IsSame3
 *  { 
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = false;
 *      static constexpr ValueType Value = false;
 *  };
 *  template<typename T1>
 *  struct IsSame3<C<T1>>
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = true;
 *      static constexpr ValueType Value = true;
 *  }
 * */

#define __DEFINE_IS_SAME_WITH_TMPL_PARAM_LIST_SPECIALIZE_TPLS1(\
    __T_NAME__)\
typename T1

__DEFINE_IS_SAME_WITH_(IsSame3, T,, TPLS1, C<T1>);

template<typename T>
using IsSame3_t = IsSame3<T>;

__DEFINE_NAME_(IsSame3<C<void>>);
__DEFINE_NAME_(IsSame3<D<void>>);
__DEFINE_NAME_(IsSame3<A>);

RegisterTest(t5, new TestIsSame<IsSame3_t, C<void>, bool, true, 
    &BoolCompare>());
RegisterTest(t6, new TestIsSame<IsSame3_t, D<void>, bool, false,
    &BoolCompare>());
RegisterTest(t7, new TestIsSame<IsSame3_t, A, bool, false,
    &BoolCompare>());

int main()
{
    return TestRun();
}
