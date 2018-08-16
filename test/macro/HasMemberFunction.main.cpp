#include "macro/HasMemberFunction.h"
#include "Test.h"

#include <type_traits>
#include <vector>
#include <typeinfo>

struct A1
{
    void Foo1() {}
    template<typename>
    void Foo2() {}
};

struct A2
{
    void Foo1() && {}
    template<typename>
    void Foo2() && {}
};

struct B
{};

template<typename, int>
struct C
{
    void Foo1() {}
};

template<typename T>
struct C <T, 1>
{
    void Foo1() && {}
};

template<>
struct C<std::false_type, 0>
{};

template<>
struct C<std::false_type, 1>
{};

template<typename T>
using C1 = C<T, 0>;

template<typename T>
using C2 = C<T, 1>;

struct D1
{
    template<typename T>
    C1<T> Foo3() {return C1<T>();}
};

struct D2
{
    template<typename T>
    C1<T> Foo3() && {return C1<T>();}
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
__DEFINE_NAME_(A1);
__DEFINE_NAME_(A2);
__DEFINE_NAME_(B);
__DEFINE_NAME_(C<std::true_type, 0>);
__DEFINE_NAME_(C<std::false_type, 0>);
__DEFINE_NAME_(C<std::true_type, 1>);
__DEFINE_NAME_(C<std::false_type, 1>);

struct BaseTest
{
    virtual ~BaseTest() {};
    virtual void Test() = 0;
};

struct TestRegister
{
    static std::vector<BaseTest*> List;
    BaseTest* m_ptr;
    TestRegister(BaseTest* ptr)
    {
        List.push_back(ptr);
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


template<template<typename> class Thmf, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmf<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmf, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thmf<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thmf<T>::value_type).hash_code() ==
            typeid(typename Thmf<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thmf<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thmf, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thmf<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thmf<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thmf<T>::value, Thmf<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasMmbrFunc : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thmf, T, Ttavt>();
        TestAliasType<Thmf, T>();
        TestValueAndTargetValue<Thmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thmf, T, Ttavt, Compare>();
    }
};

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc1(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc1(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasMmbrFunc1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc1, _HasLValMmbrFunc1, _HasRValMmbrFunc1, T,
    Tr, Targs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Foo1);

template<typename T>
using HasMmbrFunc1_t = HasMmbrFunc1<T, void>;

__DEFINE_NAME_(HasMmbrFunc1<A1, void>);
__DEFINE_NAME_(HasMmbrFunc1<A2, void>);
__DEFINE_NAME_(HasMmbrFunc1<B, void>);

TestRegister t1(new TestHasMmbrFunc<HasMmbrFunc1_t, A1, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasMmbrFunc<HasMmbrFunc1_t, A2, bool, true, 
    &BoolCompare>());
TestRegister t3(new TestHasMmbrFunc<HasMmbrFunc1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc2(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc2(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc2(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc2(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasMmbrFunc2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value ||  decltype(_HasRValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc2, _HasLValMmbrFunc2, _HasRValMmbrFunc2,
    T, Tr, Targs, TPL1, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc2_t = HasMmbrFunc2<T, void, void>;

__DEFINE_NAME_(HasMmbrFunc2<A1, void, void>);
__DEFINE_NAME_(HasMmbrFunc2<A2, void, void>);
__DEFINE_NAME_(HasMmbrFunc2<B, void, void>);

TestRegister t4(new TestHasMmbrFunc<HasMmbrFunc2_t, A1, bool, true, 
    &BoolCompare>());
TestRegister t5(new TestHasMmbrFunc<HasMmbrFunc2_t, A2, bool, true, 
    &BoolCompare>());
TestRegister t6(new TestHasMmbrFunc<HasMmbrFunc2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc3(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc3(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc3(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc3(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasMmbrFunc3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc3, _HasLValMmbrFunc3,
    _HasRValMmbrFunc3, T, Tr, Targs, TPL2, T_NAME_TMPL_, TNTAL1,,,,
    PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc3_1_t = HasMmbrFunc3<C1, T, void>;
template<typename T>
using HasMmbrFunc3_2_t = HasMmbrFunc3<C2, T, void>;

__DEFINE_NAME_(HasMmbrFunc3<C1, std::true_type, void>);
__DEFINE_NAME_(HasMmbrFunc3<C1, std::false_type, void>);
__DEFINE_NAME_(HasMmbrFunc3<C2, std::true_type, void>);
__DEFINE_NAME_(HasMmbrFunc3<C2, std::false_type, void>);

TestRegister t7(new TestHasMmbrFunc<HasMmbrFunc3_1_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t8(new TestHasMmbrFunc<HasMmbrFunc3_2_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t9(new TestHasMmbrFunc<HasMmbrFunc3_1_t, std::false_type,
    bool, false, &BoolCompare>());
TestRegister t10(new TestHasMmbrFunc<HasMmbrFunc3_2_t, std::false_type,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc4(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc4(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasMmbrFunc4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc4, _HasLValMmbrFunc4, _HasRValMmbrFunc4, T, Tr, 
    Targs, TPL1, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc4_t = HasMmbrFunc4<T, void, void>;

__DEFINE_NAME_(HasMmbrFunc4<A1, void, void>);
__DEFINE_NAME_(HasMmbrFunc4<A2, void, void>);
__DEFINE_NAME_(HasMmbrFunc4<B, void, void>);

TestRegister t11(new TestHasMmbrFunc<HasMmbrFunc4_t, A1, bool, true, 
    &BoolCompare>());
TestRegister t12(new TestHasMmbrFunc<HasMmbrFunc4_t, A2, bool, true, 
    &BoolCompare>());
TestRegister t13(new TestHasMmbrFunc<HasMmbrFunc4_t, B, bool, false, 
    &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(t.template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc5(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc5(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasMmbrFunc5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc5, _HasLValMmbrFunc5,
    _HasRValMmbrFunc5, T, Tr, Targs,, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL2,
    PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, template Foo2<T1>);

template<typename T>
using HasMmbrFunc5_t = HasMmbrFunc5<T, void>;

__DEFINE_NAME_(HasMmbrFunc5<A1, void>);
__DEFINE_NAME_(HasMmbrFunc5<A2, void>);
__DEFINE_NAME_(HasMmbrFunc5<B, void>);

TestRegister t14(new TestHasMmbrFunc<HasMmbrFunc5_t, A1, 
    bool, true, &BoolCompare>());
TestRegister t15(new TestHasMmbrFunc<HasMmbrFunc5_t, A2, 
    bool, true, &BoolCompare>());
TestRegister t16(new TestHasMmbrFunc<HasMmbrFunc5_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs, typename T1>
 *  constexpr auto _HasLValMmbrFunc6(T<T1> t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc6(...);
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs, typename T1>
 *  constexpr auto _HasRValMmbrFunc6(T<T1> t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc6(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasMmbrFunc6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, template<typename> class T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__, typename T1

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__,  typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_FTNTAL1()\
T1

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc6, _HasLValMmbrFunc6, 
    _HasRValMmbrFunc6, T, Tr, Targs, TPL3, T_NAME_,, PFTTPL2, PFFTPL2, 
    PFTAL3, PROTO_FUNC_T_NAME_TMPL_, FTNTAL1, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc6_1_t = HasMmbrFunc6<T, C1, void>;
template<typename T>
using HasMmbrFunc6_2_t = HasMmbrFunc6<T, C2, void>;

__DEFINE_NAME_(HasMmbrFunc6<C1<std::true_type>, C1, void>);
__DEFINE_NAME_(HasMmbrFunc6<C2<std::true_type>, C2, void>);
__DEFINE_NAME_(HasMmbrFunc6<C1<std::false_type>, C1, void>);
__DEFINE_NAME_(HasMmbrFunc6<C2<std::false_type>, C2, void>);

TestRegister t17(new TestHasMmbrFunc<HasMmbrFunc6_1_t, C1<std::true_type>, 
    bool, true, &BoolCompare>());
TestRegister t18(new TestHasMmbrFunc<HasMmbrFunc6_2_t, C2<std::true_type>, 
    bool, true, &BoolCompare>());
TestRegister t19(new TestHasMmbrFunc<HasMmbrFunc6_1_t, C1<std::false_type>, 
    bool, false, &BoolCompare>());
TestRegister t20(new TestHasMmbrFunc<HasMmbrFunc6_2_t, C2<std::false_type>, 
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr auto _HasLValMmbrFunc7(T t, Targs... args) ->
 *      decltype(Tr<T1>(t.template Foo3<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc7(...);
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr auto _HasRValMmbrFunc7(T t, Targs... args) ->
 *      decltype(Tr<T1>(std::move(t).template Foo3<T1>(args...)),
 *           std::true_type());
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc7(...);
 *  template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 *  struct HasMmbrFunc7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value || decltype(_HasRValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNRAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc7, _HasLValMmbrFunc7, 
    _HasRValMmbrFunc7, T, Tr, Targs, TPL4, T_NAME_,, PFTTPL3, PFFTPL3,
    PFTAL1, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_TMPL_, 
    PFTRNRAL1, template Foo3<T1>);

template<typename T>
using HasMmbrFunc7_t = HasMmbrFunc7<T, void, C1>;

__DEFINE_NAME_(HasMmbrFunc7<D1, void, C1>);
__DEFINE_NAME_(HasMmbrFunc7<D2, void, C1>);
__DEFINE_NAME_(HasMmbrFunc7<B, void, C1>);

TestRegister t21(new TestHasMmbrFunc<HasMmbrFunc7_t, D1, 
    bool, true, &BoolCompare>());
TestRegister t22(new TestHasMmbrFunc<HasMmbrFunc7_t, D2, 
    bool, true, &BoolCompare>());
TestRegister t23(new TestHasMmbrFunc<HasMmbrFunc7_t, B, 
    bool, false, &BoolCompare>());

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
