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
struct TestHasMmbrFunc : basic::test::Base
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thmf, T, Ttavt>();
        TestAliasType<Thmf, T>();
        TestValueAndTargetValue<Thmf, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thmf, T, Ttavt, Compare>();
    }
};

int main()
{
    return TestRun();
}
