#include "type/Name.h"
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


template<template<typename> class Tn, typename T,
    typename Tta>
void TestCompareToString(Tta target)
{
    std::string error_msg = Name<Tn<T>>::Value;
    error_msg += "<";
    error_msg += Name<T>::Value;
    error_msg += ">::ToString() is not same with ";
    error_msg += "\"";
    error_msg += target;
    error_msg += "\"";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Tn<T>>::Value;
    info_msg += "<";
    info_msg += Name<T>::Value;
    info_msg += ">::ToString() and \"";
    info_msg += target;
    info_msg += "\" : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Tn<T>::ToString().compare(target) == 0))
            Info("Pass\n");
}

template<template<typename> class Tn, typename T, typename Tta>
struct TestName : BaseTest
{
    Tta m_target;
    TestName(Tta target) : m_target(target)
    {};
    void Test() 
    {
        TestCompareToString<Tn, T, Tta>(m_target);
    };
};

template<typename T>
struct Name<basic::type::Name<T>>
{
    static constexpr const char * Value = 
        "basic::type::Name";
};

__DEFINE_NAME_(void);
__DEFINE_NAME_(std::nullptr_t);
__DEFINE_NAME_(char);
__DEFINE_NAME_(short);
__DEFINE_NAME_(int);
__DEFINE_NAME_(const int);
__DEFINE_NAME_(volatile int);
__DEFINE_NAME_(const volatile int);
__DEFINE_NAME_(long);
__DEFINE_NAME_(long long);
__DEFINE_NAME_(unsigned char);
__DEFINE_NAME_(unsigned short);
__DEFINE_NAME_(unsigned int);
__DEFINE_NAME_(unsigned long);
__DEFINE_NAME_(unsigned long long);
__DEFINE_NAME_(float);
__DEFINE_NAME_(double);
__DEFINE_NAME_(long double);

TestRegister t1_1_1(new TestName<basic::type::Name, void, 
    std::string>("void"));
TestRegister t1_1_2(new TestName<basic::type::Name, std::nullptr_t, 
    std::string>("std::nullptr_t"));
TestRegister t1_1_3(new TestName<basic::type::Name, char, 
    std::string>("char"));
TestRegister t1_1_4(new TestName<basic::type::Name, short, 
    std::string>("short"));
TestRegister t1_1_5(new TestName<basic::type::Name, int, 
    std::string>("int"));
TestRegister t1_1_6(new TestName<basic::type::Name, const int,
    std::string>("const int"));
TestRegister t1_1_7(new TestName<basic::type::Name, volatile int, 
    std::string>("volatile int"));
TestRegister t1_1_8(new TestName<basic::type::Name, const volatile int, 
    std::string>("const volatile int"));
TestRegister t1_1_9(new TestName<basic::type::Name, long, 
    std::string>("long"));
TestRegister t1_1_10(new TestName<basic::type::Name, long long, 
    std::string>("long long"));
TestRegister t1_1_11(new TestName<basic::type::Name, unsigned char, 
    std::string>("unsigned char"));
TestRegister t1_1_12(new TestName<basic::type::Name, unsigned short, 
    std::string>("unsigned short"));
TestRegister t1_1_13(new TestName<basic::type::Name, unsigned int, 
    std::string>("unsigned int"));
TestRegister t1_1_14(new TestName<basic::type::Name, unsigned long, 
    std::string>("unsigned long"));
TestRegister t1_1_15(new TestName<basic::type::Name, unsigned long long, 
    std::string>("unsigned long long"));
TestRegister t1_1_16(new TestName<basic::type::Name, float, 
    std::string>("float"));
TestRegister t1_1_17(new TestName<basic::type::Name, double, 
    std::string>("double"));
TestRegister t1_1_18(new TestName<basic::type::Name, long double, 
    std::string>("long double"));

__DEFINE_NAME_(int&);
__DEFINE_NAME_(const int&);
__DEFINE_NAME_(volatile int&);
__DEFINE_NAME_(const volatile int&);

TestRegister t1_2_1(new TestName<basic::type::Name, int&,
    std::string>("int&"));
TestRegister t1_2_2(new TestName<basic::type::Name, const int&, 
    std::string>("const int&"));
TestRegister t1_2_3(new TestName<basic::type::Name, volatile int&, 
    std::string>("volatile int&"));
TestRegister t1_2_4(new TestName<basic::type::Name, const volatile int&, 
    std::string>("const volatile int&"));

__DEFINE_NAME_(int&&);
__DEFINE_NAME_(const int&&);
__DEFINE_NAME_(volatile int&&);
__DEFINE_NAME_(const volatile int&&);

TestRegister t1_3_1(new TestName<basic::type::Name, int&&, 
    std::string>("int&&"));
TestRegister t1_3_2(new TestName<basic::type::Name, const int&&, 
    std::string>("const int&&"));
TestRegister t1_3_3(new TestName<basic::type::Name, volatile int&&, 
    std::string>("volatile int&&"));
TestRegister t1_3_4(new TestName<basic::type::Name, const volatile int&&,
    std::string>("const volatile int&&"));

__DEFINE_NAME_(int*);
__DEFINE_NAME_(const int*);
__DEFINE_NAME_(volatile int*);
__DEFINE_NAME_(const volatile int*);
__DEFINE_NAME_(int*const);
__DEFINE_NAME_(int*volatile);
__DEFINE_NAME_(int*const volatile);

TestRegister t1_4_1(new TestName<basic::type::Name, int*, 
    std::string>("int*"));
TestRegister t1_4_2(new TestName<basic::type::Name, const int*, 
    std::string>("const int*"));
TestRegister t1_4_3(new TestName<basic::type::Name, volatile int*, 
    std::string>("volatile int*"));
TestRegister t1_4_4(new TestName<basic::type::Name, const volatile int*, 
    std::string>("const volatile int*"));
TestRegister t1_4_5(new TestName<basic::type::Name, int*const, 
    std::string>("int*const"));
TestRegister t1_4_6(new TestName<basic::type::Name, int*volatile,
    std::string>("int*volatile"));
TestRegister t1_4_7(new TestName<basic::type::Name, int*const volatile, 
    std::string>("int*const volatile"));

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

TestRegister t1_5_1(new TestName<basic::type::Name, int**, 
    std::string>("int**"));
TestRegister t1_5_2(new TestName<basic::type::Name, const int**, 
    std::string>("const int**"));
TestRegister t1_5_3(new TestName<basic::type::Name, volatile int**, 
    std::string>("volatile int**"));
TestRegister t1_5_4(new TestName<basic::type::Name, const volatile int**,
    std::string>("const volatile int**"));
TestRegister t1_5_5(new TestName<basic::type::Name, int**const,
    std::string>("int**const"));
TestRegister t1_5_6(new TestName<basic::type::Name, int**volatile,
    std::string>("int**volatile"));
TestRegister t1_5_7(new TestName<basic::type::Name, int**const volatile,
    std::string>("int**const volatile"));
TestRegister t1_5_8(new TestName<basic::type::Name, int*const*, 
    std::string>("int*const*"));
TestRegister t1_5_9(new TestName<basic::type::Name, int*const*const, 
    std::string>("int*const*const"));
TestRegister t1_5_10(new TestName<basic::type::Name, int*const*volatile, 
    std::string>("int*const*volatile"));
TestRegister t1_5_11(new TestName<basic::type::Name, int*const*const volatile,
    std::string>("int*const*const volatile"));
TestRegister t1_5_12(new TestName<basic::type::Name, int*volatile*, 
    std::string>("int*volatile*"));
TestRegister t1_5_13(new TestName<basic::type::Name, int*volatile*const, 
    std::string>("int*volatile*const"));
TestRegister t1_5_14(new TestName<basic::type::Name, int*volatile*volatile,
    std::string>("int*volatile*volatile"));
TestRegister t1_5_15(new TestName<basic::type::Name, 
    int*volatile*const volatile, std::string>("int*volatile*const volatile"));
TestRegister t1_5_16(new TestName<basic::type::Name, int*const volatile*, 
    std::string>("int*const volatile*"));
TestRegister t1_5_17(new TestName<basic::type::Name, int*const volatile*const, 
    std::string>("int*const volatile*const"));
TestRegister t1_5_18(new TestName<basic::type::Name, 
    int*const volatile*volatile, std::string>("int*const volatile*volatile"));
TestRegister t1_5_19(new TestName<basic::type::Name, 
    int*const volatile*const volatile, std::string>(
        "int*const volatile*const volatile"));

__DEFINE_NAME_(int[]);
__DEFINE_NAME_(const int[]);
__DEFINE_NAME_(volatile int[]);
__DEFINE_NAME_(const volatile int[]);

TestRegister t1_6_1(new TestName<basic::type::Name, int[], 
    std::string>("int[]"));
TestRegister t1_6_2(new TestName<basic::type::Name, const int[],
    std::string>("const int[]"));
TestRegister t1_6_3(new TestName<basic::type::Name, volatile int[],
    std::string>("volatile int[]"));
TestRegister t1_6_4(new TestName<basic::type::Name, const volatile int[], 
    std::string>("const volatile int[]"));

__DEFINE_NAME_(int(&)[]);
__DEFINE_NAME_(const int(&)[]);
__DEFINE_NAME_(volatile int(&)[]);
__DEFINE_NAME_(const volatile int(&)[]);

TestRegister t1_7_1(new TestName<basic::type::Name, int(&)[],
    std::string>("int(&)[]"));
TestRegister t1_7_2(new TestName<basic::type::Name, const int(&)[], 
    std::string>("const int(&)[]"));
TestRegister t1_7_3(new TestName<basic::type::Name, volatile int(&)[], 
    std::string>("volatile int(&)[]"));
TestRegister t1_7_4(new TestName<basic::type::Name, const volatile int(&)[],
    std::string>("const volatile int(&)[]"));

__DEFINE_NAME_(int(&&)[]);
__DEFINE_NAME_(const int(&&)[]);
__DEFINE_NAME_(volatile int(&&)[]);
__DEFINE_NAME_(const volatile int(&&)[]);

TestRegister t1_8_1(new TestName<basic::type::Name, int(&&)[], 
    std::string>("int(&&)[]"));
TestRegister t1_8_2(new TestName<basic::type::Name, const int(&&)[],
    std::string>("const int(&&)[]"));
TestRegister t1_8_3(new TestName<basic::type::Name, volatile int(&&)[], 
    std::string>("volatile int(&&)[]"));
TestRegister t1_8_4(new TestName<basic::type::Name, const volatile int(&&)[],
    std::string>("const volatile int(&&)[]"));

__DEFINE_NAME_(int(*)[]);
__DEFINE_NAME_(const int(*)[]);
__DEFINE_NAME_(volatile int(*)[]);
__DEFINE_NAME_(const volatile int(*)[]);
__DEFINE_NAME_(int(*const)[]);
__DEFINE_NAME_(int(*volatile)[]);
__DEFINE_NAME_(int(*const volatile)[]);

TestRegister t1_9_1(new TestName<basic::type::Name, int(*)[],
    std::string>("int(*)[]"));
TestRegister t1_9_2(new TestName<basic::type::Name, const int(*)[],
    std::string>("const int(*)[]"));
TestRegister t1_9_3(new TestName<basic::type::Name, volatile int(*)[],
    std::string>("volatile int(*)[]"));
TestRegister t1_9_4(new TestName<basic::type::Name, const volatile int(*)[], 
    std::string>("const volatile int(*)[]"));
TestRegister t1_9_5(new TestName<basic::type::Name, int(*const)[],
    std::string>("int(*const)[]"));
TestRegister t1_9_6(new TestName<basic::type::Name, int(*volatile)[], 
    std::string>("int(*volatile)[]"));
TestRegister t1_9_7(new TestName<basic::type::Name, int(*const volatile)[], 
    std::string>("int(*const volatile)[]"));

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

TestRegister t1_10_1(new TestName<basic::type::Name, int(**)[],
    std::string>("int(**)[]"));
TestRegister t1_10_2(new TestName<basic::type::Name, const int(**)[], 
    std::string>("const int(**)[]"));
TestRegister t1_10_3(new TestName<basic::type::Name, volatile int(**)[], 
    std::string>("volatile int(**)[]"));
TestRegister t1_10_4(new TestName<basic::type::Name, const volatile int(**)[],
    std::string>("const volatile int(**)[]"));
TestRegister t1_10_5(new TestName<basic::type::Name, int(**const)[],
    std::string>("int(**const)[]"));
TestRegister t1_10_6(new TestName<basic::type::Name, int(**volatile)[],
    std::string>("int(**volatile)[]"));
TestRegister t1_10_7(new TestName<basic::type::Name, int(**const volatile)[],
    std::string>("int(**const volatile)[]"));
TestRegister t1_10_8(new TestName<basic::type::Name, int(*const*)[], 
    std::string>("int(*const*)[]"));
TestRegister t1_10_9(new TestName<basic::type::Name, int(*const*const)[],
    std::string>("int(*const*const)[]"));
TestRegister t1_10_10(new TestName<basic::type::Name, int(*const*volatile)[],
    std::string>("int(*const*volatile)[]"));
TestRegister t1_10_11(new TestName<basic::type::Name, int(*const*const volatile)[], 
    std::string>("int(*const*const volatile)[]"));
TestRegister t1_10_12(new TestName<basic::type::Name, int(*volatile*)[], 
    std::string>("int(*volatile*)[]"));
TestRegister t1_10_13(new TestName<basic::type::Name, int(*volatile*const)[], 
    std::string>("int(*volatile*const)[]"));
TestRegister t1_10_14(new TestName<basic::type::Name, int(*volatile*volatile)[], 
    std::string>("int(*volatile*volatile)[]"));
TestRegister t1_10_15(new TestName<basic::type::Name, int(*volatile*const volatile)[], 
    std::string>("int(*volatile*const volatile)[]"));
TestRegister t1_10_16(new TestName<basic::type::Name, int(*const volatile*)[], 
    std::string>("int(*const volatile*)[]"));
TestRegister t1_10_17(new TestName<basic::type::Name, int(*const volatile*const)[],
    std::string>("int(*const volatile*const)[]"));
TestRegister t1_10_18(new TestName<basic::type::Name, int(*const volatile*volatile)[],
    std::string>("int(*const volatile*volatile)[]"));
TestRegister t1_10_19(new TestName<basic::type::Name, 
    int(*const volatile*const volatile)[], std::string>(
        "int(*const volatile*const volatile)[]" ));

__DEFINE_NAME_(int[1]);
__DEFINE_NAME_(const int[1]);
__DEFINE_NAME_(volatile int[1]);
__DEFINE_NAME_(const volatile int[1]);

TestRegister t1_11_1(new TestName<basic::type::Name, int[1],
    std::string>("int[1]"));
TestRegister t1_11_2(new TestName<basic::type::Name, const int[1], 
    std::string>("const int[1]"));
TestRegister t1_11_3(new TestName<basic::type::Name, volatile int[1],
    std::string>("volatile int[1]"));
TestRegister t1_11_4(new TestName<basic::type::Name, const volatile int[1],
    std::string>("const volatile int[1]"));

__DEFINE_NAME_(int(&)[1]);
__DEFINE_NAME_(const int(&)[1]);
__DEFINE_NAME_(volatile int(&)[1]);
__DEFINE_NAME_(const volatile int(&)[1]);

TestRegister t1_12_1(new TestName<basic::type::Name, int(&)[1],
    std::string>("int(&)[1]"));
TestRegister t1_12_2(new TestName<basic::type::Name, const int(&)[1],
    std::string>("const int(&)[1]"));
TestRegister t1_12_3(new TestName<basic::type::Name, volatile int(&)[1],
    std::string>("volatile int(&)[1]"));
TestRegister t1_12_4(new TestName<basic::type::Name, const volatile int(&)[1],
    std::string>("const volatile int(&)[1]"));

__DEFINE_NAME_(int(&&)[1]);
__DEFINE_NAME_(const int(&&)[1]);
__DEFINE_NAME_(volatile int(&&)[1]);
__DEFINE_NAME_(const volatile int(&&)[1]);

TestRegister t1_13_1(new TestName<basic::type::Name, int(&&)[1],
    std::string>("int(&&)[1]"));
TestRegister t1_13_2(new TestName<basic::type::Name, const int(&&)[1],
    std::string>("const int(&&)[1]"));
TestRegister t1_13_3(new TestName<basic::type::Name, volatile int(&&)[1],
    std::string>("volatile int(&&)[1]"));
TestRegister t1_13_4(new TestName<basic::type::Name, const volatile int(&&)[1], 
    std::string>("const volatile int(&&)[1]"));

__DEFINE_NAME_(int(*)[1]);
__DEFINE_NAME_(const int(*)[1]);
__DEFINE_NAME_(volatile int(*)[1]);
__DEFINE_NAME_(const volatile int(*)[1]);
__DEFINE_NAME_(int(*const)[1]);
__DEFINE_NAME_(int(*volatile)[1]);
__DEFINE_NAME_(int(*const volatile)[1]);

TestRegister t1_14_1(new TestName<basic::type::Name, int(*)[1],
    std::string>("int(*)[1]"));
TestRegister t1_14_2(new TestName<basic::type::Name, const int(*)[1],
    std::string>("const int(*)[1]"));
TestRegister t1_14_3(new TestName<basic::type::Name, volatile int(*)[1],
    std::string>("volatile int(*)[1]"));
TestRegister t1_14_4(new TestName<basic::type::Name, const volatile int(*)[1],
    std::string>("const volatile int(*)[1]"));
TestRegister t1_14_5(new TestName<basic::type::Name, int(*const)[1],
    std::string>("int(*const)[1]"));
TestRegister t1_14_6(new TestName<basic::type::Name, int(*volatile)[1],
    std::string>("int(*volatile)[1]"));
TestRegister t1_14_7(new TestName<basic::type::Name, int(*const volatile)[1],
    std::string>("int(*const volatile)[1]"));

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

TestRegister t1_15_1(new TestName<basic::type::Name, int(**)[1],
    std::string>("int(**)[1]"));
TestRegister t1_15_2(new TestName<basic::type::Name, const int(**)[1],
    std::string>("const int(**)[1]"));
TestRegister t1_15_3(new TestName<basic::type::Name, volatile int(**)[1],
    std::string>("volatile int(**)[1]"));
TestRegister t1_15_4(new TestName<basic::type::Name, const volatile int(**)[1], 
    std::string>("const volatile int(**)[1]"));
TestRegister t1_15_5(new TestName<basic::type::Name, int(**const)[1],
    std::string>("int(**const)[1]"));
TestRegister t1_15_6(new TestName<basic::type::Name, int(**volatile)[1], 
    std::string>("int(**volatile)[1]"));
TestRegister t1_15_7(new TestName<basic::type::Name, int(**const volatile)[1],
    std::string>("int(**const volatile)[1]"));
TestRegister t1_15_8(new TestName<basic::type::Name, int(*const*)[1],
    std::string>("int(*const*)[1]"));
TestRegister t1_15_9(new TestName<basic::type::Name, int(*const*const)[1],
    std::string>("int(*const*const)[1]"));
TestRegister t1_15_10(new TestName<basic::type::Name, int(*const*volatile)[1],
    std::string>("int(*const*volatile)[1]"));
TestRegister t1_15_11(new TestName<basic::type::Name, 
    int(*const*const volatile)[1], std::string>(
        "int(*const*const volatile)[1]"));
TestRegister t1_15_12(new TestName<basic::type::Name, int(*volatile*)[1],
    std::string>("int(*volatile*)[1]"));
TestRegister t1_15_13(new TestName<basic::type::Name, int(*volatile*const)[1], 
    std::string>("int(*volatile*const)[1]"));
TestRegister t1_15_14(new TestName<basic::type::Name, 
    int(*volatile*volatile)[1], std::string>("int(*volatile*volatile)[1]"));
TestRegister t1_15_15(new TestName<basic::type::Name, 
    int(*volatile*const volatile)[1], std::string>(
        "int(*volatile*const volatile)[1]"));
TestRegister t1_15_16(new TestName<basic::type::Name, int(*const volatile*)[1],
    std::string>("int(*const volatile*)[1]"));
TestRegister t1_15_17(new TestName<basic::type::Name, 
    int(*const volatile*const)[1], std::string>(
        "int(*const volatile*const)[1]"));
TestRegister t1_15_18(new TestName<basic::type::Name, 
    int(*const volatile*volatile)[1], std::string>(
        "int(*const volatile*volatile)[1]"));
TestRegister t1_15_19(new TestName<basic::type::Name, 
    int(*const volatile*const volatile)[1], 
        std::string>("int(*const volatile*const volatile)[1]"));

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

TestRegister t1_16_1(new TestName<basic::type::Name, int(),
    std::string>("int()"));
TestRegister t1_16_2(new TestName<basic::type::Name, int(char),
    std::string>("int(char)"));
TestRegister t1_16_3(new TestName<basic::type::Name, int(char, short),
    std::string>("int(char, short)"));
TestRegister t1_16_4(new TestName<basic::type::Name, 
    int(char, short, int, long), std::string>("int(char, short, int, long)"));
TestRegister t1_16_5(new TestName<basic::type::Name, const int(),
    std::string>("const int()"));
TestRegister t1_16_6(new TestName<basic::type::Name, volatile int(),
    std::string>("volatile int()"));
TestRegister t1_16_7(new TestName<basic::type::Name, const volatile int(),
    std::string>("const volatile int()"));
TestRegister t1_16_8(new TestName<basic::type::Name, int() const,
    std::string>("int() const"));
TestRegister t1_16_9(new TestName<basic::type::Name, int() volatile,
    std::string>("int() volatile"));
TestRegister t1_16_10(new TestName<basic::type::Name, int() const volatile,
    std::string>("int() const volatile"));
TestRegister t1_16_11(new TestName<basic::type::Name, int() &,
    std::string>("int() &"));
TestRegister t1_16_12(new TestName<basic::type::Name, int() const &,
    std::string>("int() const &"));
TestRegister t1_16_13(new TestName<basic::type::Name, int() volatile &,
    std::string>("int() volatile &"));
TestRegister t1_16_14(new TestName<basic::type::Name, int() const volatile &,
    std::string>("int() const volatile &"));
TestRegister t1_16_15(new TestName<basic::type::Name, int() &&,
    std::string>("int() &&"));
TestRegister t1_16_16(new TestName<basic::type::Name, int() const &&,
    std::string>("int() const &&"));
TestRegister t1_16_17(new TestName<basic::type::Name, int() volatile &&,
    std::string>("int() volatile &&"));
TestRegister t1_16_18(new TestName<basic::type::Name, int() const volatile &&,
    std::string>("int() const volatile &&"));

__DEFINE_NAME_(int(&)());
__DEFINE_NAME_(int(&)(char));
__DEFINE_NAME_(int(&)(char, short));
__DEFINE_NAME_(int(&)(char, short, int, long));
__DEFINE_NAME_(const int(&)());
__DEFINE_NAME_(volatile int(&)());
__DEFINE_NAME_(const volatile int(&)());

TestRegister t1_17_1(new TestName<basic::type::Name, int(&)(),
    std::string>("int(&)()"));
TestRegister t1_17_2(new TestName<basic::type::Name, int(&)(char), 
    std::string>("int(&)(char)"));
TestRegister t1_17_3(new TestName<basic::type::Name, int(&)(char, short),
    std::string>("int(&)(char, short)"));
TestRegister t1_17_4(new TestName<basic::type::Name, 
    int(&)(char, short, int, long), std::string>(
        "int(&)(char, short, int, long)"));
TestRegister t1_17_5(new TestName<basic::type::Name, const int(&)(),
    std::string>("const int(&)()"));
TestRegister t1_17_6(new TestName<basic::type::Name, volatile int(&)(),
    std::string>("volatile int(&)()"));
TestRegister t1_17_7(new TestName<basic::type::Name, const volatile int(&)(),
    std::string>("const volatile int(&)()"));

__DEFINE_NAME_(int(&&)());
__DEFINE_NAME_(int(&&)(char));
__DEFINE_NAME_(int(&&)(char, short));
__DEFINE_NAME_(int(&&)(char, short, int, long));
__DEFINE_NAME_(const int(&&)());
__DEFINE_NAME_(volatile int(&&)());
__DEFINE_NAME_(const volatile int(&&)());

TestRegister t1_18_1(new TestName<basic::type::Name, int(&&)(),
    std::string>("int(&&)()"));
TestRegister t1_18_2(new TestName<basic::type::Name, int(&&)(char),
    std::string>("int(&&)(char)"));
TestRegister t1_18_3(new TestName<basic::type::Name, int(&&)(char, short),
    std::string>("int(&&)(char, short)"));
TestRegister t1_18_4(new TestName<basic::type::Name,
    int(&&)(char, short, int, long), std::string>(
        "int(&&)(char, short, int, long)"));
TestRegister t1_18_5(new TestName<basic::type::Name, const int(&&)(),
    std::string>("const int(&&)()"));
TestRegister t1_18_6(new TestName<basic::type::Name, volatile int(&&)(),
    std::string>("volatile int(&&)()"));
TestRegister t1_18_7(new TestName<basic::type::Name, const volatile int(&&)(),
    std::string>("const volatile int(&&)()"));

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

TestRegister t1_19_1(new TestName<basic::type::Name, int(*)(),
    std::string>("int(*)()"));
TestRegister t1_19_2(new TestName<basic::type::Name, int(*)(char),
    std::string>("int(*)(char)"));
TestRegister t1_19_3(new TestName<basic::type::Name, int(*)(char, short),
    std::string>("int(*)(char, short)"));
TestRegister t1_19_4(new TestName<basic::type::Name, 
    int(*)(char, short, int, long), std::string>(
        "int(*)(char, short, int, long)"));
TestRegister t1_19_5(new TestName<basic::type::Name, const int(*)(), 
    std::string>("const int(*)()"));
TestRegister t1_19_6(new TestName<basic::type::Name, volatile int(*)(),
    std::string>("volatile int(*)()"));
TestRegister t1_19_7(new TestName<basic::type::Name, const volatile int(*)(),
    std::string>("const volatile int(*)()"));
TestRegister t1_19_8(new TestName<basic::type::Name, int(*const)(),
    std::string>("int(*const)()"));
TestRegister t1_19_9(new TestName<basic::type::Name, int(*volatile)(),
    std::string>("int(*volatile)()"));
TestRegister t1_19_10(new TestName<basic::type::Name, int(*const volatile)(),
    std::string>("int(*const volatile)()"));

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

TestRegister t1_20_1(new TestName<basic::type::Name, int(**)(),
    std::string>("int(**)()"));
TestRegister t1_20_2(new TestName<basic::type::Name, int(**)(char),
    std::string>("int(**)(char)"));
TestRegister t1_20_3(new TestName<basic::type::Name, int(**)(char, short),
    std::string>("int(**)(char, short)"));
TestRegister t1_20_4(new TestName<basic::type::Name, 
    int(**)(char, short, int, long), std::string>(
        "int(**)(char, short, int, long)"));
TestRegister t1_20_5(new TestName<basic::type::Name, const int(**)(),
    std::string>("const int(**)()"));
TestRegister t1_20_6(new TestName<basic::type::Name, volatile int(**)(),
    std::string>("volatile int(**)()"));
TestRegister t1_20_7(new TestName<basic::type::Name, const volatile int(**)(),
    std::string>("const volatile int(**)()"));
TestRegister t1_20_8(new TestName<basic::type::Name, int(**const)(), 
    std::string>("int(**const)()"));
TestRegister t1_20_9(new TestName<basic::type::Name, int(**volatile)(),
    std::string>("int(**volatile)()"));
TestRegister t1_20_10(new TestName<basic::type::Name, int(**const volatile)(),
    std::string>("int(**const volatile)()"));
TestRegister t1_20_11(new TestName<basic::type::Name, int(*const*)(),
    std::string>("int(*const*)()"));
TestRegister t1_20_12(new TestName<basic::type::Name, int(*const*const)(),
    std::string>("int(*const*const)()"));
TestRegister t1_20_13(new TestName<basic::type::Name, int(*const*volatile)(),
    std::string>("int(*const*volatile)()"));
TestRegister t1_20_14(new TestName<basic::type::Name, 
    int(*const*const volatile)(), std::string>(
        "int(*const*const volatile)()"));
TestRegister t1_20_15(new TestName<basic::type::Name, int(*volatile*)(),
    std::string>("int(*volatile*)()"));
TestRegister t1_20_16(new TestName<basic::type::Name, int(*volatile*const)(),
    std::string>("int(*volatile*const)()"));
TestRegister t1_20_17(new TestName<basic::type::Name, int(*volatile*volatile)(), 
    std::string>("int(*volatile*volatile)()"));
TestRegister t1_20_18(new TestName<basic::type::Name, 
    int(*volatile*const volatile)(), std::string>(
        "int(*volatile*const volatile)()"));
TestRegister t1_20_19(new TestName<basic::type::Name, int(*const volatile*)(),
    std::string>("int(*const volatile*)()"));
TestRegister t1_20_20(new TestName<basic::type::Name, 
    int(*const volatile*const)(), std::string>(
        "int(*const volatile*const)()"));
TestRegister t1_20_21(new TestName<basic::type::Name, 
    int(*const volatile*volatile)(), std::string>(
        "int(*const volatile*volatile)()"));
TestRegister t1_20_22(new TestName<basic::type::Name, 
    int(*const volatile*const volatile)(), std::string>(
        "int(*const volatile*const volatile)()"));

struct A
{};

namespace basic
{
namespace type
{
namespace name
{

template<>
struct Type<A>
{
    static void ToString(std::string& str, std::stack<std::string>& str_stack)
    {
        str += "A";
    }
};

}

}

}

__DEFINE_NAME_(int A::*);
__DEFINE_NAME_(const int A::*);
__DEFINE_NAME_(volatile int A::*);
__DEFINE_NAME_(const volatile int A::*);
__DEFINE_NAME_(int A::*const);
__DEFINE_NAME_(int A::*volatile);
__DEFINE_NAME_(int A::*const volatile);

TestRegister t1_21_1(new TestName<basic::type::Name, int A::*, 
    std::string>("int A::*"));
TestRegister t1_21_2(new TestName<basic::type::Name, const int A::*,
    std::string>("const int A::*"));
TestRegister t1_21_3(new TestName<basic::type::Name, volatile int A::*,
    std::string>("volatile int A::*"));
TestRegister t1_21_4(new TestName<basic::type::Name, const volatile int A::*,
    std::string>("const volatile int A::*"));
TestRegister t1_21_5(new TestName<basic::type::Name, int A::*const,
    std::string>("int A::*const"));
TestRegister t1_21_6(new TestName<basic::type::Name, int A::*volatile,
    std::string>("int A::*volatile"));
TestRegister t1_21_7(new TestName<basic::type::Name, int A::*const volatile,
    std::string>("int A::*const volatile"));

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

TestRegister t1_22_1(new TestName<basic::type::Name, int A::**,
    std::string>("int A::**"));
TestRegister t1_22_2(new TestName<basic::type::Name, const int A::**,
    std::string>("const int A::**"));
TestRegister t1_22_3(new TestName<basic::type::Name, volatile int A::**,
    std::string>("volatile int A::**"));
TestRegister t1_22_4(new TestName<basic::type::Name, const volatile int A::**,
    std::string>("const volatile int A::**"));
TestRegister t1_22_5(new TestName<basic::type::Name, int A::**const,
    std::string>("int A::**const"));
TestRegister t1_22_6(new TestName<basic::type::Name, int A::**volatile,
    std::string>("int A::**volatile"));
TestRegister t1_22_7(new TestName<basic::type::Name, int A::**const volatile,
    std::string>("int A::**const volatile"));
TestRegister t1_22_8(new TestName<basic::type::Name, int A::*const*,
    std::string>("int A::*const*"));
TestRegister t1_22_9(new TestName<basic::type::Name, int A::*const*const,
    std::string>("int A::*const*const"));
TestRegister t1_22_10(new TestName<basic::type::Name, int A::*const*volatile,
    std::string>("int A::*const*volatile"));
TestRegister t1_22_11(new TestName<basic::type::Name, 
    int A::*const*const volatile, std::string>(
        "int A::*const*const volatile"));
TestRegister t1_22_12(new TestName<basic::type::Name, int A::*volatile*,
    std::string>("int A::*volatile*"));
TestRegister t1_22_13(new TestName<basic::type::Name, int A::*volatile*const,
    std::string>("int A::*volatile*const"));
TestRegister t1_22_14(new TestName<basic::type::Name, 
    int A::*volatile*volatile, std::string>(
        "int A::*volatile*volatile"));
TestRegister t1_22_15(new TestName<basic::type::Name, 
    int A::*volatile*const volatile, std::string>(
        "int A::*volatile*const volatile"));
TestRegister t1_22_16(new TestName<basic::type::Name, int A::*const volatile*,
    std::string>("int A::*const volatile*"));
TestRegister t1_22_17(new TestName<basic::type::Name, 
    int A::*const volatile*const, std::string>(
        "int A::*const volatile*const"));
TestRegister t1_22_18(new TestName<basic::type::Name, 
    int A::*const volatile*volatile, std::string>(
        "int A::*const volatile*volatile"));
TestRegister t1_22_19(new TestName<basic::type::Name, 
    int A::*const volatile*const volatile, std::string>(
        "int A::*const volatile*const volatile"));

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

TestRegister t1_23_1(new TestName<basic::type::Name, int(A::*)(),
    std::string>("int(A::*)()"));
TestRegister t1_23_2(new TestName<basic::type::Name, int(A::*)(char),
    std::string>("int(A::*)(char)"));
TestRegister t1_23_3(new TestName<basic::type::Name, int(A::*)(char, short),
    std::string>("int(A::*)(char, short)"));
TestRegister t1_23_4(new TestName<basic::type::Name, 
    int(A::*)(char, short, int, long), std::string>(
        "int(A::*)(char, short, int, long)"));
TestRegister t1_23_5(new TestName<basic::type::Name, const int(A::*)(),
    std::string>("const int(A::*)()"));
TestRegister t1_23_6(new TestName<basic::type::Name, volatile int(A::*)(),
    std::string>("volatile int(A::*)()"));
TestRegister t1_23_7(new TestName<basic::type::Name, 
    const volatile int(A::*)(), std::string>("const volatile int(A::*)()"));
TestRegister t1_23_8(new TestName<basic::type::Name, int(A::*)() const, 
    std::string>("int(A::*)() const"));
TestRegister t1_23_9(new TestName<basic::type::Name, int(A::*)() volatile,
    std::string>("int(A::*)() volatile"));
TestRegister t1_23_10(new TestName<basic::type::Name, 
    int(A::*)() const volatile, std::string>(
        "int(A::*)() const volatile"));
TestRegister t1_23_11(new TestName<basic::type::Name, int(A::*)() &, 
    std::string>("int(A::*)() &"));
TestRegister t1_23_12(new TestName<basic::type::Name, int(A::*)() const &,
    std::string>("int(A::*)() const &"));
TestRegister t1_23_13(new TestName<basic::type::Name, int(A::*)() volatile &, 
    std::string>("int(A::*)() volatile &"));
TestRegister t1_23_14(new TestName<basic::type::Name, 
    int(A::*)() const volatile &, std::string>(
        "int(A::*)() const volatile &"));
TestRegister t1_23_15(new TestName<basic::type::Name, int(A::*)() &&,
    std::string>("int(A::*)() &&"));
TestRegister t1_23_16(new TestName<basic::type::Name, int(A::*)() const &&,
    std::string>("int(A::*)() const &&"));
TestRegister t1_23_17(new TestName<basic::type::Name, int(A::*)() volatile &&,
    std::string>("int(A::*)() volatile &&"));
TestRegister t1_23_18(new TestName<basic::type::Name, 
    int(A::*)() const volatile &&, std::string>(
        "int(A::*)() const volatile &&"));
TestRegister t1_23_19(new TestName<basic::type::Name, int(A::*const)(),
    std::string>("int(A::*const)()"));
TestRegister t1_23_20(new TestName<basic::type::Name, int(A::*volatile)(),
    std::string>("int(A::*volatile)()"));
TestRegister t1_23_21(new TestName<basic::type::Name, 
    int(A::*const volatile)(), std::string>(
        "int(A::*const volatile)()"));

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

TestRegister t1_24_1(new TestName<basic::type::Name, int(A::**)(),
    std::string>("int(A::**)()"));
TestRegister t1_24_2(new TestName<basic::type::Name, int(A::**)(char),
    std::string>("int(A::**)(char)"));
TestRegister t1_24_3(new TestName<basic::type::Name, int(A::**)(char, short), 
    std::string>("int(A::**)(char, short)"));
TestRegister t1_24_4(new TestName<basic::type::Name, 
    int(A::**)(char, short, int, long), std::string>(
        "int(A::**)(char, short, int, long)"));
TestRegister t1_24_5(new TestName<basic::type::Name, const int(A::**)(),
    std::string>("const int(A::**)()"));
TestRegister t1_24_6(new TestName<basic::type::Name, volatile int(A::**)(),
    std::string>("volatile int(A::**)()"));
TestRegister t1_24_7(new TestName<basic::type::Name, 
    const volatile int(A::**)(), std::string>("const volatile int(A::**)()"));
TestRegister t1_24_8(new TestName<basic::type::Name, int(A::**)() const,
    std::string>("int(A::**)() const"));
TestRegister t1_24_9(new TestName<basic::type::Name, int(A::**)() volatile,
    std::string>("int(A::**)() volatile"));
TestRegister t1_24_10(new TestName<basic::type::Name, 
    int(A::**)() const volatile, std::string>("int(A::**)() const volatile"));
TestRegister t1_24_11(new TestName<basic::type::Name, int(A::**)() &,
    std::string>("int(A::**)() &"));
TestRegister t1_24_12(new TestName<basic::type::Name, int(A::**)() const &,
    std::string>("int(A::**)() const &"));
TestRegister t1_24_13(new TestName<basic::type::Name, int(A::**)() volatile &,
    std::string>("int(A::**)() volatile &"));
TestRegister t1_24_14(new TestName<basic::type::Name, 
    int(A::**)() const volatile &, std::string>(
        "int(A::**)() const volatile &"));
TestRegister t1_24_15(new TestName<basic::type::Name, int(A::**)() &&,
    std::string>("int(A::**)() &&"));
TestRegister t1_24_16(new TestName<basic::type::Name, int(A::**)() const &&,
    std::string>("int(A::**)() const &&"));
TestRegister t1_24_17(new TestName<basic::type::Name, int(A::**)() volatile &&,
    std::string>("int(A::**)() volatile &&"));
TestRegister t1_24_18(new TestName<basic::type::Name, 
    int(A::**)() const volatile &&, std::string>(
        "int(A::**)() const volatile &&"));
TestRegister t1_24_19(new TestName<basic::type::Name, int(A::**const)(),
    std::string>("int(A::**const)()"));
TestRegister t1_24_20(new TestName<basic::type::Name, int(A::**volatile)(),
    std::string>("int(A::**volatile)()"));
TestRegister t1_24_21(new TestName<basic::type::Name, 
    int(A::**const volatile)(), std::string>("int(A::**const volatile)()"));
TestRegister t1_24_22(new TestName<basic::type::Name, int(A::*const*)(),
    std::string>("int(A::*const*)()"));
TestRegister t1_24_23(new TestName<basic::type::Name, int(A::*const*const)(),
    std::string>("int(A::*const*const)()"));
TestRegister t1_24_24(new TestName<basic::type::Name, 
    int(A::*const*volatile)(), std::string>("int(A::*const*volatile)()"));
TestRegister t1_24_25(new TestName<basic::type::Name, 
    int(A::*const*const volatile)(), std::string>(
        "int(A::*const*const volatile)()"));
TestRegister t1_24_26(new TestName<basic::type::Name, int(A::*volatile*)(),
    std::string>("int(A::*volatile*)()"));
TestRegister t1_24_27(new TestName<basic::type::Name, 
    int(A::*volatile*const)(), std::string>("int(A::*volatile*const)()"));
TestRegister t1_24_28(new TestName<basic::type::Name, 
    int(A::*volatile*volatile)(), std::string>(
        "int(A::*volatile*volatile)()"));
TestRegister t1_24_29(new TestName<basic::type::Name, 
    int(A::*volatile*const volatile)(), std::string>(
        "int(A::*volatile*const volatile)()"));
TestRegister t1_24_30(new TestName<basic::type::Name, 
    int(A::*const volatile*)(), std::string>("int(A::*const volatile*)()"));
TestRegister t1_24_31(new TestName<basic::type::Name, 
    int(A::*const volatile*const)(), std::string>(
        "int(A::*const volatile*const)()"));
TestRegister t1_24_32(new TestName<basic::type::Name, 
    int(A::*const volatile*volatile)(), std::string>(
        "int(A::*const volatile*volatile)()"));
TestRegister t1_24_33(new TestName<basic::type::Name, 
    int(A::*const volatile*const volatile)(), std::string>(
        "int(A::*const volatile*const volatile)()"));


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