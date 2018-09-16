#include "macro/HasMemberDefinition.h"
#include "Test.h"

BasicTestConstruct;

#include <vector>
#include <type_traits>

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
__DEFINE_NAME_(A);
__DEFINE_NAME_(B);

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Thmd, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thmd<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmd<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmd, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thmd<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thmd<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmd<T>::value_type).hash_code() ==
            typeid(typename Thmd<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmd, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thmd<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thmd<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thmd, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thmd<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thmd<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thmd<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thmd<T>::value, Thmd<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thmd, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasMmbrDefn : basic::test::Base
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thmd, T, Ttavt>();
        TestAliasType<Thmd, T>();
        TestValueAndTargetValue<Thmd, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thmd, T, Ttavt, Compare>();
    };
};

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
using HasMmbrDefn1_t = HasMmbrDefn1<T>;

__DEFINE_NAME_(HasMmbrDefn1<A>);
__DEFINE_NAME_(HasMmbrDefn1<B>);

RegisterTest(t1, new TestHasMmbrDefn<HasMmbrDefn1_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t2, new TestHasMmbrDefn<HasMmbrDefn1_t, B, bool, false,
    &BoolCompare>());

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
using HasMmbrDefn2_t = HasMmbrDefn2<T, void>;

__DEFINE_NAME_(HasMmbrDefn2<A, void>);
__DEFINE_NAME_(HasMmbrDefn2<B, void>);

RegisterTest(t3, new TestHasMmbrDefn<HasMmbrDefn2_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t4, new TestHasMmbrDefn<HasMmbrDefn2_t, B, bool, false,
    &BoolCompare>());

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
using HasMmbrDefn3_t = HasMmbrDefn3<C, T>;

__DEFINE_NAME_(HasMmbrDefn3<C, std::true_type>);
__DEFINE_NAME_(HasMmbrDefn3<C, std::false_type>);

RegisterTest(t5, new TestHasMmbrDefn<HasMmbrDefn3_t, std::true_type,
    bool, true, &BoolCompare>());
RegisterTest(t6, new TestHasMmbrDefn<HasMmbrDefn3_t, std::false_type,
    bool, false, &BoolCompare>());

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
using HasMmbrDefn4_t = HasMmbrDefn4<T>;

__DEFINE_NAME_(HasMmbrDefn4<A>);
__DEFINE_NAME_(HasMmbrDefn4<B>);

RegisterTest(t7, new TestHasMmbrDefn<HasMmbrDefn4_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t8, new TestHasMmbrDefn<HasMmbrDefn4_t, B, bool, false, 
    &BoolCompare>());

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
using HasMmbrDefn5_t = HasMmbrDefn5<T>;

__DEFINE_NAME_(HasMmbrDefn5<A>);
__DEFINE_NAME_(HasMmbrDefn5<B>);

RegisterTest(t9, new TestHasMmbrDefn<HasMmbrDefn5_t, A, bool, true, 
    &BoolCompare>());
RegisterTest(t10, new TestHasMmbrDefn<HasMmbrDefn5_t, B, bool, false, 
    &BoolCompare>());

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
using HasMmbrDefn6_t = HasMmbrDefn6<C, T>;

__DEFINE_NAME_(HasMmbrDefn6<C, std::true_type>);
__DEFINE_NAME_(HasMmbrDefn6<C, std::false_type>);

RegisterTest(t11, new TestHasMmbrDefn<HasMmbrDefn6_t, std::true_type, 
    bool, true, &BoolCompare>());
RegisterTest(t12, new TestHasMmbrDefn<HasMmbrDefn6_t, std::false_type, 
    bool, false, &BoolCompare>());

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
using HasMmbrDefn7_t = HasMmbrDefn7<T, void>;

__DEFINE_NAME_(HasMmbrDefn7<D, void>);
__DEFINE_NAME_(HasMmbrDefn7<B, void>);

RegisterTest(t13, new TestHasMmbrDefn<HasMmbrDefn7_t, D, bool, true, 
    &BoolCompare>());
RegisterTest(t14, new TestHasMmbrDefn<HasMmbrDefn7_t, B, bool, false, 
    &BoolCompare>());

int main()
{
    return TestRun();
}
