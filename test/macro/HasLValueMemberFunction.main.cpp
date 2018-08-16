#include "macro/HasLValueMemberFunction.h"
#include "Test.h"

#include <type_traits>
#include <vector>
#include <typeinfo>

struct A
{
    void Foo1() {}
    template<typename>
    void Foo2() {}
};

struct B
{};

template<typename>
struct C
{
    void Foo1() {}
};

template<>
struct C<std::false_type>
{};

struct D
{
    template<typename T>
    C<T> Foo3() {return C<T>();}
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

template<template<typename> class Thlvmf, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thlvmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thlvmf<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thlvmf, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thlvmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thlvmf<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thlvmf<T>::value_type).hash_code() ==
            typeid(typename Thlvmf<T>::ValueType).hash_code()))
                Info("Pass\n");
}

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Thlvmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thlvmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thlvmf<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thlvmf, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thlvmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thlvmf<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thlvmf<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thlvmf<T>::value, Thlvmf<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thlvmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasLValMmbrFunc : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thlvmf, T, Ttavt>();
        TestAliasType<Thlvmf, T>();
        TestValueAndTargetValue<Thlvmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thlvmf, T, Ttavt, Compare>();
    }
};

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc1(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc1<
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
 *          ))::value;
 *  };
 * */

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc1, _HasLValMmbrFunc1, T, Tr, 
    Targs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasLValMmbrFunc1_t = HasLValMmbrFunc1<T, void>;

__DEFINE_NAME_(HasLValMmbrFunc1<A, void>);
__DEFINE_NAME_(HasLValMmbrFunc1<B, void>);

TestRegister t1(new TestHasLValMmbrFunc<HasLValMmbrFunc1_t, A, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasLValMmbrFunc<HasLValMmbrFunc1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc2(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc2(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc2<
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
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc2, _HasLValMmbrFunc2, T, Tr, 
    Targs, TPL1, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Foo1);

template<typename T>
using HasLValMmbrFunc2_t = HasLValMmbrFunc2<T, void, void>;

__DEFINE_NAME_(HasLValMmbrFunc2<A, void, void>);
__DEFINE_NAME_(HasLValMmbrFunc2<B, void, void>);

TestRegister t3(new TestHasLValMmbrFunc<HasLValMmbrFunc2_t, A, bool, true, 
    &BoolCompare>());
TestRegister t4(new TestHasLValMmbrFunc<HasLValMmbrFunc2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc3(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc3(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc3<
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
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc3, _HasLValMmbrFunc3, T, Tr, 
    Targs, TPL2, T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasLValMmbrFunc3_t = HasLValMmbrFunc3<C, T, void>;

__DEFINE_NAME_(HasLValMmbrFunc3<C, std::true_type, void>);
__DEFINE_NAME_(HasLValMmbrFunc3<C, std::false_type, void>);

TestRegister t5(new TestHasLValMmbrFunc<HasLValMmbrFunc3_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t6(new TestHasLValMmbrFunc<HasLValMmbrFunc3_t, std::false_type,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc4(T t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc4<
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
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc4, _HasLValMmbrFunc4, T, Tr, 
    Targs, TPL1, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasLValMmbrFunc4_t = HasLValMmbrFunc4<T, void, void>;

__DEFINE_NAME_(HasLValMmbrFunc4<A, void, void>);
__DEFINE_NAME_(HasLValMmbrFunc4<B, void, void>);

TestRegister t7(new TestHasLValMmbrFunc<HasLValMmbrFunc4_t, A, 
    bool, true, &BoolCompare>());
TestRegister t8(new TestHasLValMmbrFunc<HasLValMmbrFunc4_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasLValMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(t.template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc5(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc5<
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
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc5, _HasLValMmbrFunc5, T, Tr, 
    Targs,, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL2, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, template Foo2<T1>);

template<typename T>
using HasLValMmbrFunc5_t = HasLValMmbrFunc5<T, void>;

__DEFINE_NAME_(HasLValMmbrFunc5<A, void>);
__DEFINE_NAME_(HasLValMmbrFunc5<B, void>);

TestRegister t9(new TestHasLValMmbrFunc<HasLValMmbrFunc5_t, A, 
    bool, true, &BoolCompare>());
TestRegister t10(new TestHasLValMmbrFunc<HasLValMmbrFunc5_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<typename T1, typename Tr, typename... Targs,
 *      template<typename> class T = A>
 *  constexpr auto _HasLValMmbrFunc6(T<T1> t, Targs... args) ->
 *      decltype(Tr(t.Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasLValMmbrFunc6(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasLValMmbrFunc6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc6<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *      static constexpr ValueType Value = decltype(_HasLValMmbrFunc6<
 *          typename basic::type::trait::rem::ptr::Recursive<T>::type,
 *                  Tr, Targs...>(
 *              std::declval<typename std::remove_cv<typename basic::type::
 *                  trait::rem::ptr::Recursive<T>::type>::type>(), 
 *              std::declval<typename std::remove_cv<Targs...>::type>()
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_RET_NAME__, typename... __T_ARGS_NAME__, typename T1,\
    template<typename> class __T_NAME__ = C

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_FTNTAL1()\
T1

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc6, _HasLValMmbrFunc6, T, Tr, 
    Targs,, T_NAME_,, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, FTNTAL1,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasLValMmbrFunc6_t = HasLValMmbrFunc6<T, void>;

__DEFINE_NAME_(HasLValMmbrFunc6<C<std::true_type>, void>);
__DEFINE_NAME_(HasLValMmbrFunc6<C<std::false_type>, void>);

TestRegister t11(new TestHasLValMmbrFunc<HasLValMmbrFunc6_t, C<std::true_type>, 
    bool, true, &BoolCompare>());
TestRegister t12(new TestHasLValMmbrFunc<HasLValMmbrFunc6_t, 
    C<std::false_type>, bool, false, &BoolCompare>());

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
 *  struct HasLValMmbrFunc7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasLValMmbrFunc7<
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
 *          ))::value;
 *  };
 * */

#define __DEFINE_HAS_LVAL_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_LVAL_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNRAL1()\
T1

__DEFINE_HAS_LVAL_MMBR_FUNC_(HasLValMmbrFunc7, _HasLValMmbrFunc7, T, Tr, 
    Targs, TPL3, T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNRAL1, template Foo3<T1>);

template<typename T>
using HasLValMmbrFunc7_t = HasLValMmbrFunc7<T, void, C>;

__DEFINE_NAME_(HasLValMmbrFunc7<D, void, C>);
__DEFINE_NAME_(HasLValMmbrFunc7<B, void, C>);

TestRegister t13(new TestHasLValMmbrFunc<HasLValMmbrFunc7_t, D, 
    bool, true, &BoolCompare>());
TestRegister t14(new TestHasLValMmbrFunc<HasLValMmbrFunc7_t, B, 
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
