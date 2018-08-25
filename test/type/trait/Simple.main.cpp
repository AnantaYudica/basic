#include "type/trait/Simple.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <sstream>

template<typename T, T TVal>
struct ValueName
{
    static constexpr const char* Value = "undefined"; 
};

#define __DEFINE_VALUE_NAME_(NAME, ...)\
template<>\
struct ValueName<__VA_ARGS__>\
{\
    static constexpr const char* Value = NAME;\
}

template<typename T>
struct Name
{
    static constexpr const char* Value = "undefined";
};

template<typename T, T TVal>
struct Name<ValueName<T, TVal>>
{
    static constexpr const char* Value = ValueName<T, TVal>::Value;
};

#define __DEFINE_NAME_(...)\
template<>\
struct Name<__VA_ARGS__>\
{\
    static constexpr const char* Value = #__VA_ARGS__;\
}

template<typename... Targs>
struct NameParameterTmpl 
{
    static void String(std::string& str, bool first = true)
    {}
};

template<typename T, typename... Targs>
struct NameParameterTmpl<T, Targs...> 
{
    static void String(std::string& str, bool first = true)
    {
        if (!first)
            str += ", ";
        str += Name<T>::Value;
        NameParameterTmpl<Targs...>::String(str, false);
    }
};

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

template<template<typename> class Ts, typename T, typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Ts<T>>::Value;
    error_msg += "<";
    error_msg += Name<T>::Value;
    error_msg += ">::type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts<T>>::Value;
    info_msg += "<";
    info_msg += Name<T>::Value;
    info_msg += ">::type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        std::is_same<typename Ts<T>::type, Tta>::value))
                Info("Pass\n");
}

template<template<typename> class Ts, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Ts<T>>::Value;
    error_msg += "<";
    error_msg += Name<T>::Value;
    error_msg += ">::type is not same with ";
    error_msg += Name<Ts<T>>::Value;
    error_msg += "<";
    error_msg += Name<T>::Value;
    error_msg += ">::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts<T>>::Value;
    info_msg += "<";
    info_msg += Name<T>::Value;
    info_msg += ">::type and ";
    info_msg += Name<Ts<T>>::Value;
    info_msg += "<";
    info_msg += Name<T>::Value;
    info_msg += ">::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        std::is_same<typename Ts<T>::type, typename Ts<T>::Type>::value))
                Info("Pass\n");
}

template<template<typename> class Ts, typename T, typename Tta>
struct TestSimple : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Ts, T, Tta>();
        TestAliasType<Ts, T>();
    };
};

template<typename T>
using Simple1 = basic::type::trait::Simple<T>;

template<typename T>
struct Name<basic::type::trait::Simple<T>>
{
    static constexpr const char * Value = 
        "basic::type::trait::Simple";
};

__DEFINE_NAME_(int);
__DEFINE_NAME_(const int);
__DEFINE_NAME_(volatile int);
__DEFINE_NAME_(const volatile int);

TestRegister t1_1_1(new TestSimple<Simple1, int, int>());
TestRegister t1_1_2(new TestSimple<Simple1, const int, int>());
TestRegister t1_1_3(new TestSimple<Simple1, volatile int, int>());
TestRegister t1_1_4(new TestSimple<Simple1, const volatile int, int>());

__DEFINE_NAME_(int&);
__DEFINE_NAME_(const int&);
__DEFINE_NAME_(volatile int&);
__DEFINE_NAME_(const volatile int&);

TestRegister t1_2_1(new TestSimple<Simple1, int&, int>());
TestRegister t1_2_2(new TestSimple<Simple1, const int&, int>());
TestRegister t1_2_3(new TestSimple<Simple1, volatile int&, int>());
TestRegister t1_2_4(new TestSimple<Simple1, const volatile int&, int>());

__DEFINE_NAME_(int&&);
__DEFINE_NAME_(const int&&);
__DEFINE_NAME_(volatile int&&);
__DEFINE_NAME_(const volatile int&&);

TestRegister t1_3_1(new TestSimple<Simple1, int&&, int>());
TestRegister t1_3_2(new TestSimple<Simple1, const int&&, int>());
TestRegister t1_3_3(new TestSimple<Simple1, volatile int&&, int>());
TestRegister t1_3_4(new TestSimple<Simple1, const volatile int&&, int>());

__DEFINE_NAME_(int*);
__DEFINE_NAME_(const int*);
__DEFINE_NAME_(volatile int*);
__DEFINE_NAME_(const volatile int*);
__DEFINE_NAME_(int*const);
__DEFINE_NAME_(int*volatile);
__DEFINE_NAME_(int*const volatile);

TestRegister t1_4_1(new TestSimple<Simple1, int*, int>());
TestRegister t1_4_2(new TestSimple<Simple1, const int*, int>());
TestRegister t1_4_3(new TestSimple<Simple1, volatile int*, int>());
TestRegister t1_4_4(new TestSimple<Simple1, const volatile int*, int>());
TestRegister t1_4_5(new TestSimple<Simple1, int*const, int>());
TestRegister t1_4_6(new TestSimple<Simple1, int*volatile, int>());
TestRegister t1_4_7(new TestSimple<Simple1, int*const volatile, int>());

__DEFINE_NAME_(int**);
__DEFINE_NAME_(const int**);
__DEFINE_NAME_(volatile int**);
__DEFINE_NAME_(const volatile int**);
__DEFINE_NAME_(int**const);
__DEFINE_NAME_(int**volatile);
__DEFINE_NAME_(int**const volatile);
__DEFINE_NAME_(int*const*);
__DEFINE_NAME_(int*const*const);
__DEFINE_NAME_(int*const*volatile);
__DEFINE_NAME_(int*const*const volatile);
__DEFINE_NAME_(int*volatile*);
__DEFINE_NAME_(int*volatile*const);
__DEFINE_NAME_(int*volatile*volatile);
__DEFINE_NAME_(int*volatile*const volatile);
__DEFINE_NAME_(int*const volatile*);
__DEFINE_NAME_(int*const volatile*const);
__DEFINE_NAME_(int*const volatile*volatile);
__DEFINE_NAME_(int*const volatile*const volatile);

TestRegister t1_5_1(new TestSimple<Simple1, int**, int>());
TestRegister t1_5_2(new TestSimple<Simple1, const int**, int>());
TestRegister t1_5_3(new TestSimple<Simple1, volatile int**, int>());
TestRegister t1_5_4(new TestSimple<Simple1, const volatile int**, int>());
TestRegister t1_5_5(new TestSimple<Simple1, int**const, int>());
TestRegister t1_5_6(new TestSimple<Simple1, int**volatile, int>());
TestRegister t1_5_7(new TestSimple<Simple1, int**const volatile, int>());
TestRegister t1_5_8(new TestSimple<Simple1, int*const*, int>());
TestRegister t1_5_9(new TestSimple<Simple1, int*const*const, int>());
TestRegister t1_5_10(new TestSimple<Simple1, int*const*volatile, int>());
TestRegister t1_5_11(new TestSimple<Simple1, 
    int*const*const volatile, int>());
TestRegister t1_5_12(new TestSimple<Simple1, int*volatile*, int>());
TestRegister t1_5_13(new TestSimple<Simple1, int*volatile*const, int>());
TestRegister t1_5_14(new TestSimple<Simple1, 
    int*volatile*volatile, int>());
TestRegister t1_5_15(new TestSimple<Simple1, 
    int*volatile*const volatile, int>());
TestRegister t1_5_16(new TestSimple<Simple1, int*const volatile*, int>());
TestRegister t1_5_17(new TestSimple<Simple1, 
    int*const volatile*const, int>());
TestRegister t1_5_18(new TestSimple<Simple1, 
    int*const volatile*volatile, int>());
TestRegister t1_5_19(new TestSimple<Simple1, 
    int*const volatile*const volatile, int>());

__DEFINE_NAME_(int[]);
__DEFINE_NAME_(const int[]);
__DEFINE_NAME_(volatile int[]);
__DEFINE_NAME_(const volatile int[]);

TestRegister t1_6_1(new TestSimple<Simple1, int[], int>());
TestRegister t1_6_2(new TestSimple<Simple1, const int[], int>());
TestRegister t1_6_3(new TestSimple<Simple1, volatile int[], int>());
TestRegister t1_6_4(new TestSimple<Simple1, const volatile int[], int>());

__DEFINE_NAME_(int(&)[]);
__DEFINE_NAME_(const int(&)[]);
__DEFINE_NAME_(volatile int(&)[]);
__DEFINE_NAME_(const volatile int(&)[]);

TestRegister t1_7_1(new TestSimple<Simple1, int(&)[], int>());
TestRegister t1_7_2(new TestSimple<Simple1, const int(&)[], int>());
TestRegister t1_7_3(new TestSimple<Simple1, volatile int(&)[], int>());
TestRegister t1_7_4(new TestSimple<Simple1, const volatile int(&)[], int>());

__DEFINE_NAME_(int(&&)[]);
__DEFINE_NAME_(const int(&&)[]);
__DEFINE_NAME_(volatile int(&&)[]);
__DEFINE_NAME_(const volatile int(&&)[]);

TestRegister t1_8_1(new TestSimple<Simple1, int(&&)[], int>());
TestRegister t1_8_2(new TestSimple<Simple1, const int(&&)[], int>());
TestRegister t1_8_3(new TestSimple<Simple1, volatile int(&&)[], int>());
TestRegister t1_8_4(new TestSimple<Simple1, const volatile int(&&)[], int>());

__DEFINE_NAME_(int(*)[]);
__DEFINE_NAME_(const int(*)[]);
__DEFINE_NAME_(volatile int(*)[]);
__DEFINE_NAME_(const volatile int(*)[]);
__DEFINE_NAME_(int(*const)[]);
__DEFINE_NAME_(int(*volatile)[]);
__DEFINE_NAME_(int(*const volatile)[]);

TestRegister t1_9_1(new TestSimple<Simple1, int(*)[], int>());
TestRegister t1_9_2(new TestSimple<Simple1, const int(*)[], int>());
TestRegister t1_9_3(new TestSimple<Simple1, volatile int(*)[], int>());
TestRegister t1_9_4(new TestSimple<Simple1, const volatile int(*)[], int>());
TestRegister t1_9_5(new TestSimple<Simple1, int(*const)[], int>());
TestRegister t1_9_6(new TestSimple<Simple1, int(*volatile)[], int>());
TestRegister t1_9_7(new TestSimple<Simple1, int(*const volatile)[], int>());

__DEFINE_NAME_(int(**)[]);
__DEFINE_NAME_(const int(**)[]);
__DEFINE_NAME_(volatile int(**)[]);
__DEFINE_NAME_(const volatile int(**)[]);
__DEFINE_NAME_(int(**const)[]);
__DEFINE_NAME_(int(**volatile)[]);
__DEFINE_NAME_(int(**const volatile)[]);
__DEFINE_NAME_(int(*const*)[]);
__DEFINE_NAME_(int(*const*const)[]);
__DEFINE_NAME_(int(*const*volatile)[]);
__DEFINE_NAME_(int(*const*const volatile)[]);
__DEFINE_NAME_(int(*volatile*)[]);
__DEFINE_NAME_(int(*volatile*const)[]);
__DEFINE_NAME_(int(*volatile*volatile)[]);
__DEFINE_NAME_(int(*volatile*const volatile)[]);
__DEFINE_NAME_(int(*const volatile*)[]);
__DEFINE_NAME_(int(*const volatile*const)[]);
__DEFINE_NAME_(int(*const volatile*volatile)[]);
__DEFINE_NAME_(int(*const volatile*const volatile)[]);

TestRegister t1_10_1(new TestSimple<Simple1, int(**)[], int>());
TestRegister t1_10_2(new TestSimple<Simple1, const int(**)[], int>());
TestRegister t1_10_3(new TestSimple<Simple1, volatile int(**)[], int>());
TestRegister t1_10_4(new TestSimple<Simple1, const volatile int(**)[], int>());
TestRegister t1_10_5(new TestSimple<Simple1, int(**const)[], int>());
TestRegister t1_10_6(new TestSimple<Simple1, int(**volatile)[], int>());
TestRegister t1_10_7(new TestSimple<Simple1, int(**const volatile)[], int>());
TestRegister t1_10_8(new TestSimple<Simple1, int(*const*)[], int>());
TestRegister t1_10_9(new TestSimple<Simple1, int(*const*const)[], int>());
TestRegister t1_10_10(new TestSimple<Simple1, int(*const*volatile)[], int>());
TestRegister t1_10_11(new TestSimple<Simple1, int(*const*const volatile)[], 
    int>());
TestRegister t1_10_12(new TestSimple<Simple1, int(*volatile*)[], int>());
TestRegister t1_10_13(new TestSimple<Simple1, int(*volatile*const)[], int>());
TestRegister t1_10_14(new TestSimple<Simple1, int(*volatile*volatile)[], 
    int>());
TestRegister t1_10_15(new TestSimple<Simple1, int(*volatile*const volatile)[], 
    int>());
TestRegister t1_10_16(new TestSimple<Simple1, int(*const volatile*)[], int>());
TestRegister t1_10_17(new TestSimple<Simple1, int(*const volatile*const)[],
    int>());
TestRegister t1_10_18(new TestSimple<Simple1, int(*const volatile*volatile)[],
    int>());
TestRegister t1_10_19(new TestSimple<Simple1, 
    int(*const volatile*const volatile)[], int>());

__DEFINE_NAME_(int[1]);
__DEFINE_NAME_(const int[1]);
__DEFINE_NAME_(volatile int[1]);
__DEFINE_NAME_(const volatile int[1]);

TestRegister t1_11_1(new TestSimple<Simple1, int[1], int>());
TestRegister t1_11_2(new TestSimple<Simple1, const int[1], int>());
TestRegister t1_11_3(new TestSimple<Simple1, volatile int[1], int>());
TestRegister t1_11_4(new TestSimple<Simple1, const volatile int[1], int>());

__DEFINE_NAME_(int(&)[1]);
__DEFINE_NAME_(const int(&)[1]);
__DEFINE_NAME_(volatile int(&)[1]);
__DEFINE_NAME_(const volatile int(&)[1]);

TestRegister t1_12_1(new TestSimple<Simple1, int(&)[1], int>());
TestRegister t1_12_2(new TestSimple<Simple1, const int(&)[1], int>());
TestRegister t1_12_3(new TestSimple<Simple1, volatile int(&)[1], int>());
TestRegister t1_12_4(new TestSimple<Simple1, const volatile int(&)[1], int>());

__DEFINE_NAME_(int(&&)[1]);
__DEFINE_NAME_(const int(&&)[1]);
__DEFINE_NAME_(volatile int(&&)[1]);
__DEFINE_NAME_(const volatile int(&&)[1]);

TestRegister t1_13_1(new TestSimple<Simple1, int(&&)[1], int>());
TestRegister t1_13_2(new TestSimple<Simple1, const int(&&)[1], int>());
TestRegister t1_13_3(new TestSimple<Simple1, volatile int(&&)[1], int>());
TestRegister t1_13_4(new TestSimple<Simple1, const volatile int(&&)[1], 
    int>());

__DEFINE_NAME_(int(*)[1]);
__DEFINE_NAME_(const int(*)[1]);
__DEFINE_NAME_(volatile int(*)[1]);
__DEFINE_NAME_(const volatile int(*)[1]);
__DEFINE_NAME_(int(*const)[1]);
__DEFINE_NAME_(int(*volatile)[1]);
__DEFINE_NAME_(int(*const volatile)[1]);

TestRegister t1_14_1(new TestSimple<Simple1, int(*)[1], int>());
TestRegister t1_14_2(new TestSimple<Simple1, const int(*)[1], int>());
TestRegister t1_14_3(new TestSimple<Simple1, volatile int(*)[1], int>());
TestRegister t1_14_4(new TestSimple<Simple1, const volatile int(*)[1], int>());
TestRegister t1_14_5(new TestSimple<Simple1, int(*const)[1], int>());
TestRegister t1_14_6(new TestSimple<Simple1, int(*volatile)[1], int>());
TestRegister t1_14_7(new TestSimple<Simple1, int(*const volatile)[1], int>());

__DEFINE_NAME_(int(**)[1]);
__DEFINE_NAME_(const int(**)[1]);
__DEFINE_NAME_(volatile int(**)[1]);
__DEFINE_NAME_(const volatile int(**)[1]);
__DEFINE_NAME_(int(**const)[1]);
__DEFINE_NAME_(int(**volatile)[1]);
__DEFINE_NAME_(int(**const volatile)[1]);
__DEFINE_NAME_(int(*const*)[1]);
__DEFINE_NAME_(int(*const*const)[1]);
__DEFINE_NAME_(int(*const*volatile)[1]);
__DEFINE_NAME_(int(*const*const volatile)[1]);
__DEFINE_NAME_(int(*volatile*)[1]);
__DEFINE_NAME_(int(*volatile*const)[1]);
__DEFINE_NAME_(int(*volatile*volatile)[1]);
__DEFINE_NAME_(int(*volatile*const volatile)[1]);
__DEFINE_NAME_(int(*const volatile*)[1]);
__DEFINE_NAME_(int(*const volatile*const)[1]);
__DEFINE_NAME_(int(*const volatile*volatile)[1]);
__DEFINE_NAME_(int(*const volatile*const volatile)[1]);

TestRegister t1_15_1(new TestSimple<Simple1, int(**)[1], int>());
TestRegister t1_15_2(new TestSimple<Simple1, const int(**)[1], int>());
TestRegister t1_15_3(new TestSimple<Simple1, volatile int(**)[1], int>());
TestRegister t1_15_4(new TestSimple<Simple1, const volatile int(**)[1], 
    int>());
TestRegister t1_15_5(new TestSimple<Simple1, int(**const)[1], int>());
TestRegister t1_15_6(new TestSimple<Simple1, int(**volatile)[1], int>());
TestRegister t1_15_7(new TestSimple<Simple1, int(**const volatile)[1], int>());
TestRegister t1_15_8(new TestSimple<Simple1, int(*const*)[1], int>());
TestRegister t1_15_9(new TestSimple<Simple1, int(*const*const)[1], int>());
TestRegister t1_15_10(new TestSimple<Simple1, int(*const*volatile)[1], int>());
TestRegister t1_15_11(new TestSimple<Simple1, int(*const*const volatile)[1], 
    int>());
TestRegister t1_15_12(new TestSimple<Simple1, int(*volatile*)[1], int>());
TestRegister t1_15_13(new TestSimple<Simple1, int(*volatile*const)[1], int>());
TestRegister t1_15_14(new TestSimple<Simple1, int(*volatile*volatile)[1],
    int>());
TestRegister t1_15_15(new TestSimple<Simple1, int(*volatile*const volatile)[1], 
    int>());
TestRegister t1_15_16(new TestSimple<Simple1, int(*const volatile*)[1], 
    int>());
TestRegister t1_15_17(new TestSimple<Simple1, int(*const volatile*const)[1], 
    int>());
TestRegister t1_15_18(new TestSimple<Simple1, int(*const volatile*volatile)[1],
    int>());
TestRegister t1_15_19(new TestSimple<Simple1, 
    int(*const volatile*const volatile)[1], int>());

__DEFINE_NAME_(int());
__DEFINE_NAME_(int(char));
__DEFINE_NAME_(int(char, short));
__DEFINE_NAME_(int(char, short, int, long));
__DEFINE_NAME_(const int());
__DEFINE_NAME_(volatile int());
__DEFINE_NAME_(const volatile int());
__DEFINE_NAME_(int() const);
__DEFINE_NAME_(int() volatile);
__DEFINE_NAME_(int() const volatile);
__DEFINE_NAME_(int() &);
__DEFINE_NAME_(int() const &);
__DEFINE_NAME_(int() volatile &);
__DEFINE_NAME_(int() const volatile &);
__DEFINE_NAME_(int() &&);
__DEFINE_NAME_(int() const &&);
__DEFINE_NAME_(int() volatile &&);
__DEFINE_NAME_(int() const volatile &&);

TestRegister t1_16_1(new TestSimple<Simple1, int(), int>());
TestRegister t1_16_2(new TestSimple<Simple1, int(char), int>());
TestRegister t1_16_3(new TestSimple<Simple1, int(char, short), int>());
TestRegister t1_16_4(new TestSimple<Simple1, int(char, short, int, long),
    int>());
TestRegister t1_16_5(new TestSimple<Simple1, const int(), int>());
TestRegister t1_16_6(new TestSimple<Simple1, volatile int(), int>());
TestRegister t1_16_7(new TestSimple<Simple1, const volatile int(), int>());
TestRegister t1_16_8(new TestSimple<Simple1, int() const, int>());
TestRegister t1_16_9(new TestSimple<Simple1, int() volatile, int>());
TestRegister t1_16_10(new TestSimple<Simple1, int() const volatile, int>());
TestRegister t1_16_11(new TestSimple<Simple1, int() &, int>());
TestRegister t1_16_12(new TestSimple<Simple1, int() const &, int>());
TestRegister t1_16_13(new TestSimple<Simple1, int() volatile &, int>());
TestRegister t1_16_14(new TestSimple<Simple1, int() const volatile &, int>());
TestRegister t1_16_15(new TestSimple<Simple1, int() &&, int>());
TestRegister t1_16_16(new TestSimple<Simple1, int() const &&, int>());
TestRegister t1_16_17(new TestSimple<Simple1, int() volatile &&, int>());
TestRegister t1_16_18(new TestSimple<Simple1, int() const volatile &&, int>());

__DEFINE_NAME_(int(&)());
__DEFINE_NAME_(int(&)(char));
__DEFINE_NAME_(int(&)(char, short));
__DEFINE_NAME_(int(&)(char, short, int, long));
__DEFINE_NAME_(const int(&)());
__DEFINE_NAME_(volatile int(&)());
__DEFINE_NAME_(const volatile int(&)());

TestRegister t1_17_1(new TestSimple<Simple1, int(&)(), int>());
TestRegister t1_17_2(new TestSimple<Simple1, int(&)(char), int>());
TestRegister t1_17_3(new TestSimple<Simple1, int(&)(char, short), int>());
TestRegister t1_17_4(new TestSimple<Simple1, int(&)(char, short, int, long), 
    int>());
TestRegister t1_17_5(new TestSimple<Simple1, const int(&)(), int>());
TestRegister t1_17_6(new TestSimple<Simple1, volatile int(&)(), int>());
TestRegister t1_17_7(new TestSimple<Simple1, const volatile int(&)(), int>());

__DEFINE_NAME_(int(&&)());
__DEFINE_NAME_(int(&&)(char));
__DEFINE_NAME_(int(&&)(char, short));
__DEFINE_NAME_(int(&&)(char, short, int, long));
__DEFINE_NAME_(const int(&&)());
__DEFINE_NAME_(volatile int(&&)());
__DEFINE_NAME_(const volatile int(&&)());

TestRegister t1_18_1(new TestSimple<Simple1, int(&&)(), int>());
TestRegister t1_18_2(new TestSimple<Simple1, int(&&)(char), int>());
TestRegister t1_18_3(new TestSimple<Simple1, int(&&)(char, short), int>());
TestRegister t1_18_4(new TestSimple<Simple1, int(&&)(char, short, int, long), 
    int>());
TestRegister t1_18_5(new TestSimple<Simple1, const int(&&)(), int>());
TestRegister t1_18_6(new TestSimple<Simple1, volatile int(&&)(), int>());
TestRegister t1_18_7(new TestSimple<Simple1, const volatile int(&&)(), int>());

__DEFINE_NAME_(int(*)());
__DEFINE_NAME_(int(*)(char));
__DEFINE_NAME_(int(*)(char, short));
__DEFINE_NAME_(int(*)(char, short, int, long));
__DEFINE_NAME_(const int(*)());
__DEFINE_NAME_(volatile int(*)());
__DEFINE_NAME_(const volatile int(*)());
__DEFINE_NAME_(int(*const)());
__DEFINE_NAME_(int(*volatile)());
__DEFINE_NAME_(int(*const volatile)());

TestRegister t1_19_1(new TestSimple<Simple1, int(*)(), int>());
TestRegister t1_19_2(new TestSimple<Simple1, int(*)(char), int>());
TestRegister t1_19_3(new TestSimple<Simple1, int(*)(char, short), int>());
TestRegister t1_19_4(new TestSimple<Simple1, int(*)(char, short, int, long),
    int>());
TestRegister t1_19_5(new TestSimple<Simple1, const int(*)(), int>());
TestRegister t1_19_6(new TestSimple<Simple1, volatile int(*)(), int>());
TestRegister t1_19_7(new TestSimple<Simple1, const volatile int(*)(), int>());
TestRegister t1_19_8(new TestSimple<Simple1, int(*const)(), int>());
TestRegister t1_19_9(new TestSimple<Simple1, int(*volatile)(), int>());
TestRegister t1_19_10(new TestSimple<Simple1, int(*const volatile)(), int>());

__DEFINE_NAME_(int(**)());
__DEFINE_NAME_(int(**)(char));
__DEFINE_NAME_(int(**)(char, short));
__DEFINE_NAME_(int(**)(char, short, int, long));
__DEFINE_NAME_(const int(**)());
__DEFINE_NAME_(volatile int(**)());
__DEFINE_NAME_(const volatile int(**)());
__DEFINE_NAME_(int(**const)());
__DEFINE_NAME_(int(**volatile)());
__DEFINE_NAME_(int(**const volatile)());
__DEFINE_NAME_(int(*const*)());
__DEFINE_NAME_(int(*const*const)());
__DEFINE_NAME_(int(*const*volatile)());
__DEFINE_NAME_(int(*const*const volatile)());
__DEFINE_NAME_(int(*volatile*)());
__DEFINE_NAME_(int(*volatile*const)());
__DEFINE_NAME_(int(*volatile*volatile)());
__DEFINE_NAME_(int(*volatile*const volatile)());
__DEFINE_NAME_(int(*const volatile*)());
__DEFINE_NAME_(int(*const volatile*const)());
__DEFINE_NAME_(int(*const volatile*volatile)());
__DEFINE_NAME_(int(*const volatile*const volatile)());

TestRegister t1_20_1(new TestSimple<Simple1, int(**)(), int>());
TestRegister t1_20_2(new TestSimple<Simple1, int(**)(char), int>());
TestRegister t1_20_3(new TestSimple<Simple1, int(**)(char, short), int>());
TestRegister t1_20_4(new TestSimple<Simple1, int(**)(char, short, int, long), 
    int>());
TestRegister t1_20_5(new TestSimple<Simple1, const int(**)(), int>());
TestRegister t1_20_6(new TestSimple<Simple1, volatile int(**)(), int>());
TestRegister t1_20_7(new TestSimple<Simple1, const volatile int(**)(), int>());
TestRegister t1_20_8(new TestSimple<Simple1, int(**const)(), int>());
TestRegister t1_20_9(new TestSimple<Simple1, int(**volatile)(), int>());
TestRegister t1_20_10(new TestSimple<Simple1, int(**const volatile)(), int>());
TestRegister t1_20_11(new TestSimple<Simple1, int(*const*)(), int>());
TestRegister t1_20_12(new TestSimple<Simple1, int(*const*const)(), int>());
TestRegister t1_20_13(new TestSimple<Simple1, int(*const*volatile)(), int>());
TestRegister t1_20_14(new TestSimple<Simple1, int(*const*const volatile)(), 
    int>());
TestRegister t1_20_15(new TestSimple<Simple1, int(*volatile*)(), int>());
TestRegister t1_20_16(new TestSimple<Simple1, int(*volatile*const)(), int>());
TestRegister t1_20_17(new TestSimple<Simple1, int(*volatile*volatile)(), 
    int>());
TestRegister t1_20_18(new TestSimple<Simple1, int(*volatile*const volatile)(), 
    int>());
TestRegister t1_20_19(new TestSimple<Simple1, int(*const volatile*)(), int>());
TestRegister t1_20_20(new TestSimple<Simple1, int(*const volatile*const)(),
    int>());
TestRegister t1_20_21(new TestSimple<Simple1, int(*const volatile*volatile)(), 
    int>());
TestRegister t1_20_22(new TestSimple<Simple1, 
    int(*const volatile*const volatile)(), int>());

struct A
{};

__DEFINE_NAME_(int A::*);
__DEFINE_NAME_(const int A::*);
__DEFINE_NAME_(volatile int A::*);
__DEFINE_NAME_(const volatile int A::*);
__DEFINE_NAME_(int A::*const);
__DEFINE_NAME_(int A::*volatile);
__DEFINE_NAME_(int A::*const volatile);

TestRegister t1_21_1(new TestSimple<Simple1, int A::*, int>());
TestRegister t1_21_2(new TestSimple<Simple1, const int A::*, int>());
TestRegister t1_21_3(new TestSimple<Simple1, volatile int A::*, int>());
TestRegister t1_21_4(new TestSimple<Simple1, const volatile int A::*, int>());
TestRegister t1_21_5(new TestSimple<Simple1, int A::*const, int>());
TestRegister t1_21_6(new TestSimple<Simple1, int A::*volatile, int>());
TestRegister t1_21_7(new TestSimple<Simple1, int A::*const volatile, int>());

__DEFINE_NAME_(int A::**);
__DEFINE_NAME_(const int A::**);
__DEFINE_NAME_(volatile int A::**);
__DEFINE_NAME_(const volatile int A::**);
__DEFINE_NAME_(int A::**const);
__DEFINE_NAME_(int A::**volatile);
__DEFINE_NAME_(int A::**const volatile);
__DEFINE_NAME_(int A::*const*);
__DEFINE_NAME_(int A::*const*const);
__DEFINE_NAME_(int A::*const*volatile);
__DEFINE_NAME_(int A::*const*const volatile);
__DEFINE_NAME_(int A::*volatile*);
__DEFINE_NAME_(int A::*volatile*const);
__DEFINE_NAME_(int A::*volatile*volatile);
__DEFINE_NAME_(int A::*volatile*const volatile);
__DEFINE_NAME_(int A::*const volatile*);
__DEFINE_NAME_(int A::*const volatile*const);
__DEFINE_NAME_(int A::*const volatile*volatile);
__DEFINE_NAME_(int A::*const volatile*const volatile);

TestRegister t1_22_1(new TestSimple<Simple1, int A::**, int>());
TestRegister t1_22_2(new TestSimple<Simple1, const int A::**, int>());
TestRegister t1_22_3(new TestSimple<Simple1, volatile int A::**, int>());
TestRegister t1_22_4(new TestSimple<Simple1, const volatile int A::**, int>());
TestRegister t1_22_5(new TestSimple<Simple1, int A::**const, int>());
TestRegister t1_22_6(new TestSimple<Simple1, int A::**volatile, int>());
TestRegister t1_22_7(new TestSimple<Simple1, int A::**const volatile, int>());
TestRegister t1_22_8(new TestSimple<Simple1, int A::*const*, int>());
TestRegister t1_22_9(new TestSimple<Simple1, int A::*const*const, int>());
TestRegister t1_22_10(new TestSimple<Simple1, int A::*const*volatile, int>());
TestRegister t1_22_11(new TestSimple<Simple1, int A::*const*const volatile, 
    int>());
TestRegister t1_22_12(new TestSimple<Simple1, int A::*volatile*, int>());
TestRegister t1_22_13(new TestSimple<Simple1, int A::*volatile*const, int>());
TestRegister t1_22_14(new TestSimple<Simple1, int A::*volatile*volatile, 
    int>());
TestRegister t1_22_15(new TestSimple<Simple1, int A::*volatile*const volatile,
    int>());
TestRegister t1_22_16(new TestSimple<Simple1, int A::*const volatile*, int>());
TestRegister t1_22_17(new TestSimple<Simple1, int A::*const volatile*const, 
    int>());
TestRegister t1_22_18(new TestSimple<Simple1, int A::*const volatile*volatile, 
    int>());
TestRegister t1_22_19(new TestSimple<Simple1, 
    int A::*const volatile*const volatile, int>());

__DEFINE_NAME_(int(A::*)());
__DEFINE_NAME_(int(A::*)(char));
__DEFINE_NAME_(int(A::*)(char, short));
__DEFINE_NAME_(int(A::*)(char, short, int, long));
__DEFINE_NAME_(const int(A::*)());
__DEFINE_NAME_(volatile int(A::*)());
__DEFINE_NAME_(const volatile int(A::*)());
__DEFINE_NAME_(int(A::*)() const);
__DEFINE_NAME_(int(A::*)() volatile);
__DEFINE_NAME_(int(A::*)() const volatile);
__DEFINE_NAME_(int(A::*)() &);
__DEFINE_NAME_(int(A::*)() const &);
__DEFINE_NAME_(int(A::*)() volatile &);
__DEFINE_NAME_(int(A::*)() const volatile &);
__DEFINE_NAME_(int(A::*)() &&);
__DEFINE_NAME_(int(A::*)() const &&);
__DEFINE_NAME_(int(A::*)() volatile &&);
__DEFINE_NAME_(int(A::*)() const volatile &&);
__DEFINE_NAME_(int(A::*const)());
__DEFINE_NAME_(int(A::*volatile)());
__DEFINE_NAME_(int(A::*const volatile)());

TestRegister t1_23_1(new TestSimple<Simple1, int(A::*)(), int>());
TestRegister t1_23_2(new TestSimple<Simple1, int(A::*)(char), int>());
TestRegister t1_23_3(new TestSimple<Simple1, int(A::*)(char, short), int>());
TestRegister t1_23_4(new TestSimple<Simple1, int(A::*)(char, short, int, long),
    int>());
TestRegister t1_23_5(new TestSimple<Simple1, const int(A::*)(), int>());
TestRegister t1_23_6(new TestSimple<Simple1, volatile int(A::*)(), int>());
TestRegister t1_23_7(new TestSimple<Simple1, const volatile int(A::*)(), 
    int>());
TestRegister t1_23_8(new TestSimple<Simple1, int(A::*)() const, int>());
TestRegister t1_23_9(new TestSimple<Simple1, int(A::*)() volatile, int>());
TestRegister t1_23_10(new TestSimple<Simple1, int(A::*)() const volatile, 
    int>());
TestRegister t1_23_11(new TestSimple<Simple1, int(A::*)() &, int>());
TestRegister t1_23_12(new TestSimple<Simple1, int(A::*)() const &, int>());
TestRegister t1_23_13(new TestSimple<Simple1, int(A::*)() volatile &, 
    int>());
TestRegister t1_23_14(new TestSimple<Simple1, int(A::*)() const volatile &, 
    int>());
TestRegister t1_23_15(new TestSimple<Simple1, int(A::*)() &&, int>());
TestRegister t1_23_16(new TestSimple<Simple1, int(A::*)() const &&, int>());
TestRegister t1_23_17(new TestSimple<Simple1, int(A::*)() volatile &&, int>());
TestRegister t1_23_18(new TestSimple<Simple1, int(A::*)() const volatile &&, 
    int>());
TestRegister t1_23_19(new TestSimple<Simple1, int(A::*const)(), int>());
TestRegister t1_23_20(new TestSimple<Simple1, int(A::*volatile)(), int>());
TestRegister t1_23_21(new TestSimple<Simple1, int(A::*const volatile)(), 
    int>());

__DEFINE_NAME_(int(A::**)());
__DEFINE_NAME_(int(A::**)(char));
__DEFINE_NAME_(int(A::**)(char, short));
__DEFINE_NAME_(int(A::**)(char, short, int, long));
__DEFINE_NAME_(const int(A::**)());
__DEFINE_NAME_(volatile int(A::**)());
__DEFINE_NAME_(const volatile int(A::**)());
__DEFINE_NAME_(int(A::**)() const);
__DEFINE_NAME_(int(A::**)() volatile);
__DEFINE_NAME_(int(A::**)() const volatile);
__DEFINE_NAME_(int(A::**)() &);
__DEFINE_NAME_(int(A::**)() const &);
__DEFINE_NAME_(int(A::**)() volatile &);
__DEFINE_NAME_(int(A::**)() const volatile &);
__DEFINE_NAME_(int(A::**)() &&);
__DEFINE_NAME_(int(A::**)() const &&);
__DEFINE_NAME_(int(A::**)() volatile &&);
__DEFINE_NAME_(int(A::**)() const volatile &&);
__DEFINE_NAME_(int(A::**const)());
__DEFINE_NAME_(int(A::**volatile)());
__DEFINE_NAME_(int(A::**const volatile)());
__DEFINE_NAME_(int(A::*const*)());
__DEFINE_NAME_(int(A::*const*const)());
__DEFINE_NAME_(int(A::*const*volatile)());
__DEFINE_NAME_(int(A::*const*const volatile)());
__DEFINE_NAME_(int(A::*volatile*)());
__DEFINE_NAME_(int(A::*volatile*const)());
__DEFINE_NAME_(int(A::*volatile*volatile)());
__DEFINE_NAME_(int(A::*volatile*const volatile)());
__DEFINE_NAME_(int(A::*const volatile*)());
__DEFINE_NAME_(int(A::*const volatile*const)());
__DEFINE_NAME_(int(A::*const volatile*volatile)());
__DEFINE_NAME_(int(A::*const volatile*const volatile)());

TestRegister t1_24_1(new TestSimple<Simple1, int(A::**)(), int>());
TestRegister t1_24_2(new TestSimple<Simple1, int(A::**)(char), int>());
TestRegister t1_24_3(new TestSimple<Simple1, int(A::**)(char, short), int>());
TestRegister t1_24_4(new TestSimple<Simple1, 
    int(A::**)(char, short, int, long), int>());
TestRegister t1_24_5(new TestSimple<Simple1, const int(A::**)(), int>());
TestRegister t1_24_6(new TestSimple<Simple1, volatile int(A::**)(), int>());
TestRegister t1_24_7(new TestSimple<Simple1, const volatile int(A::**)(), 
    int>());
TestRegister t1_24_8(new TestSimple<Simple1, int(A::**)() const, int>());
TestRegister t1_24_9(new TestSimple<Simple1, int(A::**)() volatile, int>());
TestRegister t1_24_10(new TestSimple<Simple1, int(A::**)() const volatile, 
    int>());
TestRegister t1_24_11(new TestSimple<Simple1, int(A::**)() &, int>());
TestRegister t1_24_12(new TestSimple<Simple1, int(A::**)() const &, int>());
TestRegister t1_24_13(new TestSimple<Simple1, int(A::**)() volatile &, int>());
TestRegister t1_24_14(new TestSimple<Simple1, int(A::**)() const volatile &, 
    int>());
TestRegister t1_24_15(new TestSimple<Simple1, int(A::**)() &&, int>());
TestRegister t1_24_16(new TestSimple<Simple1, int(A::**)() const &&, int>());
TestRegister t1_24_17(new TestSimple<Simple1, int(A::**)() volatile &&, 
    int>());
TestRegister t1_24_18(new TestSimple<Simple1, int(A::**)() const volatile &&, 
    int>());
TestRegister t1_24_19(new TestSimple<Simple1, int(A::**const)(), int>());
TestRegister t1_24_20(new TestSimple<Simple1, int(A::**volatile)(), int>());
TestRegister t1_24_21(new TestSimple<Simple1, int(A::**const volatile)(), 
    int>());
TestRegister t1_24_22(new TestSimple<Simple1, int(A::*const*)(), int>());
TestRegister t1_24_23(new TestSimple<Simple1, int(A::*const*const)(), int>());
TestRegister t1_24_24(new TestSimple<Simple1, int(A::*const*volatile)(), 
    int>());
TestRegister t1_24_25(new TestSimple<Simple1, int(A::*const*const volatile)(),
    int>());
TestRegister t1_24_26(new TestSimple<Simple1, int(A::*volatile*)(), int>());
TestRegister t1_24_27(new TestSimple<Simple1, int(A::*volatile*const)(), 
    int>());
TestRegister t1_24_28(new TestSimple<Simple1, int(A::*volatile*volatile)(), 
    int>());
TestRegister t1_24_29(new TestSimple<Simple1, 
    int(A::*volatile*const volatile)(), int>());
TestRegister t1_24_30(new TestSimple<Simple1, int(A::*const volatile*)(),
    int>());
TestRegister t1_24_31(new TestSimple<Simple1, int(A::*const volatile*const)(),
    int>());
TestRegister t1_24_32(new TestSimple<Simple1, 
    int(A::*const volatile*volatile)(), int>());
TestRegister t1_24_33(new TestSimple<Simple1, 
    int(A::*const volatile*const volatile)(), int>());

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
