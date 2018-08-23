#include "type/conditional/Switch.h"
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
    
template<typename Ts, typename Tt>
void TestAliasTypeAndTarget()
{
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::type and ";
    info_msg += Name<Tt>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Tt>::Value;
    if(Assert(error_msg.c_str(), 
        typeid(typename Ts::type).hash_code() ==
            typeid(Tt).hash_code()))
                Info("Pass\n");
}

template<typename Ts>
void TestAliasType()
{
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::type is not same with ";
    error_msg += Name<Ts>::Value;
    error_msg += "::Type";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::type and ";
    info_msg += Name<Ts>::Value;
    info_msg += "::Type : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Ts::type).hash_code() ==
            typeid(typename Ts::Type).hash_code()))
                Info("Pass\n");
}

template<typename Ts, typename Tt, Tt TtValue>
void TestIndexAndTarget()
{
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::index is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::index and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ts::index == TtValue))
            Info("Pass\n");
}

template<typename Ts>
void TestIndex()
{
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::index is not same with ";
    error_msg += Name<Ts>::Value;
    error_msg += "::Index";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::index is not same with ";
    info_msg += Name<Ts>::Value;
    info_msg += "::Index : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ts::index == Ts::Index))
            Info("Pass\n");
}

template<typename Ts, typename Tt, Tt TtValue>
void TestSizeAndTarget()
{
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::size is not same with ";
    error_msg += Name<ValueName<Tt, TtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::size and ";
    info_msg += Name<ValueName<Tt, TtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ts::size == TtValue))
            Info("Pass\n");
}

template<typename Ts>
void TestSize()
{
    std::string error_msg = Name<Ts>::Value;
    error_msg += "::size is not same with ";
    error_msg += Name<Ts>::Value;
    error_msg += "::Size";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Ts>::Value;
    info_msg += "::size is not same with ";
    info_msg += Name<Ts>::Value;
    info_msg += "::Size : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Ts::size == Ts::Size))
            Info("Pass\n");
}

template<typename Ts, typename Tt, typename Tti, Tti TtiValue, 
    typename Tts, Tts TtsValue>
struct TestSwitch : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Ts, Tt>();
        TestAliasType<Ts>();
        TestIndexAndTarget<Ts, Tti, TtiValue>();
        TestIndex<Ts>();
        TestSizeAndTarget<Ts, Tts, TtsValue>();
        TestSize<Ts>();
    }
};

__DEFINE_VALUE_NAME_("0", std::size_t, 0);
__DEFINE_VALUE_NAME_("1", std::size_t, 1);
__DEFINE_VALUE_NAME_("2", std::size_t, 2);
__DEFINE_VALUE_NAME_("3", std::size_t, 3);
__DEFINE_VALUE_NAME_("4", std::size_t, 4);

using Switch0_0_d_t = basic::type::conditional::Switch<std::false_type>;

__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type>);

TestRegister t1_0_0_d(new TestSwitch<Switch0_0_d_t, std::false_type, std::size_t, 0,
    std::size_t, 0>());

using Switch1_0_d_t = basic::type::conditional::Switch<std::false_type, 
    std::true_type>;

using Switch1_1_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type>;

__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::true_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type>);

TestRegister t2_1_0_d(new TestSwitch<Switch1_0_d_t, std::true_type, std::size_t, 0,
    std::size_t, 1>());
TestRegister t2_1_1_d(new TestSwitch<Switch1_1_d_t, std::false_type, std::size_t, 1,
    std::size_t, 1>());

using Switch2_0_d_t = basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type>;
using Switch2_1_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type>;  
using Switch2_2_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type>;

__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type>);

TestRegister t3_2_0_d(new TestSwitch<Switch2_0_d_t, std::true_type, std::size_t, 0,
    std::size_t, 2>());
TestRegister t3_2_1_d(new TestSwitch<Switch2_1_d_t, std::true_type, std::size_t, 1,
    std::size_t, 2>());
TestRegister t3_2_2_d(new TestSwitch<Switch2_2_d_t, std::false_type, std::size_t, 2,
    std::size_t, 2>());

using Switch4_0_d_t = basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>;
using Switch4_1_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>;  
using Switch4_2_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>; 
using Switch4_3_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>; 
using Switch4_4_d_t = basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>;    

__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::true_type, std::false_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::true_type, std::false_type, std::false_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::true_type, std::false_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::true_type>);
__DEFINE_NAME_(basic::type::conditional::Switch<std::false_type, 
    std::false_type, std::false_type, std::false_type, std::false_type>);

TestRegister t4_4_0_d(new TestSwitch<Switch4_0_d_t, std::true_type, std::size_t, 0,
    std::size_t, 4>());
TestRegister t4_4_1_d(new TestSwitch<Switch4_1_d_t, std::true_type, std::size_t, 1,
    std::size_t, 4>());
TestRegister t4_4_2_d(new TestSwitch<Switch4_2_d_t, std::true_type, std::size_t, 2,
    std::size_t, 4>());
TestRegister t4_4_3_d(new TestSwitch<Switch4_3_d_t, std::true_type, std::size_t, 3,
    std::size_t, 4>());
TestRegister t4_4_4_d(new TestSwitch<Switch4_4_d_t, std::false_type, std::size_t, 4,
    std::size_t, 4>());

struct A {};
struct B {};
struct C {};

using Switch3_1_t = basic::type::conditional::Switch<A, A, B, C>;
using Switch3_2_t = basic::type::conditional::Switch<B, A, B, C>;
using Switch3_3_t = basic::type::conditional::Switch<C, A, B, C>;
using Switch3_4_t = basic::type::conditional::Switch<A, B, C, A>;
using Switch3_5_t = basic::type::conditional::Switch<B, B, C, A>;
using Switch3_6_t = basic::type::conditional::Switch<C, B, C, A>;
using Switch3_7_t = basic::type::conditional::Switch<A, C, A, B>;
using Switch3_8_t = basic::type::conditional::Switch<B, C, A, B>;
using Switch3_9_t = basic::type::conditional::Switch<C, C, A, B>;

__DEFINE_NAME_(basic::type::conditional::Switch<A, A, B, C>);
__DEFINE_NAME_(basic::type::conditional::Switch<B, A, B, C>);
__DEFINE_NAME_(basic::type::conditional::Switch<C, A, B, C>);
__DEFINE_NAME_(basic::type::conditional::Switch<A, B, C, A>);
__DEFINE_NAME_(basic::type::conditional::Switch<B, B, C, A>);
__DEFINE_NAME_(basic::type::conditional::Switch<C, B, C, A>);
__DEFINE_NAME_(basic::type::conditional::Switch<A, C, A, B>);
__DEFINE_NAME_(basic::type::conditional::Switch<B, C, A, B>);
__DEFINE_NAME_(basic::type::conditional::Switch<C, C, A, B>);

TestRegister t5_3_1(new TestSwitch<Switch3_1_t, B, std::size_t, 1,
    std::size_t, 3>());
TestRegister t5_3_2(new TestSwitch<Switch3_2_t, A, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_3(new TestSwitch<Switch3_3_t, A, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_4(new TestSwitch<Switch3_4_t, B, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_5(new TestSwitch<Switch3_5_t, C, std::size_t, 1,
    std::size_t, 3>());
TestRegister t5_3_6(new TestSwitch<Switch3_6_t, B, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_7(new TestSwitch<Switch3_7_t, C, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_8(new TestSwitch<Switch3_8_t, C, std::size_t, 0,
    std::size_t, 3>());
TestRegister t5_3_9(new TestSwitch<Switch3_9_t, A, std::size_t, 1,
    std::size_t, 3>());

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
