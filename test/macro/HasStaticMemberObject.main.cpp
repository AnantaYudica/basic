#include "macro/HasStaticMemberObject.h"
#include "Test.h"

#include <vector>
#include <type_traits>
#include <typeinfo>

struct A
{
    static int Obj1;
};

int A::Obj1;

struct B
{};

template<typename>
struct C
{
    static int Obj2;
};

template<typename T>
int C<T>::Obj2;

template<>
struct C<std::false_type>
{};

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

bool BoolCompare(bool a, bool b)
{
    return a == b;
}

template<template<typename> class Thsmo, typename T,
    typename Tta>
void TestAliasTypeAndTarget()
{
    std::string error_msg = Name<Thsmo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Tta>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Tta>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thsmo<T>::value_type).hash_code() ==
            typeid(Tta).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thsmo, typename T>
void TestAliasType()
{
    std::string error_msg = Name<Thsmo<T>>::Value;
    error_msg += "::value_type is not same with ";
    error_msg += Name<Thsmo<T>>::Value;
    error_msg += "::ValueType";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::value_type and ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::ValueType : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        typeid(typename Thsmo<T>::value_type).hash_code() ==
            typeid(typename Thsmo<T>::ValueType).hash_code()))
                Info("Pass\n");
}

template<template<typename> class Thsmo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValueAndTargetValue()
{
    std::string error_msg = Name<Thsmo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<ValueName<Ttavt, TtavtValue>>::Value;
    info_msg += " : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(TtavtValue, Thsmo<T>::value)))
            Info("Pass\n");
}

template<template<typename> class Thsmo, typename T,
    typename Ttavt, bool(*Compare)(Ttavt a, Ttavt b)>
void TestValue()
{
    std::string error_msg = Name<Thsmo<T>>::Value;
    error_msg += "::value is not same with ";
    error_msg += Name<Thsmo<T>>::Value;
    error_msg += "::Value";
    std::string info_msg = "Test compare between ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::value and ";
    info_msg += Name<Thsmo<T>>::Value;
    info_msg += "::Value : ";
    Info(info_msg.c_str());
    if (Assert(error_msg.c_str(), 
        Compare(Thsmo<T>::value, Thsmo<T>::Value)))
            Info("Pass\n");
}

template<template<typename> class Thsmo, typename T,
    typename Ttavt, Ttavt TtavtValue, bool(*Compare)(Ttavt a, Ttavt b)>
struct TestHasStaticMmbrObj : BaseTest
{
    void Test() 
    {
        TestAliasTypeAndTarget<Thsmo, T, Ttavt>();
        TestAliasType<Thsmo, T>();
        TestValueAndTargetValue<Thsmo, T, Ttavt, TtavtValue, Compare>();
        TestValue<Thsmo, T, Ttavt, Compare>();
    };
};

/**
 *  template<typename T>
 *  constexpr auto _HasStaticMmbrObj1(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj1(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj1
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj1<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj1, _HasStaticMmbrObj1, T,, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasStaticMmbrObj1_t = HasStaticMmbrObj1<T>;

__DEFINE_NAME_(HasStaticMmbrObj1<A>);
__DEFINE_NAME_(HasStaticMmbrObj1<B>);

TestRegister t1(new TestHasStaticMmbrObj<HasStaticMmbrObj1_t, A, bool, true, 
    &BoolCompare>());
TestRegister t2(new TestHasStaticMmbrObj<HasStaticMmbrObj1_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T>
 *  constexpr auto _HasStaticMmbrObj2(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj2(...);
 *  template<typename T, typename T1>
 *  struct HasStaticMmbrObj2
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj2<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj2, _HasStaticMmbrObj2, T, TPL1, 
    T_NAME_,,,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasStaticMmbrObj2_t = HasStaticMmbrObj2<T, void>;

__DEFINE_NAME_(HasStaticMmbrObj2<A, void>);
__DEFINE_NAME_(HasStaticMmbrObj2<B, void>);

TestRegister t3(new TestHasStaticMmbrObj<HasStaticMmbrObj2_t, A, bool, true, 
    &BoolCompare>());
TestRegister t4(new TestHasStaticMmbrObj<HasStaticMmbrObj2_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T>
 *  constexpr auto _HasStaticMmbrObj3(T t) -> 
 *      decltype(t.Obj2, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj3(...);
 *  template<template<typename> class T, typename T1>
 *  struct HasStaticMmbrObj3
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj3<
 *          typename basic::type::trait::Simple<T<T1>>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj3<
 *          typename basic::type::trait::Simple<T<T1>>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_TMPL_PARAM_LIST_TPL2(\
    __T_NAME__)\
template<typename> class __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_T_NAME_TMPL_ARG_LIST_TNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj3, _HasStaticMmbrObj3, T, TPL2,
    T_NAME_TMPL_, TNTAL1,,,, PROTO_FUNC_T_NAME_,, Obj2);

template<typename T>
using HasStaticMmbrObj3_t = HasStaticMmbrObj3<C, T>;

__DEFINE_NAME_(HasStaticMmbrObj3<C, std::true_type>);
__DEFINE_NAME_(HasStaticMmbrObj3<C, std::false_type>);

TestRegister t5(new TestHasStaticMmbrObj<HasStaticMmbrObj3_t, std::true_type,
    bool, true, &BoolCompare>());
TestRegister t6(new TestHasStaticMmbrObj<HasStaticMmbrObj3_t, std::false_type,
    bool, false, &BoolCompare>());

/**
 *  template<typename T, typename T1 = void>
 *  constexpr auto _HasStaticMmbrObj4(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T>
 *  constexpr std::false _HasStaticMmbrObj4(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj4
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj4<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1 = void

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj4, _HasStaticMmbrObj4, T,,
    T_NAME_,, PFTTPL1,,, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasStaticMmbrObj4_t = HasStaticMmbrObj4<T>;

__DEFINE_NAME_(HasStaticMmbrObj4<A>);
__DEFINE_NAME_(HasStaticMmbrObj4<B>);

TestRegister t7(new TestHasStaticMmbrObj<HasStaticMmbrObj4_t, A, bool, true, 
    &BoolCompare>());
TestRegister t8(new TestHasStaticMmbrObj<HasStaticMmbrObj4_t, B , bool, false, 
    &BoolCompare>());

/**
 *  template<typename T, typename T1>
 *  constexpr auto _HasStaticMmbrObj5(int) -> 
 *      decltype(T::Obj1, std::true_type());
 *  template<typename T, typename T1>
 *  constexpr std::false _HasStaticMmbrObj5(...);
 *  template<typename T, typename T1>
 *  struct HasStaticMmbrObj5
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj5<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj5<
 *          typename basic::type::trait::Simple<T>::type, T1>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL2(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL1(\
    __T_NAME__)\
typename __T_NAME__, typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TMPL_ARG_LIST_PFTAL1(\
    __T_NAME__,\
    __T_NAME_SIMPLE_TYPE__)\
__T_NAME_SIMPLE_TYPE__, T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj5, _HasStaticMmbrObj5, T, TPL1,
    T_NAME_,, PFTTPL2, PFFTPL1, PFTAL1, PROTO_FUNC_T_NAME_,, Obj1);

template<typename T>
using HasStaticMmbrObj5_t = HasStaticMmbrObj5<T, void>;

__DEFINE_NAME_(HasStaticMmbrObj5<A, void>);
__DEFINE_NAME_(HasStaticMmbrObj5<B, void>);

TestRegister t9(new TestHasStaticMmbrObj<HasStaticMmbrObj5_t, A, bool, true,
    &BoolCompare>());
TestRegister t10(new TestHasStaticMmbrObj<HasStaticMmbrObj5_t, B, bool, false,
    &BoolCompare>());

/**
 *  template<typename T1, template<typename> class T = C>
 *  constexpr auto _HasStaticMmbrObj6(int) -> 
 *      decltype(T<T1>::Obj2, std::true_type());
 *  template<typename T1>
 *  constexpr std::false _HasStaticMmbrObj6(...);
 *  template<typename T>
 *  struct HasStaticMmbrObj6
 *  {
 *      typedef bool value_type;
 *      typedef bool ValueType;
 *      static constexpr value_type value = decltype(_HasStaticMmbrObj6<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *      static constexpr ValueType Value = decltype(_HasStaticMmbrObj6<
 *          typename basic::type::trait::Simple<T>::type>(0))::value;
 *  };
 * */

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_TRUE_TMPL_PARAM_LIST_PFTTPL3(\
    __T_NAME__)\
typename T1, template<typename> class __T_NAME__ = C

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_FALSE_TMPL_PARAM_LIST_PFFTPL2(\
    __T_NAME__)\
typename T1

#define __DEFINE_HAS_STATIC_MMBR_OBJ_PROTO_FUNC_T_NAME_TMPL_ARG_LIST_PFTNTAL1()\
T1

__DEFINE_HAS_STATIC_MMBR_OBJ_(HasStaticMmbrObj6, _HasStaticMmbrObj6, T,,
    T_NAME_,, PFTTPL3, PFFTPL2,, PROTO_FUNC_T_NAME_TMPL_, PFTNTAL1,
    Obj2);

template<typename T>
using HasStaticMmbrObj6_t = HasStaticMmbrObj6<T>;

__DEFINE_NAME_(HasStaticMmbrObj6<std::true_type>);
__DEFINE_NAME_(HasStaticMmbrObj6<std::false_type>);

TestRegister t11(new TestHasStaticMmbrObj<HasStaticMmbrObj6_t, std::true_type, 
    bool, true, &BoolCompare>());
TestRegister t12(new TestHasStaticMmbrObj<HasStaticMmbrObj6_t, std::false_type, 
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
