#include "macro/HasRValueMemberFunction.h"
#include "Test.h"

#include <type_traits>
#include <vector>
#include <typeinfo>

struct A
{
    void Foo1() && {}
    template<typename>
    void Foo2() && {}
};

struct B
{};

template<typename>
struct C
{
    void Foo1() && {}
};

template<>
struct C<std::false_type>
{};

struct D
{
    template<typename T>
    C<T> Foo3() && {return C<T>();}
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
__DEFINE_NAME_(C<std::true_type>);
__DEFINE_NAME_(C<std::false_type>);

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

template<template<typename> class Thrvmf, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thrvmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thrvmf<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thrvmf, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thrvmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thrvmf<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thrvmf<T>::value_type).hash_code() ==
            typeid(typename Thrvmf<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thrvmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thrvmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thrvmf<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thrvmf, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thrvmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thrvmf<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thrvmf<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thrvmf<T>::value, Thrvmf<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thrvmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasRValMmbrFunc : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thrvmf, T, Ttavt>();
        TestAliasType<Thrvmf, T>();
        TestValueAndTargetValue<Thrvmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thrvmf, T, Ttavt, Compare>();
    }
};

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc1(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc1<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc1, _HasRValMmbrFunc1, T,
    Tr, Targs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Foo1);

template<typename T>
using HasRValMmbrFunc1_t = HasRValMmbrFunc1<T, void>;

__DEFINE_NAME_(HasRValMmbrFunc1<A, void>);
__DEFINE_NAME_(HasRValMmbrFunc1<B, void>);

TestRegister t1(new TestHasRValMmbrFunc<HasRValMmbrFunc1_t, A, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasRValMmbrFunc<HasRValMmbrFunc1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc2(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc2(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc2<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc2, _HasRValMmbrFunc2,
    T, Tr, Targs, TPL1, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasRValMmbrFunc2_t = HasRValMmbrFunc2<T, void, void>;

__DEFINE_NAME_(HasRValMmbrFunc2<A, void, void>);
__DEFINE_NAME_(HasRValMmbrFunc2<B, void, void>);

TestRegister t3(new TestHasRValMmbrFunc<HasRValMmbrFunc2_t, A, bool, true, 
    &BoolCompare>());
TestRegister t4(new TestHasRValMmbrFunc<HasRValMmbrFunc2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc3(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc3(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc3<
 *          typename basic::type::trait::rem::ptr::Recursive<T<T1>>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T<T1>>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRvalMmbrFunc3, _HasRValMmbrFunc3, T, Tr, Targs, 
    TPL2, T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasRvalMmbrFunc3_t = HasRvalMmbrFunc3<C, T, void>;

__DEFINE_NAME_(HasRvalMmbrFunc3<C, std::true_type, void>);
__DEFINE_NAME_(HasRvalMmbrFunc3<C, std::false_type, void>);

TestRegister t5(new TestHasRValMmbrFunc<HasRvalMmbrFunc3_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t6(new TestHasRValMmbrFunc<HasRvalMmbrFunc3_t, std::false_type,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc4(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc4<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc4, _HasRValMmbrFunc4, T, Tr, 
    Targs, TPL1, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasRValMmbrFunc4_t = HasRValMmbrFunc4<T, void, void>;

__DEFINE_NAME_(HasRValMmbrFunc4<A, void, void>);
__DEFINE_NAME_(HasRValMmbrFunc4<B, void, void>);

TestRegister t7(new TestHasRValMmbrFunc<HasRValMmbrFunc4_t, A, bool, true, 
    &BoolCompare>());
TestRegister t8(new TestHasRValMmbrFunc<HasRValMmbrFunc4_t, B, bool, false, 
    &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasRValMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(std::move(t).template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc5(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc5<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  void, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc5, _HasRValMmbrFunc5, T, Tr, 
    Targs,, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL2, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, template Foo2<T1>);

template<typename T>
using HasRValMmbrFunc5_t = HasRValMmbrFunc5<T, void>;

__DEFINE_NAME_(HasRValMmbrFunc5<A, void>);
__DEFINE_NAME_(HasRValMmbrFunc5<B, void>);

TestRegister t9(new TestHasRValMmbrFunc<HasRValMmbrFunc5_t, A, 
    bool, true, &BoolCompare>());
TestRegister t10(new TestHasRValMmbrFunc<HasRValMmbrFunc5_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs, typename T1>
 *  constexpr auto _HasRValMmbrFunc6(T<T1> t, Targs... args) ->
 *      decltype(Tr(std::move(t).Foo1(args...)), std::true_type());
 *  template<template<typename> class T,  typename Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasRValMmbrFunc6(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasRValMmbrFunc6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc6<
 *          T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, template<typename> class T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__, typename T1

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__,  typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_FTNTAL1()\
T1

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc6, _HasRValMmbrFunc6, T, Tr, Targs,
    TPL3, T_NAME_,, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, FTNTAL1,
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasRValMmbrFunc6_t = HasRValMmbrFunc6<T, C, void>;

__DEFINE_NAME_(HasRValMmbrFunc6<C<std::true_type>, C, void>);
__DEFINE_NAME_(HasRValMmbrFunc6<C<std::false_type>, C, void>);

TestRegister t11(new TestHasRValMmbrFunc<HasRValMmbrFunc6_t, C<std::true_type>, 
    bool, true, &BoolCompare>());
TestRegister t12(new TestHasRValMmbrFunc<HasRValMmbrFunc6_t, C<std::false_type>, 
    bool, false, &BoolCompare>());

/**
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
 *  struct HasRValMmbrFunc7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasRValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasRValMmbrFunc7<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  T1, Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_RVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL4(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_RVAL_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNRAL1()\
T1

__DEFINE_HAS_RVAL_MMBR_FUNC_(HasRValMmbrFunc7, _HasRValMmbrFunc7, T, Tr, Targs,
    TPL4, T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNRAL1, template Foo3<T1>);

template<typename T>
using HasRValMmbrFunc7_t = HasRValMmbrFunc7<T, void, C>;

__DEFINE_NAME_(HasRValMmbrFunc7<D, void, C>);
__DEFINE_NAME_(HasRValMmbrFunc7<B, void, C>);

TestRegister t13(new TestHasRValMmbrFunc<HasRValMmbrFunc7_t, D, 
    bool, true, &BoolCompare>());
TestRegister t14(new TestHasRValMmbrFunc<HasRValMmbrFunc7_t, B, 
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
