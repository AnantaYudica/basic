#include "macro/HasMemberFunction.h"
#include "Test.h"

BasicTestConstruct;

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
    void Foo1() const {}
    template<typename>
    void Foo2() const {}
};

struct A3
{
    void Foo1() volatile {}
    template<typename>
    void Foo2() volatile {}
};

struct A4
{
    void Foo1() const volatile {}
    template<typename>
    void Foo2() const volatile {}
};

struct A5
{
    void Foo1() & {}
    template<typename>
    void Foo2() & {}
};

struct A6
{
    void Foo1() const & {}
    template<typename>
    void Foo2() const & {}
};

struct A7
{
    void Foo1() volatile & {}
    template<typename>
    void Foo2() volatile & {}
};

struct A8
{
    void Foo1() const volatile & {}
    template<typename>
    void Foo2() const volatile & {}
};

struct A9
{
    void Foo1() && {}
    template<typename>
    void Foo2() && {}
};

struct A10
{
    void Foo1() const && {}
    template<typename>
    void Foo2() const && {}
};

struct A11
{
    void Foo1() volatile && {}
    template<typename>
    void Foo2() volatile && {}
};

struct A12
{
    void Foo1() const volatile && {}
    template<typename>
    void Foo2() const volatile && {}
};

struct B
{};

template<typename T>
struct C1
{
    void Foo1() {}
    template<typename>
    void Foo2() {}
};

template<>
struct C1<std::false_type>
{};

struct D1
{
    template<typename T>
    C1<T> Foo3() {return C1<T>();}
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

template<template<typename> class Thmf, typename Ttavt, 
    bool(*Compare)(Ttavt a, Ttavt b), typename... Ts>
struct TestHasMmbrFunc : basic::test::Base
{
    void Test() 
    {
    }
};

template<template<typename> class Thmf, typename Ttavt, 
    bool(*Compare)(Ttavt a, Ttavt b), typename T, typename... Ts>
struct TestHasMmbrFunc<Thmf, Ttavt, Compare, T, Ts...> :
    TestHasMmbrFunc<Thmf, Ttavt, Compare, Ts...>
{
    void Test() 
    {
        T::template Test<Thmf, Compare>();
        TestHasMmbrFunc<Thmf, Ttavt, Compare, Ts...>::Test();
    }
};

template<typename T, typename Ttavt, Ttavt TtavtValue>
struct TestHasMmbrFuncPair
{
    template<template<typename> class Thmf, bool(*Compare)(Ttavt a, Ttavt b)>
    static void Test() 
    {
        TestAliasTypeAndTarget<Thmf, T, Ttavt>();
        TestAliasType<Thmf, T>();
        TestValueAndTargetValue<Thmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thmf, T, Ttavt, Compare>();
    }
};

template<typename T, bool TtavtValue>
using TPair = TestHasMmbrFuncPair<T, bool, TtavtValue>;

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc1(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc1 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc1
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc1<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc1<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc1, _HasMmbrFunc1, T, Tr, Targs,,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc1_t = HasMmbrFunc1<T, void>;

__DEFINE_NAME_(HasMmbrFunc1<A1, void>);
__DEFINE_NAME_(HasMmbrFunc1<A2, void>);
__DEFINE_NAME_(HasMmbrFunc1<A3, void>);
__DEFINE_NAME_(HasMmbrFunc1<A4, void>);
__DEFINE_NAME_(HasMmbrFunc1<A5, void>);
__DEFINE_NAME_(HasMmbrFunc1<A6, void>);
__DEFINE_NAME_(HasMmbrFunc1<A7, void>);
__DEFINE_NAME_(HasMmbrFunc1<A8, void>);
__DEFINE_NAME_(HasMmbrFunc1<A9, void>);
__DEFINE_NAME_(HasMmbrFunc1<A10, void>);
__DEFINE_NAME_(HasMmbrFunc1<A11, void>);
__DEFINE_NAME_(HasMmbrFunc1<A12, void>);
__DEFINE_NAME_(HasMmbrFunc1<B, void>);

RegisterTest(t1, new TestHasMmbrFunc<HasMmbrFunc1_t, bool, &BoolCompare,
    TPair<A1, true>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc2(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc2 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc2
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc2<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc2<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc2, _HasMmbrFunc2, T, Tr, Targs, const,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc2_t = HasMmbrFunc2<T, void>;

__DEFINE_NAME_(HasMmbrFunc2<A1, void>);
__DEFINE_NAME_(HasMmbrFunc2<A2, void>);
__DEFINE_NAME_(HasMmbrFunc2<A3, void>);
__DEFINE_NAME_(HasMmbrFunc2<A4, void>);
__DEFINE_NAME_(HasMmbrFunc2<A5, void>);
__DEFINE_NAME_(HasMmbrFunc2<A6, void>);
__DEFINE_NAME_(HasMmbrFunc2<A7, void>);
__DEFINE_NAME_(HasMmbrFunc2<A8, void>);
__DEFINE_NAME_(HasMmbrFunc2<A9, void>);
__DEFINE_NAME_(HasMmbrFunc2<A10, void>);
__DEFINE_NAME_(HasMmbrFunc2<A11, void>);
__DEFINE_NAME_(HasMmbrFunc2<A12, void>);
__DEFINE_NAME_(HasMmbrFunc2<B, void>);

RegisterTest(t2, new TestHasMmbrFunc<HasMmbrFunc2_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, true>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc3(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc3 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc3
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc3<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc3<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc3, _HasMmbrFunc3, T, Tr, Targs, volatile,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc3_t = HasMmbrFunc3<T, void>;

__DEFINE_NAME_(HasMmbrFunc3<A1, void>);
__DEFINE_NAME_(HasMmbrFunc3<A2, void>);
__DEFINE_NAME_(HasMmbrFunc3<A3, void>);
__DEFINE_NAME_(HasMmbrFunc3<A4, void>);
__DEFINE_NAME_(HasMmbrFunc3<A5, void>);
__DEFINE_NAME_(HasMmbrFunc3<A6, void>);
__DEFINE_NAME_(HasMmbrFunc3<A7, void>);
__DEFINE_NAME_(HasMmbrFunc3<A8, void>);
__DEFINE_NAME_(HasMmbrFunc3<A9, void>);
__DEFINE_NAME_(HasMmbrFunc3<A10, void>);
__DEFINE_NAME_(HasMmbrFunc3<A11, void>);
__DEFINE_NAME_(HasMmbrFunc3<A12, void>);
__DEFINE_NAME_(HasMmbrFunc3<B, void>);

RegisterTest(t3, new TestHasMmbrFunc<HasMmbrFunc3_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, true>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc4(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc4 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc4
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc4<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc4<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc4, _HasMmbrFunc4, T, Tr, Targs, const volatile,,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc4_t = HasMmbrFunc4<T, void>;

__DEFINE_NAME_(HasMmbrFunc4<A1, void>);
__DEFINE_NAME_(HasMmbrFunc4<A2, void>);
__DEFINE_NAME_(HasMmbrFunc4<A3, void>);
__DEFINE_NAME_(HasMmbrFunc4<A4, void>);
__DEFINE_NAME_(HasMmbrFunc4<A5, void>);
__DEFINE_NAME_(HasMmbrFunc4<A6, void>);
__DEFINE_NAME_(HasMmbrFunc4<A7, void>);
__DEFINE_NAME_(HasMmbrFunc4<A8, void>);
__DEFINE_NAME_(HasMmbrFunc4<A9, void>);
__DEFINE_NAME_(HasMmbrFunc4<A10, void>);
__DEFINE_NAME_(HasMmbrFunc4<A11, void>);
__DEFINE_NAME_(HasMmbrFunc4<A12, void>);
__DEFINE_NAME_(HasMmbrFunc4<B, void>);

RegisterTest(t4, new TestHasMmbrFunc<HasMmbrFunc4_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, true>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc5(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) &>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc5 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc5
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc5<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc5<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc5, _HasMmbrFunc5, T, Tr, Targs,, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc5_t = HasMmbrFunc5<T, void>;

__DEFINE_NAME_(HasMmbrFunc5<A1, void>);
__DEFINE_NAME_(HasMmbrFunc5<A2, void>);
__DEFINE_NAME_(HasMmbrFunc5<A3, void>);
__DEFINE_NAME_(HasMmbrFunc5<A4, void>);
__DEFINE_NAME_(HasMmbrFunc5<A5, void>);
__DEFINE_NAME_(HasMmbrFunc5<A6, void>);
__DEFINE_NAME_(HasMmbrFunc5<A7, void>);
__DEFINE_NAME_(HasMmbrFunc5<A8, void>);
__DEFINE_NAME_(HasMmbrFunc5<A9, void>);
__DEFINE_NAME_(HasMmbrFunc5<A10, void>);
__DEFINE_NAME_(HasMmbrFunc5<A11, void>);
__DEFINE_NAME_(HasMmbrFunc5<A12, void>);
__DEFINE_NAME_(HasMmbrFunc5<B, void>);

RegisterTest(t5, new TestHasMmbrFunc<HasMmbrFunc5_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, true>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc6(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const &>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc6 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc6
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc6<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc6<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc6, _HasMmbrFunc6, T, Tr, Targs, const, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc6_t = HasMmbrFunc6<T, void>;

__DEFINE_NAME_(HasMmbrFunc6<A1, void>);
__DEFINE_NAME_(HasMmbrFunc6<A2, void>);
__DEFINE_NAME_(HasMmbrFunc6<A3, void>);
__DEFINE_NAME_(HasMmbrFunc6<A4, void>);
__DEFINE_NAME_(HasMmbrFunc6<A5, void>);
__DEFINE_NAME_(HasMmbrFunc6<A6, void>);
__DEFINE_NAME_(HasMmbrFunc6<A7, void>);
__DEFINE_NAME_(HasMmbrFunc6<A8, void>);
__DEFINE_NAME_(HasMmbrFunc6<A9, void>);
__DEFINE_NAME_(HasMmbrFunc6<A10, void>);
__DEFINE_NAME_(HasMmbrFunc6<A11, void>);
__DEFINE_NAME_(HasMmbrFunc6<A12, void>);
__DEFINE_NAME_(HasMmbrFunc6<B, void>);

RegisterTest(t6, new TestHasMmbrFunc<HasMmbrFunc6_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, true>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc7(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile &>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc7 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc7
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc7<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc7<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc7, _HasMmbrFunc7, T, Tr, Targs, volatile, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc7_t = HasMmbrFunc7<T, void>;

__DEFINE_NAME_(HasMmbrFunc7<A1, void>);
__DEFINE_NAME_(HasMmbrFunc7<A2, void>);
__DEFINE_NAME_(HasMmbrFunc7<A3, void>);
__DEFINE_NAME_(HasMmbrFunc7<A4, void>);
__DEFINE_NAME_(HasMmbrFunc7<A5, void>);
__DEFINE_NAME_(HasMmbrFunc7<A6, void>);
__DEFINE_NAME_(HasMmbrFunc7<A7, void>);
__DEFINE_NAME_(HasMmbrFunc7<A8, void>);
__DEFINE_NAME_(HasMmbrFunc7<A9, void>);
__DEFINE_NAME_(HasMmbrFunc7<A10, void>);
__DEFINE_NAME_(HasMmbrFunc7<A11, void>);
__DEFINE_NAME_(HasMmbrFunc7<A12, void>);
__DEFINE_NAME_(HasMmbrFunc7<B, void>);

RegisterTest(t7, new TestHasMmbrFunc<HasMmbrFunc7_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, true>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc8(T t, Targs... args) ->
 * 	    decltype((static_cast<T&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile &>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc8 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc8
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc8<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc8<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc8, _HasMmbrFunc8, T, Tr, Targs, const volatile, &,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc8_t = HasMmbrFunc8<T, void>;

__DEFINE_NAME_(HasMmbrFunc8<A1, void>);
__DEFINE_NAME_(HasMmbrFunc8<A2, void>);
__DEFINE_NAME_(HasMmbrFunc8<A3, void>);
__DEFINE_NAME_(HasMmbrFunc8<A4, void>);
__DEFINE_NAME_(HasMmbrFunc8<A5, void>);
__DEFINE_NAME_(HasMmbrFunc8<A6, void>);
__DEFINE_NAME_(HasMmbrFunc8<A7, void>);
__DEFINE_NAME_(HasMmbrFunc8<A8, void>);
__DEFINE_NAME_(HasMmbrFunc8<A9, void>);
__DEFINE_NAME_(HasMmbrFunc8<A10, void>);
__DEFINE_NAME_(HasMmbrFunc8<A11, void>);
__DEFINE_NAME_(HasMmbrFunc8<A12, void>);
__DEFINE_NAME_(HasMmbrFunc8<B, void>);

RegisterTest(t8, new TestHasMmbrFunc<HasMmbrFunc8_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, true>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);


/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc9(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc9 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc9
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc9<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc9<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc9, _HasMmbrFunc9, T, Tr, Targs,, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);
    
template<typename T>
using HasMmbrFunc9_t = HasMmbrFunc9<T, void>;

__DEFINE_NAME_(HasMmbrFunc9<A1, void>);
__DEFINE_NAME_(HasMmbrFunc9<A2, void>);
__DEFINE_NAME_(HasMmbrFunc9<A3, void>);
__DEFINE_NAME_(HasMmbrFunc9<A4, void>);
__DEFINE_NAME_(HasMmbrFunc9<A5, void>);
__DEFINE_NAME_(HasMmbrFunc9<A6, void>);
__DEFINE_NAME_(HasMmbrFunc9<A7, void>);
__DEFINE_NAME_(HasMmbrFunc9<A8, void>);
__DEFINE_NAME_(HasMmbrFunc9<A9, void>);
__DEFINE_NAME_(HasMmbrFunc9<A10, void>);
__DEFINE_NAME_(HasMmbrFunc9<A11, void>);
__DEFINE_NAME_(HasMmbrFunc9<A12, void>);
__DEFINE_NAME_(HasMmbrFunc9<B, void>);

RegisterTest(t9, new TestHasMmbrFunc<HasMmbrFunc9_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, true>, TPair<A10, false>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc10(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc10 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc10
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc10<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc10<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
 
__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc10, _HasMmbrFunc10, T, Tr, Targs, const, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc10_t = HasMmbrFunc10<T, void>;

__DEFINE_NAME_(HasMmbrFunc10<A1, void>);
__DEFINE_NAME_(HasMmbrFunc10<A2, void>);
__DEFINE_NAME_(HasMmbrFunc10<A3, void>);
__DEFINE_NAME_(HasMmbrFunc10<A4, void>);
__DEFINE_NAME_(HasMmbrFunc10<A5, void>);
__DEFINE_NAME_(HasMmbrFunc10<A6, void>);
__DEFINE_NAME_(HasMmbrFunc10<A7, void>);
__DEFINE_NAME_(HasMmbrFunc10<A8, void>);
__DEFINE_NAME_(HasMmbrFunc10<A9, void>);
__DEFINE_NAME_(HasMmbrFunc10<A10, void>);
__DEFINE_NAME_(HasMmbrFunc10<A11, void>);
__DEFINE_NAME_(HasMmbrFunc10<A12, void>);
__DEFINE_NAME_(HasMmbrFunc10<B, void>);

RegisterTest(t10, new TestHasMmbrFunc<HasMmbrFunc10_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, true>, TPair<A11, false>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc11(T t, Targs... args) ->
 * 	    decltype((static_cast<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) volatile &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc11 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc11
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc11<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc11<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc11, _HasMmbrFunc11, T, Tr, Targs, volatile, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc11_t = HasMmbrFunc11<T, void>;

__DEFINE_NAME_(HasMmbrFunc11<A1, void>);
__DEFINE_NAME_(HasMmbrFunc11<A2, void>);
__DEFINE_NAME_(HasMmbrFunc11<A3, void>);
__DEFINE_NAME_(HasMmbrFunc11<A4, void>);
__DEFINE_NAME_(HasMmbrFunc11<A5, void>);
__DEFINE_NAME_(HasMmbrFunc11<A6, void>);
__DEFINE_NAME_(HasMmbrFunc11<A7, void>);
__DEFINE_NAME_(HasMmbrFunc11<A8, void>);
__DEFINE_NAME_(HasMmbrFunc11<A9, void>);
__DEFINE_NAME_(HasMmbrFunc11<A10, void>);
__DEFINE_NAME_(HasMmbrFunc11<A11, void>);
__DEFINE_NAME_(HasMmbrFunc11<A12, void>);
__DEFINE_NAME_(HasMmbrFunc11<B, void>);

RegisterTest(t11, new TestHasMmbrFunc<HasMmbrFunc11_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, true>, TPair<A12, false>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc12(T t, Targs... args) ->
 * 	    decltype((static<T&&>(t).*(
 *          static_cast<Tr (T::*)(Targs...) const volatile &&>(
 *              &T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc12 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc12
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc12<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc12<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc12, _HasMmbrFunc12, T, Tr, Targs, const volatile, &&,,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc12_t = HasMmbrFunc12<T, void>;

__DEFINE_NAME_(HasMmbrFunc12<A1, void>);
__DEFINE_NAME_(HasMmbrFunc12<A2, void>);
__DEFINE_NAME_(HasMmbrFunc12<A3, void>);
__DEFINE_NAME_(HasMmbrFunc12<A4, void>);
__DEFINE_NAME_(HasMmbrFunc12<A5, void>);
__DEFINE_NAME_(HasMmbrFunc12<A6, void>);
__DEFINE_NAME_(HasMmbrFunc12<A7, void>);
__DEFINE_NAME_(HasMmbrFunc12<A8, void>);
__DEFINE_NAME_(HasMmbrFunc12<A9, void>);
__DEFINE_NAME_(HasMmbrFunc12<A10, void>);
__DEFINE_NAME_(HasMmbrFunc12<A11, void>);
__DEFINE_NAME_(HasMmbrFunc12<A12, void>);
__DEFINE_NAME_(HasMmbrFunc12<B, void>);

RegisterTest(t12, new TestHasMmbrFunc<HasMmbrFunc12_t, bool, &BoolCompare,
    TPair<A1, false>, TPair<A2, false>, TPair<A3, false>, TPair<A4, false>,
    TPair<A5, false>, TPair<A6, false>, TPair<A7, false>, TPair<A8, false>, 
    TPair<A9, false>, TPair<A10, false>, TPair<A11, false>, TPair<A12, true>,
    TPair<B, false>>);

/**
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc13(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc13 (...);
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc13
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc13<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc13<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/
    
#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc13, _HasMmbrFunc13, T, Tr, Targs,,, TPL1,
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc13_t = HasMmbrFunc13<T, void, void>;

__DEFINE_NAME_(HasMmbrFunc13<A1, void, void>);
__DEFINE_NAME_(HasMmbrFunc13<B, void, void>);

RegisterTest(t13, new TestHasMmbrFunc<HasMmbrFunc13_t, bool, &BoolCompare,
    TPair<A1, true>, TPair<B, false>>);

/**
 * 	template<template T, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc14(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc14 (...);
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc14
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc14<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T<T1>>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc14<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T<T1>>::type, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc14, _HasMmbrFunc14, T, Tr, Targs,,, TPL2,
    T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc14_t = HasMmbrFunc14<C1, T, void>;

__DEFINE_NAME_(HasMmbrFunc14<C1, std::true_type, void>);
__DEFINE_NAME_(HasMmbrFunc14<C1, std::false_type, void>);

RegisterTest(t14, new TestHasMmbrFunc<HasMmbrFunc14_t, bool, &BoolCompare,
    TPair<std::true_type, true>, TPair<std::false_type, false>>);

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc15(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc15 (...);
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc15
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc15<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc15<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTP1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS__NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS__NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTP1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS__NAME__)\
typename __T_NAME__, typename T1, typename __T_RET_NAME__,\
    typename... __T_ARGS__NAME__
    
#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, T1, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc15, _HasMmbrFunc15, T, Tr, Targs,,, TPL1,
    T_NAME_,, PFTTP1, PFFTP1, PFTAL1, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc15_t = HasMmbrFunc15<T, void, void>;

__DEFINE_NAME_(HasMmbrFunc15<A1, void, void>);
__DEFINE_NAME_(HasMmbrFunc15<B, void, void>);

RegisterTest(t15, new TestHasMmbrFunc<HasMmbrFunc15_t, bool, &BoolCompare,
    TPair<A1, true>, TPair<B, false>>);

/**
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr auto _HasMmbrFunc16(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, typename Tr, typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc16 (...);
 * 	template<typename T, typename Tr, typename... Targs>
 * 	struct HasMmbrFunc16
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc16<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, void, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc16<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, void, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_REM_RECV_PTR_TYPE__, ...)\
__T_NAME_REM_RECV_PTR_TYPE__,##__VA_ARGS__, void, __T_RET_NAME__,\
    __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc16, _HasMmbrFunc16, T, Tr, Targs,,,,
    T_NAME_,, PFTTP1, PFFTP1, PFTAL2, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc16_t = HasMmbrFunc16<T, void>;

__DEFINE_NAME_(HasMmbrFunc16<A1, void>);
__DEFINE_NAME_(HasMmbrFunc16<B, void>);

RegisterTest(t16, new TestHasMmbrFunc<HasMmbrFunc16_t, bool, &BoolCompare,
    TPair<A1, true>, TPair<B, false>>);

/**
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	constexpr auto _HasMmbrFunc17(T<T1> t, Targs... args) ->
 * 	    decltype((static_cast<T<T1>>(t).*(
 *      static_cast<Tr (T<T1>::*)(Targs...)>(&T<T1>::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc17 (...);
 * 	template<template<typename> class T, typename T1, typename Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc17
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc17<T, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc17<T, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T<T1>>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__,\
    __T_RET_NAME__,\
    __T_ARGS_NAME__)\
 template<typename> class __T_NAME__, typename T1, typename __T_RET_NAME__,\
     typename... __T_ARGS_NAME__

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_TMPL_ARG_LIST_PFTAL3(\
    __T_NAME__, \
    __T_RET_NAME__,\
    __T_ARGS_NAME__,\
    __T_NAME_SIMPLE_TYPE__, ...)\
__T_NAME__, T1, __T_RET_NAME__, __T_ARGS_NAME__...

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc17, _HasMmbrFunc17, T, Tr, Targs,,, TPL2,
    T_NAME_TMPL_, TNTAL1, PFTTPL2, PFFTPL2, PFTAL3, PROTO_FUNC_T_NAME_TMPL_, 
    PFTNTAL1, PROTO_FUNC_T_RET_NAME_,, Foo1);

template<typename T>
using HasMmbrFunc17_t = HasMmbrFunc17<C1, T, void>;

__DEFINE_NAME_(HasMmbrFunc17<C1, std::true_type, void>);
__DEFINE_NAME_(HasMmbrFunc17<C1, std::false_type, void>);

RegisterTest(t17, new TestHasMmbrFunc<HasMmbrFunc17_t, bool, &BoolCompare,
    TPair<std::true_type, true>, TPair<std::false_type, false>>);


/**
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	constexpr auto _HasMmbrFunc18(T t, Targs... args) ->
 * 	    decltype((static_cast<T>(t).*(
 *      static_cast<Tr<T1> (T::*)(Targs...)>(&T::Foo1)))(args...),
 * 	        std::true_type());
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	constexpr std::false_type _HasMmbrFunc18 (...);
 * 	template<typename T, typename T1, template<typename> class Tr, 
 *      typename... Targs>
 * 	struct HasMmbrFunc18
 * 	{
 * 	    typedef bool value_type;
 * 	    typedef bool ValueType;
 * 	    static constexpr value_type value =
 * 	        decltype(_HasMmbrFunc18<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	    static constexpr ValueType Value =
 * 	        decltype(_HasMmbrFunc18<typename basic::type::trait::rem::ptr::
 * 	            Recursive<T>::type, T1, Tr, Targs...>(std::declval<
 * 	                typename std::remove_cv<typename basic::type::trait::rem::ptr::
 * 	                    Recursive<T>::type>::type>(), std::declval<
 * 	                    typename std::remove_cv<Targs>::type>()...))::value;
 * 	};
*/

#define __DEFINE_HAS_MMBR_FUNC_TMPL_PARAM_LIST_TPL3(\
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

#define __DEFINE_HAS_MMBR_FUNC_PROTO_FUNC_T_RET_NAME_TMPL_ARG_LIST_PFTRNTAL1()\
T1

__DEFINE_HAS_MMBR_FUNC_(HasMmbrFunc18, _HasMmbrFunc18, T, Tr, Targs,,, TPL3,
    T_NAME_,, PFTTPL3, PFFTPL3, PFTAL1, PROTO_FUNC_T_NAME_,, 
    PROTO_FUNC_T_RET_NAME_TMPL_, PFTRNTAL1, template Foo3<T1>);

template<typename T>
using HasMmbrFunc18_t = HasMmbrFunc18<T, void, C1>;

__DEFINE_NAME_(HasMmbrFunc18<D1, void, C1>);
__DEFINE_NAME_(HasMmbrFunc18<B, void, C1>);

RegisterTest(t18, new TestHasMmbrFunc<HasMmbrFunc18_t, bool, &BoolCompare,
    TPair<D1, true>, TPair<B, false>>);


int main()
{
    return TestRun();
}
