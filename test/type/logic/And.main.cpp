#include "type/logic/And.h"
#include "Test.h"

BasicTestConstruct;

#include <typeinfo>
#include <type_traits>
#include <string>
#include <vector>

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

__DEFINE_NAME_(std::true_type);
__DEFINE_NAME_(std::false_type);
__DEFINE_NAME_(void);

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

template<typename Ta, typename Tt, Tt TtValue>
void TestValueAndTarget()
{
    std::string error_msg = Name<Ta>::Value;
    error_msg += "::value is same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ta>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ta::value == TtValue))
            Info("Pass\n");
}

template<typename Ta>
void TestValue()
{
    std::string error_msg = Name<Ta>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Ta>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ta>::Value;
    info_msg += "::value and ";
    info_msg += Name<Ta>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ta::value == Ta::Value))
            Info("Pass\n");
}

template<typename Ta, typename Ttv, Ttv TtvValuee>
struct TestAnd : basic::test::Base
{
    void Test() 
    {
        TestValueAndTarget<Ta, Ttv, TtvValuee>();
        TestValue<Ta>();
    }
};

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);


using And1_1_d = basic::type::logic::And<std::true_type, std::false_type>;
using And1_2_d = basic::type::logic::And<std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::And<std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, std::true_type>);

RegisterTest(t1_1, new TestAnd<And1_1_d, bool, false>());
RegisterTest(t1_2, new TestAnd<And1_2_d, bool, true>());

using And2_1_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type>;
using And2_2_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type>;
using And2_3_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type>;
using And2_4_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type>);

RegisterTest(t2_1, new TestAnd<And2_1_d, bool, false>());
RegisterTest(t2_2, new TestAnd<And2_2_d, bool, false>());
RegisterTest(t2_3, new TestAnd<And2_3_d, bool, false>());
RegisterTest(t2_4, new TestAnd<And2_4_d, bool, true>());

using And4_1_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;
using And4_2_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>;
using And4_3_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>;
using And4_4_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>;
using And4_5_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;
using And4_6_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>;
using And4_7_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>;
using And4_8_d = basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>;
using And4_9_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using And4_10_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>;
using And4_11_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>;
using And4_12_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>;
using And4_13_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>;
using And4_14_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>;
using And4_15_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>;
using And4_16_d = basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::And<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>);

RegisterTest(t3_1, new TestAnd<And4_1_d, bool, false>());
RegisterTest(t3_2, new TestAnd<And4_2_d, bool, false>());
RegisterTest(t3_3, new TestAnd<And4_3_d, bool, false>());
RegisterTest(t3_4, new TestAnd<And4_4_d, bool, false>());
RegisterTest(t3_5, new TestAnd<And4_5_d, bool, false>());
RegisterTest(t3_6, new TestAnd<And4_6_d, bool, false>());
RegisterTest(t3_7, new TestAnd<And4_7_d, bool, false>());
RegisterTest(t3_8, new TestAnd<And4_8_d, bool, false>());
RegisterTest(t3_9, new TestAnd<And4_9_d, bool, false>());
RegisterTest(t3_10, new TestAnd<And4_10_d, bool, false>());
RegisterTest(t3_11, new TestAnd<And4_11_d, bool, false>());
RegisterTest(t3_12, new TestAnd<And4_12_d, bool, false>());
RegisterTest(t3_13, new TestAnd<And4_13_d, bool, false>());
RegisterTest(t3_14, new TestAnd<And4_14_d, bool, false>());
RegisterTest(t3_15, new TestAnd<And4_15_d, bool, false>());
RegisterTest(t3_16, new TestAnd<And4_16_d, bool, true>());

int main()
{
    return TestRun();
}
