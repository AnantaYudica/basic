#include "type/logic/Xor.h"
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
struct TestXor : BaseTest
{
    void Test() 
    {
        TestValueAndTarget<Ta, Ttv, TtvValuee>();
        TestValue<Ta>();
    }
};

__DEFINE_VALUE_NAME_("true", bool, true);
__DEFINE_VALUE_NAME_("false", bool, false);


using Xor1_1_d = basic::type::logic::Xor<std::true_type, std::false_type>;
using Xor1_2_d = basic::type::logic::Xor<std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, std::true_type>);

TestRegister t1_1(new TestXor<Xor1_1_d, bool, false>());
TestRegister t1_2(new TestXor<Xor1_2_d, bool, false>());

using Xor2_1_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type>;
using Xor2_2_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type>;
using Xor2_3_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type>;
using Xor2_4_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type>);

TestRegister t2_1(new TestXor<Xor2_1_d, bool, false>());
TestRegister t2_2(new TestXor<Xor2_2_d, bool, true>());
TestRegister t2_3(new TestXor<Xor2_3_d, bool, true>());
TestRegister t2_4(new TestXor<Xor2_4_d, bool, false>());

using Xor4_1_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;
using Xor4_2_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>;
using Xor4_3_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>;
using Xor4_4_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>;
using Xor4_5_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;
using Xor4_6_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>;
using Xor4_7_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>;
using Xor4_8_d = basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>;
using Xor4_9_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using Xor4_10_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>;
using Xor4_11_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>;
using Xor4_12_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>;
using Xor4_13_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>;
using Xor4_14_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>;
using Xor4_15_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>;
using Xor4_16_d = basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>;

__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::false_type, std::true_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::false_type, std::true_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::logic::Xor<std::true_type, 
    std::true_type, std::true_type, std::true_type, std::true_type>);

TestRegister t3_1(new TestXor<Xor4_1_d, bool, false>());
TestRegister t3_2(new TestXor<Xor4_2_d, bool, true>());
TestRegister t3_3(new TestXor<Xor4_3_d, bool, true>());
TestRegister t3_4(new TestXor<Xor4_4_d, bool, true>());
TestRegister t3_5(new TestXor<Xor4_5_d, bool, true>());
TestRegister t3_6(new TestXor<Xor4_6_d, bool, true>());
TestRegister t3_7(new TestXor<Xor4_7_d, bool, true>());
TestRegister t3_8(new TestXor<Xor4_8_d, bool, true>());
TestRegister t3_9(new TestXor<Xor4_9_d, bool, true>());
TestRegister t3_10(new TestXor<Xor4_10_d, bool, true>());
TestRegister t3_11(new TestXor<Xor4_11_d, bool, true>());
TestRegister t3_12(new TestXor<Xor4_12_d, bool, true>());
TestRegister t3_13(new TestXor<Xor4_13_d, bool, true>());
TestRegister t3_14(new TestXor<Xor4_14_d, bool, true>());
TestRegister t3_15(new TestXor<Xor4_15_d, bool, true>());
TestRegister t3_16(new TestXor<Xor4_16_d, bool, false>());

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
