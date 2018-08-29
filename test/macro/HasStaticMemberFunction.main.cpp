#include "macro/HasStaticMemberFunction.h"
#include "Test.h"

#include <type_traits>
#include <vector>
#include <typeinfo>

struct A
{
    static void Foo1() {}
    template<typename>
    static void Foo2() {}
};

struct B
{};

template<typename>
struct C
{
    static void Foo1() {}
};

template<>
struct C<std::false_type>
{};

struct D
{
    template<typename T>
    static C<T> Foo3() {return C<T>();}
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

template<template<typename> class Thsmf, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thsmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thsmf<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thsmf, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thsmf<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thsmf<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thsmf<T>::value_type).hash_code() ==
            typeid(typename Thsmf<T>::ValueType).hash_code()))
                Info("Pass\n");
}

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Thsmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thsmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thsmf<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thsmf, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thsmf<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thsmf<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thsmf<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thsmf<T>::value, Thsmf<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thsmf, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasStaticMmbrFunc : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thsmf, T, Ttavt>();
        TestAliasType<Thsmf, T>();
        TestValueAndTargetValue<Thsmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thsmf, T, Ttavt, Compare>();
    }
};

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc1(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc1(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc1<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc1<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc1, _HasStaticMmbrFunc1, T, Tr, 
    Targs,, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasStaticMmbrFunc1_t = HasStaticMmbrFunc1<T, void>;

__DEFINE_NAME_(HasStaticMmbrFunc1<A, void>);
__DEFINE_NAME_(HasStaticMmbrFunc1<B, void>);

TestRegister t1(new TestHasStaticMmbrFunc<HasStaticMmbrFunc1_t, A, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasStaticMmbrFunc<HasStaticMmbrFunc1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc2(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc2(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc2<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc2<
 *          typename basic::type::trait::Simple<T>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc2, _HasStaticMmbrFunc2, T, Tr, 
    Targs, TPL1, T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, 
    Foo1);

template<typename T>
using HasStaticMmbrFunc2_t = HasStaticMmbrFunc2<T, void, void>;

__DEFINE_NAME_(HasStaticMmbrFunc2<A, void, void>);
__DEFINE_NAME_(HasStaticMmbrFunc2<B, void, void>);

TestRegister t3(new TestHasStaticMmbrFunc<HasStaticMmbrFunc2_t, A, bool, true, 
    &BoolCompare>());
TestRegister t4(new TestHasStaticMmbrFunc<HasStaticMmbrFunc2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc3(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc3(...);
 *  template<template<typename> class T, typename T1, 
 *      typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *          typename basic::type::trait::Simple<T<T1>>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *          typename basic::type::trait::Simple<T<T1>::type, Tr, Targs...>(0, 
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc3, _HasStaticMmbrFunc3, T, Tr, 
    Targs, TPL2, T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasStaticMmbrFunc3_t = HasStaticMmbrFunc3<C, T, void>;

__DEFINE_NAME_(HasStaticMmbrFunc3<C, std::true_type, void>);
__DEFINE_NAME_(HasStaticMmbrFunc3<C, std::false_type, void>);

TestRegister t5(new TestHasStaticMmbrFunc<HasStaticMmbrFunc3_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t6(new TestHasStaticMmbrFunc<HasStaticMmbrFunc3_t, std::false_type,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc4(int, Targs... args) ->
 *      decltype(Tr(T::Foo1(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc4(...);
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME_SIMPLE_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc4, _HasStaticMmbrFunc4, T, Tr, 
    Targs, TPL1, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasStaticMmbrFunc4_t = HasStaticMmbrFunc4<T, void, void>;

__DEFINE_NAME_(HasStaticMmbrFunc4<A, void, void>);
__DEFINE_NAME_(HasStaticMmbrFunc4<B, void, void>);

TestRegister t7(new TestHasStaticMmbrFunc<HasStaticMmbrFunc4_t, A, 
    bool, true, &BoolCompare>());
TestRegister t8(new TestHasStaticMmbrFunc<HasStaticMmbrFunc4_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc5(T t, Targs... args) ->
 *      decltype(Tr(t.template Foo2<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc5(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, void, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc3<
 *              typename basic::type::trait::Simple<T>::type, void, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME_SIMPLE_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc5, _HasStaticMmbrFunc5, T, Tr, 
    Targs,, T_NAME_,, PFTTPL1, PFFTPL1, PFTAL2, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_,, template Foo2<T1>);

template<typename T>
using HasStaticMmbrFunc5_t = HasStaticMmbrFunc5<T, void>;

__DEFINE_NAME_(HasStaticMmbrFunc5<A, void>);
__DEFINE_NAME_(HasStaticMmbrFunc5<B, void>);

TestRegister t9(new TestHasStaticMmbrFunc<HasStaticMmbrFunc5_t, A, 
    bool, true, &BoolCompare>());
TestRegister t10(new TestHasStaticMmbrFunc<HasStaticMmbrFunc5_t, B,
    bool, false, &BoolCompare>());

/**
 *  template<typename T1, typename Tr, typename... Targs,
 *      template<typename> class T = C>
 *  constexpr auto _HasStaticMmbrFunc6(int, Targs... args) ->
 *      decltype(Tr(T<T1>::Foo1(args...)), std::true_type());
 *  template<typename T, typename Tr, typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc6(...);
 *  template<typename T, typename Tr, typename... Targs>
 *  struct HasStaticMmbrFunc6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc6<
 *                  T, Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc6<
 *              T, Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 typename T1, typename __T_RET_NAME__, typename... __T_ARGS_NAME__,\
    template<typename> class __T_NAME__ = C

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_RET_NAME__, typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_FTNTAL1()\
T1

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME__, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc6, _HasStaticMmbrFunc6, T, Tr, 
    Targs,, T_NAME_,, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, FTNTAL1,\
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasStaticMmbrFunc6_t = HasStaticMmbrFunc6<T, void>;

__DEFINE_NAME_(HasStaticMmbrFunc6<std::true_type, void>);
__DEFINE_NAME_(HasStaticMmbrFunc6<std::false_type, void>);

TestRegister t11(new TestHasStaticMmbrFunc<HasStaticMmbrFunc6_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t12(new TestHasStaticMmbrFunc<HasStaticMmbrFunc6_t, 
    std::false_type, bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr auto _HasStaticMmbrFunc7(int, Targs... args) ->
 *      decltype(Tr<T1>(T::template Foo3<T1>(args...)), std::true_type());
 *  template<typename T, typename T1, template<typename> class Tr,
 *      typename... Targs>
 *  constexpr std::false_type _HasStaticMmbrFunc7(...);
 *  template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 *  struct HasStaticMmbrFunc7
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrFunc7<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrFunc7<
 *              typename basic::type::trait::Simple<T>::type, T1, 
 *          Tr, Targs...>(0,
 *             std::declval<typename std::remove_cv<Targs...>::type>()
 *      ))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL3(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, template<typename> class __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_STATIC_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNRAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_FUNC_(HasStaticMmbrFunc7, _HasStaticMmbrFunc7, T, Tr, 
    Targs, TPL3, T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,,\
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNRAL1, template Foo3<T1>);

template<typename T>
using HasStaticMmbrFunc7_t = HasStaticMmbrFunc7<T, void, C>;

__DEFINE_NAME_(HasStaticMmbrFunc7<D, void, C>);
__DEFINE_NAME_(HasStaticMmbrFunc7<B, void, C>);

TestRegister t13(new TestHasStaticMmbrFunc<HasStaticMmbrFunc7_t, D, 
    bool, true, &BoolCompare>());
TestRegister t14(new TestHasStaticMmbrFunc<HasStaticMmbrFunc7_t, B, 
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
