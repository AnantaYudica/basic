#include "type/logic/Or.h"
#include "Test.h"

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
    error_msg += "::value is not same with ";
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
struct TestOr : BaseTest
{
    void Test() 
    {
        TestValueAndTarget<Ta, Ttv, TtvValuee>();
        TestValue<Ta>();
    }
};

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);


using Or1_1_d = basic::type::logic::Or<std::true_type, std::false_type>;
using Or1_2_d = basic::type::logic::Or<std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Or<std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, std::true_type>);

TestRegister t1_1(new TestOr<Or1_1_d, bool, false>());
TestRegister t1_2(new TestOr<Or1_2_d, bool, true>());

using Or2_1_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type>;
using Or2_2_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type>;
using Or2_3_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type>;
using Or2_4_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type>);

TestRegister t2_1(new TestOr<Or2_1_d, bool, false>());
TestRegister t2_2(new TestOr<Or2_2_d, bool, true>());
TestRegister t2_3(new TestOr<Or2_3_d, bool, true>());
TestRegister t2_4(new TestOr<Or2_4_d, bool, true>());

using Or4_1_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;
using Or4_2_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>;
using Or4_3_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>;
using Or4_4_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>;
using Or4_5_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;
using Or4_6_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>;
using Or4_7_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>;
using Or4_8_d = basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>;
using Or4_9_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using Or4_10_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>;
using Or4_11_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>;
using Or4_12_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>;
using Or4_13_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>;
using Or4_14_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>;
using Or4_15_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>;
using Or4_16_d = basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Or<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>);

TestRegister t3_1(new TestOr<Or4_1_d, bool, false>());
TestRegister t3_2(new TestOr<Or4_2_d, bool, true>());
TestRegister t3_3(new TestOr<Or4_3_d, bool, true>());
TestRegister t3_4(new TestOr<Or4_4_d, bool, true>());
TestRegister t3_5(new TestOr<Or4_5_d, bool, true>());
TestRegister t3_6(new TestOr<Or4_6_d, bool, true>());
TestRegister t3_7(new TestOr<Or4_7_d, bool, true>());
TestRegister t3_8(new TestOr<Or4_8_d, bool, true>());
TestRegister t3_9(new TestOr<Or4_9_d, bool, true>());
TestRegister t3_10(new TestOr<Or4_10_d, bool, true>());
TestRegister t3_11(new TestOr<Or4_11_d, bool, true>());
TestRegister t3_12(new TestOr<Or4_12_d, bool, true>());
TestRegister t3_13(new TestOr<Or4_13_d, bool, true>());
TestRegister t3_14(new TestOr<Or4_14_d, bool, true>());
TestRegister t3_15(new TestOr<Or4_15_d, bool, true>());
TestRegister t3_16(new TestOr<Or4_16_d, bool, true>());

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
